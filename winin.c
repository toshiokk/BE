/**************************************************************************
 *   winin.c                                                              *
 *                                                                        *
 *   Copyright (C) 1999-2003 Chris Allegretta                             *
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation; either version 2, or (at your option)  *
 *   any later version.                                                   *
 *                                                                        *
 *   This program is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 *   GNU General Public License for more details.                         *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program; if not, write to the Free Software          *
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.            *
 *                                                                        *
 **************************************************************************/

#include "headers.h"

PRIVATE int input_string_pos_(const char *default__, char *input_buf, int cursor_byte_idx,
 int hist_type_idx, const char *msg, va_list ap);
PRIVATE int input_string_pos__(const char *default__, char *input_buf, int cursor_byte_idx,
 int hist_type_idx, const char *msg);
PRIVATE void disp_input_box(const char *buf, const char *input_buf, int x);
PRIVATE void blank_input_box(void);

// input string
int input_string_pos(const char *default__, char *input_buf, int cursor_byte_idx,
 int hist_type_idx, const char *msg, ...)
{
	va_list ap;

	va_start(ap, msg);
	int ret = input_string_pos_(default__, input_buf, cursor_byte_idx, hist_type_idx, msg, ap);
	va_end(ap);
	return ret;
}

// return -1: recursively called
// return 0 : cancelled
// return 1 : input normally
PRIVATE int input_string_pos_(const char *default__, char *input_buf, int cursor_byte_idx,
 int hist_type_idx, const char *msg, va_list ap)
{
	static int recursively_called = 0;
	char dir_save[MAX_PATH_LEN + 1];
	char msg_buf[MAX_SCRN_LINE_BUF_LEN+1];
	int byte_idx;

	if (recursively_called >= 3) {
		return -1;				// -1: recursive called
	}

	vsnprintf(msg_buf, MAX_SCRN_LINE_BUF_LEN+1, msg, ap);
	byte_idx = byte_idx_from_col_idx(msg_buf, main_win_get_columns(), CHAR_LEFT, NULL);
	msg_buf[byte_idx] = '\0';		// limit message length

	update_screen_app(1, 1);

	get_full_path_of_cur_dir(dir_save);
	tio_set_cursor_on(1);
	recursively_called++;
	//--------------------------------------------------------------------------
	int ret = input_string_pos__(default__, input_buf, cursor_byte_idx, hist_type_idx, msg_buf);
	//--------------------------------------------------------------------------
	recursively_called--;
flf_d_printf("ret: %d\n", ret);
	tio_set_cursor_on(0);
	change_cur_dir(dir_save);

	update_screen_app(1, 1);

	if (ret <= EF_QUIT) {
		disp_status_bar_done(_("Cancelled"));
	}
#ifdef ENABLE_HISTORY
	if ((ret == EF_INPUT) || (ret == EF_INPUT_W_ALT)) {
		// input normally
		update_history(hist_type_idx, input_buf);
	}
#endif
	return ret;
}

// Input string. This should only be called from input_string_xxx().
PRIVATE int input_string_pos__(const char *default__, char *input_buf, int cursor_byte_idx,
 int hist_type_idx, const char *message)
{
	int key_input;
	int bytes;
#if defined(ENABLE_HISTORY) || defined(ENABLE_FILER)
	char buffer[MAX_PATH_LEN+1];
#endif
	char cut_buf[MAX_PATH_LEN+1] = "";
	int ret = EF_NONE;

	strlcpy__(input_buf, default__, MAX_PATH_LEN);
	cursor_byte_idx = MIN_MAX_(0, cursor_byte_idx, strlen_path(default__));

	blank_key_list_lines();
	// Main input loop
	for ( ; ; ) {
		ret = EF_NONE;
		update_screen_app(1, 0);
		disp_input_box(message, input_buf, cursor_byte_idx);
		//---------------------------
		key_input = input_key_wait_return();
		//---------------------------
		mflf_d_printf("input%ckey:0x%04x(%s)=======================================\n",
		 '_', (UINT16)key_input, short_key_name_from_key_code(key_input, NULL));

		const char *func_id;
		if (is_key_char(key_input)) {
			// character key
			if (strlen_path(input_buf) < MAX_PATH_LEN) {
				insert_str_chr(input_buf, MAX_PATH_LEN, cursor_byte_idx, key_input);
				cursor_byte_idx++;
			}
			func_id = "";
		} else {
			// function key
			func_id = get_func_id_from_key(key_input);
		}
		if ((key_input == K_ESC) || (key_input == K_M_ESC)
		 || cmp_func_id(func_id, "doe_close_file_ask")
		 || cmp_func_id(func_id, "doe_close_all_ask")) {
			strcpy__(input_buf, "");
			ret = EF_CANCELLED;		// cancelled, return
		} else
		if (key_input == K_ENTER) {
			ret = EF_INPUT;			// confirm a string input
		} else
		if (key_input == K_M_ENTER) {
			ret = EF_INPUT_W_ALT;			// confirm a string input
		} else
		if (cmp_func_id(func_id, "doe_left")) {
			// cursor left
			if (cursor_byte_idx > 0) {
				bytes = utf8c_prev_bytes(input_buf, &input_buf[cursor_byte_idx]);
				cursor_byte_idx -= bytes;
			}
		} else
		if (cmp_func_id(func_id, "doe_right")) {
			// cursor right
			if (cursor_byte_idx < strlen_path(input_buf)) {
				bytes = utf8c_bytes(&input_buf[cursor_byte_idx]);
				cursor_byte_idx += bytes;
			}
		} else
		if (cmp_func_id(func_id, "doe_start_of_line")
		 || cmp_func_id(func_id, "doe_prev_word")) {
			// goto line head
			cursor_byte_idx = 0;
		} else
		if (cmp_func_id(func_id, "doe_end_of_line")
		 || cmp_func_id(func_id, "doe_next_word")) {
			// goto line tail
			cursor_byte_idx = strlen_path(input_buf);
		} else
		if (cmp_func_id(func_id, "doe_backspace")
		 || (key_input == K_BS)) {
			// backspace
			if (cursor_byte_idx > 0) {
				bytes = utf8c_prev_bytes(input_buf, &input_buf[cursor_byte_idx]);
				cursor_byte_idx -= bytes;
				delete_str(input_buf, cursor_byte_idx, bytes);
			}
		} else
		if (cmp_func_id(func_id, "doe_delete_char")
		 || (key_input == K_DEL)) {
			// delete
			if (cursor_byte_idx < strlen_path(input_buf)) {
				bytes = utf8c_bytes(&input_buf[cursor_byte_idx]);
				delete_str(input_buf, cursor_byte_idx, bytes);
			}
		} else
		if (cmp_func_id(func_id, "doe_cut_to_head")) {
			// cut to line head
			strcut__(cut_buf, MAX_PATH_LEN, input_buf, 0, cursor_byte_idx);
			delete_str(input_buf, 0, cursor_byte_idx);
			cursor_byte_idx = 0;
		} else
		if (cmp_func_id(func_id, "doe_cut_text")) {
			// cut line
			strlcpy__(cut_buf, input_buf, MAX_PATH_LEN);
			strcpy__(input_buf, "");
			cursor_byte_idx = 0;
		} else
		if (cmp_func_id(func_id, "doe_cut_to_tail")) {
			// cut to line tail
			strcut__(cut_buf, MAX_PATH_LEN,
			 input_buf, cursor_byte_idx, strlen_path(input_buf));
			delete_str(input_buf, cursor_byte_idx,
			 strlen_path(input_buf) - cursor_byte_idx);
		} else
		if (cmp_func_id(func_id, "doe_copy_text")) {
			// copy to the cut buffer
			strlcpy__(cut_buf, input_buf, MAX_PATH_LEN);
		} else
		if (cmp_func_id(func_id, "doe_paste_text_with_pop")) {
			// paste from the cut buffer
			insert_str(input_buf, MAX_PATH_LEN, cursor_byte_idx, cut_buf, -1);
#ifdef ENABLE_HISTORY
		} else
		if (key_input == K_TAB) {
			// tab history completion
			strlcpy__(input_buf, get_history_completion(hist_type_idx, input_buf),
			 MAX_PATH_LEN);
			cursor_byte_idx = strlen_path(input_buf);
		} else
		if (cmp_func_id(func_id, "doe_up")
		 || cmp_func_id(func_id, "doe_page_up")
		 || cmp_func_id(func_id, "doe_first_line")) {
			//----------------------------------------------------
			ret = select_from_history_list(hist_type_idx, buffer);
			//----------------------------------------------------
flf_d_printf("do_call_editor ret: EF__%d, buffer: [%s]\n", ret, buffer);
			if ((ret == EF_INPUT_TO_REPLACE) || (ret == EF_INPUT_TO_APPEND)) {
				if ((ret == EF_INPUT_TO_REPLACE) || cmp_func_id(func_id, "doe_page_up")) {
					// clear input buffer
					strcpy__(input_buf, "");
					cursor_byte_idx = 0;
				} else {
					// insert string into buffer without clearing buffer
				}
				cursor_byte_idx = insert_str_separating_by_space(input_buf, MAX_PATH_LEN,
				 cursor_byte_idx, buffer);
			}
#endif // ENABLE_HISTORY
#ifdef ENABLE_FILER
		} else
		if (cmp_func_id(func_id, "doe_down")
		 || cmp_func_id(func_id, "doe_page_down")
		 || cmp_func_id(func_id, "doe_last_line")) {
			//---------------------------------------------------
			ret = do_call_filer(1, APP_MODE_CHOOSER, "", "", buffer, MAX_PATH_LEN);
			//---------------------------------------------------
flf_d_printf("do_call_filer ret: EF__%d, buffer: [%s]\n", ret, buffer);
			if ((ret == EF_INPUT_TO_REPLACE) || (ret == EF_INPUT_TO_APPEND)) {
				if ((ret == EF_INPUT_TO_REPLACE) || cmp_func_id(func_id, "doe_page_down")) {
					// clear input buffer
					strcpy__(input_buf, "");
					cursor_byte_idx = 0;
				} else {
					// insert string into buffer without clearing buffer
				}
				cursor_byte_idx = insert_str_separating_by_space(input_buf, MAX_PATH_LEN,
				 cursor_byte_idx, buffer);
			}
#endif // ENABLE_FILER
		} else
		if (cmp_func_id(func_id, "doe_search_backward_first")
		 || cmp_func_id(func_id, "doe_search_forward_first")
		 || cmp_func_id(func_id, "doe_replace")) {
			// get string from edit buffer's current cursor position
			if (edit_bufs_count_bufs()) {
				char *line = EPCBVC_CL->data;
				cursor_byte_idx = strlen_path(input_buf);
				int start_byte_idx = byte_idx_from_byte_idx(line, EPCBVC_CLBI + cursor_byte_idx);
				int byte_idx = start_byte_idx;
				if ((cmp_func_id(func_id, "doe_search_backward_first") && (SEARCH_DIR() > 0))
				 || (cmp_func_id(func_id, "doe_search_forward_first") && (SEARCH_DIR() < 0))) {
					// copy whole line
					byte_idx = byte_idx_from_byte_idx(line, MAX_PATH_LEN);
				} else {
					if (cursor_byte_idx == 0) {
						// copy one token
						for ( ; (byte_idx - start_byte_idx) < (MAX_PATH_LEN - MAX_UTF8C_BYTES); ) {
							if (is_char_id(line[byte_idx]) == 0) {
								break;
							}
							byte_idx++;
						}
					}
					if ((byte_idx - start_byte_idx) == 0) {
						// copy one character
						byte_idx += utf8c_bytes(&line[byte_idx]);
					}
				}
				strlncat__(input_buf, MAX_PATH_LEN, &line[start_byte_idx],
				 byte_idx - start_byte_idx);
				cursor_byte_idx = strlen_path(input_buf);
			}
		}
		// EF_QUIT: stay in this loop
		if ((ret == EF_CANCELLED) || (ret == EF_INPUT) || (ret == EF_INPUT_W_ALT)
		 || (ret == EF_LOADED) || (ret == EF_EXECUTED)) {
			break;
		}
	}
flf_d_printf("ret: EF__%d, input_buf: [%s]\n", ret, input_buf);
	return ret;		// return from input_string_pos__()
}

/* display input box
#Prompt message#######################################################
#input-string                                                        #
###UP:history##DOWN:browser###########################################
+Prompt message------------------------------------------------------+
|input-string                                                        |
+--------------------------------------------------------------------+
*/
PRIVATE void disp_input_box(const char *msg, const char *input_buf, int cursor_byte_idx)
{
	int cursor_col_idx = col_idx_from_byte_idx(input_buf, 0, cursor_byte_idx);
	int input_area_width;
	int start_byte_idx;
	int bytes;

	determine_input_line_y();
	blank_input_box();
	set_color_by_idx(ITEM_COLOR_IDX_MENU_FRAME, 0);
	main_win_output_string(get_input_line_y(), 1, msg, -1);
	main_win_output_string(get_input_line_y()+2, 1,
	 _("UP:history, DOWN:filer, PgUp:insert from history, PgDn:insert from filer"), -1);
	set_color_by_idx(ITEM_COLOR_IDX_INPUT, 0);

	input_area_width = main_win_get_columns()-2;
	if (cursor_col_idx < input_area_width) {
		bytes = byte_idx_from_col_idx(input_buf, input_area_width, CHAR_LEFT, NULL);
		main_win_output_string(get_input_line_y()+1, 1, input_buf, bytes);
		main_win_set_cursor_pos(get_input_line_y()+1, 1 + cursor_col_idx);
	} else {
#define TRUNCATION_MARK	"."
		//"abcdefghijklmnopqrstuvwxyz"
		// ==> |.ghijklmnopqrstuvwxyz |
		//                           ^cursor
		//
		//    "abcdefghijklmnopqrstuvwxyz"
		// ==> |.cdefghijklmnopqrstuvw|
		//                           ^cursor
		//
		//     "abcdefghijklmnopqrstuvwxyz"
		// ==> |abcdefghijklmnopqrstuv|
		//                           ^cursor
		start_byte_idx = byte_idx_from_col_idx(input_buf,
		 cursor_col_idx - (input_area_width-2), CHAR_RIGHT, NULL);
		bytes = byte_idx_from_col_idx(&input_buf[start_byte_idx],
		 input_area_width - utf8s_columns(TRUNCATION_MARK, MAX_SCRN_COLS), CHAR_LEFT, NULL);
		main_win_output_string(get_input_line_y()+1, 1, TRUNCATION_MARK, -1);
		main_win_output_string(-1, -1, &input_buf[start_byte_idx], bytes);
		main_win_set_cursor_pos(get_input_line_y()+1,
		 1 + utf8s_columns(TRUNCATION_MARK, MAX_SCRN_COLS)
		 + col_idx_from_byte_idx(&input_buf[start_byte_idx],
		 0, cursor_byte_idx - start_byte_idx));
	}
	tio_refresh();
}

PRIVATE void blank_input_box(void)
{
	// display frame
	set_color_by_idx(ITEM_COLOR_IDX_MENU_FRAME, 0);
	//+--------------------------------------------------------------------+
	//|                                                                    |
	//+--------------------------------------------------------------------+
	main_win_clear_lines(get_input_line_y(), get_input_line_y() + 3);
	// clear input area
	set_color_by_idx(ITEM_COLOR_IDX_INPUT, 0);
	//+--------------------------------------------------------------------+
	//|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
	//+--------------------------------------------------------------------+
	main_win_output_string(get_input_line_y()+1, 1, tio_blank_line(0), main_win_get_columns()-2);
}

//------------------------------------------------------------------------------

PRIVATE void list_one_key(char key, const char *desc);

// Ask a simple yes/no question on the status_bar.
int ask_yes_no(int flags, const char *msg, ...)
{
	int key_lines_save;
	va_list ap;
	char msg_buf[MAX_SCRN_LINE_BUF_LEN+1];
	const char *chars_yes = "Yy";				// Yes(replace)
	const char *chars_no = "Nn";				// No
	const char *chars_all = "Aa";				// All
	const char *chars_backward = "Bb";			// Backward search
	const char *chars_forward = "Ff ";			// Forward search
	const char *chars_cancel = "CcSs" S_ESC;	// Cancel/Stop/ESC
	const char *chars_end = "EeQqRr" S_C_Q;		// End/Quit/Return/Ctrl-Q
	const char *chars_undo = "Uu";				// Undo
	const char *chars_redo = "Oo";				// redO

	key_lines_save = GET_APPMD(app_KEY_LINES);		// save KEY_LINES
	SET_APPMD_VAL(app_KEY_LINES, LIM_MIN(1, key_lines_save));	// set lines more than 1

	blank_key_list_lines();
	// First, display key list
	if (get_key_list_lines()) {
		main_win_set_cursor_pos(get_yes_no_line_y(), 0);
		if (flags & ASK_YES) {
			list_one_key(chars_yes[0], _("Yes"));
		}
		if (flags & ASK_NO) {
			list_one_key(chars_no[0], _("No"));
		}
		if (flags & ASK_ALL) {
			list_one_key(chars_all[0], _("All"));
		}
		if (flags & ASK_BACKWARD) {
			list_one_key(chars_backward[0], _("Backward"));
		}
		if (flags & ASK_FORWARD) {
			list_one_key(chars_forward[0], _("Forward"));
		}
		list_one_key(chars_cancel[0], _("Cancel"));
		if (flags & ASK_END || flags & ASK_NO) {
			list_one_key(chars_end[0], _("End"));
		}
		if (flags & ASK_UNDO) {
			list_one_key(chars_undo[0], _("Undo"));
		}
		if (flags & ASK_REDO) {
			list_one_key(chars_redo[0], _("Redo"));
		}
	}

	// Second, display prompt message
	if (*msg) {
		va_start(ap, msg);
		vsnprintf(msg_buf, MAX_SCRN_LINE_BUF_LEN+1, msg, ap);
		va_end(ap);
		strlcat__(msg_buf, MAX_SCRN_LINE_BUF_LEN, " ");
		int byte_idx = byte_idx_from_col_idx(msg_buf, MAX_SCRN_LINE_BUF_LEN, CHAR_LEFT, NULL);
		msg_buf[byte_idx] = '\0';
		set_color_by_idx(ITEM_COLOR_IDX_STATUS, 0);
		set_color_by_idx(ITEM_COLOR_IDX_WARNING1, 0);
		blank_status_bar();
		main_win_output_string(get_status_line_y(), 0, msg_buf, -1);
	}

	tio_refresh();

	int answer;
	for (answer = ANSWER_NONE; answer == ANSWER_NONE; ) {
		// "Save modified buffer ?"[] <== cursor
		tio_set_cursor_on(1);
		//---------------------------
		key_code_t key_input = input_key_loop();
		const char *func_id = get_func_id_from_key(key_input);
		//---------------------------
		// Look for the key_input in yes/no/all
		if (strchr__(chars_yes, key_input) != NULL)
			answer = ANSWER_YES;
		else if (strchr__(chars_no, key_input) != NULL)
			answer = ANSWER_NO;
		else if ((flags & ASK_ALL) && (strchr__(chars_all, key_input) != NULL))
			answer = ANSWER_ALL;
		else if ((flags & ASK_BACKWARD)
		 && ((strchr__(chars_backward, key_input) != NULL)
		  || cmp_func_id(func_id, "doe_search_backward_next")))
			answer = ANSWER_BACKWARD;
		else if ((flags & ASK_FORWARD)
		 && ((strchr__(chars_forward, key_input) != NULL)
		  || cmp_func_id(func_id, "doe_search_forward_next")))
			answer = ANSWER_FORWARD;
		else if (strchr__(chars_cancel, key_input) != NULL)
			answer = ANSWER_CANCEL;
		else if ((flags & ASK_END || flags & ASK_NO) && (strchr__(chars_end, key_input) != NULL))
			answer = ANSWER_END;
		else if ((flags & ASK_UNDO) && (strchr__(chars_undo, key_input) != NULL))
			answer = ANSWER_UNDO;
		else if ((flags & ASK_REDO) && (strchr__(chars_redo, key_input) != NULL))
			answer = ANSWER_REDO;
	}

	// Then blank the status_bar.
	set_color_by_idx(ITEM_COLOR_IDX_STATUS, 0);
	blank_status_bar();
	disp_key_list_editor();

	SET_APPMD_VAL(app_KEY_LINES, key_lines_save);	// recover KEY_LINES
	update_screen_app(1, 1);

	return answer;	// x > 0: yes, x = 0: no, x < 0: cancel
}

PRIVATE void list_one_key(char key, const char *desc)
{
	char buf[MAX_SCRN_LINE_BUF_LEN+1];
	char key_name[MAX_KEY_NAME_LEN+1];		// "RIGHT"

	snprintf(buf, MAX_SCRN_LINE_BUF_LEN+1, "%s", short_key_name_from_key_code(key, key_name));
	set_color_by_idx(ITEM_COLOR_IDX_KEY_LIST, 0);
	main_win_output_string(-1, -1, buf, strnlen(buf, MAX_SCRN_LINE_BUF_LEN));
	set_color_by_idx(ITEM_COLOR_IDX_KEY_LIST2, 0);

	snprintf(buf, MAX_SCRN_LINE_BUF_LEN+1, "%s ", desc);
	main_win_output_string(-1, -1, buf, strnlen(buf, MAX_SCRN_LINE_BUF_LEN));
}

//------------------------------------------------------------------------------

void disp_fkey_list()
{
	key_code_t func_keys[] = { K_ESC,
	 K_SP, K_F01, K_F02, K_F03, K_F04,
	 K_SP, K_F05, K_F06, K_F07, K_F08,
	 K_SP, K_F09, K_F10, K_F11, K_F12, K_NONE };
	if (get_key_list_lines() > 0) {
		char buf[MAX_SCRN_LINE_BUF_LEN+1] = "";
		for (int key_idx = 0; func_keys[key_idx] != K_NONE; key_idx++) {
			if (func_keys[key_idx] == K_SP) {
				strcat_printf(buf, MAX_SCRN_LINE_BUF_LEN+1, " ");	// separator
			} else {
				func_key_list_t *fkey_list = get_fkey_entry_table_from_key(
				 NULL, func_keys[key_idx], -1);
				if (fkey_list) {
					strcat_printf(buf, MAX_SCRN_LINE_BUF_LEN+1, "{%s} ", fkey_list->desc);
				} else {
					strcat_printf(buf, MAX_SCRN_LINE_BUF_LEN+1, "{-----} ");
				}
			}
		}
/////flf_d_printf("buf: [%s]\n", buf);
		display_reverse_text(get_key_list_line_y() + 0, buf);
	}
}
void disp_key_list(const char *key_lists[])
{
	for (int line_idx = 1; line_idx < get_key_list_lines(); line_idx++) {
		display_reverse_text(get_key_list_line_y() + line_idx, key_lists[line_idx - 1]);
	}
}
// text parenthesized by {} or <> are displayed in reversed
// 1. type-1: "{Menu}  {RecKM} ..."
// 2. type-2: "<doe_first_line>TopOfFile ..."
void display_reverse_text(int yy, const char *text)
{
	const char *ptr;
	const char *begin;
	char buf[MAX_SCRN_LINE_BUF_LEN+1];
	int columns = 1;
	int xx;
	char delimiter = 0;

	set_color_by_idx(ITEM_COLOR_IDX_KEY_LIST2, 0);
	main_win_clear_lines(yy, -1);
	xx = 0;
	// get default fkey_list
	func_key_list_t *fkey_list = get_fkey_entry_table_from_key(NULL, K_ESC, 0);
	for (ptr = text; *ptr && xx < main_win_get_columns(); ) {
		if (*ptr == '{' || *ptr == '<' || *ptr == '}' || *ptr == '>')
			delimiter = *ptr++;
		for (begin = ptr; *ptr; ptr++) {
			if (*ptr == '{' || *ptr == '<' || *ptr == '}' || *ptr == '>')
				break;
		}
		if (ptr > begin) {
			strlcpy__(buf, begin, ptr - begin);
			if (delimiter == '<') {
				fkey_list = get_fkey_entry_from_func_id(buf);
				strlcpy__(buf, short_key_name_from_func_id(buf), MAX_SCRN_LINE_BUF_LEN);
			}
			if (delimiter == '{' || delimiter == '<') {
				set_color_by_idx(ITEM_COLOR_IDX_KEY_LIST, 0);
			}
			if (fkey_list && (is_fkey_entry_executable(fkey_list, -1) >= 2)) {
				columns = LIM_MAX(main_win_get_columns() - xx, utf8s_columns(buf, MAX_SCRN_COLS));
				truncate_tail_utf8s_columns(buf, columns);
				expand_utf8s_columns(buf, columns);
				main_win_output_string(yy, xx, buf, -1);
				xx += columns;
			}
			if (delimiter == '{' || delimiter == '<') {
				set_color_by_idx(ITEM_COLOR_IDX_KEY_LIST2, 0);
			}
		}
	}
}

// End of winin.c

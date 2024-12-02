/**************************************************************************
 *   keys.c                                                               *
 *                                                                        *
 *   Copyright (C) 1999-2003 Chris Allegretta                             *
 *   Copyright (C) 2010-2018 PCR                                          *
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

func_key_table_t *get_app_func_key_table(void)
{
#ifdef ENABLE_FILER
	if (GET_APPMD(app_EDITOR_FILER) == 0) {
#endif // ENABLE_FILER
		return editor_func_key_table;
#ifdef ENABLE_FILER
	} else {
		return filer_func_key_table;
	}
#endif // ENABLE_FILER
}

//-----------------------------------------------------------------------------
int cmp_func_id(const char *func_id_1, const char *func_id_2)
{
	return strcmp(func_id_1, func_id_2) == 0;
}
void *get_app_function_for_key(key_code_t key)
{
	func_key_table_t *fkey_table = get_func_key_table_from_key(get_app_func_key_table(), key);
	if (fkey_table) {
		return (void *)fkey_table->func;
	}
	return NULL;
}
const char *get_func_id_from_key(key_code_t key)
{
	func_key_table_t *fkey_table = get_func_key_table_from_key(editor_func_key_table, key);
	if (fkey_table) {
		return fkey_table->func_id;
	}
#ifdef ENABLE_FILER
	fkey_table = get_func_key_table_from_key(filer_func_key_table, key);
	if (fkey_table) {
		return fkey_table->func_id;
	}
#endif // ENABLE_FILER
	return "";
}
func_key_table_t *get_func_key_table_from_key(func_key_table_t *fkey_table, key_code_t key)
{
	for (int idx = 0; fkey_table[idx].help[0]; idx++) {
		if (is_key_assigned_to_func(key, &fkey_table[idx])) {
			return &fkey_table[idx];
		}
	}
	return NULL;
}
key_code_t get_key_for_func_id(char *func_id)
{
	func_key_table_t *fkey_table = get_func_table_from_func_id(func_id);
	if (fkey_table == NULL) {
		return K_NONE;
	}
	return fkey_table->key1;
}
PRIVATE func_key_table_t *get_func_table_from_func_id__(func_key_table_t *fkey_table,
 const char *func_id);
func_key_table_t *get_func_table_from_func_id(const char *func_id)
{
	func_key_table_t *fkey_table = get_func_table_from_func_id__(editor_func_key_table, func_id);
	if (fkey_table) {
		return fkey_table;
	}
#ifdef ENABLE_FILER
	fkey_table = get_func_table_from_func_id__(filer_func_key_table, func_id);
	if (fkey_table) {
		return fkey_table;
	}
#endif // ENABLE_FILER
	return NULL;
}
PRIVATE func_key_table_t *get_func_table_from_func_id__(func_key_table_t *fkey_table,
 const char *func_id)
{
	for (int idx = 0; fkey_table[idx].help[0]; idx++) {
		if (strcmp(fkey_table[idx].func_id, func_id) == 0) {
			return &fkey_table[idx];
		}
	}
	return NULL;
}

int is_key_assigned_to_func(key_code_t key, func_key_table_t *fkey_table)
{
	return key != KNA
	 && (key == fkey_table->key1
	  || key == fkey_table->key2
	  || key == fkey_table->key3);
}
void clear_keys_if_bound(key_code_t *keys)
{
	func_key_table_t *fkey_table = editor_func_key_table;
	for (int idx = 0; fkey_table[idx].func != NULL; idx++) {
		clear_key_if_bound_to_func(keys[0], &fkey_table[idx]);
		clear_key_if_bound_to_func(keys[1], &fkey_table[idx]);
	}
}
void clear_key_if_bound_to_func(key_code_t key, func_key_table_t *fkey_table)
{
	if (fkey_table->key1 == key) {
		fkey_table->key1 = KNA;
	}
	if (fkey_table->key2 == key) {
		fkey_table->key2 = KNA;
	}
	if (fkey_table->key3 == key) {
		fkey_table->key3 = KNA;
	}
}
void clear_keys_bound_to_func(func_key_table_t *fkey_table)
{
	fkey_table->key1 = KNA;
	fkey_table->key2 = KNA;
}

void bind_key_to_func(func_key_table_t *fkey_table, key_code_t *keys)
{
	if (keys[0] >= 0) {
		fkey_table->key1 = keys[0];
	}
	if (keys[1] >= 0) {
		fkey_table->key2 = keys[1];
	}
	if (keys[2] >= 0) {
		fkey_table->key3 = keys[2];
	}
}

// 0x01 ==> "^A"
const char *short_key_name_from_func_id(char *buf)
{
	return short_key_name_from_key_code(get_key_for_func_id(buf), buf);
}

//-----------------------------------------------------------------------------
PRIVATE key_code_t menu_key = -1;
void set_menu_key(key_code_t key)
{
flf_d_printf("set_menu_key(%04x)\n", key);
	menu_key = key;
}
key_code_t get_menu_key(void)
{
	key_code_t key = K_NONE;

	if (menu_key >= 0) {
		key = menu_key;
		menu_key = K_NONE;
flf_d_printf("get_menu_key(%04x)\n", key);
	}
	return key;
}

void set_menu_key_for_do_app_menu_0(void)
{
#ifndef ENABLE_FILER
	set_menu_key(get_key_for_func_id("doe_editor_menu_0"));
#else // ENABLE_FILER
	if (GET_APPMD(app_EDITOR_FILER) == 0) {
		set_menu_key(get_key_for_func_id("doe_editor_menu_0"));
	} else {
		set_menu_key(get_key_for_func_id("dof_filer_menu_0"));
	}
#endif // ENABLE_FILER
}

//-----------------------------------------------------------------------------
PRIVATE unsigned long msec_when_input_key = 0;
void update_msec_when_input_key()
{
	msec_when_input_key = get_msec();
}
unsigned long msec_past_input_key()
{
	return get_msec() - msec_when_input_key;
}

PRIVATE key_code_t input_key_timeout(void);
PRIVATE key_code_t input_key_check_break_key(void);
PRIVATE key_code_t map_key_code(key_code_t key);

key_code_t input_key_loop(void)
{
	key_code_t key;

	while ((key = input_key_wait_return()) < 0) {
	}
	return key;
}
// Key input interval:
// | type                  | duration [mSec] |
// |-----------------------|-----------------|
// | repaint all of screen | 10000           |
//
///PPP#define WHOLE_UPDATE_INTERVAL_MSEC		10000	// 10[Sec]
#define WHOLE_UPDATE_INTERVAL_MSEC		5000	// 10[Sec]
key_code_t input_key_wait_return(void)
{
	static key_code_t prev_key = KEY_NONE;
	key_code_t key = input_key_timeout();
	if (key < 0 && prev_key >= 0) {
		tio_repaint_all();
	}
	prev_key = key;
	if (key >= 0) {
		if (msec_past_input_key() >= WHOLE_UPDATE_INTERVAL_MSEC) {
			tio_flash_screen(10);
		}
		update_msec_when_input_key();
	}
	return key;
}

// Display update durations:
// | type                              | duration [mSec] |
// |-----------------------------------|-----------------|
// | current time update in title bar  | 1000            |
// | file list update                  | 1000            |
// | recording key macro               |  200            |
// | splash screen by key              | infinite        |
//
#define DEFAULT_KEY_WAIT_MSEC		1000	// return every 1[Sec]
#define KEY_MACRO_KEY_WAIT_MSEC		200		// fast title bar blinking
PRIVATE key_code_t input_key_timeout(void)
{
	long key_wait_time_msec = DEFAULT_KEY_WAIT_MSEC;
	if (key_macro_is_recording()) {
		key_wait_time_msec = KEY_MACRO_KEY_WAIT_MSEC;
	}
	long msec_enter = get_msec();
	key_code_t key;
	while ((key = input_key_macro()) < 0) {
		if (tio_check_update_terminal_size()) {
			win_reinit_win_size();
			disp_status_bar_done(_("Screen resized to (%d, %d)"),
			 tio_get_columns(), tio_get_lines());
			update_screen_app(1, 1);
			break;		// return after "Screen resizing"
		}
		if ((long)(get_msec() - msec_enter) >= key_wait_time_msec) {
			break;
		}
		MSLEEP(10);		// wait 10[mS]
	}
	return key;
}

key_code_t input_key_macro(void)
{
	key_code_t key = K_NONE;

	if (IS_KEY_VALID(key = get_menu_key())) {
		return key;
	}
#ifndef ENABLE_HISTORY
	key = input_key_check_break_key();
#else
	key = key_macro_get_key();
	if (key < 0) {
		key = input_key_check_break_key();
	}
	key_macro_put_key(key);
#endif // ENABLE_HISTORY
	return key;
}

// Record key strokes pushed while loading large or many files
// and Restore it after finished loading files.
PRIVATE int key_codes_saved = -1;			// >=0: saving,    -1: not recording
PRIVATE int key_codes_restored = -1;		// >=0: restoring, -1: not restoring
#define MAX_KEY_STROKES_CHECK_BREAK_KEY		40
PRIVATE key_code_t key_codes_check_break_key[MAX_KEY_STROKES_CHECK_BREAK_KEY+1];
PRIVATE int is_saving_check_break_key(void);
PRIVATE int is_restoring_check_break_key(void);

PRIVATE int is_saving_check_break_key(void)
{
	return (0 <= key_codes_saved && key_codes_saved < MAX_KEY_STROKES_CHECK_BREAK_KEY)
	 && (is_restoring_check_break_key() == 0);
}
PRIVATE int is_restoring_check_break_key(void)
{
	return (0 <= key_codes_restored && key_codes_restored < key_codes_saved);
}
void begin_check_break_key(void)
{
	key_codes_saved = 0;		// start saving
	key_codes_restored = -1;	// stop restoration
	clear_sigint_signaled();
}
void end_check_break_key(void)
{
	if (key_codes_saved > 0) {
		key_codes_restored = 0;		// start restoring
	} else {
		key_codes_saved = -1;		// clear saved keys
		key_codes_restored = -1;	// stop restoration
	}
}
int check_break_key(void)
{
	if (is_saving_check_break_key()) {
		if (input_key_check_break_key() == K_C_C) {	// Ctrl-C key is break key
			set_sigint_signaled();
flf_d_printf("sigint_signaled\n");
		}
	}
	return is_sigint_signaled();
}
PRIVATE key_code_t input_key_check_break_key(void)
{
	key_code_t key;

	if (is_restoring_check_break_key()) {
		// restoring key strokes
		key = key_codes_check_break_key[key_codes_restored];
		key_codes_restored++;
		if (key_codes_restored >= key_codes_saved) {
			key_codes_saved = -1;		// clear saved keys
			key_codes_restored = -1;	// stop restoration
		}
flf_d_printf("<[%04x]\n", key);
		return key;
	}
	key = tio_input_key();
	key = map_key_code(key);
	if (is_saving_check_break_key()) {
		// saving key strokes
		if (key >= 0) {
			key_codes_check_break_key[key_codes_saved] = key;
			key_codes_saved++;
flf_d_printf(">[%04x]\n", key);
		}
	}
	return key;
}

PRIVATE key_code_t map_key_code(key_code_t key)
{
	switch (key) {
	case CHAR_DEL:
#define MAP_KEY_7F_BS
#ifdef MAP_KEY_7F_BS
		if (GET_APPMD(app_MAP_KEY_7F_BS)) {
flf_d_printf("KEY_7F ==> BS\n");
			key = K_BS;		// CHAR_DEL ==> BS
		} else {
#endif // MAP_KEY_7F_BS
flf_d_printf("KEY_7F ==> DEL\n");
			key = K_DEL;	// CHAR_DEL ==> Delete
#ifdef MAP_KEY_7F_BS
		}
#endif // MAP_KEY_7F_BS
		break;
	case KEY_BACKSPACE:		// 0x0107
#ifdef MAP_KEY_7F_BS
		if (GET_APPMD(app_MAP_KEY_7F_BS) == 0) {
flf_d_printf("KEY_BACKSPACE ==> BS\n");
			key = K_BS;		// KEY_BACKSPACE ==> BS
		} else {
#endif // MAP_KEY_7F_BS
flf_d_printf("KEY_BACKSPACE ==> DEL\n");
			key = K_DEL;	// KEY_BACKSPACE ==> DEL
#ifdef MAP_KEY_7F_BS
		}
#endif // MAP_KEY_7F_BS
		break;
	case KEY_DC:
flf_d_printf("KEY_DC ==> DEL\n");
		// Delete(0x0113) key code was seen.
		SET_APPMD(app_MAP_KEY_7F_BS);	// set conversion of CHAR_DEL ==> BS
		key = K_DEL;
		break;
	case KEY_ENTER:		// 0x0157
		key = K_ENTER;
	default:
		break;
	}
	return key;
}

//-----------------------------------------------------------------------------
key_name_table_t key_name_table[] = {
//					   12345678
	{ ' '			, "SP", },
	{ K_BS			, "BS", },
	{ K_TAB			, "TAB", },
	{ K_ENTER		, "ENTER", },
	{ K_ESC			, "ESC", },
	{ K_C_AT		, "C-@", },
	{ K_C_A			, "C-A", },
	{ K_C_B			, "C-B", },
	{ K_C_C			, "C-C", },
	{ K_C_D			, "C-D", },
	{ K_C_E			, "C-E", },
	{ K_C_F			, "C-F", },
	{ K_C_G			, "C-G", },
	{ K_C_H			, "C-H", },
	{ K_C_J			, "C-J", },
	{ K_C_K			, "C-K", },
	{ K_C_L			, "C-L", },
	{ K_C_M			, "C-M", },
	{ K_C_N			, "C-N", },
	{ K_C_O			, "C-O", },
	{ K_C_P			, "C-P", },
	{ K_C_Q			, "C-Q", },
	{ K_C_R			, "C-R", },
	{ K_C_S			, "C-S", },
	{ K_C_T			, "C-T", },
	{ K_C_U			, "C-U", },
	{ K_C_V			, "C-V", },
	{ K_C_W			, "C-W", },
	{ K_C_X			, "C-X", },
	{ K_C_Y			, "C-Y", },
	{ K_C_Z			, "C-Z", },
	{ K_C_LBRAK		, "C-[", },
	{ K_C_BAKSL		, "C-\\", },
	{ K_C_RBRAK		, "C-]", },
	{ K_C_CARET		, "C-^", },
	{ K_C_UNDLN		, "C-_", },

	{ K_INS			, "INS", },
	{ K_DEL			, "DEL", },
	{ K_HOME		, "HOME", },
	{ K_END			, "END", },
	{ K_PPAGE		, "PGUP", },
	{ K_NPAGE		, "PGDN", },
	{ K_UP			, "UP", },
	{ K_DOWN		, "DOWN", },
	{ K_RIGHT		, "RIGHT", },
	{ K_LEFT		, "LEFT", },

	{ K_M_BS		, "M-BS", },
	{ K_M_TAB		, "M-TAB", },
	{ K_M_CR		, "M-CR", },
	{ K_M_ESC		, "M-ESC", },
	{ K_M_SP		, "M-SP", },
	{ K_M_EXCLA		, "M-EXCLA", },
	{ K_M_QUOTA		, "M-QUOTA", },
	{ K_M_SHARP		, "M-SHARP", },
	{ K_M_DOLLA		, "M-DOLLA", },
	{ K_M_PERCE		, "M-PERCE", },
	{ K_M_AMPSD		, "M-AMPSD", },
	{ K_M_APOST		, "M-APOST", },
	{ K_M_LPARE		, "M-LPARE", },
	{ K_M_RPARE		, "M-RPARE", },
	{ K_M_ASTER		, "M-ASTER", },
	{ K_M_PLUS		, "M-PLUS", },
	{ K_M_COMMA		, "M-COMMA", },
	{ K_M_HYPHE		, "M-HYPHE", },
	{ K_M_PERIO		, "M-PERIO", },
	{ K_M_SLASH		, "M-SLASH", },
	{ K_M_0			, "M-0", },
	{ K_M_1			, "M-1", },
	{ K_M_2			, "M-2", },
	{ K_M_3			, "M-3", },
	{ K_M_4			, "M-4", },
	{ K_M_5			, "M-5", },
	{ K_M_6			, "M-6", },
	{ K_M_7			, "M-7", },
	{ K_M_8			, "M-8", },
	{ K_M_9			, "M-9", },
	{ K_M_COLON		, "M-COLON", },
	{ K_M_SEMCO		, "M-SEMCO", },
	{ K_M_LESST		, "M-LESST", },
	{ K_M_EQUAL		, "M-EQUAL", },
	{ K_M_GREAT		, "M-GREAT", },
	{ K_M_QUEST		, "M-QUEST", },
	{ K_M_AT		, "M-AT", },
	{ K_M_A			, "M-A", },
	{ K_M_B			, "M-B", },
	{ K_M_C			, "M-C", },
	{ K_M_D			, "M-D", },
	{ K_M_E			, "M-E", },
	{ K_M_F			, "M-F", },
	{ K_M_G			, "M-G", },
	{ K_M_H			, "M-H", },
	{ K_M_I			, "M-I", },
	{ K_M_J			, "M-J", },
	{ K_M_K			, "M-K", },
	{ K_M_L			, "M-L", },
	{ K_M_M			, "M-M", },
	{ K_M_N			, "M-N", },
	{ K_M_O			, "M-O", },
	{ K_M_P			, "M-P", },
	{ K_M_Q			, "M-Q", },
	{ K_M_R			, "M-R", },
	{ K_M_S			, "M-S", },
	{ K_M_T			, "M-T", },
	{ K_M_U			, "M-U", },
	{ K_M_V			, "M-V", },
	{ K_M_W			, "M-W", },
	{ K_M_X			, "M-X", },
	{ K_M_Y			, "M-Y", },
	{ K_M_Z			, "M-Z", },

	{ K_M_LBRAK		, "M-LBRAK", },
	{ K_M_BAKSL		, "M-BAKSL", },
	{ K_M_RBRAK		, "M-RBRAK", },
	{ K_M_CARET		, "M-CARET", },
	{ K_M_UNDLN		, "M-UNDLN", },

	{ K_M_BAKQT		, "M-BACKQ", },
	{ K_M_a			, "M-a", },
	{ K_M_b			, "M-b", },
	{ K_M_c			, "M-c", },
	{ K_M_d			, "M-d", },
	{ K_M_e			, "M-e", },
	{ K_M_f			, "M-f", },
	{ K_M_g			, "M-g", },
	{ K_M_h			, "M-h", },
	{ K_M_i			, "M-i", },
	{ K_M_j			, "M-j", },
	{ K_M_k			, "M-k", },
	{ K_M_l			, "M-l", },
	{ K_M_m			, "M-m", },
	{ K_M_n			, "M-n", },
	{ K_M_o			, "M-o", },
	{ K_M_p			, "M-p", },
	{ K_M_q			, "M-q", },
	{ K_M_r			, "M-r", },
	{ K_M_s			, "M-s", },
	{ K_M_t			, "M-t", },
	{ K_M_u			, "M-u", },
	{ K_M_v			, "M-v", },
	{ K_M_w			, "M-w", },
	{ K_M_x			, "M-x", },
	{ K_M_y			, "M-y", },
	{ K_M_z			, "M-z", },

	{ K_M_LBRAC		, "M-LBRAC", },
	{ K_M_VERTB		, "M-VERTB", },
	{ K_M_RBRAC		, "M-RBRAC", },
	{ K_M_TILDE		, "M-TILDE", },
	{ K_M_DEL		, "M-DEL", },

	{ K_MC_A		, "MC-A", },
	{ K_MC_B		, "MC-B", },
	{ K_MC_C		, "MC-C", },
	{ K_MC_D		, "MC-D", },
	{ K_MC_E		, "MC-E", },
	{ K_MC_F		, "MC-F", },
	{ K_MC_G		, "MC-G", },
	{ K_MC_H		, "MC-H", },
	{ K_MC_I		, "MC-I", },
	{ K_MC_J		, "MC-J", },
	{ K_MC_K		, "MC-K", },
	{ K_MC_L		, "MC-L", },
	{ K_MC_M		, "MC-M", },
	{ K_MC_N		, "MC-N", },
	{ K_MC_O		, "MC-O", },
	{ K_MC_P		, "MC-P", },
	{ K_MC_Q		, "MC-Q", },
	{ K_MC_R		, "MC-R", },
	{ K_MC_S		, "MC-S", },
	{ K_MC_T		, "MC-T", },
	{ K_MC_U		, "MC-U", },
	{ K_MC_V		, "MC-V", },
	{ K_MC_W		, "MC-W", },
	{ K_MC_X		, "MC-X", },
	{ K_MC_Y		, "MC-Y", },
	{ K_MC_Z		, "MC-Z", },
	{ K_MC_LBRAK	, "MC-LBRAK", },
	{ K_MC_BAKSL	, "MC-BAKSL", },
	{ K_MC_RBRAK	, "MC-RBRAK", },
	{ K_MC_CARET	, "MC-CARET", },
	{ K_MC_UNDLN	, "MC-UNDLN", },

	{ K_F01			, "F01", },
	{ K_F02			, "F02", },
	{ K_F03			, "F03", },
	{ K_F04			, "F04", },
	{ K_F05			, "F05", },
	{ K_F06			, "F06", },
	{ K_F07			, "F07", },
	{ K_F08			, "F08", },
	{ K_F09			, "F09", },
	{ K_F10			, "F10", },
	{ K_F11			, "F11", },
	{ K_F12			, "F12", },
	{ K_S_F01		, "S-F01", },
	{ K_S_F02		, "S-F02", },
	{ K_S_F03		, "S-F03", },
	{ K_S_F04		, "S-F04", },
	{ K_S_F05		, "S-F05", },
	{ K_S_F06		, "S-F06", },
	{ K_S_F07		, "S-F07", },
	{ K_S_F08		, "S-F08", },
	{ K_S_F09		, "S-F09", },
	{ K_S_F10		, "S-F10", },
	{ K_S_F11		, "S-F11", },
	{ K_S_F12		, "S-F12", },
};

const char *short_key_name_from_key_code(key_code_t key_code, char *buf)
{
	static char buf_s_[MAX_KEY_NAME_LEN+1];
	if (buf == NULL) {
		buf = buf_s_;
	}
	char buf_key_name[MAX_KEY_NAME_LEN+1];		// "MC-RIGHT"
	return short_key_name_from_key_name(key_name_from_key_code(key_code, buf_key_name), buf);
}
const char *key_name_from_key_code(key_code_t key_code, char *buf)
{
	static char buf_s_[MAX_KEY_NAME_LEN+1];
	if (buf == NULL) {
		buf = buf_s_;
	}
	for (int idx = 0; idx < ARRAY_SIZE_OF(key_name_table); idx++) {
		if (key_name_table[idx].key_code == key_code)
			return key_name_table[idx].key_name;
	}
	if (isgraph(key_code)) {
		snprintf(buf, MAX_KEY_NAME_LEN+1, "%c", key_code);
	} else if ((key_code & 0xff00) == K_M(0)) {	// 0x1bxx
		if (isgraph(key_code & 0x00ff)) {
			snprintf(buf, MAX_KEY_NAME_LEN+1, "M-%c", key_code & 0x00ff);
		} else if (0 <= (key_code & 0x00ff) && (key_code & 0x00ff) < 0x20) {
			snprintf(buf, MAX_KEY_NAME_LEN+1, "MC-%c", '@' + (key_code & 0xff));
		} else {
			snprintf(buf, MAX_KEY_NAME_LEN+1, "%04x", key_code);
		}
	} else if (key_code == KEY_NONE) {
		snprintf(buf, MAX_KEY_NAME_LEN+1, "--------");
	} else {
		snprintf(buf, MAX_KEY_NAME_LEN+1, "%04x", key_code);
	}
	return buf;
}
const char *short_key_name_from_key_name(const char *key_name, char *buf)
{
	if (strlcmp__(key_name, "C-") == 0) {
		// "C-x" ==> "^x"
		snprintf(buf, MAX_KEY_NAME_LEN+1, "%s%s", "^", &key_name[2]);
	} else
	if (strlcmp__(key_name, "M-") == 0) {
		// "M-x" ==> "@x"
		snprintf(buf, MAX_KEY_NAME_LEN+1, "%s%s", "@", &key_name[2]);
	} else
	if (strlcmp__(key_name, "MC-") == 0) {
		// "MC-x" ==> "@^x"
		snprintf(buf, MAX_KEY_NAME_LEN+1, "%s%s", "@^", &key_name[3]);
	} else {
		strlcpy__(buf, key_name, MAX_KEY_NAME_LEN);
	}
	return buf;
}

key_code_t key_code_from_key_name(char *key_name)
{
	int idx;

	for (idx = 0; idx < ARRAY_SIZE_OF(key_name_table); idx++) {
		if (strcmp(key_name_table[idx].key_name, key_name) == 0)
			return key_name_table[idx].key_code;
	}
	return -1;
}
key_code_t key_code_from_short_key_name(char *short_key_name)
{
	int idx;
	char buf_key_name[MAX_KEY_NAME_LEN+1];		// "MC-RIGHT"

	for (idx = 0; idx < ARRAY_SIZE_OF(key_name_table); idx++) {
		if (strcmp(short_key_name_from_key_name(key_name_table[idx].key_name, buf_key_name),
		 short_key_name) == 0)
			return key_name_table[idx].key_code;
	}
	return -1;
}

int get_key_name_table_entries(void)
{
	return ARRAY_SIZE_OF(key_name_table);
}

//-----------------------------------------------------------------------------
#ifdef ENABLE_DEBUG

#ifdef START_UP_TEST

PRIVATE int check_multiple_assignment_of_key_(func_key_table_t *fkey_table);
int check_multiple_assignment_of_key()
{
flf_d_printf("-------------------------\n");
	int err = check_multiple_assignment_of_key_(editor_func_key_table);
#ifdef ENABLE_FILER
	err += check_multiple_assignment_of_key_(filer_func_key_table);
#endif // ENABLE_FILER
	return err;
}

PRIVATE int check_multiple_assignment_of_key_(func_key_table_t *fkey_table)
{
	for (int func_idx = 0; fkey_table[func_idx].help[0]; func_idx++) {
		for (int key_idx = 0; key_idx < MAX_KEYS_BOUND; key_idx++) {
			key_code_t key;
			switch (key_idx) {
			default:
			case 0:		key = fkey_table[func_idx].key1;	break;
			case 1:		key = fkey_table[func_idx].key2;	break;
			case 2:		key = fkey_table[func_idx].key3;	break;
			}
			if (key == KEY_NONE) {
				continue;
			}
			for (int func_idx2 = func_idx + 1; fkey_table[func_idx2].help[0] ; func_idx2++) {
				for (int key_idx2 = 0; key_idx2 < MAX_KEYS_BOUND; key_idx2++) {
					key_code_t key2;
					switch (key_idx2) {
					default:
					case 0:		key2 = fkey_table[func_idx2].key1;	break;
					case 1:		key2 = fkey_table[func_idx2].key2;	break;
					case 2:		key2 = fkey_table[func_idx2].key3;	break;
					}
					if (key2 == key) {
						warning_printf("key: %04x assigned multiple to func:[%s] and [%s]\n",
						 key, fkey_table[func_idx].desc, fkey_table[func_idx2].desc);
					}
				}
			}
		}
	}
	return 0;
}
PRIVATE int check_all_functions_accessible_without_function_key_(func_key_table_t *fkey_table);
int check_all_functions_accessible_without_function_key()
{
flf_d_printf("-------------------------\n");
	int err = check_all_functions_accessible_without_function_key_(editor_func_key_table);
#ifdef ENABLE_FILER
	err += check_all_functions_accessible_without_function_key_(filer_func_key_table);
#endif // ENABLE_FILER
	return err;
}
PRIVATE int check_all_functions_accessible_without_function_key_(func_key_table_t *fkey_table)
{
	for (int func_idx = 0; fkey_table[func_idx].help[0]; func_idx++) {
		int accessible = 0;
		int accessible_without_fkey = 0;
		for (int key_idx = 0; key_idx < MAX_KEYS_BOUND; key_idx++) {
			key_code_t key;
			switch (key_idx) {
			default:
			case 0:
				key = fkey_table[func_idx].key1;	break;
			case 1:
				key = fkey_table[func_idx].key2;	break;
			case 2:
				key = fkey_table[func_idx].key3;	break;
			}
			if (IS_KEY_VALID(key)) {
				accessible++;
				if (IS_BYTE_KEY(key) || IS_META_KEY(key)) {
					accessible_without_fkey++;
				}
			}
		}
		if (accessible && (accessible_without_fkey == 0)) {
			warning_printf("func:[%s] is not accessible without Func-key\n",
			 fkey_table[func_idx].desc);
		}
	}
	return 0;
}
#endif // START_UP_TEST

#endif // ENABLE_DEBUG

// End of keys.c

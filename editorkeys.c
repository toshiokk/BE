/**************************************************************************
 *   editorkeys.c                                                         *
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

func_key_list_t editor_func_key_table[] = {
//             12345678901234567890   123456789012345678901234567890
// 12345678901234567890
 { EFAM_EXEC, "Menu",                "Previous Menu",
   {K_ESC,        KNA, KNA}, F_I(doe_menu_0), get_str_setting_none },

 { EFNM_EXEC, "",                    "File Menu",
   {KNA,          KNA, KNA}, F_I(doe_menu_0), get_str_setting_none },
 { EFLM_QUIT, "Quit",                "Quit editor",
   {K_C_Q, K_M_q,      KNA}, F_I(doe_quit_editor), get_str_setting_none },
 { E_LM_CULN, "Open file",           "Open file",
   {K_M_e,        KNA, KNA}, F_I(doe_open_file), get_str_setting_none },
 { E_LM_CULN, "Open file",           "View file (Read-Only)",
   {K_M_E,        KNA, KNA}, F_I(doe_open_file_ro), get_str_setting_none },
 { E_LM_CULN, "Open New File",       "Open new file",
   {K_M_n, K_M_N,      KNA}, F_I(doe_open_new_file), get_str_setting_none },
 { E_LM_CULN, "Open locked file",    "Open locked file",
   {K_MC_E,       KNA, KNA}, F_I(doe_open_locked_file), get_str_setting_none },
 { EFNM_EXEC, "Reopen",              "Reopen file",
   {K_C_Z,        KNA, KNA}, F_I(doe_reopen_file), get_str_setting_none },
 { EFNM_EXEC, "Reopen, goto Last pos.", "Reopen and go to Last line",
   {K_M_Z,        KNA, KNA}, F_I(doe_reopen_file_last_line), get_str_setting_none },
 { EFNM_EXEC, "Write File as",       "Write file as",
   {K_M_S,        KNA, KNA}, F_I(doe_write_file_to), get_str_setting_none },
 { EFNM_EXEC, "Write File",          "Write file",
   {K_M_w,        KNA, KNA}, F_I(doe_write_file_ask), get_str_setting_none },
 { EFNM_EXEC, "Write File always.",  "Write file always",
   {K_M_W,        KNA, KNA}, F_I(doe_write_file_always), get_str_setting_none },
 { EFNM_EXEC, "Write All",           "Write all files",
   {K_M_A,        KNA, KNA}, F_I(doe_write_all_ask), get_str_setting_none },
 { EFNM_EXEC, "Write All Modif.",    "Write all files modified",
   {K_MC_A,       KNA, KNA}, F_I(doe_write_all_modified), get_str_setting_none },
 { EFNM_EXEC, "Close",               "Close file",
   {K_C_Q,        KNA, KNA}, F_I(doe_close_file_ask), get_str_setting_none },
 { EFNM_EXEC, "Close always",        "Close file always",
   {K_MC_Q,       KNA, KNA}, F_I(doe_close_file_always), get_str_setting_none },
 { EFNM_EXEC, "Close All files",     "Close all files",
   {K_M_q,        KNA, KNA}, F_I(doe_close_all_ask), get_str_setting_none },
 { EFNM_EXEC, "Close All modified",  "Close all files modified",
   {K_M_Q,        KNA, KNA}, F_I(doe_close_all_modified), get_str_setting_none },
 { EFNM_EXEC, "Open Files",          "Open files in buffer",
   {K_M_L,        KNA, KNA}, F_I(doe_open_files_in_buf), get_str_setting_none },
 { EFNM_EXEC, "Read into buffer",    "Read file into current pos",
   {K_M_i,        KNA, KNA}, F_I(doe_read_file_into_cur_buf), get_str_setting_none },
#ifdef ENABLE_FILER
 { EFAM_EXEC, "Open filer",          "Open filer",
   {K_M_F,        KNA, KNA}, F_I(doe_filer), get_str_setting_none },
#endif // ENABLE_FILER
#ifdef ENABLE_HELP
 { EFNM_EXEC, "Splash",              "Splash screen",
   {K_M_v,        KNA, KNA}, F_I(doe_splash), get_str_setting_none },
#endif // ENABLE_HELP
 { EFNM_EXEC, "Color pairs",         "Display color pairs",
   {K_M_c,        KNA, KNA}, F_I(doe_display_color_settings), get_str_setting_none },

 { EFNM_EXEC, "",                    "Cursor Menu",
   {KNA,          KNA, KNA}, F_I(doe_menu_0), get_str_setting_none },
 { EFAM_EXEC, "Up",                  "Move cursor UP",
   {K_C_E, K_UP,       KNA}, F_I(doe_up), get_str_setting_none },
 { EFAM_EXEC, "Down",                "Move cursor DOWN",
   {K_C_X, K_DOWN,     KNA}, F_I(doe_down), get_str_setting_none },
 { EFAM_EXEC, "Left",                "Move cursor LEFT",
   {K_C_S, K_LEFT,     KNA}, F_I(doe_left), get_str_setting_none },
 { EFAM_EXEC, "Right",               "Move cursor RIGHT",
   {K_C_D, K_RIGHT,    KNA}, F_I(doe_right), get_str_setting_none },
 { EFAM_EXEC, "Page up  ",           "Page UP",
   {K_C_R, K_PPAGE,    KNA}, F_I(doe_page_up), get_str_setting_none },
 { EFAM_EXEC, "Page down",           "Page DOWN",
   {K_C_C, K_NPAGE,    KNA}, F_I(doe_page_down), get_str_setting_none },
 { EFAM_EXEC, "Prev Word",           "Move backward one word",
   {K_C_A,        KNA, KNA}, F_I(doe_prev_word), get_str_setting_none },
 { EFAM_EXEC, "Next Word",           "Move forward one word",
   {K_C_F,        KNA, KNA}, F_I(doe_next_word), get_str_setting_none },
 { EFAM_EXEC, "Goto columns",        "Goto columns in the line",
   {K_MC_F,       KNA, KNA}, F_I(doe_goto_column), get_str_setting_none },
 { EFAM_EXEC, "Start of line",       "Start of the line",
   {K_C_T, K_HOME,     KNA}, F_I(doe_start_of_line), get_str_setting_none },
 { EFAM_EXEC, "End of line",         "End of the line",
   {K_C_B, K_C_V, K_END},    F_I(doe_end_of_line), get_str_setting_none },
 { EFAM_EXEC, "First line",          "Top of the file",
   {K_M_t,        KNA, KNA}, F_I(doe_first_line), get_str_setting_none },
 { EFAM_EXEC, "Last line",           "Bottom of the file",
   {K_M_b,        KNA, KNA}, F_I(doe_last_line), get_str_setting_none },
 { EFAM_EXEC, "Go To Line",          "Go to specified line",
   {K_C_UNDLN,    KNA, KNA}, F_I(doe_goto_line), get_str_setting_none },
#ifdef ENABLE_FILER
 { EFAM_EXEC, "ToDir",               "Goto directory",
   {K_M_LBRAC,    KNA, KNA}, F_I(doe_goto_directory_in_cur_cursor_pos), get_str_setting_none },
 { EFAM_EXEC, "ToDir",               "Goto directory",
   {K_M_RBRAC,    KNA, KNA}, F_I(doe_goto_directory_in_cur_line), get_str_setting_none },
#endif // ENABLE_FILER
 { EFAM_EXEC, "TagJp",               "Tag-jump to file or directory",
   {K_F11, K_M_J,      KNA}, F_I(doe_tag_jump_in_cur_cursor_pos), get_str_setting_none },
 { EFAM_EXEC, "TagJp",               "Tag-jump to file or directory",
   {K_F12, K_M_j,      KNA}, F_I(doe_tag_jump_in_cur_line), get_str_setting_none },

 { EFNM_EXEC, "",                    "Edit Menu",
   {KNA,          KNA, KNA}, F_I(doe_menu_0), get_str_setting_none },
 { EFNM_EXEC, "Tab",                 "Insert a TAB character",
   {K_TAB,        KNA, KNA}, F_I(doe_tab), get_str_setting_none },
 { E_LM_CULN, "Enter",               "Insert a carriage return",
   {K_ENTER,      KNA, KNA}, F_I(doe_carriage_return), get_str_setting_none },
 { E_LM_CULN, "Enter with auto indent", "Insert a carriage return",
   {K_M_ENTER,    KNA, KNA}, F_I(doe_carriage_return_with_auto_indent), get_str_setting_none },
 { EFNM_EXEC, "Backspace",           "Backspace",
   {K_C_H, K_BS,       KNA}, F_I(doe_backspace), get_str_setting_none },
 { EFNM_EXEC, "Backspace(limited)",   "Backspace(limited)",
   {K_MC_H,       KNA, KNA}, F_I(doe_backspace_limited), get_str_setting_none },
 { EFNM_EXEC, "Delete",              "Delete a character",
   {K_C_G, K_DEL,      KNA}, F_I(doe_delete_char), get_str_setting_none },
 { EFNM_EXEC, "UpperLower",          "Invert upper/lower letter",
   {K_C_W,        KNA, KNA}, F_I(doe_conv_upp_low_letter), get_str_setting_none },
 { EFNM_EXEC, "UpperLetter",         "Make upper letter",
   {K_MC_U,       KNA, KNA}, F_I(doe_conv_low_letter), get_str_setting_none },
 { EFNM_EXEC, "Ctrl code",           "Input control code",
   {K_M_EXCLA,    KNA, KNA}, F_I(doe_control_code), get_str_setting_none },
 { EFNM_EXEC, "Char code",           "Input character code",
   {K_M_AT,       KNA, KNA}, F_I(doe_charcode), get_str_setting_none },
 { EFNM_EXEC, "Memorize column pos.","Memorize column position",
   {K_M_APOST,    KNA, KNA}, F_I(doe_memorize_columns), get_str_setting_none },
 { EFNM_EXEC, "Fill spaces",         "Fill spaces till the columns",
   {K_M_QUOTA,    KNA, KNA}, F_I(doe_fill_spaces_to_columns), get_str_setting_none },
 { EFNM_EXEC, "Paste history",       "Paste from history",
   {K_M_h,        KNA, KNA}, F_I(doe_paste_from_history), get_str_setting_none },
#ifdef ENABLE_UNDO
 { EFNM_EXEC, "Undo",                "Undo",
   {K_M_u, K_M_z,      KNA}, F_I(doe_undo), get_str_setting_none },
 { EFNM_EXEC, "Redo",                "Redo",
   {K_M_o,        KNA, KNA}, F_I(doe_redo), get_str_setting_none },
#endif // ENABLE_UNDO

 { EFNM_EXEC, "",                    "Search/Replace Menu",
   {KNA,          KNA, KNA}, F_I(doe_menu_0), get_str_setting_none },
 { EFAM_EXEC, "SrchB",               "Search keyword forward",
   {K_S_F03, K_C_RBRAK, KNA}, F_I(doe_search_backward_first), get_str_setting_none },
 { EFAM_EXEC, "SrchF",               "Search keyword backward",
   {K_S_F04, K_C_BAKSL, KNA}, F_I(doe_search_forward_first), get_str_setting_none },
 { EFAM_EXEC, "SrchB",               "Search keyword backward again",
   {K_F03, K_M_a, K_M_s},    F_I(doe_search_backward_next), get_str_setting_none },
 { EFAM_EXEC, "SrchF",               "Search keyword forward again",
   {K_F04, K_M_f, K_M_d},    F_I(doe_search_forward_next), get_str_setting_none },
 { EFNM_EXEC, "Replace",             "Replace keyword",
   {K_C_CARET,    KNA, KNA}, F_I(doe_replace), get_str_setting_none },
#ifdef ENABLE_REGEX
 { EFNM_EXEC, "Find Bracket()",      "Find counter bracket()",
   {K_M_RBRAK,    KNA, KNA}, F_I(doe_find_bracket), get_str_setting_none },
 { EFNM_EXEC, "Find Bracket)(",      "Find counter bracket)(",
   {K_M_LBRAK,    KNA, KNA}, F_I(doe_find_bracket_reverse), get_str_setting_none },
#endif // ENABLE_REGEX
 { EFNM_EXEC, "RecKM",               "Start/Stop recording key-macro",
   {K_F01, K_M_r,      KNA}, F_I(doe_start_rec__cancel_rec), get_str_setting_none },
 { EFNM_EXEC, "PlyBk",               "End-rec/Playback key-macro",
   {K_F02, K_M_p,      KNA}, F_I(doe_end_rec__playback), get_str_setting_none },
 { EFNM_EXEC, "Playback-1",          "Playback 1st newest key-macro",
   {K_M_1,        KNA, KNA}, F_I(doe_playback_last_1), get_str_setting_none },
 { EFNM_EXEC, "Playback-2",          "Playback 2nd newest key-macro",
   {K_M_2,        KNA, KNA}, F_I(doe_playback_last_2), get_str_setting_none },
#ifdef ENABLE_HISTORY
 { EFNM_EXEC, "Playback-string",     "Playback input string",
   {K_M_3,        KNA, KNA}, F_I(doe_playback_string), get_str_setting_none },
#endif // ENABLE_HISTORY
 { EFAM_EXEC, "Run line soon",       "Run current line soon",
   {K_M_x,        KNA, KNA}, F_I(doe_run_line_soon), get_str_setting_none },
 { EFAM_EXEC, "Run line soon(w/ logging)", "Run current line soon w/ log",
   {K_M_X,        KNA, KNA}, F_I(doe_run_line_soon_w_log), get_str_setting_none },

 { EFNM_EXEC, "",                    "Buffer Menu",
   {KNA,          KNA, KNA}, F_I(doe_menu_0), get_str_setting_none },
 { EFAM_EXEC, "Previous buffer",     "Switch to previous file",
   {K_M_COMMA,    KNA, KNA}, F_I(doe_switch_to_prev_buffer), get_str_setting_none },
 { EFAM_EXEC, "Next buffer",         "Switch to next file",
   {K_M_PERIO,    KNA, KNA}, F_I(doe_switch_to_next_buffer), get_str_setting_none },
 { EFNM_EXEC, "Top File",            "Switch to top file",
   {K_M_LESST,    KNA, KNA}, F_I(doe_switch_to_top_buffer), get_str_setting_none },
 { EFNM_EXEC, "Bottom File",         "Switch to bottom file",
   {K_M_GREAT,    KNA, KNA}, F_I(doe_switch_to_bot_buffer), get_str_setting_none },
 { EFNM_EXEC, "File List",           "Display File List",
   {K_M_SEMCO,    KNA, KNA}, F_I(doe_view_file_list), get_str_setting_none },
 { EFAM_EXEC, "Previous buffers",    "Switch to previous buffers",
   {KNA,          KNA, KNA}, F_I(doe_switch_to_prev_buffers), get_str_setting_none },
 { EFAM_EXEC, "Next buffers",        "Switch to next buffers",
   {KNA,          KNA, KNA}, F_I(doe_switch_to_next_buffers), get_str_setting_none },
 { EFNM_EXEC, "Open project file",   "Open project file",
   {K_M_P,        KNA, KNA}, F_I(doe_open_proj_file), get_str_setting_none },
 { EFNM_EXEC, "Open execution log file", "Open exec. log file",
   {K_M_l,        KNA, KNA}, F_I(doe_open_exec_log_file), get_str_setting_none },
 { EFNM_EXEC, "Goto prev. pos",      "Goto previous pos.",
   {K_M_SLASH,    KNA, KNA}, F_I(doe_return_to_prev_file_pos), get_str_setting_none },
#ifdef ENABLE_HELP
 { EFNM_EXEC, "Key List",            "Display Key List",
   {K_M_QUEST,    KNA, KNA}, F_I(doe_view_func_list), get_str_setting_none },
#endif // ENABLE_HELP

 { EFNM_EXEC, "",                    "Cut-buffer Menu",
   {KNA,          KNA, KNA}, F_I(doe_menu_0), get_str_setting_none },
 { EFNM_EXEC, "Mark ",               "Mark text",
   {K_F05, K_C_N, K_M_5},    F_I(doe_tog_mark), get_str_setting_none },
 { EFNM_EXEC, "Select all",          "Select all of buffer",
   {K_S_F05, K_M_PERCE, KNA}, F_I(doe_select_all_lines), get_str_setting_none },
 { EFNM_EXEC, "Cut  ",               "Cut into Cut-buffer",
   {K_F06, K_C_K, K_M_6},    F_I(doe_cut_text), get_str_setting_none },
 { EFNM_EXEC, "Del  ",               "Delete text",
   {K_M_k, K_S_F06, K_M_CARET}, F_I(doe_delete_text), get_str_setting_none },
 { EFAM_EXEC, "Copy ",               "Copy to Cut-buffer",
   {K_F07, K_M_7,      KNA}, F_I(doe_copy_text), get_str_setting_none },
 { EFNM_EXEC, "Paste",               "Paste from Cut-buf with pop",
   {K_F08, K_M_8,      KNA}, F_I(doe_paste_text_with_pop), get_str_setting_none },
 { EFNM_EXEC, "Paste",               "Paste from Cut-buf without pop",
   {K_F09, K_M_9, K_INS},    F_I(doe_paste_text_without_pop), get_str_setting_none },
 { EFNM_EXEC, "Dupli",               "Duplicate line",
   {K_F10, K_M_0,      KNA}, F_I(doe_duplicate_text), get_str_setting_none },
 { EFNM_EXEC, "Copy to clip-board",  "Copy to clip-board",
   {K_S_F07, K_M_C,    KNA}, F_I(doe_copy_text_to_system_clipboard), get_str_setting_none },
 { EFNM_EXEC, "Paste clip-board",    "Paste from clip-board",
   {K_S_F08, K_M_V,    KNA}, F_I(doe_read_clipboard_into_cur_line), get_str_setting_none },
 { EFNM_EXEC, "CutToHead",           "Cut to head of the line",
   {K_C_J,        KNA, KNA}, F_I(doe_cut_to_head), get_str_setting_none },
 { EFNM_EXEC, "CutToTail",           "Cut to tail of the line",
   {K_C_L,        KNA, KNA}, F_I(doe_cut_to_tail), get_str_setting_none },
 { EFNM_EXEC, "DeleteToHead",        "Delete to head of the line",
   {K_C_U,        KNA, KNA}, F_I(doe_cut_to_head), get_str_setting_none },
 { EFNM_EXEC, "DeleteToTail",        "Delete to tail of the line",
   {K_C_O,        KNA, KNA}, F_I(doe_cut_to_tail), get_str_setting_none },
 { EFNM_EXEC, "ClrCB",               "Clear all cut buffers",
   {K_SCM_DEL,    KNA, KNA}, F_I(doe_clear_all_cut_bufs), get_str_setting_none },

 { EFNM_EXEC, "",                    "Settings Menu",
   {KNA,          KNA, KNA}, F_I(doe_menu_0), get_str_setting_none },
 { EFAM_EXEC, "App mode",            "Increment mode",
   {KNA,          KNA, KNA}, F_I(doe_inc_app_mode), get_str_app_mode },
 { EFNM_EXEC, "Split pane",          "Split screen into panes",
   {K_M_VERTB,    KNA, KNA}, F_I(doe_tog_panes), get_str_editor_panes },
 { EFNM_EXEC, "Switch pane",         "Switch editor pane",
   {K_M_TAB,      KNA, KNA}, F_I(doe_tog_panex), get_str_editor_panex },
 { EFNM_EXEC, "Draw cursor",         "Toggle Drawing cursor",
   {K_MC_C,       KNA, KNA}, F_I(doe_tog_draw_cursor),    get_str_draw_cursor },
 { EFNM_EXEC, "Ignore case",         "Toggle Ignore case",
   {K_MC_G,       KNA, KNA}, F_I(doe_tog_ignore_case),    get_str_ignore_case },
 { EFNM_EXEC, "Auto indent",         "Toggle Auto indent",
   {K_MC_O,       KNA, KNA}, F_I(doe_tog_auto_indent),    get_str_auto_indent },
 { EFNM_EXEC, "Display key list",    "Increment Displaying key list",
   {K_MC_K,       KNA, KNA}, F_I(doe_inc_key_list_lines), get_str_key_list_lines },
 { EFNM_EXEC, "Back up files",       "Increment Back up files",
   {K_MC_B,       KNA, KNA}, F_I(doe_inc_backup_files),   get_str_backup_files },
#ifdef ENABLE_REGEX
 { EFNM_EXEC, "RegExp",              "Toggle Regex search/replace",
   {K_MC_X,       KNA, KNA}, F_I(doe_tog_regexp),         get_str_regexp },
#endif // ENABLE_REGEX
 { EFNM_EXEC, "Cursor center",       "Increment Cursor-center mode",
   {K_MC_S,       KNA, KNA}, F_I(doe_inc_cursor_positioning),  get_str_cursor_positioning },
 { EFNM_EXEC, "Dual scroll",         "Toggle Dual scroll",
   {K_MC_D,       KNA, KNA}, F_I(doe_tog_dual_scroll),    get_str_dual_scroll },
 { EFNM_EXEC, "Show ruler",          "Toggle Show Ruler",
   {K_MC_R,       KNA, KNA}, F_I(doe_tog_show_ruler),     get_str_show_ruler },
 { EFNM_EXEC, "Show line number",    "Toggle Show Line number",
   {K_MC_N,       KNA, KNA}, F_I(doe_tog_show_line_num),  get_str_show_line_num },
#ifdef ENABLE_SYNTAX
 { EFNM_EXEC, "Syntax HL",           "Toggle Syntax Highlighting",
   {K_M_H,        KNA, KNA}, F_I(doe_tog_syntax_hl),      get_str_syntax_hl },
 { EFNM_EXEC, "TAB/EOL notation",    "Toggle TAB/EOL notation",
   {K_MC_Z,       KNA, KNA}, F_I(doe_tog_tab_eol_notation), get_str_tab_eol_notation },
#endif // ENABLE_SYNTAX
 { EFNM_EXEC, "Code-7F Key-BS",      "Toggle Code-7F Key-BS",
   {K_M_BS,       KNA, KNA}, F_I(doe_tog_map_key_7f_bs), get_str_map_key_7f_bs },

 { EFNM_EXEC, "",                    "File type Menu",
   {KNA,          KNA, KNA}, F_I(doe_menu_0), get_str_setting_none },
 { EFNM_EXEC, "View mode",           "Increment View mode",
   {K_MC_V,       KNA, KNA}, F_I(doe_inc_buf_view_mode),      get_str_buf_view_mode },
 { EFNM_EXEC, "nix format",          "Set nix format (LF)",
   {KNA,          KNA, KNA}, F_I(doe_set_buf_nix_file),       get_str_buf_nix_file },
 { EFNM_EXEC, "Mac format",          "Set Mac format (CR)",
   {KNA,          KNA, KNA}, F_I(doe_set_buf_mac_file),       get_str_buf_mac_file },
 { EFNM_EXEC, "DOS format",          "Set DOS format (CR+LF)",
   {KNA,          KNA, KNA}, F_I(doe_set_buf_dos_file),       get_str_buf_dos_file },
 { EFNM_EXEC, "ASCII  encoding",     "Set ASCII  encoding",
   {KNA,          KNA, KNA}, F_I(doe_set_buf_enc_ascii),   get_str_buf_enc_ascii },
 { EFNM_EXEC, "UTF-8  encoding",     "Set UTF-8  encoding",
   {KNA,          KNA, KNA}, F_I(doe_set_buf_enc_utf8),    get_str_buf_enc_utf8 },
#ifdef USE_NKF
 { EFNM_EXEC, "EUC-JP encoding",     "Set EUC-JP encoding",
   {KNA,          KNA, KNA}, F_I(doe_set_buf_enc_eucjp),   get_str_buf_enc_eucjp },
 { EFNM_EXEC, "S-JIS  encoding",     "Set S-JIS  encoding",
   {KNA,          KNA, KNA}, F_I(doe_set_buf_enc_sjis),    get_str_buf_enc_sjis },
 { EFNM_EXEC, "JIS    encoding",     "Set JIS    encoding",
   {KNA,          KNA, KNA}, F_I(doe_set_buf_enc_jis),     get_str_buf_enc_jis },
#endif // USE_NKF
 { EFNM_EXEC, "BINARY encoding",     "Set BINARY encoding",
   {KNA,          KNA, KNA}, F_I(doe_set_buf_enc_binary),  get_str_buf_enc_binary },
 { EFNM_EXEC, "Tab size",            "Toggle Tab size",
   {K_MC_T,       KNA, KNA}, F_I(doe_tog_buf_tab_size),       get_str_buf_tab_size },
 { EFNM_EXEC, "Tab size",            "Increment Tab size",
   {K_MC_Y,       KNA, KNA}, F_I(doe_inc_buf_tab_size),       get_str_buf_tab_size },
 { EFNM_EXEC, "Line-wrap mode",      "Toggle Line-wrap mode",
   {K_MC_W,       KNA, KNA}, F_I(doe_tog_buf_line_wrap_mode), get_str_buf_line_wrap_mode },

 { EFNM_EXEC, "",                    "",
   {KNA,          KNA, KNA}, F_I(NULL), NULL },
};

// End of editorkeys.c

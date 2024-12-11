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

func_key_table_t editor_func_key_table[] = {
//  12345678901234567890   123456789012345678901234567890            123456789012345678901234567890
//      12345678901234567890
 { "Prev.Menu",           "Previous Menu",                           K_M_ESC, K_M_BAKQT, KNA,
   EFLM_NO_EXEC, F_I(doe_editor_menu_0), NULL },

 { "",                    "File Menu",                               K_ESC,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_editor_menu_0), NULL },
 { "Open File",           "Open file",                               K_M_e,        KNA, KNA,
   E_LM_CUR_LIN, F_I(doe_open_file), NULL },
 { "Open New File",       "Open new file",                           K_M_E, K_M_n,      KNA,
   E_LM_CUR_LIN, F_I(doe_open_new_file), NULL },
 { "Reopen",              "Reopen file",                             K_C_Z,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_reopen_file), NULL },
 { "Reopen, goto Last pos.", "Reopen and go to Last line",           K_M_Z,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_reopen_file_last_line), NULL },
 { "Write File as",       "Write file as",                           K_M_S,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_write_file_to), NULL },
 { "Write File",          "Write file",                              K_M_w,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_write_file_ask), NULL },
 { "Write File always.",  "Write file always",                       K_M_W,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_write_file_always), NULL },
 { "Write All",           "Write all files",                         K_M_A,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_write_all_ask), NULL },
 { "Write All Modif.",    "Write all files modified",                K_MC_A,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_write_all_modified), NULL },
 { "Close",               "Close file",                              K_C_Q,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_close_file_ask), NULL },
 { "Close always",        "Close file always",                       K_MC_Q,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_close_file_always), NULL },
 { "Close All files",     "Close all files",                         K_M_q,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_close_all_ask), NULL },
 { "Close All modified",  "Close all files modified",                K_M_Q,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_close_all_modified), NULL },
 { "Open Files",          "Open files in buffer",                    K_M_L,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_open_files_in_buf), NULL },
 { "Read into buffer",    "Read file into current pos",              K_M_i,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_read_file_into_cur_buf), NULL },
#ifdef ENABLE_FILER
 { "Open filer",          "Open filer",                              K_M_F,        KNA, KNA,
   EFAM_EXECUTE, F_I(doe_filer), NULL },
#endif // ENABLE_FILER
#ifdef ENABLE_HELP
 { "Splash",              "Splash screen",                           K_M_v,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_splash), NULL },
#endif // ENABLE_HELP
 { "Color pairs",         "Display color pairs",                     K_M_c,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_display_color_settings), NULL },

 { "",                    "Cursor Menu",                             KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_editor_menu_0), NULL },
 { "Up",                  "Move cursor UP",                          K_C_E, K_UP,       KNA,
   EFAM_EXECUTE, F_I(doe_up), NULL },
 { "Down",                "Move cursor DOWN",                        K_C_X, K_DOWN,     KNA,
   EFAM_EXECUTE, F_I(doe_down), NULL },
 { "Left",                "Move cursor LEFT",                        K_C_S, K_LEFT,     KNA,
   EFAM_EXECUTE, F_I(doe_left), NULL },
 { "Right",               "Move cursor RIGHT",                       K_C_D, K_RIGHT,    KNA,
   EFAM_EXECUTE, F_I(doe_right), NULL },
 { "Page up  ",           "Page UP",                                 K_C_R, K_PPAGE,    KNA,
   EFAM_EXECUTE, F_I(doe_page_up), NULL },
 { "Page down",           "Page DOWN",                               K_C_C, K_NPAGE,    KNA,
   EFAM_EXECUTE, F_I(doe_page_down), NULL },
 { "Prev Word",           "Move backward one word",                  K_C_A,        KNA, KNA,
   EFAM_EXECUTE, F_I(doe_prev_word), NULL },
 { "Next Word",           "Move forward one word",                   K_C_F,        KNA, KNA,
   EFAM_EXECUTE, F_I(doe_next_word), NULL },
 { "Goto columns",        "Goto columns in the line",                K_MC_F,       KNA, KNA,
   EFAM_EXECUTE, F_I(doe_goto_column), NULL },
 { "Start of line",       "Start of the line",                       K_C_T, K_HOME,     KNA,
   EFAM_EXECUTE, F_I(doe_start_of_line), NULL },
 { "End of line",         "End of the line",                         K_C_B, K_C_V, K_END,
   EFAM_EXECUTE, F_I(doe_end_of_line), NULL },
 { "First line",          "Top of the file",                         K_M_t,        KNA, KNA,
   EFAM_EXECUTE, F_I(doe_first_line), NULL },
 { "Last line",           "Bottom of the file",                      K_M_b,        KNA, KNA,
   EFAM_EXECUTE, F_I(doe_last_line), NULL },
 { "Go To Line",          "Go to specified line",                    K_C_UNDLN,    KNA, KNA,
   EFAM_EXECUTE, F_I(doe_goto_line), NULL },
 { "Tag-jump",            "Tag-jump to file or directory",           K_F12, K_M_j,      KNA,
   EFAM_EXECUTE, F_I(doe_goto_file_or_dir_in_cur_line), NULL },
 { "Tag-jump",            "Tag-jump to file or directory",           K_F11, K_M_J,      KNA,
   EFAM_EXECUTE, F_I(doe_goto_file_or_dir_in_cur_cursor_pos), NULL },

 { "",                    "Edit Menu",                               KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_editor_menu_0), NULL },
 { "Tab",                 "Insert a TAB character",                  K_TAB,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tab), NULL },
 { "Enter",               "Insert a carriage return",                K_ENTER,      KNA, KNA,
   E_LM_CUR_LIN, F_I(doe_carriage_return), NULL },
 { "Enter with auto indent", "Insert a carriage return",             K_M_ENTER,    KNA, KNA,
   E_LM_CUR_LIN, F_I(doe_carriage_return_with_auto_indent), NULL },
 { "Backspace",           "Backspace",                               K_C_H, K_BS,       KNA,
   EFLM_NO_EXEC, F_I(doe_backspace), NULL },
 { "Backspace(limited)",   "Backspace(limited)",                     K_MC_H,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_backspace_limited), NULL },
 { "Delete",              "Delete a character",                      K_C_G, K_DEL,      KNA,
   EFLM_NO_EXEC, F_I(doe_delete_char), NULL },
 { "UpperLower",          "Invert upper/lower letter",               K_C_W,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_conv_upp_low_letter), NULL },
 { "UpperLetter",         "Make upper letter",                       K_MC_U,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_conv_low_letter), NULL },
 { "Ctrl code",           "Input control code",                      K_M_EXCLA,    KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_control_code), NULL },
 { "Char code",           "Input character code",                    K_M_AT,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_charcode), NULL },
 { "Memorize column pos.","Memorize column position",                K_M_LPARE,    KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_memorize_columns), NULL },
 { "Fill spaces",         "Fill spaces till the columns",            K_M_RPARE,    KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_fill_spaces_to_columns), NULL },
 { "Paste history",       "Paste from history",                      K_M_h,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_paste_from_history), NULL },
#ifdef ENABLE_UNDO
 { "Undo",                "Undo",                                    K_M_u, K_M_z,      KNA,
   EFLM_NO_EXEC, F_I(doe_undo), NULL },
 { "Redo",                "Redo",                                    K_M_o,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_redo), NULL },
#endif // ENABLE_UNDO

 { "",                    "Search/Replace Menu",                     KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_editor_menu_0), NULL },
 { "Search Bw",           "Search keyword forward",                  K_S_F03, K_C_RBRAK, KNA,
   EFAM_EXECUTE, F_I(doe_search_backward_first), NULL },
 { "Search Fw",           "Search keyword backward",                 K_S_F04, K_C_BAKSL, KNA,
   EFAM_EXECUTE, F_I(doe_search_forward_first), NULL },
 { "Srch Nx Bw",          "Search keyword backward again",           K_F03, K_M_a, K_M_s,
   EFAM_EXECUTE, F_I(doe_search_backward_next), NULL },
 { "Srch Nx Fw",          "Search keyword forward again",            K_F04, K_M_f, K_M_d,
   EFAM_EXECUTE, F_I(doe_search_forward_next), NULL },
 { "Replace",             "Replace keyword",                         K_C_CARET,    KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_replace), NULL },
#ifdef ENABLE_REGEX
 { "Find Bracket()",      "Find counter bracket()",                  K_M_RBRAK,    KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_find_bracket), NULL },
 { "Find Bracket)(",      "Find counter bracket)(",                  K_M_LBRAK,    KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_find_bracket_reverse), NULL },
#endif // ENABLE_REGEX
 { "Record/Stop-rec",     "Start/Stop recording key-macro",          K_F01, K_M_r,      KNA,
   EFLM_NO_EXEC, F_I(doe_start_rec__cancel_rec), NULL },
 { "End-rec/Playback",    "End-rec/Playback key-macro",              K_F02, K_M_p,      KNA,
   EFLM_NO_EXEC, F_I(doe_end_rec__playback), NULL },
 { "Playback-1",          "Playback 1st newest key-macro",           K_M_1,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_playback_last_1), NULL },
 { "Playback-2",          "Playback 2nd newest key-macro",           K_M_2,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_playback_last_2), NULL },
#ifdef ENABLE_HISTORY
 { "Playback-string",     "Playback input string",                   K_M_3,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_playback_string), NULL },
#endif // ENABLE_HISTORY
 { "Run line soon",       "Run current line soon",                   K_M_x,        KNA, KNA,
   EFAM_EXECUTE, F_I(doe_run_line_soon), NULL },
 { "Run line soon(w/ logging)", "Run current line soon w/ log",      K_M_X,        KNA, KNA,
   EFAM_EXECUTE, F_I(doe_run_line_soon_w_log), NULL },

 { "",                    "Buffer Menu",                             KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_editor_menu_0), NULL },
 { "Previous File",       "Switch to previous file",                 K_M_COMMA,    KNA, KNA,
   EFAM_EXECUTE, F_I(doe_switch_to_prev_buffer), NULL },
 { "Next File",           "Switch to next file",                     K_M_PERIO,    KNA, KNA,
   EFAM_EXECUTE, F_I(doe_switch_to_next_buffer), NULL },
 { "Top File",            "Switch to top file",                      K_M_LESST,    KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_switch_to_top_buffer), NULL },
 { "Bottom File",         "Switch to bottom file",                   K_M_GREAT,    KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_switch_to_bot_buffer), NULL },
 { "File List",           "Display File List",                       K_M_SEMCO,    KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_view_file_list), NULL },
#if APP_REL_LVL <= APP_REL_LVL_TEST
 { "Previous buffers",    "Switch to previous buffers",              K_M_LBRAC,    KNA, KNA,
   EFAM_EXECUTE, F_I(doe_switch_to_prev_buffers), NULL },
 { "Next buffers",        "Switch to next buffers",                  K_M_RBRAC,    KNA, KNA,
   EFAM_EXECUTE, F_I(doe_switch_to_next_buffers), NULL },
#endif // APP_REL_LVL
 { "Open project file",   "Open project file",                       K_M_P,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_open_proj_file), NULL },
 { "Open execution log file", "Open exec. log file",                 K_M_l,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_open_exec_log_file), NULL },
 { "Goto prev. pos",      "Goto previous pos.",                      K_M_SLASH,    KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_return_to_prev_file_pos), NULL },
#ifdef ENABLE_HELP
 { "Key List",            "Display Key List",                        K_M_QUEST,    KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_view_func_list), NULL },
#endif // ENABLE_HELP

 { "",                    "Cut-buffer Menu",                         KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_editor_menu_0), NULL },
 { "Mark Text",           "Mark text",                               K_C_N, K_F05, K_M_5,
   EFLM_NO_EXEC, F_I(doe_tog_mark), NULL },
 { "Select all",          "Select all of buffer",                    K_S_F05, K_M_PERCE, KNA,
   EFLM_NO_EXEC, F_I(doe_select_all_lines), NULL },
 { "Cut Text",            "Cut into Cut-buffer",                     K_C_K, K_F06, K_M_6,
   EFLM_NO_EXEC, F_I(doe_cut_text), NULL },
 { "Delete Text",         "Delete text",                             K_M_k, K_S_F06, K_M_CARET,
   EFLM_NO_EXEC, F_I(doe_delete_text), NULL },
 { "Copy Text",           "Copy to Cut-buffer",                      K_F07, K_M_7,      KNA,
   EFAM_EXECUTE, F_I(doe_copy_text), NULL },
 { "Paste Text",          "Paste from Cut-buf with pop",             K_F08, K_M_8,      KNA,
   EFLM_NO_EXEC, F_I(doe_paste_text_with_pop), NULL },
 { "Paste2 Text",         "Paste from Cut-buf without pop",          K_F09, K_M_9, K_INS,
   EFLM_NO_EXEC, F_I(doe_paste_text_without_pop), NULL },
 { "Duplic Text",         "Duplicate line",                          K_F10, K_M_0,      KNA,
   EFLM_NO_EXEC, F_I(doe_duplicate_text), NULL },
 { "Copy to clip-board",  "Copy to clip-board",                      K_S_F07, K_M_C,    KNA,
   EFLM_NO_EXEC, F_I(doe_copy_text_to_system_clipboard), NULL },
 { "Paste clip-board",    "Paste from clip-board",                   K_S_F08, K_M_V,    KNA,
   EFLM_NO_EXEC, F_I(doe_read_clipboard_into_cur_line), NULL },
 { "CutToHead",           "Cut to head of the line",                 K_C_J,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_cut_to_head), NULL },
 { "CutToTail",           "Cut to tail of the line",                 K_C_L,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_cut_to_tail), NULL },
 { "DeleteToHead",        "Delete to head of the line",              K_C_U,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_cut_to_head), NULL },
 { "DeleteToTail",        "Delete to tail of the line",              K_C_O,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_cut_to_tail), NULL },

 { "",                    "Settings Menu",                           KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_editor_menu_0), NULL },
 { "App mode",            "Application mode",                        KNA,          KNA, KNA,
   EFAM_EXECUTE, F_I(doe_inc_app_mode), get_str_app_mode },
 { "Split pane",          "Split screen into panes",                 K_M_VERTB, K_M_BAKSL, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_panes), get_str_editor_panes },
 { "Switch pane",         "Switch editor pane",                      K_M_TAB,      KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_panex), get_str_editor_panex },
 { "Draw cursor",         "Toggle Drawing cursor",                   K_MC_C,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_draw_cursor),    get_str_draw_cursor },
 { "Ignore case",         "Toggle Ignore case",                      K_MC_G,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_ignore_case),    get_str_ignore_case },
 { "Auto indent",         "Toggle Auto indent",                      K_MC_O,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_auto_indent),    get_str_auto_indent },
 { "Display key list",    "Toggle Displaying key list",              K_MC_K,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_inc_key_list_lines), get_str_key_list_lines },
 { "Back up files",       "Increment Back up files",                 K_MC_B,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_inc_backup_files),   get_str_backup_files },
#ifdef ENABLE_REGEX
 { "RegExp",              "Toggle Regex search/replace",             K_MC_X,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_regexp),         get_str_regexp },
#endif // ENABLE_REGEX
 { "Cursor center",       "Toggle Cursor-center mode",               K_MC_S,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_inc_cursor_positioning),  get_str_cursor_positioning },
 { "Dual scroll",         "Toggle Dual scroll",                      K_MC_D,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_dual_scroll),    get_str_dual_scroll },
 { "Show ruler",          "Toggle Show Ruler",                       K_MC_R,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_show_ruler),     get_str_show_ruler },
 { "Show line number",    "Toggle Show Line number",                 K_MC_N,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_show_line_num),  get_str_show_line_num },
#ifdef ENABLE_SYNTAX
 { "Syntax HL",           "Toggle Syntax Highlighting",              K_M_H,        KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_syntax_hl),      get_str_syntax_hl },
 { "TAB/EOL notation",    "Toggle TAB/EOL notation",                 K_MC_Z,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_tab_eol_notation), get_str_tab_eol_notation },
#endif // ENABLE_SYNTAX
 { "Code-7F Key-BS",      "Toggle Code-7F Key-BS",                   K_M_DEL,      KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_map_key_7f_bs), get_str_map_key_7f_bs },

 { "",                    "File type Menu",                          KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_editor_menu_0), NULL },
 { "View mode",           "Toggle View mode",                        K_MC_V,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_buf_view_mode),      get_str_buf_view_mode },
 { "nix format",          "Set nix format (LF)",                     KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_set_buf_nix_file),       get_str_buf_nix_file },
 { "Mac format",          "Set Mac format (CR)",                     KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_set_buf_mac_file),       get_str_buf_mac_file },
 { "DOS format",          "Set DOS format (CR+LF)",                  KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_set_buf_dos_file),       get_str_buf_dos_file },
 { "ASCII  encoding",     "Set ASCII  encoding",                     KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_set_buf_enc_ascii),   get_str_buf_enc_ascii },
 { "UTF-8  encoding",     "Set UTF-8  encoding",                     KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_set_buf_enc_utf8),    get_str_buf_enc_utf8 },
#ifdef USE_NKF
 { "EUC-JP encoding",     "Set EUC-JP encoding",                     KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_set_buf_enc_eucjp),   get_str_buf_enc_eucjp },
 { "S-JIS  encoding",     "Set S-JIS  encoding",                     KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_set_buf_enc_sjis),    get_str_buf_enc_sjis },
 { "JIS    encoding",     "Set JIS    encoding",                     KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_set_buf_enc_jis),     get_str_buf_enc_jis },
#endif // USE_NKF
 { "BINARY encoding",     "Set BINARY encoding",                     KNA,          KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_set_buf_enc_binary),  get_str_buf_enc_binary },
 { "Tab size",            "Toggle Tab size",                         K_MC_T,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_buf_tab_size),       get_str_buf_tab_size },
 { "Tab size",            "Incurement Tab size",                     K_MC_Y,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_inc_buf_tab_size),       get_str_buf_tab_size },
 { "Line-wrap mode",      "Toggle Line-wrap mode",                   K_MC_W,       KNA, KNA,
   EFLM_NO_EXEC, F_I(doe_tog_buf_line_wrap_mode), get_str_buf_line_wrap_mode },

 { "",                    "",                                        KNA,          KNA, KNA,
   EFAM_EXECUTE, F_I(NULL), NULL },
};

// End of editorkeys.c

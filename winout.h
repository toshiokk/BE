/**************************************************************************
 *   winout.h - windowed terminal output                                  *
 *                                                                        *
 *   Copyright (C) 2005-2018 PCR                                          *
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

#ifndef winout_h
#define winout_h

typedef struct win_rect {
	int top;			// Top line of screen
	int left;			// Left column of window
	int lines;			// Lines
	int columns;		// Columns
} win_rect_t;

// window				win_idx
// --------------------	-----------
#define WIN_IDX_MAIN		0	// sub_win_rects[0]
#define WIN_IDX_SUB_WHOLE	1	// sub_win_rects[1]
#define WIN_IDX_SUB_LEFT	2	// sub_win_rects[2]
#define WIN_IDX_SUB_RIGHT	3	// sub_win_rects[3]
#define SUB_WINS			4
extern win_rect_t sub_win_rects[SUB_WINS];
extern win_rect_t *main_win, *cur_win;
extern int cur_win_idx;

void win_init_win_size(void);

void set_win_depth(int app_stack_depth);
void inc_win_depth(void);
void dec_win_depth(void);
const int get_win_depth(void);
void win_reinit_win_size();

void win_setup_win_size(int win_depth);
void win_select_win(int sub_win_idx);
void dump_cur_win(void);

int main_win_get_lines(void);
int main_win_get_columns(void);

int main_win_get_top_win_lines(void);
int main_win_get_mid_win_lines(void);
int main_win_get_bottom_win_lines(void);

int main_win_get_top_win_y(void);
int main_win_get_mid_win_y(void);
int main_win_get_bottom_win_y(void);
void main_win_set_cursor_pos(int yy, int xx);
void main_win_clear_screen(void);
void main_win_clear_lines(int line_1, int line_2);
void main_win_output_string(int yy, int xx, const char *string, int bytes);

int sub_win_get_lines(void);
int sub_win_get_columns(void);
void sub_win_set_cursor_pos(int yy, int xx);
void sub_win_clear_screen(void);
void sub_win_clear_lines(int line_1, int line_2);
void sub_win_output_string(int yy, int xx, const char *string, int bytes);

void win_save_cursor_pos();
int win_get_saved_cursor_y();

const char *shrink_str_to_scr_static(const char *str);

#endif // winout_h

// End of winout.h

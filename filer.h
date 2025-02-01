/**************************************************************************
 *   filer.h                                                              *
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

#ifndef filer_h
#define filer_h

#ifdef ENABLE_FILER

#define _FILE_SEL_NONE_	0x00	// file un-selected
#define _FILE_SEL_MAN_	0x01	// file selected manually
#define _FILE_SEL_AUTO_	0x02	// file selected automatically on execution of a command
typedef struct {
	char *file_name;
						// | regular file | symlink               |
						// |--------------|-----------------------|
	struct stat lst;	// | file itself  | symlink               |
	struct stat st;		// | file itself  | symlinked file or dir |
	char *symlink;
	char selected;
} file_info_t;

typedef struct {
	char cur_dir[MAX_PATH_LEN+1];		// current directory
	char filter[MAX_PATH_LEN+1];		// e.g. "*.h", "*.c", "": no filter
	char listed_dir[MAX_PATH_LEN+1];	// directory from which file list gotten
	int file_list_entries;
	file_info_t *file_list_ptr;
	int prev_file_idx;
	int cur_file_idx;
	int top_file_idx;
	char prev_dir[MAX_PATH_LEN+1];		// previous current directory
	char next_file[MAX_PATH_LEN+1];		// next file to be selected after changing dir
										//  or after updating file list
} filer_view_t;

#define FILER_PANES		MAX_APP_PANES_2
typedef struct {
	char org_cur_dir[MAX_PATH_LEN+1];	// original current directory
	filer_view_t filer_views[FILER_PANES];
} filer_panes_t;
extern filer_panes_t *cur_filer_panes;	// Current Filer Panes (instance is allocated locally)

extern ef_do_next_t filer_do_next;

void set_cur_filer_panes(filer_panes_t *fps);
filer_panes_t *get_cur_filer_panes();
void init_cur_filer_panes(filer_panes_t *fps, const char *cur_dir);	// TODO: rename
void destroy_filer_panes();
void copy_filer_panes_cur_dir(filer_panes_t *dest, filer_panes_t *src);

filer_view_t *get_cur_filer_view(int pane_idx);
filer_view_t *get_cur_filer_pane_view(void);
filer_view_t *get_other_filer_pane_view(void);
file_info_t *get_cur_fv_file_list_ptr();
file_info_t *get_cur_fv_cur_file_ptr();
file_info_t *get_cur_fv_file_ptr(int file_idx);
int get_cur_fv_file_idx();
void set_cur_fv_file_idx(int file_idx);

int do_call_filer(int push_win, int list_mode,
 const char *dir, const char *filter, char *path_buf, int buf_len);

int update_screen_filer(int status_bar, int refresh);

int filer_vert_scroll_margin_lines();
int filer_vert_scroll_lines();

int filer_win_get_file_path_lines(void);
int filer_win_get_file_list_lines(void);
int filer_win_get_file_path_y(void);
int filer_win_get_file_list_y(void);

#endif // ENABLE_FILER

#endif // filer_h

// End of filer.h

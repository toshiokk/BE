/**************************************************************************
 *   editorundo.c                                                         *
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

#ifdef ENABLE_UNDO

// Undo-buffers manipulation routines -----------------------------------------

// push ==> insert one buffer to top of buffers
be_buf_t *push_undo_buf(be_buf_t *buf)
{
	buf = buf_create_copy(buf);
	buf_view_copy(&(buf->buf_views[get_editor_counter_pane_idx()]),
				 &(buf->buf_views[get_editor_cur_pane_idx()]));
	snprintf(buf->file_path_, MAX_PATH_LEN, "#undo_buf-%02d", count_undo_bufs());
	return buf_insert_after(UNDO_BUFS_TOP_ANCH, buf);
}
// pop ==> remove buffer from top of buffers
be_buf_t *pop_undo_buf(void)
{
	if (IS_NODE_BOT_ANCH(UNDO_BUFS_TOP_NODE))
		return NULL;
	return buf_unlink(UNDO_BUFS_TOP_NODE);
}
be_buf_t *push_redo_buf(be_buf_t *buf)
{
	buf = buf_create_copy(buf);
	snprintf(buf->file_path_, MAX_PATH_LEN, "#redo_buf-%02d", count_redo_bufs());
	return buf_insert_after(REDO_BUFS_TOP_ANCH, buf);
}
be_buf_t *pop_redo_buf(void)
{
	if (IS_NODE_BOT_ANCH(REDO_BUFS_TOP_NODE))
		return NULL;
	return buf_unlink(REDO_BUFS_TOP_NODE);
}
int delete_undo_redo_buf(be_buf_t *edit_buf)
{
	// delete undo, redo buffers related to edit_buf
	return delete_do_buf(edit_buf, UNDO_BUFS_TOP_NODE)
	 + delete_do_buf(edit_buf, REDO_BUFS_TOP_NODE);
}
int delete_do_buf(be_buf_t *edit_buf, be_buf_t *buf)
{
	int deleted = 0;

	for ( ; IS_NODE_INT(buf); ) {
		if (strcmp(buf->abs_path_, edit_buf->abs_path_) == 0) {
			buf = buf_unlink_free(buf);
			deleted++;
		} else {
			buf = NODE_NEXT(buf);
		}
	}
	return deleted;
}
int count_undo_bufs(void)
{
	return bufs_count_bufs(&undo_buffers);
}
int count_redo_bufs(void)
{
	return bufs_count_bufs(&redo_buffers);
}

#ifdef ENABLE_DEBUG
PRIVATE be_buf_t *prev_epc_buf;
PRIVATE size_t prev_epc_buf_size;
PRIVATE int prev_count_undo_bufs;
PRIVATE char func_id_done[MAX_PATH_LEN+1];
void memorize_undo_state_before_change(const char *func_id)
{
	prev_epc_buf = get_epc_buf();
	prev_epc_buf_size = get_epc_buf()->buf_size;
	prev_count_undo_bufs = count_undo_bufs();
	if (func_id) {
		strlcpy__(func_id_done, func_id, MAX_PATH_LEN);
	}
}
void check_undo_state_after_change(void)
{
	if (get_epc_buf() != EDIT_BUFS_TOP_ANCH
	 && get_epc_buf() == prev_epc_buf && get_epc_buf()->buf_size != prev_epc_buf_size
		// edit buffer has been modified
	 && count_undo_bufs() == prev_count_undo_bufs) {
		// but no undo info pushed
		// warn it by setting unusual application color
		set_work_space_color_warn();
		disp_status_bar_err(_("!!!! No UNDO info pushed !!!!"));
		progerr_printf("No UNDO info pushed for %s\n", func_id_done);
	}
	strcpy__(func_id_done, "");
}
#endif // ENABLE_DEBUG

//------------------------------------------------------------------------------
// aaaa				<== undo_min_line (line not-modified)
// BBBB				first line which will be modified
// CCCC				last line which will be modified
// dddd				<== undo_max_line (line not-modified)
PRIVATE be_line_t *undo_min_line = NULL;
PRIVATE be_line_t *undo_max_line = NULL;
PRIVATE int undo_lines = 0;
PRIVATE void save_region_to_undo_buf(void);

PRIVATE void undo_set_region(be_line_t *min_line, be_line_t *max_line, int cut_buf_lines);
PRIVATE void undo_adjust_max_line(void);
PRIVATE void undo_save_before_change(void);
// set region and save before change
void undo_set_region__save_before_change(be_line_t *min_line, be_line_t *max_line,
 int cut_buf_lines)
{
	undo_set_region(min_line, max_line, cut_buf_lines);
	undo_save_before_change();
}
PRIVATE void undo_set_region(be_line_t *min_line, be_line_t *max_line, int cut_buf_lines)
{
	undo_min_line = NODE_PREV(min_line);
	undo_max_line = NODE_NEXT(max_line);
	undo_lines = cut_buf_lines;

	undo_adjust_max_line();
}
PRIVATE void undo_adjust_max_line(void)
{
	char has_past_max_line = 0;

	be_line_t *line = NODE_NEXT(undo_min_line);
	for (int lines = 0 ; IS_NODE_INT(line); lines++) {
		if (line == undo_max_line) {
			has_past_max_line = 1;
		}
		if (lines >= undo_lines && has_past_max_line) {
			// more than undo_lines
			// or has_past_max_line
			break;
		}
		line = NODE_NEXT(line);
	}
	undo_max_line = line;	// adjust max line
}
// save undo info before change
PRIVATE void undo_save_before_change(void)
{
	save_region_to_undo_buf();
}

// save undo info after change
void undo_save_after_change(void)
{
	if (count_undo_bufs() % 2) {
		// count_undo_bufs() is odd.
		// The state before change was saved.
		// Save the state after change.
		save_region_to_undo_buf();	// save the state after change
		if (count_undo_bufs() >= 2) {
			// compare buffer after change and buffer before change
			if (buf_compare(UNDO_BUFS_TOP_NODE, NODE_NEXT(UNDO_BUFS_TOP_NODE)) == 0) {
				// not changed, pop two buffer (pushed "after" and "before")
				buf_free_node(pop_undo_buf());
				buf_free_node(pop_undo_buf());
			} else {
				set_cur_buf_modified();
			}
		}
	}
}
PRIVATE void save_region_to_undo_buf(void)
{
	push_undo_buf(get_epc_buf());
	for (be_line_t *line = NODE_NEXT(undo_min_line); line != undo_max_line;
	 line = NODE_NEXT(line)) {
		buf_append_line_to_bottom(UNDO_BUFS_TOP_NODE, line_create_copy(line));
		buf_set_cur_line(UNDO_BUFS_TOP_NODE, line);
	}
	flf_d_printf("CLBI(0): %d\n", BUFV0_CLBI(UNDO_BUFS_TOP_NODE));
	flf_d_printf("CLBI(1): %d\n", BUFV1_CLBI(UNDO_BUFS_TOP_NODE));
}

typedef enum /*undo0_redo1*/ {
	UNDO0,	// undo
	REDO1	// redo
} undo0_redo1_t;

PRIVATE int do_undo_redo_(undo0_redo1_t undo0_redo1);
PRIVATE be_line_t *restore_region_from_buffer(undo0_redo1_t undo0_redo1);
PRIVATE be_line_t *delete_region_in_buf(be_buf_t *buf);
PRIVATE be_line_t *insert_region_from_buf(be_line_t *edit_line, be_buf_t *buf);

int doe_undo(void)
{
	do_clear_mark_();
	if (count_undo_bufs() < 2) {
		disp_status_bar_warn(_("Undo-buffer empty !!"));
		return 0;
	}
	return do_undo_redo_(UNDO0);
}
int doe_redo(void)
{
	do_clear_mark_();
	if (count_redo_bufs() < 2) {
		disp_status_bar_warn(_("Redo-buffer empty !!"));
		return 0;
	}
	return do_undo_redo_(REDO1);
}
PRIVATE int do_undo_redo_(undo0_redo1_t undo0_redo1)
{
	set_cur_buf_modified();
	be_line_t *top_line = restore_region_from_buffer(undo0_redo1);
	post_cmd_processing(top_line, CURS_MOVE_HORIZ, LOCATE_CURS_NONE, UPDATE_SCRN_ALL_SOON);
	return 1;
}

// modification:
//	[edit-buf(before)]	[edit-buf(after)]	[undo-stack]	[redo-stack]
//	aaaa				aaaa				BBBB
//	bbbb				BBBB				bbbb
//	cccc				cccc
//
// undo:
//	[edit-buf(before)]	[edit-buf(after)]	[undo-stack]	[redo-stack]
//	aaaa				aaaa								bbbb
//	BBBB				bbbb								BBBB
//	cccc				cccc
//
// redo:
//	[edit-buf(before)]	[edit-buf(after)]	[undo-stack]	[redo-stack]
//	aaaa				aaaa				BBBB
//	bbbb				BBBB				bbbb
//	cccc				cccc
//
PRIVATE be_line_t *restore_region_from_buffer(undo0_redo1_t undo0_redo1)
{
	be_buf_t *buf_after;
	be_buf_t *buf_before;

	if (undo0_redo1 == UNDO0) {
		// undo (move undo information from undo-buf to redo-buf)
		buf_after = pop_undo_buf();
		push_redo_buf(buf_after);
		buf_before = pop_undo_buf();
		push_redo_buf(buf_before);
	} else {
		// redo (move undo information from redo-buf to undo-buf)
		buf_after = pop_redo_buf();
		push_undo_buf(buf_after);
		buf_before = pop_redo_buf();
		push_undo_buf(buf_before);
	}

	// delete modified lines
	be_line_t *edit_line = delete_region_in_buf(buf_after);
	be_line_t *top_line = NODE_PREV(edit_line);
	// insert unmodified lines
	insert_region_from_buf(edit_line, buf_before);
	return top_line;
}
PRIVATE be_line_t *delete_region_in_buf(be_buf_t *buf)
{
	// switch buffer to undo
	if (switch_epc_buf_by_file_path(buf->abs_path_) == 0) {
		progerr_printf("No such buffer: %s\n", buf->abs_path_);
		return CUR_EDIT_BUF_BOT_LINE;
	}
	be_line_t *edit_line = get_line_ptr_in_cur_buf_by_line_num(NODES_TOP_NODE(buf)->line_num);
	for (be_line_t *undo_line = NODES_TOP_NODE(buf); IS_NODE_INT(undo_line);
	 undo_line = NODE_NEXT(undo_line)) {
		edit_line = line_unlink_free(edit_line);	// delete line
	}
	return edit_line;
}
PRIVATE be_line_t *insert_region_from_buf(be_line_t *edit_line, be_buf_t *buf)
{
	if (switch_epc_buf_by_file_path(buf->abs_path_) == 0) {
		progerr_printf("No such buffer: %s\n", buf->abs_path_);
		return CUR_EDIT_BUF_BOT_LINE;
	}
	for (be_line_t *undo_line = NODES_TOP_NODE(buf); IS_NODE_INT(undo_line);
	 undo_line = NODE_NEXT(undo_line)) {
		line_insert(edit_line, line_create_copy(undo_line), INSERT_BEFORE);
	}
	// restore pointers
	EPCBVC_CL = get_line_ptr_in_cur_buf_by_line_num(NODES_TOP_NODE(buf)->line_num);
	EPCBVC_CLBI = MIN_MAX_(0, buf->buf_views[0].cur_line_byte_idx, line_strlen(EPCBVC_CL));
	return edit_line;
}

#ifdef ENABLE_DEBUG
void dump_undo_bufs_lines(void)
{
	buf_dump_bufs_lines(UNDO_BUFS_TOP_NODE, "undo-bufs");
}
void dump_redo_bufs_lines(void)
{
	buf_dump_bufs_lines(REDO_BUFS_TOP_NODE, "redo-bufs");
}
#endif // ENABLE_DEBUG

#endif // ENABLE_UNDO

// End of editorundo.c

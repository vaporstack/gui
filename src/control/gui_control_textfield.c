
//  gui_control_textfield.c
//  g_control_textfield
//
//  Created by Andrew Macfarlane on 04/08/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_control_textfield.h"

#include <drw/drw.h>
#include <stdlib.h>

#define TMP_TEXTFIELD_MAX 16

static void move_cursor(GuiComponent* cmp, int pos);
static void update(GuiComponent* cmp);
static void start(GuiComponent* cmp)
{

	cmp->interacting  = true;
	GTextField* field = cmp->data;

	field->len    = strlen(field->addr);
	field->cursor = field->len;
	if (!field->edit)
	{
		field->edit = calloc(TMP_TEXTFIELD_MAX, sizeof(char));
	}
	sprintf(field->edit, "%s", field->addr);

	printf("textfield START\n");
}

static void end(GuiComponent* cmp)
{
	printf("textfield END\n");

	GTextField* field = cmp->data;
	free(field->edit);

	cmp->interacting = false;
	r_input_delegate_pop();
}

static void delete (GuiComponent* cmp)
{
	printf("Delete!\n");
	move_cursor(cmp, -1);
	update(cmp);
}
static void fdelete(GuiComponent* cmp)
{
	printf("F Delete!\n");
	//move_cursor(cmp, -1);
	update(cmp);
}

static void move_cursor(GuiComponent* cmp, int pos)
{
	GTextField* field = cmp->data;

	if (pos == -2)
	{
		//	top
		printf("top\n");
		field->cursor = 0;
	}
	else if (pos == 2)
	{
		printf("bottom\n");
		field->cursor = field->len;
	}
	else if (pos == -1)
	{

		printf("left\n");
		field->cursor--;
	}
	else if (pos == 1)
	{

		printf("right\n");
		field->cursor++;
	}
	else
	{
		printf("UNknown input to %s\n", __func__);
	}
	if (field->cursor < 0)
		field->cursor = 0;
	if (field->cursor > field->len - 1)
		field->cursor = field->len - 1;
	printf("Cursor is now %lu\n", field->cursor);
}

static void update(GuiComponent* cmp)
{
	GTextField* field = cmp->data;
	memset(field->edit, '\0', strlen(field->addr));
	strncpy(field->edit, field->addr, field->cursor);
	printf("edit buffer is now: [%s]\n", field->edit);
}

static void commit(GuiComponent* cmp)
{
	GTextField* field = cmp->data;
	printf("commit!\n");
	strncpy(field->addr, field->edit, field->cursor);
	end(cmp);
	if (field->on_change)
		field->on_change(cmp);
}

static void cancel(GuiComponent* cmp)
{
	//GTextField* field = cmp->data;
	//free(field->edit);
	printf("cancel!!\n");
	end(cmp);
}

static void touch_cancel(struct InputDelegate* del, double x, double y, double r)
{

	end(del->parent);
}

static void touch_began(struct InputDelegate* del, double x, double y, double r)
{
}

static void touch_move(struct InputDelegate* del, double x, double y, double r)
{
}

static void touch_ended(struct InputDelegate* del, double x, double y, double r)
{

	end(del->parent);
}

static void tablet_down_rich(struct InputDelegate* del, double x, double y, int button, double pressure, double rotation, double tilt_x, double tilt_y, double tangential)
{
	touch_began(del, x, y, -1);
}

static void tablet_up_rich(struct InputDelegate* del, double x, double y, int button, double pressure, double rotation, double tilt_x, double tilt_y, double tangential)
{

	touch_ended(del, x, y, -1);
}

static void tablet_drag_rich(struct InputDelegate* del, double x, double y, int button, double pressure, double rotation, double tilt_x, double tilt_y, double tangential)
{

	touch_move(del, x, y, -1);
}

static void mouse_button(InputDelegate* del, int btn, int action, int mods)
{
	if (btn != 0)
		return;
	//if ( action == 1 )
	//	start(del->parent);

	//do_slider(del, app_settings., y, -1);
	if (action == 0)
	{
		start(del->parent);
	}
}

static void key(struct InputDelegate* del, int key, int scan, int action, int mods)
{
#ifndef RPLATFORM_IOS
	printf("%d %d\n", key, action);
	if (action == 1)
		return;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		cancel(del->parent);
		break;
	case GLFW_KEY_ENTER:
	case GLFW_KEY_KP_ENTER:
		commit(del->parent);
		break;
	case GLFW_KEY_LEFT:
		move_cursor(del->parent, -1);
		break;
	case GLFW_KEY_RIGHT:
		move_cursor(del->parent, 1);
		break;
	case GLFW_KEY_UP:
		move_cursor(del->parent, -2);
		break;
	case GLFW_KEY_DOWN:
		move_cursor(del->parent, 2);
		break;
	case GLFW_KEY_BACKSPACE:
		delete (del->parent);
		break;
	case GLFW_KEY_DELETE:
		fdelete(del->parent);
		break;
	default:
		break;
	}
#endif
}

static void charcb(struct InputDelegate* del, unsigned int c)
{
	printf("%c!~\n", c);
	GuiComponent* cmp   = del->parent;
	GTextField*   field = cmp->data;
	if (!field->edit)
		return;
	field->edit[field->cursor] = c;
	field->cursor++;
}

static void mouse_motion(InputDelegate* del, double x, double y)
{
}

static int click(GuiComponent* cmp, double d)
{
	return true;
}

static void setup_delegate(InputDelegate* del)
{
	del->mouse_button     = mouse_button;
	del->mouse_motion     = mouse_motion;
	del->touch_move       = touch_move;
	del->touch_began      = touch_began;
	del->touch_cancel     = touch_cancel;
	del->touch_ended      = touch_ended;
	del->tablet_down_rich = tablet_down_rich;
	del->tablet_up_rich   = tablet_up_rich;
	del->tablet_drag_rich = tablet_drag_rich;
	del->supports_handoff = true;
	del->char_cb	  = charcb;
	del->key	      = key;
	del->name	     = "a textfield delegate";
}

static void draw(GuiComponent* cmp)
{

	gui_component_draw(cmp);
	GTextField* field = cmp->data;
	if (field->addr)
	{
		drw_push();
		drw_translate(cmp->bounds.pos.x + cmp->bounds.size.x * .5, cmp->bounds.pos.y + cmp->bounds.size.y * .5, 0);

		//if ( cmp->interacting )
		{
		}

		drw_type_set_align(DRW_TYPE_ALIGN_H_CENTER, DRW_TYPE_ALIGN_V_CENTER);
		if (!cmp->interacting)
		{
			drw_push();
			drw_scale_u(4);
			drw_type_draw(field->addr);
			drw_pop();
		}
		else
		{
			drw_push();
			drw_scale_u(4);
			char* buf = calloc(field->cursor, sizeof(char));
			strncpy(buf, field->edit, field->cursor);
			drw_type_draw(buf);

			float* box = calloc(6, sizeof(float));
			;
			drw_type_get_bbox(buf, field->cursor, box);
			double wx = box[3] - box[0];
			double wy = box[4] - box[1];

			double cur = field->cursor;
			double w   = drw_type_size_real_get();
			double pos = w * cur;

			drw_rect(pos, 0, wx / cur, wy);
			free(buf);
			drw_pop();
		}
		drw_pop();
	}
}

static void destroy(GuiComponent* cmp)
{
	//	todo implement
}

GuiComponent* g_control_textfield_create(void* gui, char* hnd)
{
	GuiComponent* cmp = gui_component_create(gui);

	GTextField* field = calloc(1, sizeof(GTextField));
	field->on_change  = NULL;

	cmp->data = field;

	field->addr = hnd;

	//double sz = gui_size
	cmp->draw	  = draw;
	cmp->bounds.size.x = cmp->bounds.size.y * 4;
	setup_delegate(&cmp->delegate);
	return cmp;
}

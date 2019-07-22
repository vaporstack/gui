//
//  gui_ios_dpad_nav.c
//  gui
//
//  Created by vs on 5/13/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_ios_dpad_nav.h"
#include <drw/drw.h>

static void begin(GuiComponent* cmp, double x, double y)
{
	cmp->interacting = true;
	GNavPad* pad     = cmp->data;
	pad->start.x = pad->current.x = x;
	pad->start.y = pad->current.y = y;

	//	if ( info->on_begin)
	//		info->on_begin(cmp, -1);
}
static void move(GuiComponent* cmp, double x, double y)
{
	GNavPad* pad = cmp->data;
	pad->current.x = x;
	pad->current.y = y;
}
static void update(GuiComponent* cmp)
{
	printf(".");
}

static void end(GuiComponent* cmp, double x, double y)
{

	cmp->interacting = false;
	r_input_delegate_pop();
}

static void touch_cancel(struct InputDelegate* del, double x, double y, double r, void* ptr)
{
	end(del->parent, x, y);
}

static void touch_began(struct InputDelegate* del, double x, double y, double r, void* ptr)
{
	begin(del->parent, x, y);
}

static void touch_move(struct InputDelegate* del, double x, double y, double r, void* ptr)
{
	move(del->parent, x, y);
}

static void touch_ended(struct InputDelegate* del, double x, double y, double r, void* ptr)
{

	end(del->parent, x, y);
}

static void mouse_button(InputDelegate* del, int btn, int action, int mods)
{
}

static void mouse_motion(InputDelegate* del, double xEVer, double y)
{
}

static void draw(GuiComponent* cmp)
{
	gui_component_draw(cmp);
	drw_push();

	drw_translate(cmp->bounds.pos.x, cmp->bounds.pos.y, 0);
	drw_circle(cmp->bounds.size.x * .5);
	drw_pop();
	if (!cmp->interacting)
		return;

	GNavPad* pad = cmp->data;
	drw_line_cp(pad->start, pad->current);

	//drw_line(cmp->bounds.pos.x, cmp->bounds.pos.y, )
}

static void layout(GuiComponent* cmp)
{
	double sz = gui_ui_unit;
	gui_component_size(cmp, sz * 2, sz * 2);
}

static void setup_delegate(InputDelegate* del)
{
	del->mouse_button = mouse_button;
	del->mouse_motion = mouse_motion;
	del->touch_move   = touch_move;
	del->touch_began  = touch_began;
	del->touch_cancel = touch_cancel;
	del->touch_ended  = touch_ended;
	//	del->tablet_down_rich = tablet_down_rich;
	//	del->tablet_up_rich   = tablet_up_rich;
	//	del->tablet_drag_rich = tablet_drag_rich;
	del->supports_handoff = false;
	del->name	     = "dpad nav";
}
static void destroy(GuiComponent* cmp)
{
	GNavPad* np = cmp->data;
	free(np);
}

GuiComponent* gui_ios_dpad_nav_create(Gui* gui, navpad_cb fn)
{
	GuiComponent* cmp = gui_component_create(gui);
	setup_delegate(&cmp->delegate);
	cmp->name = "dpad_nav";
	
	GNavPad* np  = calloc(1, sizeof(GNavPad));
	np->callback = fn;
	cmp->data    = np;
	cmp->update  = update;
	cmp->destroy = destroy;
	cmp->draw    = draw;
	cmp->layout = layout;
	return cmp;
}

//
//  gui_ios_dpad.c
//  gui
//
//  Created by vs on 5/11/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_ios_dpad.h"

#pragma mark input
#include <drw/drw.h>

#include "gui_ios_dpad_button.h"

static void begin(GuiComponent* cmp)
{
	cmp->interacting = true;
	//	if ( info->on_begin)
	//		info->on_begin(cmp, -1);
}

static void end(GuiComponent* cmp)
{

	cmp->interacting = false;
	r_input_delegate_pop();
}

static void touch_cancel(struct InputDelegate* del, double x, double y, double r, void* ptr)
{
	end(del->parent);
}

static void touch_began(struct InputDelegate* del, double x, double y, double r, void* ptr)
{
	begin(del->parent);
}

static void touch_move(struct InputDelegate* del, double x, double y, double r, void* ptr)
{
}

static void touch_ended(struct InputDelegate* del, double x, double y, double r, void* ptr)
{

	end(del->parent);
}

static void tablet_down_rich(struct InputDelegate* del, double x, double y, int button, double pressure, double rotation, double tilt_x, double tilt_y, double tangential)
{
	//begin(del->parent);
	touch_began(del, x, y, -1, NULL);
}

static void tablet_up_rich(struct InputDelegate* del, double x, double y, int button, double pressure, double rotation, double tilt_x, double tilt_y, double tangential)
{
	touch_ended(del, x, y, -1, NULL);
}

static void tablet_drag_rich(struct InputDelegate* del, double x, double y, int button, double pressure, double rotation, double tilt_x, double tilt_y, double tangential)
{

	touch_move(del, x, y, -1, NULL);
}

static void mouse_button(InputDelegate* del, int btn, int action, int mods)
{
}

static void mouse_motion(InputDelegate* del, double xEVer, double y)
{
}

#pragma mark logic

static void draw(GuiComponent* cmp)
{
	drw_color(1,1,0,1);
	gui_component_draw(cmp);
}

static void layout(GuiComponent* cmp)
{
	double w = *gui_fb_w;
	double h = *gui_fb_h;

	
	double x = w * -.333;
	double y = h * -.333;
	
	x += cmp->bounds.size.x;
	y += cmp->bounds.size.y;
	
	gui_component_set(cmp, x, y);
}

static void update(GuiComponent* cmp)
{
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
	del->name	     = "dpad delegate";
}

GuiComponent* gui_ios_dpad_create(Gui* gui)
{
	GuiComponent* dpad = gui_component_create(gui);
	dpad->draw	 = draw;
	dpad->layout       = layout;
	dpad->update       = update;

	GuiComponent* left  = gui_ios_dpad_button_create(gui);
	GuiComponent* right = gui_ios_dpad_button_create(gui);

	gui_component_child_add(dpad, left);
	gui_component_child_add(dpad, right);
	setup_delegate(&dpad->delegate);

	return dpad;
}

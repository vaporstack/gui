//
//  gui_control_encoder.c
//  gui
//
//  Created by vs on 7/25/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_control_encoder.h"

#include <drw/drw.h>
#include <gui/gui.h>

#pragma mark logic

static void begin(GuiComponent* cmp, double x, double y)
{
	printf("encoder BEGIN %f %f\n", x, y);
	
}

static void update(GuiComponent* cmp, double x, double y)
{
}

static void end(GuiComponent* cmp, double x, double y)
{
	printf("encoder END %f %f\n", x, y);

}

static void layout(GuiComponent* cmp)
{
}

#pragma mark input

#pragma mark desktop

static void mouse_motion(struct InputDelegate* delegate, double x, double y)
{
}

static void mouse_button(struct InputDelegate* delegate, int button, int action,
			 int mods)
{
	printf("!");
}

static void key(struct InputDelegate* delegate, int key, int scan, int action, int mods)
{
}

static void char_cb(struct InputDelegate* delegate, unsigned c)
{
}

#pragma mark touch

static void touch_cancel(struct InputDelegate* delegate, double x, double y, double r)
{
}

static void touch_began(struct InputDelegate* delegate, double x, double y, double r)
{
	begin(delegate->parent, x, y);
}

static void touch_ended(struct InputDelegate* delegate, double x, double y, double r)
{
}

static void touch_move(struct InputDelegate* delegate, double x, double y,
		       double r)
{
}

#pragma mark tablet

static void tablet_proximity(bool v)
{
}

static void tablet_motion_rich(struct InputDelegate* delegate, double x,
			       double y, int button, double pressure,
			       double rotation, double tilt_x, double tilt_y,
			       double tangential)
{
}

static void tablet_drag_rich(struct InputDelegate* delegate, double x, double y,
			     int button, double pressure, double rotation,
			     double tilt_x, double tilt_y, double tangential)
{
}

static void tablet_down_rich(struct InputDelegate* delegate, double x, double y,
			     int button, double pressure, double rotation,
			     double tilt_x, double tilt_y, double tangential)
{
}

static void tablet_up_rich(struct InputDelegate* delegate, double x, double y,
			   int button, double pressure, double rotation,
			   double tilt_x, double tilt_y, double tangential)
{
}

#pragma mark core

static void setup_delegate(InputDelegate* del)
{
	del->mouse_button       = mouse_button;
	del->mouse_motion       = mouse_motion;
	del->touch_move		= touch_move;
	del->touch_began	= touch_began;
	del->touch_cancel       = touch_cancel;
	del->touch_ended	= touch_ended;
	del->tablet_motion_rich = tablet_motion_rich;
	del->tablet_proximity   = tablet_proximity;
	del->tablet_down_rich   = tablet_down_rich;
	del->tablet_up_rich     = tablet_up_rich;
	del->tablet_drag_rich   = tablet_drag_rich;
	del->supports_handoff   = true;
	del->char_cb		= char_cb;
	del->key		= key;
	del->name		= "a input boilerplate";
}

static void draw(GuiComponent* cmp)
{

	gui_component_draw(cmp);
	drw_push();
	drw_translate2f(cmp->bounds.pos.x + cmp->bounds.size.y * .5, cmp->bounds.pos.y + cmp->bounds.size.y * .5);
	drw_circle(cmp->bounds.size.x * PHI_I * .5);
	drw_pop();
}

GuiComponent* gui_control_encoder_create(Gui* gui)
{
	GuiComponent* cmp = gui_component_create(gui);

	cmp->draw = draw;
	return cmp;
}

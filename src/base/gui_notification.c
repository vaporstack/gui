//
//  gui_notification.c
//  gui
//
//  Created by vs on 3/22/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_notification.h"

#include "../control/gui_control_label.h"
#include <drw/drw.h>
#include <r4/src/core/r_time.h>

static double calculate_delta(GuiComponent* cmp)
{
	GNotification* info = cmp->data;
	if (!info)
		return -1;

	double now = r_time_peek();
	double d   = now - info->birth;
	d *= .25;
	d = 1 - d;

	//	notifications are only a wrapper for dismissing and such so passthrough here
	//if ( d < 0 )
	//	d = .1;
	return d;
}
static void update(GuiComponent* cmp)
{

	//double d = now - info->birth;
	double d = calculate_delta(cmp);
	if (d < 0)
		cmp->destroy(cmp);
	//if ( d > 4 )
	{
		//	cmp->destroy(cmp);
	}
	//printf("%.2f\n", d);
}

static void do_slider(InputDelegate* del, double x, double y, double r)
{
}

static void start(GuiComponent* cmp)
{
	cmp->interacting = true;
}

static void end(GuiComponent* cmp)
{
	//	I am the notification. I destroy my child and then remove myself from my
	//	parent and then finally destroy myself.

	r_input_delegate_pop();
	cmp->destroy(cmp);
}

static void touch_cancel(struct InputDelegate* del, double x, double y, double r)
{
	end(del->parent);
}

static void touch_began(struct InputDelegate* del, double x, double y, double r)
{
	do_slider(del, x, y, r);
}

static void touch_move(struct InputDelegate* del, double x, double y, double r)
{
	do_slider(del, x, y, r);
}

static void touch_ended(struct InputDelegate* del, double x, double y, double r)
{
	do_slider(del, x, y, r);
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
	if (btn == 0 && action == 0)
	{
		end(del->parent);
	}
}

static void mouse_motion(InputDelegate* del, double x, double y)
{
	do_slider(del, x, y, -1);
}

static int click(GuiComponent* cmp, double d)
{

	return 0;
}

static void draw(GuiComponent* cmp)
{
	GNotification* info = cmp->data;
	if (!info)
		return;

	double   d = calculate_delta(cmp);
	RColor16 c = r_app_color_get_bg();
	drw_color(c.r, c.g, c.b, d);
	//drw_color_c16( r_app_color_get_bg() );
	drw_fill_set(true);
	//drw_alpha(d);
	drw_alpha_mult(d);

	drw_rect_r(cmp->bounds);
	drw_fill_pop();
	drw_color_pop();
	//drw_set_line_width(2);
	drw_alpha_mult(d);
	drw_rect_r(cmp->bounds);
	//drw_set_line_width(1);
	drw_alpha_mult_pop();
	//gui_component_draw(cmp);

	//GNotification* info = cmp->data;
	GuiComponent* sub = info->sub;

	(sub->draw) ? sub->draw(sub) : gui_component_draw(sub);
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
	del->name	     = "a notification delegate";
}

static void destroy(GuiComponent* cmp)
{
	GNotification* info = cmp->data;
	if (!info)
	{
		printf("ack\n");
	}
	else
	{
		GuiComponent* sub = info->sub;
		if (!sub)
		{
			printf("ack\n");
		}
		else
		{
			sub->destroy(sub);
		}
		free(info);
	}

	cmp->data = NULL;

	GuiComponent* par = cmp->parent;

	gui_component_child_remove(par, cmp);

	//free(cmp);
}

GuiComponent* gui_notification_create(Gui* gui, const char* text)
{
	GuiComponent* cmp = gui_component_create(gui);
	setup_delegate(&cmp->delegate);

	double	sz    = gui_default_ui(gui);
	GuiComponent* notif = gui_control_label_create(gui, text);
	float*	buf   = calloc(6, sizeof(float));

	drw_type_get_bbox(text, strlen(text), buf);
	double bw	    = buf[3] - buf[0];
	double bh	    = buf[4] - buf[1];
	notif->bounds.size.x = bw + sz;
	cmp->bounds	  = notif->bounds;
	GNotification* info  = calloc(1, sizeof(GNotification));
	info->sub	    = notif;
	info->birth	  = r_time_peek();
	cmp->data	    = info;
	cmp->name	    = "notification";
	cmp->update	  = update;
	cmp->draw	    = draw;
	cmp->destroy	 = destroy;

	return cmp;
}

GuiComponent* gui_notification_create_custom(Gui* gui, GuiComponent* sub)
{
	GuiComponent*  cmp  = gui_component_create(gui);
	GNotification* info = calloc(1, sizeof(GNotification));
	info->sub	   = sub;
	info->birth	 = r_time_peek();
	cmp->data	   = info;

	cmp->draw   = draw;
	cmp->bounds = sub->bounds;
	cmp->name   = "notification";
	setup_delegate(&cmp->delegate);
	cmp->update  = update;
	cmp->destroy = destroy;

	return cmp;
}

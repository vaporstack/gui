//
//  gui_button.c
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

//#include "gui_button.h"

#include "../base/gui_component.h"
#include <stdlib.h>

#include <drw/drw.h>

#include "../base/g_gui.h"
#include <gui/gui.h>

#pragma mark centralized

static double calculate_position(GuiComponent* cmp, double x, double y )
{
	double w = cmp->bounds.size.x;
	double loc = (x - cmp->bounds.pos.x) / w;
	if ( loc < 0 ) loc = 0;
	if ( loc > 1 ) loc = 1;
	return loc;
}

static void do_slider(InputDelegate* del, double x, double y, double r)
{
	
	GuiComponent* cmp = del->parent;
	GuiSliderD* attr = cmp->data;
	cmp->interacting = true;
	
	if ( !attr->function )
	{
		gui_log("Bad pathway (no function) %s", __func__);
		return;
	}
	
	double loc = calculate_position(cmp, x, y);
	attr->function(cmp, loc);
}


static void start(GuiComponent* cmp )
{
	
	
	
}

static void update(GuiComponent* cmp )
{
	
}

static void end(GuiComponent* cmp )
{
	
	//GuiComponent* cmp = del->parent;
	cmp->interacting = false;
	r_input_delegate_pop();
	
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


static void mouse_button(InputDelegate* del, int btn, int action, int mods )
{
	if ( btn == 0 && action == 0 )
	{
		end(del->parent);
	}
}


static void mouse_motion(InputDelegate* del, double x, double y )
{
	do_slider(del, x, y, -1);
}

static int click(GuiComponent* cmp, double d)
{

	GuiSliderD* attr   = cmp->data;
	double*     target = attr->target;
	if ( !d )
	{
		printf("Can't set, no data!\n");
		return 7;
	}
	*target		   = d;

	return 0;
}

static void layout(struct GuiComponent* cmp)
{

	GuiComponent* gui = cmp->parent;

	double w = gui->bounds.size.x;
	double h = gui->bounds.size.y;
	
	double x = 0;

	double y = (h * -.5);// + cmp->bounds.size.y;

	switch (cmp->orientation.horizontal) {
		case -1:
			x = w * -.5;
			break;
		case 0:
			x = 0;
			break;
		case 1:
			 x = w * .5 - cmp->bounds.size.x;
			break;
			
		default:
			break;
	}
	x += cmp->offset.x;
	y += cmp->offset.y;
	gui_component_set(cmp, x, y);
}

static void destroy(GuiComponent* cmp)
{
	GuiSliderD* info = cmp->data;
	free(info);
}

void g_control_slider_draw(struct GuiComponent* cmp, struct GuiComponent* gui)
{
	gui_component_draw(cmp, gui);
	double margin = cmp->bounds.size.y * .5;
	GuiSliderD* attr = cmp->data;
	double*     d    = attr->target;

	drw_push();
	drw_translate2f(cmp->bounds.pos.x, cmp->bounds.pos.y);
	drw_translate2f(0, cmp->bounds.size.y * .5);
	drw_line(margin, 0, cmp->bounds.size.x - margin, 0);
	if ( !d)
	{
		printf("Slider created with NULL data\n");
		drw_pop();
		return;;
		
	}
	drw_push();
	drw_translate2f(margin + (*d * (cmp->bounds.size.x - margin * 2)), 0);
	double v = gui_default_ui(cmp->root) * PHI * .25;

	drw_circle(v );
	drw_pop();
	if ( cmp->interacting )
	{
		drw_push();
		drw_translate2f(cmp->bounds.size.x * .5, 0);
		drw_circle(v);
		drw_type_set_align(DRW_TYPE_ALIGN_H_CENTER, DRW_TYPE_ALIGN_V_CENTER);
		drw_type_draw("%.2f", *d);
		drw_pop();
	}
	drw_pop();
	
}

static void setup_delegate(InputDelegate* del )
{
	del->mouse_button = mouse_button;
	del->mouse_motion = mouse_motion;
	del->touch_move = touch_move;
	del->touch_began = touch_began;
	del->touch_cancel = touch_cancel;
	del->touch_ended = touch_ended;
	del->tablet_down_rich = tablet_down_rich;
	del->tablet_up_rich = tablet_up_rich;
	del->tablet_drag_rich = tablet_drag_rich;
	del->supports_handoff = true;
	del->name = "a slider delegate";
	
}

GuiComponent* g_control_slider_create_d(double* data, void* guidata)
{
	GuiComponent* cmp    = gui_component_create(guidata);
	GuiSliderD*   slider = calloc(1, sizeof(GuiSliderD));
	slider->function     = click;
	slider->target       = data;
	cmp->data	    = slider;
	cmp->draw	    = g_control_slider_draw;
	cmp->update	  = update;
	cmp->layout	  = layout;
	cmp->name	    = "an_unnamed_slider";
	cmp->bounds.size.x *= 3;
	
	cmp->delegate.name = "slider delegate";
	cmp->delegate.parent = cmp;
	setup_delegate(&cmp->delegate);
	cmp->destroy = destroy;
	
	return cmp;
}

GuiComponent* g_control_slider_create_cb(double* addr, my_slider_func cb, void* data)
{
	GuiComponent* cmp    = gui_component_create(data);
	GuiSliderD*   slider = calloc(1, sizeof(GuiSliderD));
	slider->function     = cb;
	slider->target       = addr;
	cmp->destroy = destroy;

	cmp->data	    = slider;
	cmp->draw	    = g_control_slider_draw;
	cmp->update	  = update;
	cmp->layout	  = layout;
	cmp->name	    = "an_unnamed_slider";
	cmp->bounds.size.x *= 3;

	setup_delegate(&cmp->delegate);

	
	return cmp;
}

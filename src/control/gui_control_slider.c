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

static void update(GuiComponent* cmp)
{
	if (cmp->parent)
		if (cmp->parent->update)
			cmp->parent->update(cmp->parent);
}

static double calculate_position(GuiComponent* cmp, double x, double y)
{
	GuiSliderD* attr = cmp->data;
	double      w    = cmp->bounds.size.x;
	double      loc  = (x - cmp->bounds.pos.x) / w;
	attr->pos	= loc;

	if (loc < 0)
		loc = 0;
	if (loc > 1)
		loc = 1;

	/* with that done, we move onto the task of calculating what that position is in the range

	 if (loc < attr->lower)
		loc = attr->lower;
	if (loc > attr->upper)
		loc = attr->upper;
	*/
	return loc;
}

static double map(double Input, double InputLow, double InputHigh, double OutputLow, double OutputHigh)
{
	return ((Input - InputLow) / (InputHigh - InputLow)) * (OutputHigh - OutputLow) + OutputLow;
}

static void do_slider(InputDelegate* del, double x, double y, double r)
{

	GuiComponent* cmp  = del->parent;
	GuiSliderD*   attr = cmp->data;
	cmp->interacting   = true;

	if (!attr->function)
	{
		gui_log("Bad pathway (no function) %s", __func__);
		return;
	}

	attr->pos       = calculate_position(cmp, x, y);
	*(attr->target) = map(attr->pos, 0, 1, attr->lower, attr->upper);

	// = v
	//v -= attr->lower;
	//double range = attr->upper - attr->lower;
	//v *= range;

	attr->function(cmp, *attr->target);
	update(cmp);
}

static void start(GuiComponent* cmp)
{
}

static void end(GuiComponent* cmp)
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

static void mouse_button(InputDelegate* del, int btn, int action, int mods)
{
	if (btn > 0)
		return;

	if (action == 1)
	{
		do_slider(del, *gui_cursor_x, *gui_cursor_y, -1);
	}
	else
	{
		end(del->parent);
		//do_slider(del, app_settings, <#double y#>, <#double r#>)
	}
}

static void mouse_motion(InputDelegate* del, double x, double y)
{
	do_slider(del, x, y, -1);
}

static int click(GuiComponent* cmp, double d)
{

	GuiSliderD* attr   = cmp->data;
	double*     target = attr->target;
	if (!d)
	{
		printf("Can't set, no data!\n");
		return 7;
	}
	*target = d;

	return 0;
}

static void layout(struct GuiComponent* cmp)
{

	GuiComponent* gui = cmp->parent;

	double w = gui->bounds.size.x;
	double h = gui->bounds.size.y;

	GuiSliderD* info = cmp->data;

	double sz = gui_default_ui(cmp->root);
	double sw, sh;
	if (info->vertical)
	{

		sw = sz;
		sh = sz * 3;
	}
	else
	{
		sw = sz * 3;
		sh = sz;
	}

	//cmp->bounds.size.x = sw;
	//..cmp->bounds.size.y = sh;

	gui_component_size(cmp, sw, sh);
	double x = 0;
	double y = (h * -.5); // + cmp->bounds.size.y;

	switch (cmp->orientation.horizontal)
	{
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

static void draw_horizontal(GuiComponent* cmp)
{
	//GuiSliderD* info = cmp->data;

	GuiSliderD* attr   = cmp->data;
	double      margin = cmp->bounds.size.y * .5;
	double*     d      = attr->target;

	double p = attr->pos;
	drw_push();
	drw_translate2f(cmp->bounds.pos.x, cmp->bounds.pos.y);
	drw_translate2f(0, cmp->bounds.size.y * .5);
	drw_line(margin, 0, cmp->bounds.size.x - margin, 0);
	if (!d)
	{
		printf("Slider created with NULL data\n");
		drw_pop();
		return;
		;
	}
	drw_push();
	drw_translate2f(margin + (p * (cmp->bounds.size.x - margin * 2)), 0);
	double v = gui_default_ui(cmp->root) * PHI * .25;

	RColor16 c = r_app_color_get_bg();
	drw_color_c16(c);
	drw_fill_set(true);
	drw_circle(v);
	drw_fill_pop();
	drw_color_pop();

	drw_circle(v);
	drw_pop();
	if (cmp->interacting)
	{
		drw_push();
		drw_translate2f(cmp->bounds.size.x * .5, 0);
		drw_color_c16(r_app_color_get_bg());
		drw_fill_set(true);
		drw_alpha(.75);
		drw_circle(v);
		drw_fill_pop();
		drw_alpha_pop();
		drw_color_pop();

		drw_circle(v);
		drw_type_set_align(DRW_TYPE_ALIGN_H_CENTER, DRW_TYPE_ALIGN_V_CENTER);
		drw_type_draw("%.2f", *d);
		drw_pop();
	}
	drw_pop();
}

static void draw_vertical(GuiComponent* cmp)
{
	GuiSliderD* attr   = cmp->data;
	double      margin = cmp->bounds.size.y * .5;
	double*     d      = attr->target;

	drw_push();
	drw_translate2f(cmp->bounds.pos.x, cmp->bounds.pos.y);
	drw_translate2f(0, cmp->bounds.size.y * .5);
	drw_line(margin, 0, cmp->bounds.size.x - margin, 0);
	if (!d)
	{
		printf("Slider created with NULL data\n");
		drw_pop();
		return;
		;
	}
	drw_push();
	drw_translate2f(margin + (*d * (cmp->bounds.size.x - margin * 2)), 0);
	double v = gui_default_ui(cmp->root) * PHI * .25;

	drw_circle(v);
	drw_pop();
	if (cmp->interacting)
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

void gui_control_slider_draw(struct GuiComponent* cmp)
{
	gui_component_draw(cmp);
	drw_circle_precision_set(16);
	GuiSliderD* attr = cmp->data;
	if (attr->vertical)
	{
		draw_horizontal(cmp);
	}
	else
	{
		draw_horizontal(cmp);
	}
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
	del->name	     = "a slider delegate";
}

GuiComponent* gui_control_slider_create_d(double* data, void* guidata)
{
	GuiComponent* cmp    = gui_component_create(guidata);
	GuiSliderD*   slider = calloc(1, sizeof(GuiSliderD));
	slider->function     = click;
	slider->target       = data;
	slider->vertical     = false;
	slider->lower	= 0;
	slider->upper	= 1;
	cmp->data	    = slider;
	cmp->draw	    = gui_control_slider_draw;
	cmp->update	  = update;
	cmp->layout	  = layout;
	cmp->name	    = "an_unnamed_slider";
	cmp->bounds.size.x *= 3;

	cmp->delegate.name   = "slider delegate";
	cmp->delegate.parent = cmp;
	setup_delegate(&cmp->delegate);
	cmp->destroy = destroy;

	return cmp;
}

GuiComponent* gui_control_slider_create_cb(double* addr, my_slider_func cb, void* data)
{
	GuiComponent* cmp    = gui_component_create(data);
	GuiSliderD*   slider = calloc(1, sizeof(GuiSliderD));
	slider->function     = cb;
	slider->target       = addr;
	slider->vertical     = false;
	slider->lower	= 0;
	slider->upper	= 1;
	cmp->destroy	 = destroy;

	cmp->data   = slider;
	cmp->draw   = gui_control_slider_draw;
	cmp->update = update;
	cmp->layout = layout;
	cmp->name   = "an_unnamed_slider";
	cmp->bounds.size.x *= 3;

	setup_delegate(&cmp->delegate);

	return cmp;
}

/*
 *	if you overwrote any of the slider defaults, make sure pos and such are correct by calling this
 */

void gui_control_slider_setup(GuiComponent* cmp)
{
	GuiSliderD* info = cmp->data;

	double* target = info->target;
	info->pos      = map(*target, info->lower, info->upper, 0, 1);

	printf("%f\n", *target);
}


//  gui_comp_rline.c
//  gui_comp_rline
//
//  Created by Andrew Macfarlane on 11/15/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_comp_rline.h"

#include <drw/drw.h>
//#include "../wash_common.h"

//	TODO: REMOVE THIS.  GUI should NOT know about the host environment
#include <r4/r4.h>

extern AppSettings app_settings;

static void draw(struct GuiComponent* comp, struct GuiComponent* gui)
{
	//drw_color(1, 0, 1, 1);
	GuiCompRLine* data = (GuiCompRLine*)comp->data;

	drw_line_r(data->hnd.src);
	drw_push();
	drw_translate2f(data->center.x, data->center.y);
	drw_circle_precision_set(20);
	double alpha = 0;
	if (comp->focus)
	{
		alpha = 1;
	}
	else
	{
		alpha = .5;
	}

	drw_color(1, 1, 1, alpha);
	double r = data->radius;
	r *= (1. / app_settings.scale_retina);
	double s = app_settings.scale_retina;
	// printf("%f\n", r);
	drw_circle(r);

	drw_pop();
	// printf("hc ret: %d\n", HC_RET);
	// printf(" ret: %f\n", app_settings.scale_retina);
}

static bool find_focus(GuiComponent* comp, double x, double y)
{
	GuiCompRLine* rec      = (GuiCompRLine*)comp->data;
	RPoint	c	= rec->center;
	bool	  focussed = (dist2d(c.x, c.y, x, y) < rec->radius);
	comp->focus	    = focussed;
	return focussed;
}

GuiComponent* gui_comp_rline_create(void* gui, RLineHnd hnd)
{
	GuiComponent* comp = gui_component_create(gui);
	GuiCompRLine* rec  = calloc(1, sizeof(GuiCompRLine));

	RPoint c    = r_line_find_center_mean(hnd.src);
	rec->center = c;

	RLine* l     = hnd.src;
	RPoint first = l->data[0];

	double delta = dist2d(c.x, c.y, first.x, first.y);
	for (int i = 0; i < l->num; i++)
	{
		RPoint p = l->data[i];
		double d = dist2d(c.x, c.y, p.x, p.y);
		if (d > delta)
		{
			delta = d;
		}
	}
	rec->radius = delta;

	rec->hnd	 = hnd;
	comp->data       = rec;
	comp->draw       = draw;
	comp->find_focus = find_focus;
	comp->name       = "rline3 manipulator";
	return comp;
}

void gui_comp_rline_destroy(GuiComponent* comp)
{

	GuiCompRLine* data = (GuiCompRLine*)comp->data;
	free(data);
	free(comp);
}

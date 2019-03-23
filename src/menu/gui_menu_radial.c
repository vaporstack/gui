
//  gui_menu_radial.c
//  gui_menu_radial
//
//  Created by Andrew Macfarlane on 06/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_menu_radial.h"
//	TODO:
//	remove rendering from here, has no biz

//#include "../render/r_render.h"

#include <r4/r4.h>

extern AppSettings app_settings;

#include "r4/src/core/r_math.h"

#include <stdio.h>
#include <stdlib.h>

#include "r4/src/app/r_app.h"
#include <drw/drw.h>

// extern AppSettings app_settings;
// extern double _gui_scale_retina;
// extern double _gui_w;
// extern double _gui_h;

void _update(GuiComponent* comp)
{
	GuiMenuRadial* cmp = comp->data;

	// GuiComponent* ptr = (GuiComponent*) comp;
	if (comp->enabled)
	{
		double dx = cmp->max_radius - cmp->cur_radius;
		cmp->cur_radius += dx * .3;
		if (dist2d(cmp->mx, cmp->my, cmp->x, cmp->y) <
		    cmp->cur_radius * app_settings.scale_retina)
		{
			comp->hover = true;
			// printf("within!\n");
		}
		else
		{
			comp->hover = false;

			printf("not within. (return)\n");
			InputDelegate* del = &comp->delegate;
			del->control_return(del);
		}
		if (dist2d(cmp->x, cmp->y, cmp->x, cmp->y) <
		    cmp->ina_radius * app_settings.scale_retina)
		{
			comp->hover = false;
		}
	}
	else
	{
		cmp->cur_radius -= cmp->cur_radius * .7;
		if (cmp->cur_radius < .001)
			cmp->cur_radius = 0;
		if (cmp->cur_radius == 0)
			comp->hidden = true;
	}
	cmp->ina_radius = cmp->cur_radius * .5;

	if (!comp->hover)
	{
		cmp->current_selection = -1;
	}
	if (comp->hover)
	{
		double inc = (M_PI * 2) / cmp->num_items;
		// drw_color(0,1,1,1);
		for (int i = 0; i < cmp->num_items; ++i)
		{

			double ax = cmp->x;
			double ay = cmp->y;
			double bx = ax + (cos(i * inc) * cmp->max_radius * 2 *
					  app_settings.scale_retina);
			double by = ay + (sin(i * inc) * cmp->max_radius * 2 *
					  app_settings.scale_retina);

			double cx = ax + (cos((i + 1) * inc) * cmp->max_radius *
					  2 * app_settings.scale_retina);
			double cy = ay + (sin((i + 1) * inc) * cmp->max_radius *
					  2 * app_settings.scale_retina);
			// drw_line(ax,ay,bx,by);
			if (tricheck(ax, ay, bx, by, cx, cy, cmp->mx,
				     cmp->my))
			{
				if (cmp->current_selection != i)
				{
					printf("Selection changed, new one is "
					       "%d\n",
					       i);
				}
				cmp->current_selection = i;
			}
			drw_tri(ax, ay, bx, by, cx, cy);
		}
	}
	// printf("+");
}

static void draw(struct GuiComponent* comp)
{
	GuiMenuRadial* ptr =
	    (GuiMenuRadial*)comp->data; //(GuiMenuRadial*) comp;
	if (comp->hidden)
		return;

	int i;

	drw_push();
	drw_circle_precision_set(32);
	if (comp->hover)
	{
		drw_alpha(.5);
	}
	else
	{
		drw_alpha(.25);
	}
	drw_translate2f(ptr->x, ptr->y);
	// drw_color(1,1,1,.25);
	drw_circle(ptr->max_radius);
	drw_alpha_pop();
	int num = ptr->num_items;

	for (i = 0; i < num; ++i)
	{
		// double r = M_PI / num;
		// double inc = i * r;
		drw_push();
		drw_rotate_z(120 * i);
		drw_line(0, 0, ptr->max_radius, 0);
		drw_type_draw(ptr->item_labels[i]);
		drw_pop();
	}

	drw_circle(ptr->cur_radius);
	// drw_color(0,.2,.1,1);
	drw_fill_set(true);
	drw_circle(ptr->ina_radius);
	drw_fill_pop();
	// printf("%d", num);

	drw_pop();

	// if ( ptr->hover )
	//{
	double inc = (M_PI * 2) / ptr->num_items;
	// drw_color(0,1,1,1);
	for (i = 0; i < ptr->num_items; ++i)
	{

		double ax = ptr->x;
		double ay = ptr->y;
		double bx = ax + (cos(i * inc) * ptr->max_radius * 2 *
				  app_settings.scale_retina);
		double by = ay + (sin(i * inc) * ptr->max_radius * 2 *
				  app_settings.scale_retina);

		double cx = ax + (cos((i + 1) * inc) * ptr->max_radius * 2 *
				  app_settings.scale_retina);
		double cy = ay + (sin((i + 1) * inc) * ptr->max_radius * 2 *
				  app_settings.scale_retina);
		// drw_line(ax,ay,bx,by);
		if (i == ptr->current_selection)
			drw_tri(ax, ay, bx, by, cx, cy);
	}
	//}
	// printf("+");
}

GuiMenuRadial* gui_menu_radial_create_attr()
{
	GuiMenuRadial* comp = calloc(1, sizeof(GuiMenuRadial));
	/// GuiMenuRadial* attr =
	// comp->update = &_update;
	// comp->render = &_render;
	// comp->hidden = true;
	// comp->active = false;
	comp->max_radius	= 128;
	comp->cur_radius	= 0.;
	comp->ina_radius	= comp->max_radius * .5;
	comp->num_items		= 0;
	comp->current_selection = -1;
	comp->item_labels       = malloc(sizeof(char*) * 32 * 256);
	comp->item_funcs	= malloc(sizeof(void*) * 256);
	return comp;
}

GuiComponent* gui_menu_radial_create(void* gui)
{
	GuiComponent* cmp = gui_component_create(gui);
	cmp->draw	 = &draw;
	cmp->update       = &_update;
	cmp->enabled      = false;
	cmp->data	 = gui_menu_radial_create_attr();
	return cmp;
}

void gui_menu_radial_destroy(GuiComponent* comp)
{
}

void gui_menu_radial_invoke(GuiComponent* comp, double x, double y)
{
	GuiMenuRadial* cmp = comp->data;
	comp->enabled      = true;
	comp->hidden       = false;
	cmp->x		   = x;
	cmp->y		   = y;
	printf("invoking menu at %f %f\n", x, y);
}

void gui_menu_radial_deinvoke(GuiComponent* comp, double x, double y)
{
	// GuiMenuRadial* cmp = comp->data;

	comp->enabled = false;
	comp->hidden  = true;
	// comp->x = x;
	// comp->y = y;

	printf("deinvoking menu at %f %f\n", x, y);
	//printf("Probably should return control to our holder here?\n");
	//comp->delegate.control_return(&comp->delegate);
	//r_input_delegate_pop();
	//comp->delegate.holder
}

void gui_menu_radial_item_add(GuiComponent* comp, char* label, void* func)
{
	GuiMenuRadial* menu = comp->data;
	printf("Adding menu item: %s\n", label);
	menu->num_items++;

	int num			   = menu->num_items;
	menu->item_labels[num - 1] = label;
	menu->item_funcs[num - 1]  = func;
	printf("Menu has %d items.\n", menu->num_items);
}

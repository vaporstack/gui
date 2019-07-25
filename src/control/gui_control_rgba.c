//
//  gui_control_rgba.c
//  gui
//
//  Created by vs on 3/24/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_control_rgba.h"

#include "gui_control_textfield.h"

static void update_color_cb(GuiComponent* cmp)
{
	printf("Updating color callback!\n");
	GTextField* field = cmp->data;
	RColor16*   col   = field->data;
	RColor16 new      = r_color_hex_to_color16(field->addr);

	col->r = new.r;
	col->g = new.g;
	col->b = new.b;
	col->a = new.a;

	//field->on_change( cmp)
}

//static RColor16 inspector_color;
//static char* text;
static void update_passthrough(GuiComponent* cmp)
{
	if (cmp->parent)
		if (cmp->parent->update)
			cmp->parent->update(cmp->parent);
}

static GuiComponent* create_rgba(RColor16* c, char* handle, Gui* gui)
{
	/*
	 GuiComponent* cont = gui_component_create(gui);
	double	sz   = gui_default_ui(gui);
	cont->bypass       = true;
	cont->container    = true;
	GuiComponent* cmp  = NULL;

	cmp		  = gui_control_textfield_create(gui, handle);
	GTextField* field = cmp->data;
	field->on_change  = update_color_cb;
	field->data       = c;

	gui_component_child_add(cont, cmp);

	cmp = gui_control_slider_create_d(&c->r, gui);
	cmp->name = "r";
	cmp->update = update_passthrough;
	gui_component_set(cmp, 0, -1 * sz);
	gui_component_child_add(cont, cmp);
	cmp->update = update_passthrough;
	cmp = gui_control_slider_create_d(&c->g, gui);
	cmp->name = "g";
	gui_component_set(cmp, 0, -2 * sz);
	gui_component_child_add(cont, cmp);
	cmp->update = update_passthrough;
	cmp = gui_control_slider_create_d(&c->b, gui);
	cmp->name = "b";
	gui_component_set(cmp, 0, -3 * sz);
	gui_component_child_add(cont, cmp);
	cmp->update = update_passthrough;;
	cmp = gui_control_slider_create_d(&c->a, gui);
	gui_component_set(cmp, 0, -4 * sz);
	cmp->name = "a";
	cmp->update = update_passthrough;
	gui_component_child_add(cont, cmp);
	cont->name = "rgba";
	cont->update = update_passthrough;
	return cont;
	 */
	return NULL;
}

void destroy(GuiComponent* cmp)
{
	struct WashInspector* inspector = cmp->data;
	free(inspector);
}

#include <drw/drw.h>

static void draw(GuiComponent* cmp)
{
	drw_color_save();
	gui_component_draw(cmp);
	GRGBAAdjustor* info = cmp->data;

	drw_fill_set(true);
	drw_color_c16(*info->color_ptr);
	drw_square(cmp->bounds.size.x * .5);
	drw_color_restore();
	
	drw_fill_pop();

	drw_color(0, .5, .5, 1);
	//drw_rect_w(info->bounds);
	//	drw_line(0,0, info->bounds.pos.x, info->bounds.pos.y);
	//	WSelection*     selection = info->selection;
	//	if ( selection)
	//	{
	//		WLineSelection* lines     = selection->lines;
	//		if(lines)
	//		{
	//			for (unsigned i = 0; i < lines->num; i++)
	//			{
	//				WLine* l       = lines->data[i];
	//				drw_rect_w(l->bounds);
	//			}
	//		}
	//	}
	//	drw_color_pop();
	//	drw_push();
	//	drw_translate_rp(info->center);
	//	drw_circle(info->radius);
	//	drw_pop();
}

static void ui_changed(GuiComponent* cmp)
{
	GRGBAAdjustor* info = cmp->data;
	/*
	 sprintf(info->hexfield, "%s", r_color16_to_hex(info->stroke));
	WSelection*     selection = info->selection;
	if ( !selection)
	{
		//	DEFO bail
		return;

	}
	if ( !selection->lines )
	{
		//for now, BAIL cuz we only care about lines.
		return;

	}
	WLineSelection* lines     = selection->lines;

	for (unsigned i = 0; i < lines->num; i++)
	{
		WLine* l       = lines->data[i];
		if ( l->stroke )
		{
			l->stroke->r = info->stroke.r;
			l->stroke->g = info->stroke.g;
			l->stroke->b = info->stroke.b;
			l->stroke->a = info->stroke.a;
		}
	}
	 */
}

#include <wsh/src/geo/wsh_rect.h>

static void selection_changed(GuiComponent* cmp)
{
	/*(printf("New selection, updating inspector ui\n");
	WashInspector*  info      = cmp->data;
	WSelection*     selection = info->selection;
	WLineSelection* lines     = selection->lines;
	WRect r = wsh_rect_create_impossible();

	double ax, ay;
	ax = ay = 0;
	for (unsigned i = 0; i < lines->num; i++)
	{
		WLine* l       = lines->data[i];
		info->stroke.r = l->stroke->r;
		info->stroke.g = l->stroke->g;
		info->stroke.b = l->stroke->b;
		info->stroke.a = l->stroke->a;
		info->bounds = l->bounds;
		gui_component_set(cmp, info->bounds.pos.x + info->bounds.size.x, info->bounds.pos.y + info->bounds.size.y * .5);
		wsh_rect_union(&r, r, l->bounds);

	}
	info->bounds = r;
	info->center.x = r.pos.x + r.size.x * .5;
	info->center.y = r.pos.y + r.size.y * .5;
	double d = -INFINITY;
	double d2 = dist2d(info->center.x, info->center.y, r.pos.x, r.pos.y);
	if (d2 > d )
		d = d2;
	d2 = dist2d(info->center.x, info->center.y, r.pos.x + r.size.x, r.pos.y);
	if (d2 > d )
		d = d2;
	d2 = dist2d(info->center.x, info->center.y, r.pos.x + r.size.x, r.pos.y + r.size.y);
	if (d2 > d )
		d = d2;
	d2 = dist2d(info->center.x, info->center.y, r.pos.x + r.size.x, r.pos.y + r.size.y);
	if (d2 > d )
		d = d2;
	info->radius = d;
	printf("radius is %f\n", info->radius);
*/
}

GuiComponent* gui_control_rgba_create(Gui* gui, WColor16* color)
{

	GRGBAAdjustor* info = calloc(1, sizeof(GRGBAAdjustor));

	info->hexfield = calloc(7, sizeof(char));
	sprintf(info->hexfield, "%s", "ffffff");
	//	info->selection_changed = selection_changed;
	GuiComponent* cmp = gui_component_create(gui);
	//	GuiComponent* rgb = create_rgba(&info->stroke, info->hexfield, gui);
	cmp->name = "inspector";

	cmp->data    = info;
	cmp->update  = ui_changed;
	cmp->draw    = draw;
	cmp->destroy = destroy;

	//gui_component_child_add(cmp, rgb);

	return cmp;
}

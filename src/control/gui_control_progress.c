
//  gui_control_progress.c
//  gui_control_progress
//
//  Created by Andrew Macfarlane on 22/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_control_progress.h"

#include <drw/drw.h>

#ifndef PHI_I

#define PHI 1.6180339887498948482
#define PHI_I 0.618033988749895
#endif

static void  cmp_update(GuiComponent* cmp)
{
	
}

static void   draw(GuiComponent* cmp)
{
	drw_push();
	//
	gui_component_draw(cmp);
	double ox = cmp->bounds.size.y;
	ox *= PHI_I;
	
	GuiProgress* info = cmp->data;
	//drw_push();
	drw_translate(cmp->bounds.pos.x, cmp->bounds.pos.y, 0);
	drw_translate(ox * .5, ox * .25, 0);
	double w = cmp->bounds.size.x - ox;
	if ( cmp->num_children > 0)
		w -= ox;
	drw_rect( 0, 0, w, ox);
	drw_fill_set(true);
	drw_rect(0,0, w * info->completion, ox);
	drw_fill_pop();
	drw_pop();

}

#include <gui/gui.h>

static void layout(GuiComponent* cmp)
{
	
	long w = *gui_fb_w;
	long h = *gui_fb_h;
	Gui* g = cmp->root;
	double sz = gui_default_ui(cmp->root);
	gui_component_set(cmp, sz * -6, h * .5 - sz);
	cmp->bounds.size.x = sz * 5;
	cmp->bounds.size.y = sz;
	if ( cmp->num_children > 0)
	{
		GuiComponent* btn = cmp->children[0];
		gui_component_set(btn, cmp->bounds.pos.x + cmp->bounds.size.x - sz, cmp->bounds.pos.y);
	}
	
}

static void setup_delegate(GuiComponent* cmp)
{

}

#include "gui_button.h"

GuiComponent* gui_control_progress_create(Gui* gui, gui_progress_update_fn update, gui_progress_complete_fn complete)
{
	
	GuiComponent* cmp = gui_component_create(gui);
	GuiProgress* pb = calloc(1, sizeof(GuiProgress));
	
	
	pb->update = update;
	pb->complete = complete;
	cmp->draw = draw;
	cmp->layout = layout;
	cmp->update = cmp_update;
	cmp->name = "progress_bar";
	cmp->delegate.name = "progress bar delegate";
	cmp->data = pb;
	setup_delegate(cmp);
	return cmp;
}
#include <r4/src/ui/r_icons.h>
#include <r4/src/ext/r_geo_interop.h>

GuiComponent* gui_control_progress_create_with_cancel_button(Gui* gui, gui_progress_update_fn update, gui_progress_complete_fn complete, gui_progress_cancel_fn cancel)
{
	GuiComponent* cmp = gui_control_progress_create(gui, update, complete);
	GuiComponent* cancel_btn = gui_button_create(gui, "cancel", cancel);
	RObject* cross = r_icons_create_cross();
	cancel_btn->art = r_geo_interop_wobject_from_robject( cross);
	
	gui_component_child_add(cmp, cancel_btn);
	return cmp;
}

GuiComponent* gui_control_progress_create_raw(Gui* gui)
{
	return NULL;
}

void	  gui_control_progress_destroy(GuiComponent* comp)
{
	
}

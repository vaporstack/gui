
//  gui_widget.c
//  gui_widget
//
//  Created by Andrew Macfarlane on 04/08/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui_widget.h"

static void update(GuiComponent* cmp)
{
}

static void draw(GuiComponent* cmp)
{
	gui_component_draw(cmp);
	GuiWidget*    wrec = (GuiWidget*)cmp->data;
	GuiComponent* bar  = wrec->bar;
	gui_component_draw(bar);
}

static void layout(GuiComponent* cmp)
{
	GuiWidget*    wrec = (GuiWidget*)cmp->data;
	GuiComponent* bar  = wrec->bar;

	gui_component_set(bar, cmp->bounds.pos.x + cmp->bounds.size.x * .5,
			  cmp->bounds.pos.y + cmp->bounds.size.y);
	gui_component_size(bar, cmp->bounds.size.x, 64);
}

GuiComponent* gui_widget_create(void* gui)
{

	GuiComponent* widget = gui_component_create(gui);

	widget->draw      = draw;
	widget->update    = update;
	widget->layout    = layout;
	widget->container = true;

	GuiComponent* bar = gui_component_create(gui);
	bar->parent       = widget;
	bar->alignment.v  = 1;
	bar->alignment.h  = 0;
	bar->name	 = "widget bar!";

	GuiWidget* wrec = calloc(1, sizeof(GuiWidget));
	wrec->bar       = bar;
	widget->data    = (void*)wrec;

	// gui_component_child_add(widget, bar);

	return widget;
}

void gui_widget_destroy(GuiComponent* comp)
{
}

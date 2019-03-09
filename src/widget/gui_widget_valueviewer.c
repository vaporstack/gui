//
//  gui_widget_valueviewer.c
//  gui
//
//  Created by vs on 6/26/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "gui_widget_valueviewer.h"

void update(GuiComponent* cmp)
{
	GuiValueViewer* target = cmp->data;
	double		value  = *target->addr;
	for (int i = 0; i < GUI_VIEWER_BUFFERSIZE - 1; i++)
	{
		target->history[i] = target->history[i + 1];
	}
	target->history[0] = value;
}

void draw(GuiComponent* gui, GuiComponent* cmp)
{
	gui_component_draw(gui, cmp);
	printf("Custom draw for valueviewer\n");
}

GuiComponent* gui_widget_valueviewer_create(void* gui, double* addr)
{
	GuiComponent*   cmp    = gui_component_create(gui);
	GuiValueViewer* viewer = calloc(1, sizeof(GuiValueViewer));
	cmp->data	      = viewer;
	cmp->draw	      = draw;
	cmp->update	    = update;
	return cmp;
}

void gui_widget_valueviewer_destroy(GuiValueViewer* viewer)
{
}

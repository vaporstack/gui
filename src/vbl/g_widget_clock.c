
//  g_widget_clock.c
//  g_widget_clock
//
//  Created by Andrew Macfarlane on 04/08/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_widget_clock.h"

GuiComponent* g_widget_clock_create(void* gui, VClock* clock_ptr)
{
	GuiComponent* cmp = gui_component_create(gui);

	ClockWidget* widget = calloc(1, sizeof(ClockWidget));
	widget->ref	 = clock_ptr;

	cmp->target = widget;
	return cmp;
}

void g_widget_clock_destroy(GuiComponent* comp)
{
	free(comp->data);
	free(comp);
}

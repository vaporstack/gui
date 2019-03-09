
//  g_widget_clock.c
//  g_widget_clock
//
//  Created by Andrew Macfarlane on 04/08/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_widget_clock_h_
#define g_widget_clock_h_

#include "../base/gui_component.h"

#include <vbl/vbl.h>

typedef struct ClockWidget
{
	VClock* ref;
} ClockWidget;

GuiComponent* g_widget_clock_create(void* gui, VClock* clock_ptr);
void	  g_widget_clock_destroy(GuiComponent* comp);

#endif

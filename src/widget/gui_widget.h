
//  gui_widget.c
//  gui_widget
//
//  Created by Andrew Macfarlane on 04/08/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_widget_h_
#define gui_widget_h_

#include "../base/gui_component.h"

typedef struct GuiWidget
{
	bool	  draggable;
	bool	  closable;
	bool	  foldable;
	bool	  folded;
	GuiComponent* bar;
} GuiWidget;

GuiComponent* gui_widget_create(void* gui);
void	  gui_widget_destroy(GuiComponent* comp);

// void		gui_widget_update(GuiComponent* comp);

#endif

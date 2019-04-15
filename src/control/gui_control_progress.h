
//  gui_control_progress.c
//  gui_control_progress
//
//  Created by Andrew Macfarlane on 22/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_control_progress_h_
#define gui_control_progress_h_

#include "../base/gui_component.h"
#include "../base/g_gui.h"

typedef void (*gui_progress_update_fn)(GuiComponent*, void*);
typedef void (*gui_progress_complete_fn)(GuiComponent*, void*);
typedef void (*gui_progress_cancel_fn)(GuiComponent*, void*);

typedef struct
{
	gui_progress_update_fn update;
	gui_progress_cancel_fn cancel;
	gui_progress_complete_fn complete;
	double completion;
}GuiProgress;

GuiComponent* gui_control_progress_create(Gui* gui, gui_progress_update_fn update, gui_progress_complete_fn complete);
GuiComponent* gui_control_progress_create_raw(Gui* gui);
void	  gui_control_progress_destroy(GuiComponent* comp);

#endif


//  gui_modal.c
//  gui_modal
//
//  Created by Andrew Macfarlane on 18/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_modal_h_
#define gui_modal_h_

#include "../base/gui_component.h"

#include "g_gui.h"
// typedef void (*function_ptr)(void);

typedef struct GuiModalExtra
{
	int	   blocking;
	const char*   name;
	const char*   label;
	function_ptr* cb_ok;
	function_ptr* cb_cancel;
} GuiModalExtra;

typedef struct GuiModalOptions
{
	int can_be_dismissed;

} GuiModalOptions;

void gui_modal_prompt(Gui* gui, const char* label, function_ptr ok,
		      function_ptr cancel);

GuiComponent* gui_modal_create(Gui* gui);
void	  gui_modal_destroy(GuiComponent*);

#endif

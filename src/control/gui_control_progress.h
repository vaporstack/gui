
//  gui_control_progress.c
//  gui_control_progress
//
//  Created by Andrew Macfarlane on 22/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_control_progress_h_
#define gui_control_progress_h_

#include "../base/gui_component.h"

GuiComponent* gui_control_progress_create(void);
void	  gui_control_progress_destroy(GuiComponent* comp);

#endif


//  gui_control_progress.c
//  g_control_progress
//
//  Created by Andrew Macfarlane on 22/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_control_progress_h_
#define g_control_progress_h_

#include "../base/gui_component.h"

GuiComponent* g_control_progress_create(void);
void	  g_control_progress_destroy(GuiComponent* comp);

#endif

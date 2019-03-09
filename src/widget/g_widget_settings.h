//
//  g_widget_settings.h
//  gui
//
//  Created by Andrew Macfarlane on 8/22/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef g_widget_settings_h
#define g_widget_settings_h

#include <stdio.h>

#include "../base/gui_component.h"

GuiComponent* g_widget_settings_create(void* gui);
void	  g_widget_settings_destroy(GuiComponent* comp);

#endif /* g_widget_settings_h */

//
//  gui_notifications.h
//  gui
//
//  Created by Andrew Macfarlane on 4/12/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef gui_notifications_h
#define gui_notifications_h

#include "g_gui.h"
#include "gui_component.h"



GuiComponent* gui_notifications_create(Gui* gui);
GuiComponent* gui_notifications_post(Gui* gui, const char* text);
GuiComponent* gui_notifications_post_custom(Gui* gui, GuiComponent* cmp);


#endif /* gui_notifications_h */

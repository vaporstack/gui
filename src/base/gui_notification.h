//
//  gui_notification.h
//  gui
//
//  Created by vs on 3/22/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef gui_notification_h
#define gui_notification_h

#include "g_gui.h"
#include "gui_component.h"

typedef struct
{
	double	birth;
	GuiComponent* sub;
} GNotification;

GuiComponent* gui_notification_create(Gui* gui, const char* text);
GuiComponent* gui_notification_create_custom(Gui* gui, GuiComponent* cmp);

#endif /* gui_notification_h */

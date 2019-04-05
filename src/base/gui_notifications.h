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

/*
typedef struct{
	unsigned num;
	GuiComponent** data;
}GNotifications;


 uhhhh we already have container infra duhhhh
 */

GuiComponent* gui_notifications_create(Gui* gui);
GuiComponent* gui_notifications_post(Gui* gui, const char* text);
GuiComponent* gui_notifications_post_custom(Gui* gui, GuiComponent* cmp);

/*
GuiComponent* gui_notification_create(void* gui);

GuiComponent* gui_notifications_create(void* gui);
// void		 	gui_notifications_destroy(void);
void gui_notifications_lazycheck(void* gui);
*/
#endif /* gui_notifications_h */

//
//  gui_widget_multiplayer.h
//  gui
//
//  Created by vs on 5/13/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef gui_widget_multiplayer_h
#define gui_widget_multiplayer_h

#include <gui/src/base/g_gui.h>
#include <gui/src/base/gui_component.h>

typedef struct
{
	int*   num;
	void** data;
} GMultiplayerWidget;

GuiComponent* gui_widget_multiplayer_create(Gui* gui);
void gui_widget_multiplayer_update(void);
void gui_widget_multiplayer_check_add(GuiComponent* cmp, void* info);

#endif /* gui_widget_multiplayer_h */

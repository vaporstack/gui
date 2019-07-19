//
//  gui_ios_dpad_nav.h
//  gui
//
//  Created by vs on 5/13/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef gui_ios_dpad_nav_h
#define gui_ios_dpad_nav_h

#include <gui/gui.h>

typedef void (*navpad_cb)(GuiComponent* cmp, double x, double y);

typedef struct
{
	navpad_cb callback;
	CPoint    current;
	CPoint    start;
} GNavPad;

GuiComponent* gui_ios_dpad_nav_create(Gui* gui, navpad_cb fn);

#endif /* gui_ios_dpad_nav_h */

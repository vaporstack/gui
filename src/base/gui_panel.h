
//  gui_panel.c
//  gui_panel
//
//  Created by Andrew Macfarlane on 04/08/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_panel_h_
#define gui_panel_h_

#include <gui/gui.h>

typedef struct
{
	int cur;
	int		  num;
	GuiStringHandle** tabs;
	
} GTabbedPanel;

typedef struct
{
	int idx;
	RLine* geo;
}GTabbedPanelTab;

GuiComponent* gui_tabbed_panel_create(Gui* gui, char** labels, int num);

#endif

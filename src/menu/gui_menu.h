//
//  gui_menu.h
//  gui
//
//  Created by Andrew Macfarlane on 9/18/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef gui_menu_h
#define gui_menu_h

#include <r4/r4.h>

#include "../base/gui_component.h"
//#include <vector/vector.h>
typedef void (*menu_transition_cb)(GuiComponent* cmp);
typedef void (*menu_select_cb)(GuiComponent* cmp);

typedef struct GMenu
{
	void**	items;
	int	   num;
	struct GMenu* parent;
	int	   selected_item;
	menu_select_cb select;
	menu_select_cb selection_change;
	menu_select_cb cancel;
} GMenu;

typedef struct GMenuCreationData
{
	int	  num;
	const char** names;
	click_func*  funcs;
} GMenuCreationData;

GuiComponent* gui_menu_create(void* gui);
GuiComponent* gui_menu_create_with_data(void* gui, GMenuCreationData data);
void	  gui_menu_activate_selected(GuiComponent* menu);
void	  gui_menu_destroy(GuiComponent* menu);
void	  gui_menu_select_prev(GuiComponent* menu);
void	  gui_menu_select_next(GuiComponent* menu);

#endif /* gui_menu_h */

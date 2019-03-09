//
//  g_menu_item.h
//  gui
//
//  Created by Andrew Macfarlane on 9/18/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef g_menu_item_h
#define g_menu_item_h

enum menu_item_types_t {
	MENU_ITEM_VOID,
	MENU_ITEM_PUSHBUTTON,
	MENU_ITEM_TOGGLEBUTTON,
	MENU_ITEM_SLIDER,
	MENU_ITEM_MENU,
	MENU_ITEM_LAST
};

typedef struct GMenuItem
{
	int   type;
	void* data;
} GMenuItem;

#endif /* g_menu_item_h */

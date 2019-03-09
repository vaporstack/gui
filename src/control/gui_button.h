//
//  gui_button.h
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef gui_button_h
#define gui_button_h

#include "../base/gui_component.h"

typedef int (*myfunc)(int);
// typedef void (*click_func)(int, int, int);
// typedef void (*click_func)(void);

typedef struct ButtonAttrs
{
	click_func click;
	bool*      value;
} ButtonAttrs;

GuiComponent* gui_button_create(void* gui, const char* label,
				click_func func);

#endif /* gui_button_h */

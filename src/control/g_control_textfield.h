
//  g_control_textfield.c
//  g_control_textfield
//
//  Created by Andrew Macfarlane on 04/08/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_control_textfield_h_
#define g_control_textfield_h_

#include "../base/gui_component.h"

typedef struct GTextField
{
	char* text;
	unsigned int len;
}GTextField;

GuiComponent* g_control_textfield_create(void* gui);


#endif

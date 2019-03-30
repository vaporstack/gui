
//  gui_control_textfield.c
//  g_control_textfield
//
//  Created by Andrew Macfarlane on 04/08/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_control_textfield_h_
#define g_control_textfield_h_

#include "../base/gui_component.h"
/*
typedef struct myStringHandle
{
	char* addr;
} myStringHandle;
*/

typedef void (*g_textfield_onchange)(GuiComponent* cmp);

typedef struct GTextField
{
//	myStringHandle* hnd;
	char* addr;
	char* edit;
	signed long len;
	signed long cursor;
	void* data;
	g_textfield_onchange on_change;
}GTextField;

GuiComponent* g_control_textfield_create(void* gui, char* hnd);


#endif

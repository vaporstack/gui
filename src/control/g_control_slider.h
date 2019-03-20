//
//  gui_button.h
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef gui_slider_h
#define gui_slider_h

#include <r4/src/geo/r_rect.h>
#include <stdlib.h>

typedef int (*my_slider_func)(GuiComponent* cmp, double v);

typedef struct
{
	char* name;
	double*	target;
	double lower;
	double upper;
	bool constrain_to_int;
	bool vertical;
	//bool show_value;
	my_slider_func function;
} GuiSliderD;

typedef struct
{
	char* name;
	//RRect* bounds;
	int* target;
	int (*func)(int);
} GuiSliderI;

GuiComponent* g_control_slider_create_d(double* data, void* gui);
GuiComponent* g_control_slider_create_cb(double* addr, my_slider_func cb, void* gui);
void g_control_slider_draw(struct GuiComponent* cmp, struct GuiComponent* gui);

// void g_slider_update_i(GuiSliderI* slider, float val);
// void g_slider_update_f(GuiSliderD* slider, float val);

// GuiButton* g_create_slider_i(char* , RRect*, myfunc, int* );

#endif /* gui_slider_h */

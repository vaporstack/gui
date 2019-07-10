//
//  gui_button.h
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef gui_control_slider_h
#define gui_control_slider_h

#include "../base/gui_component.h"
//#include <r4/src/geo/r_rect.h>
//#include <stdlib.h>

typedef int (*my_slider_func)(GuiComponent* cmp, double v);

typedef struct
{
	bool	   transient;
	bool	   constrain_to_int;
	bool	   vertical;
	char*	  name;
	double*	target;
	double	 pos;
	double	 lower;
	double	 upper;
	double	 defaults;
	double	 original;
	my_slider_func function;
	my_slider_func on_begin;
	my_slider_func on_end;
} GuiSliderD;

typedef struct
{
	char* name;
	//RRect* bounds;
	int* target;
	int (*func)(int);
} GuiSliderI;

GuiComponent* gui_control_slider_create_d(double* data, void* gui);
GuiComponent* gui_control_slider_create_cb(double* addr, my_slider_func cb, void* gui);
void	  gui_control_slider_draw(struct GuiComponent* cmp);
void	  gui_control_slider_setup(GuiComponent* cmp);
void	gui_control_slider_update_changed_val(GuiComponent* cmp, double val);
// void g_slider_update_i(GuiSliderI* slider, float val);
// void g_slider_update_f(GuiSliderD* slider, float val);

// GuiButton* g_create_slider_i(char* , RRect*, myfunc, int* );

#endif /* gui_control_slider_h */

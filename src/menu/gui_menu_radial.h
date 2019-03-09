
//  gui_menu_radial.c
//  gui_menu_radial
//
//  Created by Andrew Macfarlane on 06/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_menu_radial_h_
#define gui_menu_radial_h_

#include <stdbool.h>

#include "../base/gui_component.h"

typedef void (*menu_callback)(void);

typedef struct
{
	double x;
	double y;
	//	dumb, get rid of this
	double mx;
	double my;
	//	these are being set Manually by other code because the update
	// function doesn't take input. oops.
	double max_radius;
	double cur_radius;
	double ina_radius;
	int    current_selection;
	// bool hidden;
	// bool active;
	// bool hover;
	bool hover_within_options;
	// void(* render)(void*);
	// void(* update)(void*, double, double);
	InputDelegate  delegate;
	int	    num_items;
	char**	 item_labels;
	menu_callback* item_funcs;

	//	todo, make this not be stupid

} GuiMenuRadial;

GuiComponent* gui_menu_radial_create(void* gui);
void	  gui_menu_radial_destroy(GuiComponent*);
void	  gui_menu_radial_invoke(GuiComponent*, double x, double y);
void	  gui_menu_radial_deinvoke(GuiComponent*, double x, double y);
void	  gui_menu_radial_item_add(GuiComponent*, char* label, void* func);

#endif

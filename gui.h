
//  gui.c
//  gui
//
//  Created by Andrew Macfarlane on 03/04/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_h_
#define gui_h_

#define GUI_VERSION_MAJOR 0
#define GUI_VERSION_MINOR 0
#define GUI_VERSION_PATCH 1

#include "stdio.h"
#include "stdlib.h"

#define kGuiUnnamedComponent "unnamed_gui_component"
#define kGuiUnnamedComponentNice "Unnamed Gui Component"

int   gui_check_version_match(const char* str);
int   gui_check_compat_match(const char* str);
char* gui_get_version_string(void);
char* gui_get_compat_string(void);

#ifndef PHI_I

#define PHI 1.6180339887498948482
#define PHI_I 0.618033988749895
#endif

//	todo: transition these to use the macro which is way more efficient
static inline char* gui_get_compat_string_header(void)
{
	char* buf = (char*)calloc(256, sizeof(char));
	sprintf(buf, "%d.%d", GUI_VERSION_MAJOR, GUI_VERSION_MINOR);
	return buf;
}

static inline char* gui_get_version_string_header(void)
{
	char* buf = (char*)calloc(256, sizeof(char));
	sprintf(buf, "%d.%d.%d", GUI_VERSION_MAJOR, GUI_VERSION_MINOR, GUI_VERSION_PATCH);
	return buf;
}
#include <r4/r4.h>

#include "gui_config.h"

#include "src/etc/gui_log.h"

void	   gui_get_default_bounds(double* x, double* y);
void	   gui_provide_cursor_pos(double* x, double* y);
void	   gui_provide_framebuffer_variables(int* x, int* y);
void	   gui_provide_global_alpha_mult(double* v);
void		gui_set_global_scale(double sc);
double		gui_get_global_scale(void);
extern double 	gui_ui_unit;
extern int* gui_fb_w;
extern int* gui_fb_h;
extern bool gui_righthanded;
extern double* gui_cursor_x;
extern double* gui_cursor_y;
extern double* gui_alpha_mult;
extern int     gui_text_direction;

//#include "gui_container.h"
/*
 
 
 nomenclature
 
 component - base element .
 all components can contain other components
 components do not necessarily need to interact
 
 
 
 
 
 
 */


#include "src/base/g_gui.h"
#include "src/base/gui_component.h"
#include "src/base/gui_modal.h"
#include "src/base/gui_notifications.h"
#include "src/comp/gui_comp_rline.h"
#include "src/control/gui_button.h"
#include "src/control/gui_control_checkbox.h"
#include "src/control/gui_control_colorwell.h"
#include "src/control/gui_control_label.h"
#include "src/control/gui_control_slider.h"
#include "src/menu/gui_menu.h"
#include "src/menu/gui_menu_item.h"
#include "src/menu/gui_menu_radial.h"
#include "src/widget/g_widget_console.h"
#include "src/widget/gui_widget.h"

#define G_UI_FONT_SIZE 18
#define G_UI_BTN_SIZE 32

#endif

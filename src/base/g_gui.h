//
//  g_gui.h
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef gui_h
#define gui_h

#include <stdbool.h>

#include "gui_component.h"

enum
{
	GuiAlignHLeft,
	GuiAlignHCenter,
	GuiAlignHRight
};

enum
{
	GuiAlignVTop,
	GuiAlignVMiddle,
	GuiAlignVBottom
};

//TODO: this appears to be for DrawTarget
#include <r4/src/app/r_app.h>

typedef struct
{
	char* src;
} GuiStringHandle;

typedef struct Gui
{
	bool	  debug;
	bool	  borderless;
	double	scale_retina;
	double	width;
	double	height;
	GuiComponent* root;
	struct map_t* items;
	DrawTarget    dtarget;
	void*	 anim_mgr;
	GuiComponent* notifications;
	// resize_func resize;
	// ResizeTarget* target;
	bool debug_visibility_override;

	InputDelegate del;

} Gui;

GuiComponent* gui_component_find(Gui* gui, const char* ident);
int	   gui_component_register(Gui* gui, const char* ident, GuiComponent* cmp);

Gui* gui_create(const char* name);
void gui_destroy(Gui*);

// void gui_init(void);
// void gui_deinit(void);

void gui_draw(Gui* gui);
void gui_update(Gui* gui);

bool gui_component_add(Gui* gui, GuiComponent*);
bool gui_remove_component(Gui* gui, GuiComponent*);

void gui_notify_resize(void* gui, unsigned int x, unsigned int y);

void gui_layout(Gui* gui);

void   gui_set_debug(Gui* gui, bool v);
void   gui_set_retina(Gui* gui, double f);
double gui_get_retina(Gui* gui);
double gui_default_ui(Gui* gui);
void   gui_toggle_enabled(Gui* gui, bool v);

GuiComponent* gui_find_pointerfocus(Gui* gui, double, double);

#endif /* gui_h */

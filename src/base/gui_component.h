//
//  gui_component.h
//  r4
//
//  Created by Andrew Macfarlane on 12/15/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#ifndef gui_component_h
#define gui_component_h

//#include <gui/gui.h>

#include <r4/src/r4_config.h>

#include <r4/src/geo/r_rect.h>
#include <r4/src/input/r_input.h>
#include <wsh/wsh.h>

//#include "../geo/r_rect.h"
#include <stdbool.h>
//#include "../input/r_input.h"

#include "../../gui_types.h"

enum GuiOrientationTypesHorizontal
{
	GUI_H_ORIENTATION_NONE,
	GUI_H_ORIENTATION_FILL,
	GUI_H_ORIENTATION_LEFT,
	GUI_H_ORIENTATION_CENTER,
	GUI_H_ORIENTATION_RIGHT
};

enum GuiOrientationTypesVertical
{
	GUI_V_ORIENTATION_NONE,
	GUI_V_ORIENTATION_FILL,
	GUI_V_ORIENTATION_TOP,
	GUI_V_ORIENTATION_CENTER,
	GUI_V_ORIENTATION_BOTTOM
};

typedef struct GuiOrientationAttrs
{
	int horizontal;
	int vertical;
} GuiOrientationAttrs;

typedef struct GuiAlignmentAttrs
{
	//deprecate these for align_h and align_v
	//int align_h;
	//int align_v;

	int h;
	int v;
	int children_h;
	int children_v;
	// int orientation;
	int child_orientation;
} GuiAlignmentAttrs;

typedef struct GuiComponent
{

	//double x;
	//double y;

	const char*	 name;
	RRect		    bounds;
	bool		    container;
	bool		    focus;
	bool		    locked;
	bool		    visible;
	bool		    hidden;
	bool		    enabled;
	bool		    bypass;
	bool		    hover;
	bool		    selected;
	bool		    on;
	bool		    draggable;
	bool		    debug;
	bool		    animating;
	int		    type;
	RPoint		    offset;
	GuiAlignmentAttrs   alignment;
	GuiOrientationAttrs orientation;
	void (*draw)(struct GuiComponent* cmp, struct GuiComponent* gui);
	void (*update)(struct GuiComponent*);
	void (*layout)(struct GuiComponent*);
	void (*activate)(struct GuiComponent*);
	bool (*find_focus)(struct GuiComponent*, double x, double y);
	void (*destroy)(struct GuiComponent*);
	void*		      animation_attrs;
	InputDelegate	 delegate;
	void*		      target;
	void*		      data;
	void*		      art;
	void*		      drag;
	//CPoint*			offset;
	int		      num_children;
	struct GuiComponent** children;
	struct vector_t*      children_vec;
	struct GuiComponent*  parent;
	void*		      root;

} GuiComponent;

typedef struct GuiComponentHnd
{
	GuiComponent* src;
} GuiComponentHnd;

typedef void (*click_func)(void);
typedef void (*resize_func)(void*, double, double);

void gui_component_set_children_type(GuiComponent* cmp, int type);
void gui_component_draw(GuiComponent* cmp, GuiComponent* gui);
void gui_component_draw_bordered(GuiComponent* cmp, GuiComponent* gui);

GuiComponent* gui_component_group_create(void* gui, int num,
					 const char** names,
					 click_func funcs[6], WObject** arts, bool* vals);

GuiComponent* gui_component_create(void* gui);
void	  gui_component_destroy(GuiComponent*);
void	  gui_component_set(GuiComponent* cmp, double x, double y);
void	  gui_component_size(GuiComponent* cmp, double x, double y);
void	  gui_component_move(void* gui, GuiComponent* cmp, double x, double y);
void	  gui_component_child_add(GuiComponent* cmp, GuiComponent* sub);
void	  gui_component_child_remove(GuiComponent* cmp, GuiComponent* sub);
void	  gui_component_hide(GuiComponent* cmp);
void	  gui_component_show(GuiComponent* cmp);
void	  gui_component_layout(GuiComponent* cmp);
void	  gui_component_layout_vertical(GuiComponent* cmp);
void	  gui_component_layout_horizontal(GuiComponent* cmp);
//void	gui_component_activate(GuiComponent* cmp, void* input_delegate);
//void gui_component_deactivate(GuiComponent* cmp);
//double g_default_ui_size(void* gui);
RRect g_create_default_bounds(void* gui);

GuiComponent* gui_component_find_pointerfocus(GuiComponent* cont, double,
					      double);
void	  gui_component_render_children(GuiComponent* cmp, GuiComponent* gui);

#endif /* gui_component_h */
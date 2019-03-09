//
//  g_gui.cpp
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "g_gui.h"

// GuiComponent* _root;

#include <drw/drw.h>
#include <r4/r4.h>

// extern ColorScheme8 cs_current;

//#include <gui/gui.h>

//#include "../render/r_render.h"

//#include <liblogger/logger.h>

//#include "../app/r_app.h"
#include <gui/gui.h>

#include "gui_component.h"

// extern AppSettings app_settings;
/*
bool   _gui_debug	= true;
double _gui_scale_retina = 1.;
double _gui_w		 = 512;
double _gui_h		 = 512;
*/

#include <cmap/map.h>

#include "../anim/gui_anim_mgr.h"
#include <vector/vector.h>

// extern DebugSettings debug_settings;
// extern AppSettings app_settings;

// logger_t *log_gui;
extern AppSettings app_settings;

// static struct map_t* gui_items = NULL;

void _gui_render_component(Gui* gui, struct GuiComponent*);
void _gui_render_components(Gui* gui, GuiComponent*);

static struct vector_t guis;
static bool	    guis_initialized = false;

static void on_resize(Gui* gui, double x, double y)
{
	printf("Got overloaded resize func %f %f\n", x, y);
}

Gui* gui_create(const char* name)
{
	Gui* gui	   = calloc(1, sizeof(Gui));
	gui->width	 = app_settings.framebuffer_width;
	gui->height	= app_settings.framebuffer_height;
	GuiComponent* root = gui_component_create(gui);
	root->enabled      = true;
	root->visible      = false;
	root->bypass       = true;
	root->animating    = false;
	root->name	 = strdup(name);
	root->container    = true;
	gui->items	 = new_map();
	gui->root	  = root;
	gui->anim_mgr      = gui_anim_mgr_create(root);

	// gui->resize = &on_resize;
	// target= calloc(1, sizeof(ResizeTarget));

	gui_notify_resize(gui, gui->width, gui->height);

	if (!guis_initialized)
	{
		vector_init(&guis, 1, sizeof(Gui));
	}
	return gui;
}

void gui_destroy(Gui* gui)
{
	// free(gui->target);
	free(gui->items);
	gui_anim_mgr_destroy(gui->anim_mgr);

	gui_component_destroy(gui->root);
}

/*
void gui_init()
{
	// log_gui = stream_logger_new("[GUI ]", LOG_LEVEL_DEBUG, stdout);
	_root		 = gui_component_create();
	_root->enabled   = true;
	_root->visible   = false;
	_root->bypass    = true;
	_root->name      = "Gui root.";
	_root->container = true;
	// l_info("gui init.\n");



	// gui_notify_resize(_gui_w,_gui_h);
	//gui_notify_resize(_gui_w, _gui_h);

	gui_items = new_map();
}

void gui_deinit()
{
	gui_component_destroy(_root);

	// l_info("gui deinit.\n");
	// destroy_map(gui_items);

	// logger_delete(&log_gui);
}
*/

void gui_set_debug(Gui* gui, bool v)
{
	gui->debug = v;
}

void _gui_render_component(Gui* gui, struct GuiComponent* cmp)
{
	if (!cmp->visible)
		return;
	if (cmp->hidden)
		return;

	if (!cmp)
	{
		printf("unable to cast!\n");
	}

	if (!cmp->draw)
	{
		return;
	}

	int last = drw_checkmatrix();

	/*	if ( 0 != strcmp("...", cmp->name))
	{
		//printf("hi!\n");
	}*/

	(cmp->draw)(cmp, gui->root);
	int cur = drw_checkmatrix();

	if (last != cur)
	{
		printf("J'ACCUSE!\n");
	}
	// printf("matrix stack was %d\n", drw_checkmatrix());
}

void _gui_render_components(Gui* gui, GuiComponent* cont)
{
	for (int i = 0; i < cont->num_children; ++i)
	{
		GuiComponent* comp = cont->children[i];
		if (comp)
		{
			_gui_render_component(gui, comp);
		}
		else
		{
			printf("!");
		}
	}
}

void _gui_update_components(Gui* gui, GuiComponent* cont)
{
	for (int i = 0; i < cont->num_children; ++i)
	{
		GuiComponent* comp = cont->children[i];
		if (!comp)
		{
			printf("!");
		}
		else
		{
			if (0 == strcmp(comp->name, "layer_widget"))
			{
				// printf("haz it");
			}
			if (!comp->update)
			{
				printf("No update function!\n");
				continue;
			}
			comp->update(comp);
		}
	}
}

#define GUI_INSET_DIST 2
static void draw_inset(GuiComponent* cmp)
{
	RRect insetb = cmp->bounds;

	insetb.pos.x += GUI_INSET_DIST;
	insetb.pos.y += GUI_INSET_DIST;
	insetb.size.x -= GUI_INSET_DIST * 2;
	insetb.size.y -= GUI_INSET_DIST * 2;
	drw_rect(insetb.pos.x, insetb.pos.y, insetb.pos.x + insetb.size.x,
		 insetb.pos.y + insetb.size.y);
}

void gui_draw(Gui* gui)
{
	if (!gui->root)
	{
		l_warning(
		    "Tried to render gui root but root does not exist.\n");
		// printf("Error!!\n");
		return;
	}

	if (!gui->root->visible)
	{
		if (!gui->borderless)
			draw_inset(gui->root);
	}

	if (gui->root->hidden)
		return;

	_gui_render_components(gui, gui->root);
}

void gui_update(Gui* gui)
{
	// printf("1");
	if (gui->anim_mgr)
		gui_anim_mgr_update(gui->anim_mgr);

	_gui_update_components(gui, gui->root);
}

void gui_set_retina(Gui* gui, double f)
{
	// printf("Gui set retina scale: %f\n", f);
	gui->scale_retina = f;
}

double gui_get_retina(Gui* gui)
{
	return gui->scale_retina;
}
/*
void _update_it(struct GuiComponent* cmp)
{
	printf("this function does nothing: %s\n", __func__);
}
*/

static void draw(struct GuiComponent* comp, struct GuiComponent* gui)
{
	if (!comp->visible)
		return;
	if (comp->hidden)
		return;

	// GuiComponent* comp = (GuiComponent*)v;
	drw_push();
	drw_translate2f(comp->bounds.pos.x, comp->bounds.pos.y);
	drw_rect(0, 0, comp->bounds.size.x, comp->bounds.size.y);

	drw_type_draw(comp->name);
	drw_pop();
}

bool gui_component_add(Gui* gui, GuiComponent* comp)
{
	if (comp->draw == NULL)
	{

		comp->draw = &draw;
	}
	/*if (comp->update == NULL)
	{
		comp->update = &_update_it;
	}
	 */

	if (!gui->root)
	{
		return false;
	}
	gui_component_child_add(gui->root, comp);

	return true;
}

bool gui_remove_component(Gui* gui, GuiComponent* comp)
{
	if (!gui->root)
	{
		return false;
	}
	gui_component_child_remove(gui->root, comp);

	return true;
}

GuiComponent* gui_find_pointerfocus(Gui* gui, double x, double y)
{
	GuiComponent* sub = gui_component_find_pointerfocus(gui->root, x, y);
	if (sub)
		printf("[%s]\n", sub->name);
	return sub;

	//	the gui is root level so we return nothing if we found ourself
	// if ( sub == _root){
	//	return NULL;
	//}
}

void gui_notify_resize(void* data, unsigned int w, unsigned int h)
{
	if (!data)
	{
		printf("Error, can't resize, no data pointer!\n");
		return;
	}
	Gui* gui = (Gui*)data;

	if (!gui->root)
	{
		l_warning("tried to resize a nonexistant gui.\n");
		return;
	}
	gui->width  = w;
	gui->height = h;

	gui->root->bounds.pos.x  = w * -.5;
	gui->root->bounds.pos.y  = h * -.5;
	gui->root->bounds.size.x = w;
	gui->root->bounds.size.y = h;
	//gui->root->x		 = gui->root->bounds.pos.x;
	//gui->root->y		 = gui->root->bounds.pos.y;

	gui_set_retina(gui, app_settings.scale_retina);
	gui_layout(gui);

	// gui_component_align_children(_root);
	// if ( debug_settings.gui )
	printf("Resized gui to %d %d %u %u\n", 0, 0, w, h);
}

void gui_layout(Gui* gui)
{
	if (!gui->root)
	{
		printf("Can't layout, _root is null\n");
		return;
	}

	if (gui->debug)
	{
		char log[256];
		sprintf(log, "Doing root gui layout. ret is %f\n",
			gui->scale_retina);
		// l_info(log);
	}
	// GuiComponent* local_root = _root;

	//	set the gui to be the size of the window
	//_root->bounds.
	gui_component_layout(gui->root);
}

void gui_toggle_enabled(Gui* gui, bool v)
{
	/*printf("ENABLING GUI? %d\n", v);
	 if ( v )
	 printf("true\n");
	 if (!v)
	 printf("false\n");
	 */

	if (!gui->root)
	{
		printf("Can't layout, gui->root is null\n");
		return;
	}
	gui->root->enabled = v;
	gui->root->hidden  = !v;
	gui->root->visible = v;
}

GuiComponent* gui_find_component(Gui* gui, const char* ident)
{
	return map_get(gui->items, ident);
}


double gui_default_ui(Gui* gui)
{
	return gui->scale_retina * 2 * G_UI_BTN_SIZE;
}

int gui_register_component(Gui* gui, const char* ident, GuiComponent* cmp)
{
	if (!ident)
	{
		printf("Can't register a component with no ident!\n");
		return false;
	}
	if (0 == strcmp(ident, ""))
	{
		printf("aaaack\n");
		return false;
	}
	GuiComponent* test = map_get(gui->items, ident);
	if (test)
	{
		printf("Already have a gui item with the name!:%s\n", ident);
		return 1;
	}

	return map_set(gui->items, ident, (void*)cmp);
}

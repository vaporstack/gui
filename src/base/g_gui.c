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

//	todo: migrate this from r4 core to gui core?
InputDelegate gui_input;

void _gui_render_component(Gui* gui, struct GuiComponent*);
void _gui_render_components(Gui* gui, GuiComponent*);

static struct vector_t guis;
static bool	    guis_initialized = false;


#pragma mark logic

static void begin(GuiComponent* cmp, double x, double y)
{
	
}

static void update(GuiComponent* cmp, double x, double y)
{
	
}


static void end(GuiComponent* cmp, double x, double y)
{
	
}
//
//static void draw(GuiComponent* cmp)
//{
//
//}

static void layout(GuiComponent* cmp)
{
	
}

#pragma mark input

#pragma mark desktop

static void mouse_motion(struct InputDelegate* delegate, double x, double y)
{
}

static void mouse_button(struct InputDelegate* delegate, int button, int action,
			 int mods)
{
	if ( button > 0 )
	return;
	
	GuiComponent* cmp = delegate->parent;
	Gui* root = cmp->root;
	
	//gui_find_pointerfocus(root, , <#double y#>)
	

}

static void key(struct InputDelegate* delegate, int key, int scan, int action, int mods)
{
}

static void char_cb(struct InputDelegate* delegate, unsigned c)
{
}

#pragma mark touch

static void touch_cancel(struct InputDelegate* delegate, double x, double y, double r)
{
}

static void touch_began(struct InputDelegate* delegate, double x, double y, double r)
{
}

static void touch_ended(struct InputDelegate* delegate, double x, double y, double r)
{
}

static void touch_move(struct InputDelegate* delegate, double x, double y,
		       double r)
{
}

#pragma mark tablet

static void tablet_proximity(bool v)
{
}

static void tablet_motion_rich(struct InputDelegate* delegate, double x,
			       double y, int button, double pressure,
			       double rotation, double tilt_x, double tilt_y,
			       double tangential)
{
}

static void tablet_drag_rich(struct InputDelegate* delegate, double x, double y,
			     int button, double pressure, double rotation,
			     double tilt_x, double tilt_y, double tangential)
{
}

static void tablet_down_rich(struct InputDelegate* delegate, double x, double y,
			     int button, double pressure, double rotation,
			     double tilt_x, double tilt_y, double tangential)
{
}

static void tablet_up_rich(struct InputDelegate* delegate, double x, double y,
			   int button, double pressure, double rotation,
			   double tilt_x, double tilt_y, double tangential)
{
}

#pragma mark core

static void setup_delegate(InputDelegate* del)
{
	del->mouse_button       = mouse_button;
	del->mouse_motion       = mouse_motion;
	del->touch_move		= touch_move;
	del->touch_began	= touch_began;
	del->touch_cancel       = touch_cancel;
	del->touch_ended	= touch_ended;
	del->tablet_motion_rich = tablet_motion_rich;
	del->tablet_proximity   = tablet_proximity;
	del->tablet_down_rich   = tablet_down_rich;
	del->tablet_up_rich     = tablet_up_rich;
	del->tablet_drag_rich   = tablet_drag_rich;
	del->supports_handoff   = true;
	del->char_cb		= char_cb;
	del->key		= key;
	del->name		= "a input boilerplate";
}


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
	gui->notifications = NULL;
	gui->scale_retina = 1;
	gui->del = gui_input;
	setup_delegate(&gui->del);
	//gui->anim_mgr      = gui_anim_mgr_create(root);

	// gui->resize = &on_resize;
	// target= calloc(1, sizeof(ResizeTarget));

	gui_ui_unit = gui_default_ui(gui);
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
	//if ( 0 == strcmp("trash_art_button", cmp->name))
	//{
	//printf("");

	//}
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

	(cmp->draw)(cmp);
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
			gui_log("NO RENDER METHOD.\n");
		}
	}
}

void _gui_update_components_invasively(Gui* gui, GuiComponent* cont)
{
	for (int i = 0; i < cont->num_children; ++i)
	{
		GuiComponent* child = cont->children[i];
		if (!child)
		{
			gui_log("NULL CHILD found on parent.\n");
			continue;
		}
		else
		{
			if (!child->update)
			{
				continue;
			}
			child->update(child);
		}
		_gui_update_components_invasively(gui, child);
	}
}

void _gui_update_components(Gui* gui, GuiComponent* cont)
{
	for (int i = 0; i < cont->num_children; ++i)
	{
		GuiComponent* comp = cont->children[i];
		if (!comp)
		{
			gui_log("NULL CHILD found on parent.\n");
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

//#define GUI_INSET_DIST
static void draw_inset(GuiComponent* cmp)
{
	double idist = gui_default_ui(cmp->root);
	idist *= PHI_I * .25;
	RRect insetb = cmp->bounds;

	insetb.pos.x += idist;
	insetb.pos.y += idist;
	insetb.size.x -= idist * 2;
	insetb.size.y -= idist * 2;
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
		//if (!gui->borderless)
		//	draw_inset(gui->root);
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

	if (gui->root)
		_gui_update_components_invasively(gui, gui->root);
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
#ifdef DEBUG
	if (sub)
	{
		if (0 == strcmp(kGuiUnnamedComponent, sub->name))
		{
			printf("Naughty!\n");
		}
		printf("[%s]\n", sub->name);
	}
#endif
	return sub;
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


	//	double bigger = ( w > h ) ? w : h;
	//	double test = 1 - (1000.0 / bigger);
	//	test *= 2.5;
	//	//printf("Test: %f\n", test);
	//
	//
	//	gui_set_global_scale(test);
	//gui_set_global_scale(1);
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
		printf("%s", log);
	}
	// GuiComponent* local_root = _root;

	//	set the gui to be the size of the window
	//_root->bounds.
	if (gui_fb_w && gui_fb_h)
	{
		int w = *gui_fb_w;
		int h = *gui_fb_h;

		gui->root->bounds.pos.x  = w * -.5;
		gui->root->bounds.pos.y  = h * -.5;
		gui->root->bounds.size.x = w;
		gui->root->bounds.size.y = h;
	}
	else
	{
		gui_log("Warning, no framebuffer variables provided!");
	}
	gui->root->layout = NULL;
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

GuiComponent* gui_component_find(Gui* gui, const char* ident)
{
	return map_get(gui->items, ident);
}

double gui_default_ui(Gui* gui)
{
	if (!gui)
	{
		l_warning("can't default, no UI\n");
		return 32;
	}

	double ret = gui->scale_retina;
	if ( ret == 0 )
	{
		printf("Something went wrong, ret was ZERO\n");
		
	}
	double sc = gui_get_global_scale();
	if ( sc == 0 )
	{
		printf("Scale was 0 too wtf\n");
		
	}
	gui_ui_unit = gui->scale_retina * 1 * G_UI_BTN_SIZE * gui_get_global_scale();
	
	return gui_ui_unit;
}

int gui_component_register(Gui* gui, const char* ident, GuiComponent* cmp)
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

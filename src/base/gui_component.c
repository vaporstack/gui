//
//  gui_component.c
//  r4
//
//  Created by Andrew Macfarlane on 12/15/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#include "gui_component.h"

#include <stdlib.h>

#include <drw/drw.h>

#include <gui/gui.h>

#include <r4/r4.h>

#include <deps/vector/vector.h>

extern AppSettings app_settings;

// extern double _gui_scale_retina;
// extern bool _gui_debug;
// extern double _gui_w;
// extern double _gui_h;
// extern DebugSettings debug_settings;
// extern AppSettings app_settings;
/*
 static void mouse_motion(double x, double y)
 {


 }

 static void mouse_button(int button, int action, int mods)
 {

 }
 */

void gui_component_draw(GuiComponent* cmp, GuiComponent* gui)
{
	//	snoopin around
//	if (0 == strcmp(cmp->name, "colorpicker_palette"))
//	{
//		printf("AHHA\n");
//
//	}

	if (cmp->debug)
	{
		drw_type_draw(cmp->name);
	}

	if (!cmp->visible && !cmp->debug)
	{
		return;
	}

	if (!cmp->enabled && !cmp->debug)
	{
		return;
	}

	if (cmp->hidden)
		return;

	//r_line(0, 0, cmp->x, cmp->y);
	drw_push();
	double s = cmp->bounds.size.x;

	drw_translate2f(cmp->bounds.pos.x, cmp->bounds.pos.y);
	double sz = cmp->bounds.size.x;


	if (cmp->type == GUI_TYPE_PUSHBUTTON)
	{
		if (cmp->on)
		{
			// drw_color(0,0,0,1);
			if (cmp->focus)
			{
				drw_alpha(1);
			}
			else
			{
				drw_alpha(.7);
			}
		}
		else
		{
			drw_alpha(.333);
		}
		//	override for disabled
		//if ( !cmp->enabled )
		//{
		//	drw_alpha(.333);
		//}
	}
	else if (cmp->type == GUI_TYPE_TOGGLEBUTTON)
	{
		ButtonAttrs* attr = (ButtonAttrs*)cmp->data;

		//printf("pushh\n");
	}
	else
	{
		drw_alpha(.8);
		// drw_color(0,1,0,1);
	}

	//if ( !cmp->bypass )
	//	drw_rect(0, 0, cmp->bounds.size.x, cmp->bounds.size.y);

	if (cmp->art)
	{
		drw_push();
		drw_translate2f(s * .5, s * .5);

		drw_scale_u(cmp->bounds.size.x * .76);

		drw_set_colorbypass(true);
		WObject* art = cmp->art;

		drw_transform_apply(art->transform);
		for (int i = 0; i < art->num; i++)
		{
			WLine* line = art->lines[i];
			drw_poly(line);
		}
		
		drw_set_colorbypass(false);

		drw_pop();
	}
	else
	{
		
		if (!cmp->bypass)
		{
			if ( gui->debug && cmp->name)
			{
				drw_type_draw(cmp->name);
			}
			else
			{
				
				//gui_log("Tried to render null text");
			}
			
		}else{
			
		}
	}
	drw_rect(0, 0, cmp->bounds.size.x, cmp->bounds.size.y);
	drw_pop();

	gui_component_render_children(cmp, gui);
	drw_alpha_pop();
}

void gui_component_draw_bordered(GuiComponent* cmp, GuiComponent* gui)
{
	if (!cmp->visible)
		return;


	int pad = gui_default_ui(cmp->root) * .3333;

	double alpha = 1;
	if (cmp->on)
	{
		// drw_color(0,0,0,1);
		// drw_alpha(.8);
		if (!cmp->focus)
			alpha -= .2;
	}
	else
	{
		alpha = .3;
	}

	//	SHOW HACKS HAX

	drw_alpha(alpha);

	drw_push();
	drw_translate2f(cmp->bounds.pos.x - pad, cmp->bounds.pos.y - pad);

	//	performance hacks
	//if ( !gui->borderless)
	//	drw_rect(0, 0, cmp->bounds.size.x + (pad * 2), cmp->bounds.size.y + (pad * 2));

	drw_pop();
	drw_alpha_pop();
	gui_component_render_children(cmp, gui);
}
//
//double g_default_ui_size(void* gdata)
//{
//	Gui* gui = gdata;
//	return gui->scale_retina * G_UI_BTN_SIZE;
//}

RRect g_create_default_bounds(void* data)
{
	// Gui* gui = (Gui*)data;
	RRect  b;
	double sz = gui_default_ui(data);
//	double sz = R_UI_BTN_SIZE * app_settings.scale_retina * HC_RET;

	b.pos.x  = 0;
	b.pos.y  = 0;
	b.size.x = sz;
	b.size.y = sz;

	return b;
}

GuiComponent* gui_component_group_create(void* data, int num,
					 const char** names,
					 click_func funcs[6], WObject** arts,
					 bool* val)
{
	Gui* gui = (Gui*)data;

	gui_log("Creating group!");
	//double sz = R_UI_BTN_SIZE * gui->scale_retina * HC_RET;
	double sz =  gui_default_ui(gui);

	GuiComponent* base  = gui_component_create(gui);
	base->draw	  = &gui_component_draw_bordered;
	base->bounds.size.x = sz * num;
	base->bounds.size.y = sz;
	for (int i = 0; i < num; ++i)
	{
		const char* name = NULL;
		if (names)
		{
			name = names[i];
		}
		else
		{
			name = "unnamed";
		}
		click_func fun = NULL;
		if (funcs)
		{
			fun = funcs[i];
		}
		GuiComponent* sub = gui_button_create(gui, name, fun);
		//sub->x		   = sz * i;
		//sub->y		   = 0;
		sub->bounds.pos.x  = sz * i;
		sub->bounds.pos.y  = 0;
		sub->bounds.size.x = sz;
		sub->bounds.size.y = sz;
		if (arts)
		{
			sub->art = arts[i];
		}
		sub->draw = &gui_component_draw;

		gui_component_child_add(base, sub);
		gui_log("adding component: %s", name);
		gui_component_register(gui, name, sub);
		// sub->type = GUI_TYPE_TOGGLEBUTTON;
	}

	return base;
}

GuiComponent* gui_component_create(void* data)
{
	Gui* gui = (Gui*)data;

	GuiComponent* comp = calloc(1, sizeof(GuiComponent));
	//comp->x			   = 0;
	//comp->y			   = 0;//

	comp->bounds		   = g_create_default_bounds(gui);
	comp->animation_attrs      = NULL;
	comp->animating		   = false;
	comp->name		   = "unnamed_gui_component";
	comp->nice_name		= "Unnamed Gui Component";
	comp->bypass		   = false;
	comp->enabled		   = true;
	comp->target		   = NULL;
	comp->data		   = NULL;
	comp->on		   = true;
	comp->container		   = false;
	comp->visible		   = true;
	comp->hidden		   = false;
	comp->children		   = NULL;
	comp->parent		   = NULL;
	comp->hover		   = false;
	comp->type		   = 0;
	comp->num_children	 = 0;
	comp->art		   = NULL;
	comp->draw		   = gui_component_draw;
	comp->alignment.h	  = GUI_H_ORIENTATION_NONE;
	comp->alignment.v	  = GUI_V_ORIENTATION_NONE;
	comp->alignment.children_h = GUI_H_ORIENTATION_NONE;
	comp->alignment.children_v = GUI_V_ORIENTATION_NONE;
	comp->offset.x = comp->offset.y = 0;
	comp->draggable  = false;
	comp->find_focus = NULL;
	// comp->alignment.orientation = 0;
	comp->alignment.child_orientation = 0;
	comp->update			  = NULL;
	comp->layout			  = NULL;
	comp->children_vec		  = calloc(1, sizeof(struct vector_t));
	vector_init(comp->children_vec, 8, sizeof(GuiComponent));
	//#ifndef RPLATFORM_WIN
	r_input_delegate_clear(&comp->delegate);
	comp->delegate.parent = comp;
	comp->root = gui;

	//#endif

	// comp->delegate =
	return comp;
}

void gui_component_destroy(GuiComponent* comp)
{
	for (int i = 0; i < comp->num_children; i++)
	{
		GuiComponent* child = comp->children[i];
		gui_component_destroy(child);
	}

	vector_uninit(comp->children_vec);
	//free(comp);
}

void gui_component_set_children_type(GuiComponent* cmp, int type)
{
	for (int i = 0; i < cmp->num_children; ++i)
		cmp->children[i]->type = type;
}

void gui_component_set(GuiComponent* cmp, double x, double y)
{

	if (!cmp)
	{
		l_warning("No cmp! can't set");
		return;
	}

	double dx = x - cmp->bounds.pos.x;
	double dy = y - cmp->bounds.pos.y;

	//if ( gui )
	//	printf("Setting comp. %s delta is %f %f\n", cmp->name, dx, dy);

	/*
	if (cmp->name)
	{
		if (strcmp(cmp->name, "fast") == 0)
		{
			printf("GOT YOU\n");
		}
	}
*/

	for (int i = 0; i < cmp->num_children; ++i)
	{
		GuiComponent* child = cmp->children[i];
		double	dx2   = dx + child->bounds.pos.x;
		double	dy2   = dy + child->bounds.pos.y;

		gui_component_set(child, dx2, dy2);
	}

	cmp->bounds.pos.x = x;
	cmp->bounds.pos.y = y;
}

void gui_component_move(void* data, GuiComponent* cmp, double x, double y)
{
	//double dx  = x - cmp->bounds.pos.x;
	//double dy  = y - cmp->bounds.pos.y;
	Gui* gui = (Gui*)data;

	if (gui)
		if (gui->debug)
			gui_log("Moving comp. %s is %f %f", cmp->name, x, y);

	//printf("Moving comp. %s is %f %f\n", cmp->name, x, y);

	for (int i = 0; i < cmp->num_children; ++i)
	{
		GuiComponent* child = cmp->children[i];
		gui_component_move(data, child, x, y);
		//child->bounds.pos.x += dx;
		//child->bounds.pos.y += dy;
		//child->x += dx;
		//child->y += dy;
	}

	cmp->bounds.pos.x += x;
	cmp->bounds.pos.y += y;
	//cmp->x += x;
	//cmp->y += y;
}

void gui_component_size(GuiComponent* cmp, double x, double y)
{
	cmp->bounds.size.x = x;
	cmp->bounds.size.y = y;
}


void gui_component_child_remove(GuiComponent* parent, GuiComponent* child)
{
	//printf("TODO IMPLEMENT THIS\n");
	void* test_item = calloc(1, sizeof(GuiComponent));
	for (int i = 0; i < parent->children_vec->length; i++)
	{
		vector_get(parent->children_vec, i, test_item);
		GuiComponent* test = (GuiComponent*)test_item;
		if (test == child)
		{
			gui_log("FOUND IT");
		}
	}

	int index = -1;
	for (int i = 0; i < parent->num_children; i++)
	{
		GuiComponent* test = parent->children[i];
		if (test == child)
		{
			index = i;
			gui_log("EYSSSSS");
		}
	}

	if (index > -1)
	{
		gui_log("deleting");
		GuiComponent* victim = parent->children[index];
		gui_component_destroy(victim);
		victim = NULL;
		for (int i = index; i < parent->num_children - 1; i++)
		{
			parent->children[index] = parent->children[index + 1];
		}
		parent->num_children--;
	}
	free(test_item);
}

void gui_component_child_add(GuiComponent* parent, GuiComponent* child)
{
	if (child == NULL)
	{
		// Gui* gui = (Gui*)data;

		// if (gui->debug)
		gui_log("Cowardly refusing to add a NULL component.");
		return;
	}

	parent->num_children++;
	parent->children = realloc(
	    parent->children, sizeof(GuiComponent*) * (parent->num_children));
	parent->children[parent->num_children - 1] = child;
	child->parent				   = parent;

	vector_push_back(parent->children_vec, child);
	// printf("Added child vec %lu\n", parent->children_vec->length);
	// cont->num_children++;
	// if(debug_settings.gui )
	//	printf("Added child: %d %s\n", cont->num_children, comp->name);
}
/*
 void 			gui_component_align_children(GuiComponent* cont)
 {
 if(debug_settings.gui )
 printf("Aligning %s's %d children.\n", cont->name, cont->num_children);

 for ( int i = 0 ;i < cont->num_children; ++i )
 {
 GuiComponent * comp = cont->children[i];
 comp->bounds.pos.x = (cont->bounds.size.x * -.5) + 128 * i;
 comp->bounds.pos.y = (cont->bounds.size.y * -.5) + 0;
 }
 }
 */

static void layout_self_in_container(GuiComponent* cmp)
{
	double w = cmp->parent->bounds.size.x;
	double h = cmp->parent->bounds.size.y;
	//double prevx = cmp->bounds.pos.x;
	//	double prevy = cmp->bounds.pos.y;

	if (cmp->orientation.horizontal == GUI_H_ORIENTATION_FILL)
	{
		cmp->bounds.pos.x  = cmp->parent->bounds.pos.x;
		cmp->bounds.size.x = cmp->parent->bounds.size.x;
		//cmp->x		   = cmp->parent->x;
	}
	if (cmp->orientation.vertical == GUI_V_ORIENTATION_FILL)
	{
		cmp->bounds.pos.y  = cmp->parent->bounds.pos.y;
		cmp->bounds.size.y = cmp->parent->bounds.size.y;
		//cmp->y		   = cmp->parent->y;
	}

	if (cmp->orientation.horizontal == GUI_H_ORIENTATION_FILL && cmp->orientation.vertical == GUI_V_ORIENTATION_FILL)
	{
		//already done? neat!
	}
	else
	{

		double sw = cmp->bounds.size.x;
		double sh = cmp->bounds.size.y;

		double px = w * .5;
		px *= cmp->alignment.h;

		double py = h * .5;
		py *= cmp->alignment.v;

		if (cmp->alignment.h == 1)
			px += cmp->alignment.h * sw * -1;

		switch (cmp->alignment.v)
		{
		case -1:
			py += 0;
			break;
		case 0:
			py -= sh * .5;
			break;
		case 1:
			py -= sh * 1;
			break;
		default:
			break;
		}
		// py += cmp->alignment.v * sh * -1;

		// if ( cmp->parent->container )
		gui_component_set(cmp, px, py);
		// gui_component_move(cmp, prevx, prevy);
	}

	//other stuff?
}

static void layout_children(GuiComponent* cmp)
{
	for (int i = 0; i < cmp->num_children; ++i)
	{
		GuiComponent* ch = cmp->children[i];
		gui_component_layout(ch);
	}
}

void gui_component_layout(GuiComponent* cmp)
{

	//	todo: chuck all this in the trash in favor of the simpler
	// each-thing-has-its-own-layout-function?

	//	where do i fit in
	if (cmp->parent)
		layout_self_in_container(cmp);

	//	where do my children go
	if (cmp->container)
		layout_children(cmp);

	//	custom overrides
	if (cmp->layout)
		cmp->layout(cmp);
}

//static void apply_layout_h(GuiComponent*)

void gui_component_layout_horizontal(GuiComponent* comp)
{

	int    num = comp->num_children;
	double w   = comp->bounds.size.x;
	double h   = comp->bounds.size.y;

	double inc = w / num;
	for (int i = 0; i < num; i++)
	{
		double	x     = inc * i;
		double	y     = h * .5;
		GuiComponent* child = comp->children[i];
		double	sx    = comp->bounds.pos.x + x;
		double	sy    = comp->bounds.pos.y + y;
		gui_component_set(child, sx, sy);
	}
	/*
	for (int i = 0; i < num; i++)
	{

		GuiComponent* child = comp->children[i];
		if ( i == 0 )
		{
			comp->x = child->x;
			comp->y = child->y;
		}

		if (!child)
		{
			printf("NULL CHILD\n");
			continue;
		}

		if (comp->alignment.children_h == GUI_H_ORIENTATION_FILL)
		{
			child->bounds.size.x = w / num;
		}
		if (comp->alignment.children_v == GUI_V_ORIENTATION_FILL)
		{
			child->bounds.size.x = h;
		}
		double ret = drw_query_dpi();
		double cy	   = h * .5 - (comp->bounds.size.y * .5) * ret;
		double cx	   = (w / num) * i - (comp->bounds.size.x * .5) * ret;
		child->x	    = cx;
		child->y	    = cy;
		child->bounds.pos.x = cx;
		child->bounds.pos.y = cy;
	}
	 */
}

void gui_component_layout_vertical(GuiComponent* cmp)
{
	double w = cmp->bounds.size.x;
	double h = cmp->bounds.size.y;
	double pad = PHI_I * gui_default_ui(cmp->root);
	
	//	assuming all elements are the same height lol
	int num = cmp->num_children;
	GuiComponent* ch = cmp->children[0];
	double stack = num * ch->bounds.size.y;
	double diff = h - stack;
	
	double pad2 = diff / (num);
	double offset = (h - 0) / num;
	for ( int i = 0; i < num; i++ )
	{
		GuiComponent* ch = cmp->children[i];
		ch->bounds.pos.y = cmp->bounds.pos.y + cmp->bounds.size.y -( i * offset + ch->bounds.size.y) - pad2 * .5;
	}
	
	
}

void	gui_component_fit_to_children(GuiComponent* cmp)
{
	//	something about this is fucked, forgetting a delta somewhere
	double minx, miny, maxx, maxy;
	minx = miny = INFINITY;
	maxx = maxy = -1 * INFINITY;
	
	for ( int i = 0 ; i < cmp->num_children; i++ )
	{
		GuiComponent* ch = cmp->children[i];
		if ( ch->bounds.pos.x < minx )
			minx = ch->bounds.pos.x;
		if ( ch->bounds.pos.y < miny )
			miny = ch->bounds.pos.x;
		if ( ch->bounds.pos.x + ch->bounds.size.x > maxx )
			maxx = ch->bounds.pos.x + ch->bounds.size.x;
		if ( ch->bounds.pos.y + ch->bounds.size.y > maxy )
			maxy = ch->bounds.pos.y + ch->bounds.size.y;
	}
	
	gui_component_set(cmp, minx, miny);
	gui_component_size(cmp, maxx - minx, maxy - miny);
	
}

void gui_component_render_children(GuiComponent* comp, GuiComponent* gui)
{
	for (int i = 0; i < comp->num_children; ++i)
	{
		GuiComponent* child = comp->children[i];
		if (!child)
		{
			gui_log("!");
		}
		else
		{
			if (child->draw != NULL)
			{
				RColor8 c = drw_checkcolor();
				child->draw(child, gui);
				RColor8 c2 = drw_checkcolor();
				if (c.r != c2.r)
				{
					gui_log("JACCUSE");
				}
			}
		}
	}
}

GuiComponent* gui_component_find_pointerfocus(GuiComponent* cont, double x,
					      double y)
{
#ifndef RPLATFORM_WIN
	if (!cont->enabled)
		return NULL;

	if (cont->hidden)
		return NULL;

	for (int i = 0; i < cont->num_children; ++i)
	{
		GuiComponent* sub = cont->children[i];
		GuiComponent* sub2 =
		    gui_component_find_pointerfocus(sub, x, y);
		if (sub2)
		{
			return sub2;
		}

		if (sub->find_focus)
		{
			if (sub->find_focus(sub, x, y))
			{
				sub->focus = true;
				return sub;
			}
		}
		else
		{
			if (r_rect_within(sub->bounds, x, y))
			{
				if (sub->enabled)
				{
					sub->focus  = true;
					cont->focus = false;
					return sub;
				}
			}
			else
			{
				sub->focus = false;
			}
		}
	}
	if (!cont->enabled)
	{
		return NULL;
	}
	if (!cont->visible)
	{
		return NULL;
	}

	if (r_rect_within(cont->bounds, x, y))
	{
		if (cont->bypass)
		{
			return NULL;
		}
		cont->focus = true;

		return cont;
	}

#endif

	return NULL;
}

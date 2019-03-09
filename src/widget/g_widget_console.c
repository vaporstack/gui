
//  gui_console.c
//  gui_console
//
//  Created by Andrew Macfarlane on 20/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_widget_console.h"

#include <drw/drw.h>
#include <r4/r4.h>
#include <string.h>

extern AppSettings app_settings;

// static char** logdata = NULL;
// int num = 32;

static void update(GuiComponent* cmp)
{

	// printf("!");
}

#ifndef RPLATFORM_WIN
extern char** application_log;
#endif

static void draw(struct GuiComponent* comp, struct GuiComponent* gui)
{

#ifndef RPLATFORM_WIN
	//	todo:
	//	temporarily disabling this,
	//	logger has memory problems
	//return;

	drw_push();
	drw_translate2f(app_settings.framebuffer_width * -.5,
			app_settings.framebuffer_height * -.45);
	// drw_translate_y(app_settings.font_size * 2);
	// printf(".");

	for (int i = 0; i < 1; ++i)
	{

		char* l = application_log[i];
		// printf("%s\n", l);
		if (l != NULL)
		{
			if (l[0] == '\0')
				continue;
			drw_translate_y(app_settings.font_size * -4);
			// int len = strlen(l);
			// printf("%d\n", len);
			drw_alpha(.5);
			drw_type_draw(l);
			drw_alpha_pop();
		}
		// if( 0 == strcmp("", l));
	}

#endif

	drw_pop();
	// drw_type_draw(logdata);
}

GuiComponent* gui_console_create(void* gui)
{
	GuiComponent* cmp = gui_component_create(gui);
	cmp->update       = &update;
	cmp->draw	 = &draw;
	cmp->name	 = "Console Widget";

	// const char* logs = r_read_file_as_text_2(app_settings.log_file);

	// logdata = malloc(sizeof(char**) * 64);
	// size_t size = strsplit(path, chunks, "/");
	// num = r_strsplit(logs, logdata, "\n");
	// printf("log has %d lines\n", num);

	// char* ptr;
	// long ret;
	// ret =  strtol(chunks[2], &ptr, 10);

	return cmp;
}

void gui_console_destroy()
{
}

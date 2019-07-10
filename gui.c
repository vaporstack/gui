
//  gui.c
//  gui
//
//  Created by Andrew Macfarlane on 11/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "gui.h"

#include "src/etc/gui_log.h"

//TODO:
//	remove this shit
#include <r4/r4.h>
extern AppSettings app_settings;

double	gui_global_scale = 1;
double*     gui_alpha_mult = NULL;
static bool screenspace    = false;
double*     gui_cursor_x   = NULL;
double*     gui_cursor_y   = NULL;

int* gui_fb_w = NULL;
int* gui_fb_h = NULL;
bool gui_righthanded = false;


double gui_ui_unit = 1;

int gui_check_version_match(const char* header_generated_version)
{
	char* version = gui_get_version_string();
	int   matches = (0 == strcmp(version, header_generated_version));
	free(version);
	return matches;
}

char* gui_get_version_string(void)
{
	char* buf = calloc(256, sizeof(char));
	sprintf(buf, "%d.%d.%d", GUI_VERSION_MAJOR, GUI_VERSION_MINOR, GUI_VERSION_PATCH);
	return buf;
}

void gui_get_default_bounds(double* x, double* y)
{
	gui_log("ERROR THIS IS A FAILED CODEPATH");
	exit(3);
	//double sz = R_UI_BTN_SIZE * app_settings.scale_retina * HC_RET;
	//*x	= sz;
	//*y	= sz;
}


void gui_provide_global_alpha_mult(double* v)
{
	gui_alpha_mult = v;
}

void		gui_set_global_scale(double sc)
{
	gui_global_scale = sc;
	gui_ui_unit = sc;
}

double		gui_get_global_scale(void)
{
	return gui_global_scale;
}

void gui_provide_framebuffer_variables(int* x, int* y)
{
	gui_fb_w = x;
	gui_fb_h = y;
}

void gui_provide_cursor_pos(double* x, double* y)
{
	gui_cursor_x = x;
	gui_cursor_y = y;
}

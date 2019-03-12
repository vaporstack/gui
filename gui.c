
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

static bool screenspace = false;


int gui_check_version_match(const char* header_generated_version)
{
	char* version =gui_get_version_string();
	int matches = (0 == strcmp(version, header_generated_version));
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
//
//  gui_log.c
//  gui
//
//  Created by vs on 3/11/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "gui_log.h"

#include <stdarg.h>
#include <stdio.h>

#define GUI_LOG_MAX 256
void gui_log(char* format, ...)
{
	
	char buf[GUI_LOG_MAX];
	sprintf(buf, "%s", format);
	va_list args;
	va_start(args, format);
	vsprintf(buf, format, args);
	va_end(args);
#ifdef DEBUG
	printf("[gui ]: %s\n", buf);
#else
	printf("DO NOTHING LATER: %s\n", buf);
#endif
}

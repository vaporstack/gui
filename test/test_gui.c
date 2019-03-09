

#include <gui/gui.h>

int main(int argc, char** argv)
{
	//	simple test program for wash.
	//	create some geometry, write an svg, possibly a png?

	printf("Running gui tests.\n");
	printf("making sure gui header matches library.\n");

	char* buf = calloc(32, sizeof(char));
	sprintf(buf, "%d.%d.%d", GUI_VERSION_MAJOR, GUI_VERSION_MINOR,
		GUI_VERSION_PATCH);

	bool match = gui_check_version_match(buf);
	free(buf);

	if (match)
	{
		printf("Version matches.\n");
	}
	else
	{
		printf("Version does not match!!\n");
		// free(buf);
		return 88;
	}

	// WLine   line;
	// WObject object;

	return 0;
}

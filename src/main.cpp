#include "app.h"

int main()
{
	App application;
	
	if (!application.init())
	{
		application.runMainLoop();
		application.terminate();
	}

    return 0;
}

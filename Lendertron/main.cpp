#include "Application.h"

int main(int argc, char** argv)
{
	//Instatntiates an application object
	Application app;
	app.SetParams(argc, argv);
	return app.Run();
}
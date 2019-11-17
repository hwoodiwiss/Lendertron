#include "Application.h"

int main(int argc, char** argv)
{
	Application app;
	app.SetParams(argc, argv);
	return app.Run();
}
#include "Utilities.h"
#include "Window.h"

int main(int argc, char *args[])
{
	Window window;

	window.createWindow("Cubes Instanced", 1920, 1080);

	while (!window.isClosed())
	{
		window.update();
		utilities::memoryMeasurent(window.getMaxVirutalMem(), window.getMaxPhysicalMem());
	}
	utilities::saveInformation(window.getProcessInfo());

	return 0;
}
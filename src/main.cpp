#include "chip++9.hpp"

int main() {
	constexpr int16_t WIDTH = 320, HEIGHT = 240;

	Tigr* screen = tigrWindow(WIDTH, HEIGHT, "Chip++9", 0);
	while (!tigrClosed(screen)) {
		tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
		tigrPrint(
			screen, tfont, 120, 110, tigrRGB(0xff, 0xff, 0xff), "Chip++9");
		tigrUpdate(screen);
	}
	tigrFree(screen);
	return 0;

	// 	chip8 myChip8;

	// int main(int argc, char **argv)
	// {
	//   // Set up render system and register input callbacks
	//   setupGraphics();
	//   setupInput();

	//   // Initialize the Chip8 system and load the game into the memory
	//   myChip8.initialize();
	//   myChip8.loadGame("pong");

	//   // Emulation loop
	//   for(;;)
	//   {
	//     // Emulate one cycle
	//     myChip8.emulateCycle();

	//     // If the draw flag is set, update the screen
	//     if(myChip8.drawFlag)
	//       drawGraphics();

	//     // Store key press state (Press and Release)
	//     myChip8.setKeys();
	//   }

	//   return 0;
	// }
}

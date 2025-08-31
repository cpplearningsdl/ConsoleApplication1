#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H 
#include <SDL3/SDL.h>
#include <array>
 

class inputManager {
public:
	static inputManager& getInstance(); 
	bool pollEvents(); 

	// Keyboard queries
	bool isKeyDown(SDL_Scancode key) const { return keyStates[key]; }
	bool wasKeyPressed(SDL_Scancode key) const { return keyPressed[key]; }
	bool wasKeyReleased(SDL_Scancode key) const { return keyReleased[key]; }

	// Mouse queries
	int getMouseX() const { return mouseX; }
	int getMouseY() const { return mouseY; }
	bool isMouseButtonDown(Uint8 button) const { return mouseButtons[button]; }

private:
	 
	inputManager();
	~inputManager() = default;

	inputManager(const inputManager&) = delete;
	inputManager& operator=(const inputManager&) = delete;
	 
	//bool running = true;

		// State storage
	std::array<bool, SDL_SCANCODE_COUNT> keyStates{};
	std::array<bool, SDL_SCANCODE_COUNT> keyPressed{};
	std::array<bool, SDL_SCANCODE_COUNT> keyReleased{};

	int mouseX = 0;
	int mouseY = 0;
	std::array<bool, 5> mouseButtons{};
};

#endif // INPUTMANAGER_H


#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H 
#include <SDL3/SDL.h>
#include <array>
#include <vector>
 

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
	bool wasMouseReleased() { return mouseReleased; }

	const std::vector<Uint32>& getEvents() const { return eventTypesThisFrame; }

private:
	 
	inputManager();
	~inputManager() = default;

	inputManager(const inputManager&) = delete;
	inputManager& operator=(const inputManager&) = delete;
	  
		// State storage
	std::vector<Uint32> eventTypesThisFrame;
	std::array<bool, SDL_SCANCODE_COUNT> keyStates{};
	std::array<bool, SDL_SCANCODE_COUNT> keyPressed{};
	std::array<bool, SDL_SCANCODE_COUNT> keyReleased{};

	int mouseX = 0;
	int mouseY = 0;
	bool mouseReleased = false;
	std::array<bool, 5> mouseButtons{};
};

#endif // INPUTMANAGER_H


#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SDL3/SDL.h>
#include <string>

class windowManager {
public:
	static windowManager& initWindowManager();
	bool openWindow(const std::string& title, int width, int height, Uint32 flags = SDL_WINDOW_RESIZABLE);

	SDL_Renderer* getRenderer() const;
	SDL_Window* getWindow() const;
	void closeWindow();

private:
	windowManager();  
	~windowManager();

	windowManager(const windowManager&) = delete;
	windowManager& operator=(const windowManager&) = delete;

	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif // WINDOWMANAGER_H

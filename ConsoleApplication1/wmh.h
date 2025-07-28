#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SDL3/SDL.h>
#include <string>

class windowManager {
public:
	static windowManager& getInstance();

	bool createWindow(const std::string& title, int width, int height, Uint32 flags = 0);
	SDL_Window* getWindow() const;
	void destroyWindow();

private:
	windowManager();
	~windowManager();

	windowManager(const windowManager&) = delete;
	windowManager& operator=(const windowManager&) = delete;

	SDL_Window* window;
};

#endif // WINDOWMANAGER_H
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SDL3/SDL.h>
#include <string>

class windowManager {
public:
	static windowManager& create(const std::string& title, int width, int height);

	SDL_Window* getWindow() const;
	void destroyWindow();

private:
	windowManager(const std::string& title, int width, int height);
	~windowManager();

	windowManager(const windowManager&) = delete;
	windowManager& operator=(const windowManager&) = delete;

	SDL_Window* window;
};

#endif // WINDOWMANAGER_H

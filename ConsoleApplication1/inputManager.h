#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class inputManager {
public:
	static inputManager& getInstance();

	bool pollEvents();

private:
	inputManager() = default;
	~inputManager() = default;

	inputManager(const inputManager&) = delete;
	inputManager& operator=(const inputManager&) = delete;



	bool running = true;
};

#endif // INPUTMANAGER_H


#pragma once
#include <vector> 

struct light;
struct SDL_Color;
class position;

class lightManager {
	public:
		lightManager();
		~lightManager();


		std::vector<light>& getLights() { return lights;}
		void addLight(position p, float radius, float intensity, SDL_Color color );
		void update(float deltaTime);
	private:
		std::vector<light> lights;
};
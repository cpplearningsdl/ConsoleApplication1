#pragma once
#include <vector>
#include <algorithm> 
#include "level.h"
#include "logManager.h"


class game;

void loadLevel(game& g);

levelData loadLevelFile(int levelNumber);

void loadEntities(game& g);
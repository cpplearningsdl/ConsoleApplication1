//#pragma once
//
//for some reason the first frame of pause menu opening tries to use the wrong key! missing 'background' from pause_menu_background etc
//
//right now textures and frame data is looked up via a string key, can store pointers when loading animations instead
//
//instead of grid based movement we can use floats and move partial squares and still have close to n(1) by using the center of entities hitbox to see what square they are in, and use 1d array to hold pointer to that entity
//in the array. then for attacks gather all squares in radius, then gather entities in those squares, then do a final radius check to see if they are actually in the radius not just in square touching radius
//

#pragma once
#include "buttonData.h"

 
inline buttonsActionData morphToCloseButton(int id) {
	return {
	id,            // id
	false,         // clicked
	butEnum::CLOSEMENU, // action
	-1,            // actionIndex1
	-1,            // actionIndex2
	0,             // value1
	0              // value2
	};
}
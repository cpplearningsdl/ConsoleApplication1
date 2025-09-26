#pragma once
enum class butEnum : int {
	NONE,
	CLOSEMENU,
	RESUME
};

inline const char* butDataToString(butEnum e) {
	switch (e) {
	case butEnum::NONE:			 return"NONE";
	case butEnum::RESUME:		 return "RESUME";
	case butEnum::CLOSEMENU:	 return "CLOSEMENU";
	}
}

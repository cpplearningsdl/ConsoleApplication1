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
inline butEnum stringToButEnum(const std::string& s) {
	if (s == "NONE")       return butEnum::NONE;
	if (s == "RESUME")     return butEnum::RESUME;
	if (s == "CLOSEMENU")  return butEnum::CLOSEMENU;
	throw std::invalid_argument("Invalid string for butEnum: " + s);
}
#pragma once
#include "../Scenes/Button.h"

namespace BUTTONMASK {
	const ButtonMask COMPONENT_TEXTURED = 1 << 0; //with image
	const ButtonMask COMPONENT_DRAWN = 1 << 1; //created from font / text
	const ButtonMask COMPONENT_SCENE = 1 << 2; //leads to scene
	const ButtonMask COMPONENT_SWITCH = 1 << 3; //leads to switch
}

struct Switch {
	bool _switch_ = false;
};
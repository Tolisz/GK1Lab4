#pragma once

#include <map>
#include <list>

#include "object_camera.h"

class G
{
public:

	// Kamery
	static OCamera* current_camera;
	static std::map<int, OCamera> cameras;

	// timing
	static float deltaTime;	// time between current frame and last frame
	static float lastFrame;

	// Drgania 
	static bool vibration;

	// Tryb Cieniowania
	//
	// 0 - stałe
	// 1 - Gourauda
	// 2 - Phonga
	//
	static std::uint8_t shading; 

	// źródła światła
};
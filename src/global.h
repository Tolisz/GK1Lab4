#pragma once

#include <map>
#include <list>

#include "object_camera.h"
#include "object_light.h"

class G
{
public:

	// Kamery
	static OCamera* current_camera;
	static std::map<int, OCamera> cameras;

	// Światło
	static std::list<OLight> lights;

	// timing
	static float deltaTime;	// time between current frame and last frame
	static float lastFrame;

	// Drgania 
	static bool vibration;

};
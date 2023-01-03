#include "global.h"

// Kamery
OCamera* G::current_camera = nullptr;// (glm::vec3(0.0f, 1.0f, 0.0f));
std::map<int, OCamera> G::cameras;

// Światło
std::list<OLight> G::lights;


// timing
float G::deltaTime = 0.0f;
float G::lastFrame = 0.0f;

// Drgania 
bool G::vibration = false;
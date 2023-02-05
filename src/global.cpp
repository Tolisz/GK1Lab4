#include "global.h"

// Kamery
OCamera* G::current_camera = nullptr;// (glm::vec3(0.0f, 1.0f, 0.0f));
std::map<int, OCamera> G::cameras;

// timing
float G::deltaTime = 0.0f;
float G::lastFrame = 0.0f;

// Drgania 
bool G::vibration = false;

// Tryb Cieniowania
//
// 0 - stałe
// 1 - Gourauda
// 2 - Phonga
//
std::uint8_t G::shading = 2;


// źródła światła
std::map<int, OLightCube> G::light_cubes;
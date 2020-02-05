#include "ManagerIrrKlang.h"

#include <chrono>
#include <iostream>

using namespace irrklang;
using namespace Aftr;
using namespace std::chrono;

ISoundEngine* ManagerIrrKlang::engine = nullptr;

void ManagerIrrKlang::init()
{
    engine = createIrrKlangDevice();

    if (!engine) {
        std::cerr << "ManagerIrrKlang::init(): Failed to create ISoundEngine" << std::endl;
    } else {
        std::cout << "Initialized IrrKlang..." << std::endl;
    }
}

void ManagerIrrKlang::shutdown()
{
    if (engine != nullptr) {
        engine->drop();
    }
}

ISoundEngine* ManagerIrrKlang::getEngine()
{
    return engine;
}

vec3df ManagerIrrKlang::convertVec(const Vector& v)
{
    // irrlicht uses left-handed coordinate system with
    // +x to the right, and +y up, and +z into the screen
    return vec3df(-v.y, v.z, v.x);
}

void ManagerIrrKlang::updateListener(const Camera& cam)
{
    // calculate delta time since last update
    static steady_clock::time_point lastTime = steady_clock::now();
    double deltaTime = duration_cast<duration<double>>(steady_clock::now() - lastTime).count();
    lastTime = steady_clock::now();

    // calculate velocity of camera since last update
    static Vector lastPos = cam.getPosition();
    Vector vel = (cam.getPosition() - lastPos) / deltaTime;
    lastPos = cam.getPosition();

    // make call to update camera position, rotation, and velocity
    ManagerIrrKlang::getEngine()->setListenerPosition(convertVec(cam.getPosition()),
                                                      convertVec(cam.getLookDirection()),
                                                      convertVec(vel),
                                                      convertVec(Vector(0, 0, 1)));
}
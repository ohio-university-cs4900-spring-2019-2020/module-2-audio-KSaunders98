#pragma once

#include "irrKlang.h"

#include "Camera.h"
#include "Vector.h"

namespace Aftr {
 // Very basic singleton manager for working with IrrKlang.
 class ManagerIrrKlang {
  public:
    static void init();
    static void shutdown();
    static irrklang::ISoundEngine* getEngine();
    static irrklang::vec3df convertVec(const Vector& v);
    static void updateListener(const Camera& cam);
  private:
    static irrklang::ISoundEngine* engine;
 };
}


// CelestialBody.cpp
#include "CelestialBody.h"

namespace SolarSystem {

    CelestialBody::CelestialBody()
    : rotation(0.0f),
      orbit(0.0f),
      rotationPeriod(0.0f),
      orbitalPeriod(0.0f),
      radius(1.0f),
      semiMajorAxis(1.0f),
      distance(1.0f),
      worldToOrbit(nullptr),
      texture_id(0)
    {
        rotation = 0.0f;
        orbit = 0.0f;
        space = glm::mat4(0.0f);
    };

    void CelestialBody::Create(glm::mat4* _worldToOrbit, float _rotationPeriod, float _orbitalPeriod, float _radius, float _semiMajorAxis, float _distance, const char* path) {
        rotationPeriod = _rotationPeriod;
        orbitalPeriod = _orbitalPeriod;
        radius = _radius * earthDiameter;
        semiMajorAxis = _semiMajorAxis * AU;
        distance = _distance;
        texture_id = 0;
        LoadTexture(path);
    }

    void CelestialBody::Update() {
        time += deltaTime;

        rotationRateEarth = deltaTime;
        orbitalPeriodEarth = rotationRateEarth * 365.0f;

        rotation += rotationRateEarth / rotationPeriod;
        orbit += orbitalPeriodEarth / orbitalPeriod;

        glm::mat4 world = glm::mat4(1.0f);
        if (!worldToOrbit)
            worldToOrbit = &world;
        if (useRealMetrics) {
            space = glm::rotate(*worldToOrbit, orbit, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))) *
                glm::translate(world, glm::vec3(semiMajorAxis, 0.0f, 0.0f)) *
                glm::rotate(world, rotation, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))) *
                glm::scale(world, glm::vec3(radius, radius, radius));
        }
        else {
            space = glm::rotate(*worldToOrbit, orbit, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))) *
                glm::translate(world, glm::vec3(distance, 0.0f, 0.0f)) *
                glm::rotate(world, rotation, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
        }
    }

    void CelestialBody::Draw(int32 _world_location, int _primitive_count) {
        //glBindTexture(GL_TEXTURE_2D, texture_id);
        //glUniformMatrix4fv(_world_location, 1, GL_FALSE, glm::value_ptr(space));
        //glDrawArrays(GL_TRIANGLES, 0, _primitive_count);
    }

    glm::mat4* CelestialBody::GetSpace() {
        return &space;
    }

    void CelestialBody::LoadTexture(const char* path)
    {
        if (!Utility::CreateTextureFromFile(texture,
            path))
        {
            return;
        }
    }
}

// CelestialBody.h

#pragma once

#include "Settings.h"

namespace SolarSystem {

    extern const float AU;
    extern const float earthDiameter;
    extern float rotationRateEarth, orbitalPeriodEarth;
    extern glm::mat4 world, view;
    extern bool useRealMetrics;

    class CelestialBody {
    public:
        CelestialBody();

        void Create(float _rotationPeriod = 0.0f, float _orbitalPeriod = 0.0f, float _radius = 0.0f, float _semiMajorAxis = 0.0f, float _distance = 0.0f, const char* path = "", glm::mat4* _worldToOrbit = &view);
        void Update();
        void Draw(GLint _world_location, int _primitive_count);


        glm::mat4* GetSpace();
        void LoadTexture(const char* path);

    private:
        float rotation, orbit;
        float rotationPeriod, orbitalPeriod, radius, semiMajorAxis, distance;
        glm::mat4 space;
        glm::mat4* worldToOrbit;
        GLuint texture_id;
    };
}

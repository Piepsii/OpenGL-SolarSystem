// CelestialBody.h

#pragma once

#include <Utility.h>
#include <Settings.h>

namespace SolarSystem {

    class CelestialBody {
    public:
        CelestialBody();

        void Create(glm::mat4* _worldToOrbit, float _rotationPeriod = 0.0f, float _orbitalPeriod = 0.0f, float _radius = 0.0f, float _semiMajorAxis = 0.0f, float _distance = 0.0f, const char* path = "" );
        void Update();
        void Draw(int32 _world_location, int _primitive_count);


        glm::mat4* GetSpace();
        void LoadTexture(const char* path);

        const static bool useRealMetrics = false;
        const float deltaTime = 0.00001f;
        float rotationRateEarth = deltaTime , orbitalPeriodEarth = rotationRateEarth * 365.0f ;
    private:
        float time{ 0.0f };
        float rotation, orbit;
        float rotationPeriod, orbitalPeriod, radius, semiMajorAxis, distance;
        glm::mat4 space;
        glm::mat4* worldToOrbit;
        uint32 texture_id;
        Texture texture;

    };
}

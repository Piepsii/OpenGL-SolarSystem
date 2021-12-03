// CelestialBody.h

#pragma once

#include <Utility.h>

namespace SolarSystem {

    class CelestialBody {
    public:
        CelestialBody();

        void Create( float _rotationPeriod,
                    float _orbitalPeriod,
                    float _distance,
                    const char* path);
        void Update();
        void Draw(RenderBackend& _backend,
                  Framebuffer& _rendertarget,
                  ShaderProgram& _world_program,
                  VertexBuffer& _vertex_buffer,
                  VertexLayout& _vertex_layout,
                  SamplerState& _linear_sampler);


        glm::mat4* GetSpacePtr();
        void SetSpaceToOrbit(glm::mat4*_space);
        void SetOffset(int _offset);
        void SetCount(int _count);
        void LoadTexture(const char* path);

        const float deltaTime = 0.000001f;
        float rotation_rate_earth = deltaTime , orbital_period_earth = rotation_rate_earth * 365.0f ;
    private:
        float time{ 0.0f };
        float rotation, orbit;
        float rotation_period, orbital_period, distance, tilt;
        glm::vec3 position;
        glm::mat4 local_space;
        glm::mat4 perspective, orthographic;
        glm::mat4* space_to_orbit;
        Texture texture;

        int offset, count;

    };
}

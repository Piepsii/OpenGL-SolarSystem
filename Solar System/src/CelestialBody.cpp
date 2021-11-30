// CelestialBody.cpp
#include "CelestialBody.h"

namespace SolarSystem {

    CelestialBody::CelestialBody() {
        rotation = 0.0f;
        orbit = 0.0f;
        space = glm::mat4(0.0f);
    };

    void CelestialBody::Create(float _rotationPeriod, float _orbitalPeriod, float _radius, float _semiMajorAxis, float _distance, const char* path, glm::mat4* _worldToOrbit) {
        rotationPeriod = _rotationPeriod;
        orbitalPeriod = _orbitalPeriod;
        radius = _radius * earthDiameter;
        semiMajorAxis = _semiMajorAxis * AU;
        distance = _distance;
        worldToOrbit = _worldToOrbit;
        texture_id = 0;
        LoadTexture(path);
    }

    void CelestialBody::Update() {
        rotation += rotationRateEarth / rotationPeriod;
        orbit += orbitalPeriodEarth / orbitalPeriod;

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

    void CelestialBody::Draw(GLint _world_location, int _primitive_count) {
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glUniformMatrix4fv(_world_location, 1, GL_FALSE, glm::value_ptr(space));
        glDrawArrays(GL_TRIANGLES, 0, _primitive_count);
    }

    glm::mat4* CelestialBody::GetSpace() {
        return &space;
    }

    void CelestialBody::LoadTexture(const char* path)
    {
        //int image_width = 0, image_height = 0, image_components = 0;
        //auto image_data = stbi_load(path, &image_width, &image_height, &image_components, STBI_rgb_alpha);
        //assert(image_data);

        //glGenTextures(1, &texture_id);
        //glBindTexture(GL_TEXTURE_2D, texture_id);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        //glGenerateMipmap(GL_TEXTURE_2D);
        ////assert(glGetError == GL_NO_ERROR);
        //stbi_image_free(image_data);
    }
}

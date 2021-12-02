// CelestialBody.cpp
#include "CelestialBody.h"

namespace SolarSystem {

	CelestialBody::CelestialBody()
		: rotation(0.0f),
		orbit(0.0f),
		rotation_period(0.0f),
		orbital_period(0.0f),
		distance(0.0f),
		count(0),
		offset(0),
		perspective(glm::perspective(3.141592f * 0.25f,
									 16.0f / 9.0f,
									 1.0f,
									 300.0f)),
		orthographic(glm::ortho(0.0f,
								1920.0f,
								1080.0f,
								0.0f)),
		world_space(glm::mat4(1.0f)),
		local_space(glm::mat4(1.0f)),
		position(glm::vec3(0.0f, 0.0f, 0.0f)),
		view_space(glm::rotate(glm::mat4(1.0f),
							   0.5f,
							   glm::vec3(1.0f, 0.0f, 0.0f)) * 
			 glm::translate(glm::mat4(1.0f),
							glm::vec3(0.0f, -30.0f, -70.0f)))
	{
	};


	void CelestialBody::Create(float _rotationPeriod,
							   float _orbitalPeriod,
							   float _distance,
							   const char* path) {
		position.x = _distance;
		rotation_period = _rotationPeriod;
		orbital_period = _orbitalPeriod;
		LoadTexture(path);
	}

	void CelestialBody::Update() {
		time += deltaTime;

		rotation_rate_earth = deltaTime;
		orbital_period_earth = rotation_rate_earth * 365.0f;

		rotation += rotation_rate_earth / rotation_period;
		orbit += orbital_period_earth / orbital_period;

		local_space = view_space *
					 glm::rotate(glm::mat4(1.0f),
								 orbit,
								 glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))) *
					 glm::translate(glm::mat4(1.0f),
									position) *
					 glm::rotate(glm::mat4(1.0f),
								 rotation,
								 glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void CelestialBody::Draw(RenderBackend &_backend,
							 Framebuffer &_rendertarget,
							 ShaderProgram &_world_program,
							 VertexBuffer &_vertex_buffer,
							 VertexLayout &_vertex_layout,
							 SamplerState &_linear_sampler) {
		_backend.SetShaderProgram(_world_program);
		_backend.SetShaderUniform(_world_program,
								 UNIFORM_TYPE_MATRIX,
								 "u_projection",
								 1, glm::value_ptr(perspective));
		_backend.SetShaderUniform(_world_program,
								 UNIFORM_TYPE_MATRIX,
								 "u_world",
								 1, glm::value_ptr(local_space));
		_backend.SetVertexBuffer(_vertex_buffer);
		_backend.SetVertexLayout(_vertex_layout);
		_backend.SetTexture(texture);
		_backend.SetSamplerState(_linear_sampler);
		_backend.SetBlendState(false);
		_backend.SetDepthState(true, true);
		_backend.SetRasterizerState(CULL_MODE_BACK, FRONT_FACE_CW);
		_backend.Draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, count);
	}

	glm::mat4* CelestialBody::GetSpace() {
		return &local_space;
	}

	void CelestialBody::SetSpaceToOrbit(glm::mat4* _space)
	{
		space_to_orbit = _space;
	}

	void CelestialBody::SetOffset(int _offset)
	{
		offset = _offset;
	}

	void CelestialBody::SetCount(int _count)
	{
		count = _count;
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

#pragma once

#include <Render.h>

namespace Utility {
	int64 GetCurrentTick();
	bool CreateShaderProgramFromFiles(ShaderProgram& program,
		const char* vertex_filename,
		const char* fragment_filename);
	bool CreateTextureFromFile(Texture& texture,
		const char* filename);
}


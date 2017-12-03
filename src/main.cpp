/*
 * Physically Based Rendering
 * Copyright (c) 2017 Michał Siejak
 */

#include <cstdio>
#include <cstring>
#include <memory>

#include "common/application.hpp"
#include "opengl.hpp"

#if _WIN32
#include "d3d11.hpp"
#endif // _WIN32

int main(int argc, char* argv[])
{
	try {
		RendererInterface* renderer;
		if(argc < 2 || strcmp(argv[1], "-opengl") == 0) {
			renderer = new OpenGL::Renderer;
		}
#if _WIN32
		else if(strcmp(argv[1], "-d3d11") == 0) {
			renderer = new D3D11::Renderer;
		}
#endif // _WIN32
		else {
#if _WIN32
			std::fprintf(stderr, "Usage: %s [-opengl|-d3d11]\n", argv[0]);
#else
			std::fprintf(stderr, "Usage: %s [-opengl]\n", argv[0]);
#endif // _WIN32
			return 1;
		}

		Application().run(std::unique_ptr<RendererInterface>{renderer});
	}
	catch(const std::exception& e) {
		std::fprintf(stderr, "Error: %s\n", e.what());
		return -1;
	}
}

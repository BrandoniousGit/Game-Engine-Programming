cmake_minimum_required(VERSION 3.0)
project(GEPENGINE)

include_directories(
	src
	contrib/windows-cl-amd64/include
)

link_directories(
	${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/lib
)

add_library(rend
	 src/rend/Animation.cpp
	 src/rend/Buffer.cpp
	 src/rend/Mesh.cpp
	 src/rend/Model.cpp
	 src/rend/ModelRenderer.cpp
	 src/rend/RenderTexture.cpp
	 src/rend/Renderer.cpp
	 src/rend/Shader.cpp
	 src/rend/Texture.cpp
	 src/rend/rendmath.cpp
)

target_link_libraries(rend glew32 opengl32)

add_library(gepEngine
	src/gepEngine/core.cpp
	src/gepEngine/core.h
	src/gepEngine/gepEngine.h
	src/gepEngine/entity.h
	src/gepEngine/entity.cpp
	src/gepEngine/component.h
	src/gepEngine/component.cpp
	src/gepEngine/triangleRenderer.h
	src/gepEngine/triangleRenderer.cpp
)

target_link_libraries(gepEngine
	glew32
	SDL2
	rend
)

add_executable(game
	src/game/main.cpp
	src/game/testScene.cpp
	src/game/testScene.h
)

target_link_libraries(game gepEngine)
cmake_minimum_required(VERSION 3.0)
project(GEPENGINE)

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  include_directories(
    src
    contrib/emcc-emscripten-wasm/include
  )

  link_directories(
    contrib/emcc-emscripten-wasm/lib
  )

 set(CMAKE_EXECUTABLE_SUFFIX ".html")
 set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sNO_DISABLE_EXCEPTION_CATCHING --preload-file ${CMAKE_SOURCE_DIR}/resources@resources")
 set(LIBOPENAL openal)
 set(LIBOPENGL GL)
 set(LIBGLEW GLEW)

else()
include_directories(
	src
	contrib/windows-cl-amd64/include
)

link_directories(
	${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/lib
)

set(LIBOPENAL openal32)
set(LIBOPENGL opengl32)
set(LIBGLEW glew32)

endif()

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

target_link_libraries(rend ${LIBGLEW} ${LIBOPENGL})

add_library(gepEngine
	src/gepEngine/core.cpp
	src/gepEngine/core.h

	src/gepEngine/gepEngine.h

	src/gepEngine/entity.h
	src/gepEngine/entity.cpp

	src/gepEngine/component.h
	src/gepEngine/component.cpp

	src/gepEngine/transform.cpp
	src/gepEngine/transform.h

	src/gepEngine/triangleRenderer.h
	src/gepEngine/triangleRenderer.cpp

	src/gepEngine/glmWrap.h

	src/gepEngine/AudioSource.cpp
	src/gepEngine/AudioSource.h

	src/gepEngine/AudioClip.cpp
	src/gepEngine/AudioClip.h

	src/gepEngine/BoxCollider.cpp
	src/gepEngine/BoxCollider.h

	src/gepEngine/Rigidbody.cpp
	src/gepEngine/Rigidbody.h

	src/gepEngine/Resources.cpp
	src/gepEngine/Resources.h

	src/gepEngine/ModelRenderer.cpp
	src/gepEngine/ModelRenderer.h
)

target_link_libraries(gepEngine
	SDL2
	rend
	${LIBOPENAL}
)

add_executable(game
	src/game/main.cpp
)

target_link_libraries(game gepEngine)
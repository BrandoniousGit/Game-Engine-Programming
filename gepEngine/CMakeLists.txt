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
	src/gepEngine/Core.cpp
	src/gepEngine/Core.h

	src/gepEngine/GepEngine.h

	src/gepEngine/Entity.h
	src/gepEngine/Entity.cpp

	src/gepEngine/Component.h
	src/gepEngine/Component.cpp

	src/gepEngine/Transform.cpp
	src/gepEngine/Transform.h

	src/gepEngine/TriangleRenderer.h
	src/gepEngine/TriangleRenderer.cpp

	src/gepEngine/GlmWrap.h

	src/gepEngine/AudioSource.cpp
	src/gepEngine/AudioSource.h

	src/gepEngine/AudioClip.cpp
	src/gepEngine/AudioClip.h

	src/gepEngine/BoxCollider.cpp
	src/gepEngine/BoxCollider.h

	src/gepEngine/Rigidbody.cpp
	src/gepEngine/Rigidbody.h

	src/gepEngine/Resource.cpp
	src/gepEngine/Resource.h

	src/gepEngine/MeshRenderer.cpp
	src/gepEngine/MeshRenderer.h

	src/gepEngine/Input.cpp
	src/gepEngine/Input.h

	src/gepEngine/Shader.cpp
	src/gepEngine/Shader.h

	src/gepEngine/Resource.cpp
	src/gepEngine/Resource.h

	src/gepEngine/Cache.cpp
	src/gepEngine/Cache.h

	src/gepEngine/Camera.cpp
	src/gepEngine/Camera.h

	src/gepEngine/Time.cpp
	src/gepEngine/Time.h

	src/gepEngine/Model.cpp
	src/gepEngine/Model.h

	src/gepEngine/Texture.cpp
	src/gepEngine/Texture.h
)

add_library(scripts
	src/scripts/Scripts.h

	src/scripts/PlayerScript.cpp
	src/scripts/EnemyScript.cpp
	src/scripts/FloorScript.cpp
	src/scripts/CameraScript.cpp

	src/scripts/PlayerScript.h
	src/scripts/EnemyScript.h
	src/scripts/FloorScript.h
	src/scripts/CameraScript.h
)

target_link_libraries(gepEngine
	SDL2
	rend
	${LIBOPENAL}
)

add_executable(game
	src/game/main.cpp
)

target_link_libraries(game gepEngine scripts)
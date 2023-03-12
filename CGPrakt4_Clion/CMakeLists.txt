# VS-Bibliotheken in CLion nutzen
cmake_minimum_required(VERSION 3.16)

# TODO: Projektnamen anpassen
project(CGPrakt4_Clion)
set(CMAKE_CXX_STANDARD 20)

# TODO: Inhalt des source-Ordners auflisten
add_executable(${CMAKE_PROJECT_NAME}
        source/Aabb.cpp
        include/Aabb.h
        source/Application.cpp
        include/Application.h
        source/BaseModel.cpp
        include/BaseModel.h
        source/BaseShader.cpp
        include/BaseShader.h
        source/Camera.cpp
        include/Camera.h
        source/color.cpp
        include/color.h
        source/ConstantShader.cpp
        include/ConstantShader.h
        source/IndexBuffer.cpp
        include/IndexBuffer.h
        source/LineBoxModel.cpp
        include/LineBoxModel.h
        source/LinePlaneModel.cpp
        include/LinePlaneModel.h
        source/main.cpp
        source/Matrix.cpp
        include/Matrix.h
        source/Model.cpp
        include/Model.h
        source/PhongShader.cpp
        include/PhongShader.h
        source/rgbimage.cpp
        include/rgbimage.h
        source/Texture.cpp
        include/Texture.h
        source/TriangleBoxModel.cpp
        include/TriangleBoxModel.h
        source/TrianglePlaneModel.cpp
        include/TrianglePlaneModel.h
        source/TriangleSphereModel.cpp
        include/TriangleSphereModel.h
        source/vector.cpp
        include/vector.h
        source/VertexBuffer.cpp
        include/VertexBuffer.h
        source/Tank.cpp
        include/Tank.h
        source/Scene.cpp
        include/Scene.h
        )

include_directories(
        source
        libraries/glfw/include
        libraries/glew/include
        libraries/freeimage/include
        libraries/assimp/include)

find_package(OpenGL REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME}
        OpenGL::GL
        OpenGL::GLU
        ../libraries/glfw/lib/glfw3
        ../libraries/glew/lib/glew32
        ../libraries/freeimage/lib/FreeImage
        ../libraries/assimp/lib/assimp-vc140-mt)

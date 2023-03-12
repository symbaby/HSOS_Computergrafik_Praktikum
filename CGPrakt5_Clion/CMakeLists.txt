# VS-Bibliotheken in CLion nutzen
cmake_minimum_required(VERSION 3.16)

# Projektnamen anpassen
project(CGPrakt5_Clion)
set(CMAKE_CXX_STANDARD 20)

#Inhalt des source-Ordners auflisten
add_executable(${CMAKE_PROJECT_NAME}
        include/Aabb.h
        source/Aabb.cpp
        include/Application.h
        source/Application.cpp
        include/BaseModel.h
        source/BaseModel.cpp
        include/BaseShader.h
        source/BaseShader.cpp
        include/Camera.h
        source/Camera.cpp
        include/color.h
        source/color.cpp
        include/ConstantShader.h
        source/ConstantShader.cpp
        include/IndexBuffer.h
        source/IndexBuffer.cpp
        include/LineBoxModel.h
        source/LineBoxModel.cpp
        include/LinePlaneModel.h
        source/LinePlaneModel.cpp
        include/Matrix.h
        source/Matrix.cpp
        include/Model.h
        source/Model.cpp
        include/PhongShader.h
        source/PhongShader.cpp
        include/rgbimage.h
        source/rgbimage.cpp
        include/Terrain.h
        source/Terrain.cpp
        include/TerrainShader.h
        source/TerrainShader.cpp
        include/Texture.h
        source/Texture.cpp
        include/TriangleBoxModel.h
        source/TriangleBoxModel.cpp
        include/TrianglePlaneModel.h
        source/TrianglePlaneModel.cpp
        include/TriangleSphereModel.h
        source/TriangleSphereModel.cpp
        include/vector.h
        source/vector.cpp
        include/VertexBuffer.h
        source/VertexBuffer.cpp
        source/main.cpp

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

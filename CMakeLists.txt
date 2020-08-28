# Project definition
cmake_minimum_required(VERSION 3.1)
project(Foundations)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Libraries")
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.hpp")

# Executable definition and properties
#add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES} Source/Graphics/Cube.cpp Source/Graphics/Cube.h "Source/Modules/Default Renderer Pass/CubeModule.cpp" "Source/Modules/Default Renderer Pass/CubeModule.h" Source/Graphics/Plane.cpp Source/Graphics/Plane.h "Source/Modules/Default Renderer Pass/PlaneModule.cpp" "Source/Modules/Default Renderer Pass/PlaneModule.h" Source/Graphics/Model.cpp Source/Graphics/Model.h "Source/Modules/Default Renderer Pass/ModelModule.cpp" "Source/Modules/Default Renderer Pass/ModelModule.h" Source/Framework/Renderer.cpp Source/Framework/Renderer.h Source/Elements/Terrain.cpp Source/Elements/Terrain.h "Source/Modules/Default Renderer Pass/TerrainModule.cpp" "Source/Modules/Default Renderer Pass/TerrainModule.h" "Source/Modules/Custom Renderer Pass/GeometryQuadModule.cpp" "Source/Modules/Custom Renderer Pass/GeometryQuadModule.h" "Source/Elements/Marching Cubes/Tables.h" "Source/Modules/Default Renderer Pass/MarchingCubesModule.cpp" "Source/Modules/Default Renderer Pass/MarchingCubesModule.h" "Source/Elements/Marching Cubes/Marcher.cpp" "Source/Elements/Marching Cubes/Marcher.h" Source/Graphics/FlatCube.cpp Source/Graphics/FlatCube.h "Source/Modules/Custom Renderer Pass/GerstnerWaveModule.cpp" "Source/Modules/Custom Renderer Pass/GerstnerWaveModule.h" "Source/Modules/Custom Renderer Pass/FogModule.cpp" "Source/Modules/Custom Renderer Pass/FogModule.h" "Source/Modules/Custom Renderer Pass/RayMarchingModule.cpp" "Source/Modules/Custom Renderer Pass/RayMarchingModule.h" Source/Framework/GL/FrameBuffer.cpp Source/Framework/GL/FrameBuffer.h "Source/Modules/Custom Renderer Pass/PostProcessingModule.cpp" "Source/Modules/Custom Renderer Pass/PostProcessingModule.h" Source/Graphics/MultiModel.cpp Source/Graphics/MultiModel.h Source/Framework/Components/Material.cpp Source/Framework/Components/Material.h Source/Graphics/Mesh.cpp Source/Graphics/Mesh.h "Source/Modules/Custom Renderer Pass/MaterialModelModule.cpp" "Source/Modules/Custom Renderer Pass/MaterialModelModule.h" Source/Framework/GL/DrawHandler.h Source/Framework/GL/DrawHandler.cpp Source/Framework/GL/TextureCube.cpp Source/Framework/GL/TextureCube.h Source/Framework/Repository.cpp Source/Framework/Repository.h Source/Framework/Simulation.cpp Source/Framework/Simulation.h)
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# GLAD
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# GLM
target_include_directories(${PROJECT_NAME} PRIVATE "Libraries/glm")

# Libs
if (APPLE)
    INCLUDE_DIRECTORIES(/System/Library/Frameworks)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
    FIND_LIBRARY(IOKit_LIBRARY IOKit)
    FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
    MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
    SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
    SET(APPLE_LIBS ${APPLE_LIBS} ${GLFW3_LIBRARY} ${ASSIMP_LIBRARY})
    set(LIBS ${LIBS} ${APPLE_LIBS})
endif (APPLE)

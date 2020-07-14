# OpenGL Scratchpad

A scratchpad for OpenGL based experimentation, intended for rapid iteration, integration and simplicity rather than
 optimisation and efficiency.
 
This uses a module based approach, allowing for selectable, reusable and distinct demo scenes, with common elements such as the renderer, textures etc being encapsulated within the rest of the application.

## Basic Modules

The project contains the following basic modules:

- **Simple Shapes:** TriangleModule, QuadModule, CubeModule, PlaneModule
- **Model Loading:** ModelModule (Stanford Dragon)

Each of these modules support:

- Transform modification
- Textured & untextured modes
- Lit & unlit shaders

## Advanced Modules

The project also contains more advanced modules that showcase various different effects or features:

- **TerrainModule:** Uses Perlin noise to generate some basic rolling hills.
- **GeometryQuadModule:** Uses the geometry shader to render a single vertex as a quad.
- **MarchingCubesModule:** An implementation of 'Marching Cubes' to generate a small terrain chunk.
- **GerstnerWaveModule:** An implementation of 'Gerstner Waves' which is an ocean wave simulation.
- **FogModule:** An implementation of distance based fog.
- **RayMarchingModule:** A simple scene generated entirely on the GPU through ray-marching.
- **PostProcessingModule:** A small collection of simple post-processing effects using 'Framebuffer Objects'.
- **MaterialModelModule:** Added material support to the models, as well as multi-part model loading.
- **InstancedModule:** Instanced model rendering


## Controls

### General

* **Escape:** Exit application

### Camera

* **W** / **S**: Forward / backward
* **A** / **D**: Strafe left / right
* **Q** / **E**: Ascend / descend
* **RMB + Mouse Move**: Look around
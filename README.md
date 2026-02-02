*This project has been created as part of the 42 curriculum by [rel-qoqu/Riyane El Qoqui] & [tbhuiyan/Taj Bhuiyan].*

# miniRT - High-Performance Raytracer

## Description

**miniRT** is an introduction to the beautiful world of Ray Tracing. The goal of this project is to generate
computer-generated images using the Raytracing protocol.

Unlike a standard implementation, this project focuses heavily on **low-level optimization** and **architectural
efficiency**. It is designed to be fast, memory-efficient, and scalable. It simulates physics-based light transport to
render scenes composed of geometric primitives (spheres, planes, cylinders, cones) and complex meshes.

**Key Objectives:**

* Accurate light simulation (Ambient, Diffuse, Specular).
* High-performance rendering using data-oriented design.
* Robust parsing and error management.

## Features

### Mandatory Part

* **Primitives:** Sphere, Plane, Cylinder.
* **Lighting:** Ambient light, Point lights, Hard shadows.
* **Camera:** Position, Orientation, Field of View (FOV).
* **Transformations:** Translation and Rotation of objects and cameras.
* **Graphics:** Fluid window management using MiniLibX.

### Bonus & Technical Highlights

* **Performance:**
    * **Multi-threading:** Parallel rendering tiles for using all CPU cores.
    * **SIMD (AVX/SSE):** Hand-written vector intrinsics (`__m128`) for math operations.
    * **BVH (Bounding Volume Hierarchy):** O(log N) intersection complexity for complex scenes.
* **Memory Management:**
    * **Arena Allocator:** Custom memory pool to ensure cache locality (spatial locality) and zero fragmentation. No
      `malloc` during the render loop.
* **Advanced Rendering:**
    * **Phong Reflection Model:** Specular highlights.
    * **Textures:** Checkerboard patterns, Bump mapping (Normal mapping).
    * **Mesh Support:** `.obj` file parsing (Wavefront format).
    * **Additional Primitives:** Cones.
    * **Multi-lights:** Support for multiple light sources.

## Instructions

### Prerequisites

* **OS:** Linux or macOS.
* **Compiler:** Clang.
* **Libraries:** MiniLibX (included or system-wide), standard math library.
    * *Linux:* `sudo apt-get install libx11-dev libxext-dev`

### Compilation

Use the `Makefile` to compile the project.

```bash
make
```

### Execution

Run the program with a scene description file (`.rt`).

```bash
./miniRT scenes/mandatory.rt
./miniRT scenes/obj.rt
```

### Controls

* `ESC` or `Red Cross`: Close the window and exit cleanly (Memory is freed via Arena destruction).

## Technical Architecture

This project follows a **Data-Oriented Design** approach rather than purely Object-Oriented.

1. **Arena Allocation:** All scene data is allocated sequentially in a pre-allocated memory block. This drastically
   reduces cache misses (L1/L2) during the intersection loop.
2. **Branchless Programming:** Critical math paths use bitwise operations and SIMD `min/max` to avoid pipeline flushes
   caused by branch misprediction.
3. **Tile-Based Rendering:** The image is divided into tiles distributed across thread workers to balance the load.

## Resources

### References

* [Ray Tracing in One Weekend](https://raytracing.github.io/) – The bible for basic ray tracing logic.
* [Scratchapixel](https://www.scratchapixel.com/) – Essential for the math behind geometric intersections.
* [Intel Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html) - Reference for
  SIMD optimization.


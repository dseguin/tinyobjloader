# tinyobjloader (Old-style GL edition)

This is a fork of `tinyobjloader` by <a href="https://github.com/syoyo">syoyo</a>, modified to suit the old OpenGL style arrays used in buffer objects. This fork is mostly for my own use, but it may be useful to others.

I'll be adding methods to load textures and materials as well.

#### Usage

Add the .cpp files to your source directory and the `tinyobjloader` folder to your include directory. Just include `tinyobjloader/tiny_obj_loader.h` in your project.

```cpp
#include "tinyobjloader/tiny_obj_loader.h"

tinyobj::obj_model object;
tinyobj::obj_load_model(&object, "filename");
int object_part = 0;
unsigned int* index = new unsigned int[object.shapes[object_part].mesh.indices.size()];
tinyobj::obj_get_index(index, &object, object_part);
unsigned int* vertex = new unsigned int[object.shapes[object_part].mesh.vertices.size()];
tinyobj::obj_get_v(vertex, &object, object_part);

// ...
// Load 'vertex' to VBO, 'index' to IBO
// Draw model
// ...

delete[] index;
delete[] vertex;
```

If you just want to use the base `tinyobjloader` source, define `TOL_DONT_USE_ARRAYS` before including `tinyobjloader/tiny_obj_loader.h`.

```cpp
#define TOL_DONT_USE_ARRAYS
#include "tinyobjloader/tiny_obj_loader.h"
// ...
```

### Original description
https://github.com/syoyo/tinyobjloader/
```
http://syoyo.github.io/tinyobjloader/

Tiny but poweful single file wavefront obj loader written in C++. No dependency except for C++ STL. It can parse 10M over polygons with moderate memory and time.

`tinyobjloader` is good for embedding .obj loader to your (global illumination) renderer ;-)
```

# tinyobjloader (Old-style GL edition)

#### Usage
```c_cpp
// ...
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

### Original description
https://github.com/syoyo/tinyobjloader/
```
http://syoyo.github.io/tinyobjloader/

Tiny but poweful single file wavefront obj loader written in C++. No dependency except for C++ STL. It can parse 10M over polygons with moderate memory and time.

`tinyobjloader` is good for embedding .obj loader to your (global illumination) renderer ;-)
```

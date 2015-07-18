#ifndef TO_ARRAYS_H
#define TO_ARRAYS_H

#include <vector>
#include "tinyobjloader/tiny_obj_loader.h"

namespace tinyobj
{

typedef struct
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
} obj_model;

void obj_load_model(obj_model* model, const char* filename);

void obj_get_index(unsigned int* index, obj_model* model, int part);

void obj_get_nv(float* vertarray, obj_model* model, int part);

} // namespace tinyobj

#endif

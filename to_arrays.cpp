#ifndef TOL_DONT_USE_ARRAYS

#include <iostream>
#include "tiny_obj_loader.h"

///////////////////////////////////////////////////////////////////////////////
// Abstracts tinyobj to make it easier to load wavefront models in OpenGL.
// Intended usage:
//
//  - Load obj data to obj_model struct:
//       GLT::obj_model model;
//       GLT::obj_load_model(&model, "filename.obj");
//
//  - Load index data from obj_model:
//       int part = 0;
//       unsigned int index[model.shapes[part].mesh.indices.size()];
//       GLT::obj_get_index(index, &model, part);
//
//  - Load vertex and attributes data from obj_model:
//       float vertarray[model.shapes[part].mesh.positions.size() * 2];
//       GLT::obj_get_nv(vertarray, &model, part);
//
///////////////////////////////////////////////////////////////////////////////

namespace tinyobj
{

///////////////////////////////////////////////////////////////////////////////
// Loads shape and material data to an obj_model struct from 'filename'.
// obj_model contains these members:
//    shapes                                (std::vector<tinyobj::shape_t>)
//       shapes[group].name                 (std::string)
//       shapes[group].mesh                 (struct)
//           mesh.positions                 (std::vector<float>)
//           mesh.normals                   (std::vector<float>)
//           mesh.texcoords                 (std::vector<float>)
//           mesh.indices                   (std::vector<unsigned int>)
//           mesh.material_ids              (std::vector<int>)
//    materials                             (std::vector<tinyobj::material_t>)
//       materials[group].name              (std::string)
//       materials[group].ambient           (float[3])
//       materials[group].diffuse           (float[3])
//       materials[group].specular          (float[3])
//       materials[group].transmittance     (float[3])
//       materials[group].emission          (float[3])
//       materials[group].shininess         (float)
//       materials[group].ior               (float) (index of refraction)
//       materials[group].dissolve          (float) (transparancy 0.0 - 1.0)
//       materials[group].illum             (int)
//       materials[group].ambient_texname   (std::string)
//       materials[group].diffuse_texname   (std::string)
//       materials[group].specular_texname  (std::string)
//       materials[group].normal_texname    (std::string)
//       materials[group].unknown_parameter (std::map<std::string,std::string>)
//
// Where 'group' is the vertex group exported from blender. (group == 0 if 
// model is just one part/object)
//
//       model     --  model to load data to
//       filename  --  path to .obj file
//
// Error handling depends entirely on tinyobj implementation.
///////////////////////////////////////////////////////////////////////////////
void obj_load_model(obj_model* model, const char* filename)
{
	std::string load_err = tinyobj::LoadObj(model->shapes, model->materials, 
			filename, NULL);
	if(!load_err.empty())
	{
		std::cerr << load_err << std::endl;
	}
	return;
}

///////////////////////////////////////////////////////////////////////////////
// Loads index data from 'model' to 'index'. The 'part' specifies which vertex 
// group (or part) of the model to access. If the model is only one part,
// part == 0.
//       
//       index  --  index array to hold index data
//       model  --  model that contains obj data
//       part   --  vertex group of model
//
// Note that 'index' must be able to hold the index data, which would be 
// model->shapes[part].mesh.indices.size() elements large. The index data 
// corresponds to the vertex and attributes data of the same 'part'. Assume 
// that means triangles.
///////////////////////////////////////////////////////////////////////////////
void obj_get_index(unsigned int* index, obj_model* model, int part)
{
	bool err_exit = false;
	if(index == NULL || model == NULL)
	{
		std::cerr << "Error: NULL arg passed to obj_get_index()" 
			<< std::endl;
		err_exit = true;
	}
	if((size_t)part > model->shapes.size() - 1 || part < 0)
	{
		std::cerr << "Error: arg 'int' passed to obj_get_index() "
			"is larger than model.shapes.size(), or is negative" << std::endl;
		err_exit = true;
	}
	if(!err_exit)
	{
		for(size_t i = 0; i < model->shapes[part].mesh.indices.size(); ++i)
		{
			index[i] = model->shapes[part].mesh.indices[i];
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Loads vertex and attribute data from 'model' to 'vertarray'. The 'part' 
// specifies which vertex group (or part) of the model to access. If the model 
// is only one part, part == 0.
//
//       vertarray  --  array to hold vertex and attributes data
//       model      --  model that contains obj data
//       part       --  vertex group of model
//
// This particular function loads normals and vertices (N3f & V3f). That means 
// 'vertarray' needs to hold 'model's normals and vertex positions, or 
// 2 * model->shapes[part].mesh.positions.size(). The attributes are 
// interleaved in this order: N0x, N0y, N0z, V0x, V0y, V0z, N1x, N1y, ...
///////////////////////////////////////////////////////////////////////////////
void obj_get_nv(float* vertarray, obj_model* model, int part)
{
	bool err_exit = false;
	if(vertarray == NULL || model == NULL)
	{
		std::cerr << "Error: NULL arg passed to obj_get_nv()" 
			<< std::endl;
		err_exit = true;
	}
	if((size_t)part > model->shapes.size() - 1 || part < 0)
	{
		std::cerr << "Error: arg 'int' passed to obj_get_nv() "
			"is larger than model.shapes.size(), or is negative" << std::endl;
		err_exit = true;
	}
	if(!err_exit)
	{
		for (size_t f = 0; f < model->shapes[part].mesh.normals.size() * 
				2 - 5; f += 6)
		{
			vertarray[f] = model->shapes[part].mesh.normals[f/2];
			vertarray[f+1] = model->shapes[part].mesh.normals[f/2+1];
			vertarray[f+2] = model->shapes[part].mesh.normals[f/2+2];
			vertarray[f+3] = model->shapes[part].mesh.positions[f/2+0];
			vertarray[f+4] = model->shapes[part].mesh.positions[f/2+1];
			vertarray[f+5] = model->shapes[part].mesh.positions[f/2+2];
		}
	}
}

} // namespace tinyobj

#endif

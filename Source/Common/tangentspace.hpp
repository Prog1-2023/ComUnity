#ifndef TANGENTSPACE_HPP
#define TANGENTSPACE_HPP

#include <vector>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;


void computeTangentBasis(
	// inputs
	vector<vec3> & vertices,
	vector<vec2> & uvs,
	vector<vec3> & normals,
	// outputs
	std::vector<vec3> & tangents,
	std::vector<vec3> & bitangents
);


#endif
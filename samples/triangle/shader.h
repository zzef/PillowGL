#include "stdio.h"

void vertex_shader(
	void* uniforms_in,
	void* attributes_in,
	struct vec3* vertex_in, 
	struct vec3* vertex_out,
	void* varyings_out
) {

	vertex_out->x = vertex_in->x;	
	vertex_out->y = vertex_in->y;	
	vertex_out->z = vertex_in->z;	
	varyings_out = attributes_in;
	
}

void pixel_shader(
	void* uniform_in,
	void* varyings_in,
	uint32_t* color
) {
	color = varyings_in;
}

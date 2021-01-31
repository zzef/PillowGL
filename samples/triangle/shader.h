#include "stdio.h"

struct attr {
	float a;
	struct vec3 b;
};

void vertex_shader(
	void* uniforms_in,
	void* attributes_in,
	struct vec3* vertex_in, 
	struct vec3* vertex_out,
	void* varyings_out
) {

	struct attr* _data_in = ( struct attr* ) attributes_in;

	printf( "data %f\n", _data_in->a );
		
	vertex_out->x = vertex_in->x;	
	vertex_out->y = vertex_in->y;	
	vertex_out->z = vertex_in->z;	

}


#include <stdlib.h>

// 3D vertex struct
struct vec3 {
	float x;
	float y;
	float z;
};

// Contains uniforms and attributes to start execution
struct execution_unit_in{
	void* uniforms;
	void** attributes;
};

// Each render unit contains the shaders needed to
// render polygons associated with it.
struct render_unit {

	// Function pointer for vertex shader
	void ( *_vertex_shader ) (
		void* uniforms_in,
		void* attributes_in,
		struct vec3* vertex_in, 
		struct vec3* vertex_out,
		void* varying_out
	);

	void ( *_pixel_shader ) (
		void* uniform_in,
		void* varying_in,
		uint32_t* color
	);	

};

void attach_vertex_shader( 
	struct render_unit* _unit,
	void ( *_vertex_shader ) (
		void* uniforms_in,
		void* attributes_in,
		struct vec3* vertex_in, 
		struct vec3* vertex_out,
		void* varyings_out
	)
);


void attach_pixel_shader( 
	struct render_unit* _unit,
	void ( *_pixel_shader ) (
		void* uniform_in,
		void* varying_in,
		uint32_t* color
	)	
);

void execute_unit(
	struct context* _ctx,
	struct render_unit* _unit,
	struct execution_unit_in _in,
	struct vec3* vertex_buffer,
	size_t vb_size
); 

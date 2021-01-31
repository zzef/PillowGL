#include <stdlib.h>

// 3D vertex struct
struct vec3 {
	float x;
	float y;
	float z;
};

// Each render unit contains the shaders needed to
// render polygons associated with it.
struct render_unit {

	// Function pointer for vertex shader
	void ( *_vertex_shader ) (
		// uniforms in
		void* data_in,
		struct vec3* vertex_in, 
		struct vec3* vertex_out,
		void* data_out
	);

	void ( *_pixel_shader ) (
		// uniforms in
		void* data_in,
		struct vec3 color
	);	

};

void attach_vertex_shader( 
	struct render_unit* _unit,
	void ( *_vertex_shader ) (
		void* data_in,
		struct vec3* vertex_in, 
		struct vec3* vertex_out,
		void* data_out
	)
);

void execute_unit(
	struct context* _ctx,
	struct render_unit* _unit,
	void* uniforms,
	void** vertex_attributes, 
	size_t va_size,
	struct vec3* vertex_buffer,
	size_t vb_size
); 

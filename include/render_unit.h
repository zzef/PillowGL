#include <stdlib.h>

// 3D vertex struct
struct vertex {
	float x;
	float y;
	float z;
};

// Each render unit contains the shaders needed to
// render polygons associated with it.
struct render_unit {

	// Function pointer for vertex shader
	void ( *_vertex_shader ) (
		struct vertex* vertex_in, 
		struct vertex* vertex_out
	);	

};

void attach_vertex_shader( 
	struct render_unit* _unit,
	void ( *_vertex_shader ) (
		struct vertex* vertex_in, 
		struct vertex* vertex_out
	)
) {
	_unit->_vertex_shader = _vertex_shader;
}

void execute_unit(
	struct context* _ctx,
	struct render_unit* _unit,
	void*** vertex_attributes_buffer, 
	size_t va_size,
	struct vertex* vertex_buffer,
	size_t vb_size
); 

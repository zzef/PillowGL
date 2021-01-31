#include "context.h"
#include "render_unit.h"
#include <stdio.h>

// Attach vertex shader to render_unit
void attach_vertex_shader( 
	struct render_unit* _unit,
	void ( *_vertex_shader ) (
		void* uniforms_in,
		void* attributes_in,
		struct vec3* vertex_in, 
		struct vec3* vertex_out,
		void* varyings_out
	)
) {
	_unit->_vertex_shader = _vertex_shader;
}

// Exceution unit for carrying out execution of
// graphics pipeiline
void execute_unit(
	struct context* _ctx,
	struct render_unit* _unit,
	struct execution_unit_in _in,
	struct vec3* vertex_buffer,
	size_t vb_size
) {
	
	for ( size_t i = 0; i < vb_size; i++ ) {

		/*
		printf("v_in ( %f, %f, %f )\n",
			vertex_buffer[ i ].x,
			vertex_buffer[ i ].y,
			vertex_buffer[ i ].z	
		);
		*/

		struct vec3 vertex_out;
		void* varyings_out;
		_unit->_vertex_shader(
			_in.uniforms,
			_in.attributes[ i ],
			&vertex_buffer[ i ],
			&vertex_out,
			varyings_out
		);

		/*
		printf("v_out ( %f, %f, %f )\n",
			vertex_out.x,
			vertex_out.y,
			vertex_out.z	
		);
		*/

		// data out

		// interpolate between data out
		// call pixel shader with data from each interpolant
		// get a color from pixel shader
		// paint pixel with color

		set_pixel( _ctx, vertex_out.x, vertex_out.y, 0, 0);
		
	}		

}

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

//Attach pixel shader to render unit
void attach_pixel_shader( 
	struct render_unit* _unit,
	void ( *_pixel_shader ) (
		void* uniform_in,
		void* varying_in,
		uint32_t* color
	)	
) {
	_unit->_pixel_shader = _pixel_shader;
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
	
	for ( size_t i = 0; i < vb_size; i+=3 ) {

		/*
		printf("v_in ( %f, %f, %f )\n",
			vertex_buffer[ i ].x,
			vertex_buffer[ i ].y,
			vertex_buffer[ i ].z	
		);
		*/

		struct vec3 vertex_0_out;
		void* varyings_0_out;
		_unit->_vertex_shader(
			_in.uniforms,
			_in.attributes[ i ],
			&vertex_buffer[ i ],
			&vertex_0_out,
			varyings_0_out
		);

		struct vec3 vertex_1_out;
		void* varyings_1_out;
		_unit->_vertex_shader(
			_in.uniforms,
			_in.attributes[ i + 1 ],
			&vertex_buffer[ i + 1 ],
			&vertex_1_out,
			varyings_1_out
		);

		struct vec3 vertex_2_out;
		void* varyings_2_out;
		_unit->_vertex_shader(
			_in.uniforms,
			_in.attributes[ i + 2 ],
			&vertex_buffer[ i + 2 ],
			&vertex_2_out,
			varyings_2_out
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

		

		set_pixel( _ctx, vertex_2_out.x, vertex_2_out.y, 0, 0);
		
	}		

}

#include "context.h"
#include "render_unit.h"
#include <stdio.h>

// Exceution unit for carrying out execution of
// graphics pipeiline
void execute_unit(
	struct context* _ctx,
	struct render_unit* _unit,
	void*** vertex_attributes_buffer, 
	size_t va_size,
	struct vertex* vertex_buffer,
	size_t vb_size
) {
	
	for ( size_t i = 0; i < vb_size; i++ ) {

		printf("v_in ( %f, %f, %f )\n",
			vertex_buffer[ i ].x,
			vertex_buffer[ i ].y,
			vertex_buffer[ i ].z	
		);

		struct vertex vertex_out;
		_unit->_vertex_shader(
			&vertex_buffer[ i ],
			&vertex_out
		);

		printf("v_out ( %f, %f, %f )\n",
			vertex_out.x,
			vertex_out.y,
			vertex_out.z	
		);

		set_pixel( _ctx, vertex_out.x, vertex_out.y, 0, 0);
		
	}		

}

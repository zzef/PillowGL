#include <stdint.h>

// Frame struct for storing all data associated with a frame
struct frame {

	int16_t width;
	int16_t height;
	
	// Upon creation, the following buffers will point to arrays 
    // of rgb values and depth(float) values respectively
	uint32_t* frame_buffer;
	float* depth_buffer;

};

// Graphical context for handling all data and functions
// associated with a specific graphical context
struct context {

	struct frame* _frame;
	int8_t depth_test;	
	uint32_t clear_color;

	// Flag for running context main loop
	int8_t stop;

	// This function gets called in an infinite loop and is set by api user	
	void ( *_main_loop ) ( struct context* _ctx );
	// api user is supplied with frame buffer data to implement custom
	// display function. This will allow for users to implement different
	// display functions for a wide range of use cases.
	void ( *_display ) ( 
		uint32_t* frame_buffer,
		int16_t width,
		int16_t height
	 );
};

// setup functions

struct context* create_context();
void set_context_frame( struct context* _ctx, struct frame* _frame );
struct frame* create_frame( int16_t width, int16_t height );
void destroy_frame( struct frame* _frame );
void set_clear_color( struct context* _ctx, uint32_t color );
void enable_depth_test( struct context* _ctx );
void disable_depth_test( struct context* _ctx );

void main_loop( 
	struct context* _ctx,
	void ( *_main_loop ) ( struct context* _ctx )
);

void display_function(
	struct context* _ctx,
	void ( *_display ) ( 
		uint32_t* frame_buffer,
		int16_t width,
		int16_t height
	 )
);

static void clear_context( struct context* _ctx ); 
void start_context( struct context* _ctx );
void stop_context( struct context* _ctx );

// static helper functions

void set_pixel(
	struct context* _ctx,
	int16_t x,
	int16_t y,
	uint32_t color,
	float depth
);


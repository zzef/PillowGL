#include "context.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Create context struct and initialize values
struct context* create_context() {
	
	struct context* _ctx = malloc( sizeof( struct context ) );
	if ( _ctx == NULL )
		return NULL;

	_ctx->depth_test = 0;
	_ctx->clear_color = 0;
	_ctx->stop = 0;
	return _ctx;

}

// Set the frame for specified context
void set_context_frame( struct context* _ctx, struct frame* _frame ) {
	_ctx->_frame = _frame;
}

// Create a frame with the specified width and height
struct frame* create_frame( int16_t width, int16_t height ) {

	// Allocate some memory for a frame struct. This struct will
	// exist for most of the duration of the program.
	struct frame* _frame = malloc( sizeof( struct frame ) );
	_frame->width = width;
	_frame->height = height;

	// Allocating memory for the frame buffer. Each color component can 
	// be stored in 8 bits (0-255). We need to store 4 color components,
	// r, g, b a, respectively. Therefore we can encode this data into 
	// a 32-bit integer.
	_frame->frame_buffer = malloc( 
		sizeof( uint32_t ) * width * height
	);

	// Allocating memory for the depth buffer. Each pixel of the depth 
	// buffer needs to store a floating point value.
	_frame->depth_buffer = malloc(
		sizeof( float ) * width * height
	);
	
	if ( _frame->frame_buffer == NULL || _frame->depth_buffer == NULL )
		return NULL;

	return _frame;

}

// Free memory from frame buffer and depth buffer
void destroy_frame( struct frame* _frame ) {

	if ( _frame->frame_buffer != NULL )
		free( _frame->frame_buffer );

	if ( _frame->depth_buffer != NULL )
		free( _frame->depth_buffer );

}

// The color used to clear the frame following each render
void set_clear_color( struct context* _ctx, uint32_t color ) {
	_ctx->clear_color = color;
}

// Enable depth test
void enable_depth_test( struct context* _ctx ) {
	_ctx->depth_test = 1;
}

// Disable depth test
void disable_depth_test( struct context* _ctx ) {
	_ctx->depth_test = 0;
}

// Set the main loop function to specified function pointer
void main_loop( 
	struct context* _ctx,
	void ( *_main_loop ) ( struct context* _ctx ) 
) {
	_ctx->_main_loop = _main_loop;
}

// Set display function to specified function pointer
void display_function(
	struct context* _ctx,
	void ( *_display ) ( 
		uint32_t* frame_buffer,
		int16_t width,
		int16_t height
	 )
) {
	_ctx->_display = _display;
}


// Set color of specified pixel in frame buffer
void set_pixel(
	struct context* _ctx,
	int16_t x,
	int16_t y,
	uint32_t color,
	float depth 
) {
	
	// return if specified pixel is outside of frame dimensions
	if ( x < 0 || x >= _ctx->_frame->width || y < 0 || y >= _ctx->_frame->height ) {
		return;
	}
		
	// Find index of pixel in frame buffer
	size_t index = ( _ctx->_frame->width * y ) + x;

	// If depth test is enabled then only set the pixel
	// if it is closer (lower depth) than the specified
	// color. If so, update the depth buffer and update 
	// the specified color
	if ( _ctx->depth_test ) {
		if ( depth < _ctx->_frame->depth_buffer[ index ]) {
			_ctx->_frame->depth_buffer[ index ] = depth;
			_ctx->_frame->frame_buffer[ index ] = color;
		}		
	}
	else {
		_ctx->_frame->frame_buffer[ index ] = color;
	}

}

// Clear frame buffer and depth buffer
static void clear_context( struct context* _ctx ) {

	size_t buffer_size = _ctx->_frame->width * _ctx->_frame->height;

	//set all pixels in frame buffer to clear color
	for ( size_t i = 0; i < buffer_size; i++ )
		_ctx->_frame->frame_buffer[ i ] = _ctx->clear_color;
	
	//set all values of depth buffer to 0
	memset( _ctx->_frame->depth_buffer, 255, 
		sizeof( float ) * buffer_size );

}

// Starts graphical context main loop
void start_context( struct context* _ctx ) {

	// Typical clear, render, display loop
	// api user is expected to issue draw calls
	// inside _main_loop implementation
	while( ! _ctx->stop ) {
		clear_context( _ctx );
		_ctx->_main_loop( _ctx );
		_ctx->_display( 
			_ctx->_frame->frame_buffer,
			_ctx->_frame->width,
			_ctx->_frame->height
		 );
	}
	_ctx->stop = 0;
}

// Stops the graphical context main loop
void stop_context( struct context* _ctx ) {
	_ctx->stop = 1;
}




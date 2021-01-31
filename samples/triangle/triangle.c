#include "pillow/context.h"
#include "pillow/render_unit.h"
#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "shader.h"

SDL_Texture *Frame;
SDL_Window *window;
SDL_Renderer *renderer;

int16_t width = 1280;
int16_t height = 720;
float t = 0;

struct vec3 vertex_buffer[ 36 ] = { 

	{-1.0f,-1.0f,-1.0f },
	{-1.0f,-1.0f, 1.0f },
	{-1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f,-1.0f },
	{-1.0f,-1.0f,-1.0f },
	{-1.0f, 1.0f,-1.0f },
	{ 1.0f,-1.0f, 1.0f },
	{-1.0f,-1.0f,-1.0f },
	{ 1.0f,-1.0f,-1.0f },
	{ 1.0f, 1.0f,-1.0f },
	{ 1.0f,-1.0f,-1.0f },
	{-1.0f,-1.0f,-1.0f },
	{-1.0f,-1.0f,-1.0f },
	{-1.0f, 1.0f, 1.0f },
	{-1.0f, 1.0f,-1.0f },
	{ 1.0f,-1.0f, 1.0f },
	{-1.0f,-1.0f, 1.0f },
	{-1.0f,-1.0f,-1.0f },
	{-1.0f, 1.0f, 1.0f },
	{-1.0f,-1.0f, 1.0f },
	{ 1.0f,-1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f,-1.0f,-1.0f },
	{ 1.0f, 1.0f,-1.0f },
	{ 1.0f,-1.0f,-1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f,-1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f,-1.0f },
	{-1.0f, 1.0f,-1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{-1.0f, 1.0f,-1.0f },
	{-1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{-1.0f, 1.0f, 1.0f },
	{ 1.0f,-1.0f, 1.0f }

};


// Display function to be called by api
void display( 
	uint32_t* frame_buffer, 
	int16_t width, 
	int16_t height 
) {

	unsigned char* bytes = NULL;
	int pitch = 0;
	//get locked pixels and store in bytes for write access

	SDL_UpdateTexture( Frame, NULL, frame_buffer, width * sizeof( uint32_t ) );
	SDL_RenderClear( renderer );
	SDL_RenderCopy( renderer, Frame, NULL, NULL );
	SDL_RenderPresent( renderer );

	uint32_t r = 0 << 24;
	uint32_t g = 0 << 16; 
	uint32_t b = 0 << 8;
	uint32_t a = 255 << 0;
	
	uint32_t color = r | g | b | a ;

}


// Graphics loop will be called by api
void gfx_loop( struct context* _ctx ) {	

	SDL_Event e;
	while ( SDL_PollEvent( &e )) {
		if ( e.type == SDL_QUIT )
			stop_context( _ctx );
	}

	struct render_unit _unit;
	attach_vertex_shader( &_unit, vertex_shader );

	struct vec3 triangle[ 3 ] = { 

		{ 150 + t, 300, 0 },
		{ 500 + t, 500, 0 },
		{ 100 + t, 500, 1.0f },
	
	};

	uint32_t col = 255;

	uint32_t color_red = col << 24;
	uint32_t color_green = col << 16;
	uint32_t color_blue = col << 8;

	void* vertex_attributes[ 3 ] = { 
		&color_red,
		&color_blue,
		&color_green
	};

	struct execution_unit_in _in = { NULL, vertex_attributes };

	t += 2;
	
	execute_unit( 
		_ctx,
		&_unit,
		_in,
		triangle,
		3
	);

}

int main() {

	SDL_Init(SDL_INIT_EVERYTHING);

	//We start by creating a window
	window = SDL_CreateWindow(
		"Pillow",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_SHOWN
	);
	//We need a renderer to do our rendering
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	//Create frame
	Frame = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, width, height
	);


	/*

	Setup steps:
		1. Create a frame using create_frame()
		2. Create a context using create_context()
		3. Set the working frame for the new context
		   using set_context_frame()
		4. Set main loop function using main_loop()
		5. Set display function using display_function()
		6. Start the context using start_context()
	
	*/


	uint32_t r = 255 << 24;
	uint32_t g = 255 << 16; 
	uint32_t b = 255 << 8;
	uint32_t a = 255 << 0;
	
	uint32_t color = r | g | b | a ;

	struct frame* _frame = create_frame( width, height );
	struct context* _ctx = create_context();
	set_context_frame( _ctx, _frame );
	set_clear_color( _ctx, color );
	main_loop( _ctx, gfx_loop );
	display_function( _ctx, display );
	start_context( _ctx );

	destroy_frame( _frame );
	SDL_DestroyWindow(window);
	SDL_Quit();

}

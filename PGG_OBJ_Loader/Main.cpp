#include <SDL/SDL.h>
#include "glew.h"
#include "Scene.h"
#include <iostream>
#include <string>

bool InitGL()
{
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		std::cerr<<"Error: GLEW failed to initialise with message: "<< glewGetErrorString(err) <<std::endl;
		return false;
	}
	std::cout<<"INFO: Using GLEW "<< glewGetString(GLEW_VERSION)<<std::endl;

	std::cout<<"INFO: OpenGL Vendor: "<< glGetString( GL_VENDOR ) << std::endl;
	std::cout<<"INFO: OpenGL Renderer: "<< glGetString( GL_RENDERER ) << std::endl;
	std::cout<<"INFO: OpenGL Version: "<< glGetString( GL_VERSION ) << std::endl;
	std::cout<<"INFO: OpenGL Shading Language Version: "<< glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
	
	return true;
}


int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
		return -1;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 1280;
	int winHeight = 720;
	SDL_Window *window = SDL_CreateWindow("OpenGL",
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	if (!InitGL())
	{
		return -1;
	}

	unsigned int lastTime = SDL_GetTicks();
	glEnable(GL_DEPTH_TEST);

	Scene myScene;

	bool cmdRotateLeft = false, cmdRotateRight = false, cmdRotateUp = false, cmdRotateDown = false;

	bool go = true;
	while (go)
	{
		SDL_Event incomingEvent;
		while (SDL_PollEvent(&incomingEvent))
		{
			switch (incomingEvent.type)
			{
			case SDL_QUIT:
				go = false;
				break;
			}
		}
			unsigned int current = SDL_GetTicks();
			float deltaTs = (float)(current - lastTime) / 1000.0f;
			myScene.Update(deltaTs);

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			myScene.Draw();

			SDL_GL_SwapWindow(window);

			if (deltaTs < (1.0f / 50.0f))
			{
				SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTs)*1000.0f));
			}
			lastTime = current;
	}
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

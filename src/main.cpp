#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include <iostream>


bool handle_events();


int main()
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_FRect available_rects[300];
    int current_count = 0;
    bool is_running = true;
    
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) 
    {
        std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(
        "OpenGL Engine",
        800, 600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!window) 
    {
        printf("Window creation failed: %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer) 
    {
        printf("Renderer creation failed: %s", SDL_GetError());
        return 1;
    }

    // Enable VSync
    SDL_GL_SetSwapInterval(1);

    while(is_running)
    {
        is_running = handle_events();

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 50, 50, 75, 255);

        for(int r_count = 0; r_count < current_count; r_count++)
        {
            SDL_RenderRects(renderer, available_rects+r_count, 1);
        }

        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}


bool handle_events() 
{
    SDL_Event event;
    // Keyboard movement using SDL_GetKeyboardState
    const bool* keys = SDL_GetKeyboardState(NULL);
    bool is_running = true;

    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_EVENT_QUIT) 
        {
            is_running = false;
        }
        else if(event.type == SDL_EVENT_KEY_DOWN)
        {
            if(event.key.key == SDLK_ESCAPE)
            {
                is_running = false; // Exit with escape key
            }
        }
    }

//    if (keys[SDL_SCANCODE_W]) 
//    {
//        camera_pos += velocity * camera_front;
//    }
//    if (keys[SDL_SCANCODE_S]) 
//    {
//        camera_pos -= velocity * camera_front;
//    }
//    if (keys[SDL_SCANCODE_A]) 
//    {
//        camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * velocity;
//    }
//    if (keys[SDL_SCANCODE_D]) 
//    {
//        camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * velocity;
//    }

    return is_running;
}

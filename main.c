#include <stdio.h>
#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>

//-----------------------------------------------------------------------------------------------//

const double FRAME_RATE = 1.0 / 60.0;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int gameRunning = 0;

//-----------------------------------------------------------------------------------------------//

int initialize_window(void){

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "Error initialising SDL\n");
        return 0;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if (!window){
        fprintf(stderr, "Error creating SDL window\n");
        return 0;
    }

    // -1 for default driver, 0 for no flags
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer){
        fprintf(stderr, "Error creating SDL renderer\n");
        return 0;
    }

    return 1;
}

//-----------------------------------------------------------------------------------------------//

void processInput(){

    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_QUIT:
            gameRunning = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE){
                gameRunning = 0;
            }
            break;
    }

}

//-----------------------------------------------------------------------------------------------//

void update(){

    //TODO

}

//-----------------------------------------------------------------------------------------------//

void render(){

    //TODO

}

//-----------------------------------------------------------------------------------------------//

void destroyWindow(){

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

//-----------------------------------------------------------------------------------------------//

void setup(){

    //TODO

}

//-----------------------------------------------------------------------------------------------//

int main(){

    gameRunning = initialize_window();

    setup();

    while (gameRunning){
        processInput();
        update();
        render();
    }

    destroyWindow();

    return 0;
}

//-----------------------------------------------------------------------------------------------//

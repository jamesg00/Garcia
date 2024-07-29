#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <random>
#include <SDL2/sdl_mixer.h>
#include <SDL2/sdl_image.h>



const int WIDTH = 300, HEIGHT = 300;

bool checkRectCollision(const SDL_Rect& r1, const SDL_Rect& r2) {
    return SDL_HasIntersection(&r1, &r2);
}

bool checkRectCollision2(const SDL_Rect& r1, const SDL_Rect& r3) {
    return SDL_HasIntersection(&r1, &r3);
}

bool checkRectCollision3(const SDL_Rect& r1, const SDL_Rect& r4) {
    return SDL_HasIntersection(&r1, &r4);
}

bool checkRectCollision4(const SDL_Rect& r1, const SDL_Rect& r5) {
    return SDL_HasIntersection(&r1, &r5);
}

bool checkRectCollision5(const SDL_Rect& r1, const SDL_Rect& r6) {
    return SDL_HasIntersection(&r1, &r6);
}
int main(int argc, char *argv[]) {
    bool rectMoves = false;
    float RectSpeed = 0.125f;
    float RectsSpeed = 0.150f;
    bool isJumping = false;
    bool onGround = false;

    int Score = 0;



    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    int init2 = Mix_Init(0);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Chunk * music = Mix_LoadWAV("audio/8-bit-fx-jump_100bpm.wav");


    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Rect r{50, 280, 20, 20}; // Initial position of the player square
    SDL_Rect r2{250, 260, 40,10}; // Platform
    SDL_Rect r3{100, 200, 40, 10}; // Platform
    SDL_Rect r4{230, 150, 40, 10}; // Platform
    SDL_Rect r5{10, 100, 40, 10}; // Platform
    SDL_Rect r6{200, 50, 40, 10}; // Platform
    SDL_Rect r7{15, 80, 40, 10}; // Platform
    SDL_Rect r8{150, 200, 40, 10}; // Platform
    

    SDL_Rect r9
    { rand() % WIDTH, rand() % HEIGHT, 40, 10}; 





    SDL_Event windowEvent;

    // Define the initial position of the triangle
    float triangleX = WIDTH - 70;
    float triangleY = HEIGHT;
    const int triangleWidth = 20;
    const int triangleHeight = 20;

    // Triangle movement direction
    float triangleSpeed = 0.2f;
    bool triangleMovingLeft = true;




    // Create a vector to hold the triangle vertices
    std::vector<SDL_Vertex> verts = {
        {SDL_FPoint{triangleX + 10, triangleY - 20}, SDL_Color{255, 0, 0, 255}, SDL_FPoint{0}}, // Top point
        {SDL_FPoint{triangleX, triangleY}, SDL_Color{0, 0, 255, 255}, SDL_FPoint{0}},           // Bottom-left point
        {SDL_FPoint{triangleX + 20, triangleY}, SDL_Color{0, 255, 0, 255}, SDL_FPoint{0}},      // Bottom-right point
    };

    // Create a window and renderer
    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) != 0) {
        std::cout << "SDL_CreateWindowAndRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    bool running = true;

    float playerVelX = 0;
    float playerVelY = 0;
    const float playerSpeed = 0.5f;
    const float gravity = 0.01f; // Gravity acceleration
    const float jumpStrength = -0.3f; // Initial velocity for jumping
    Uint8 direction = 0; // To store the most recent direction pressed

    Uint32 lastUpdateTime = SDL_GetTicks();

    while (running) {
        // Get the state of the keyboard
        rectMoves = true;
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        while (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) {
                running = false;
            } else if (windowEvent.type == SDL_KEYDOWN) {
                switch (windowEvent.key.keysym.sym) {
                    case SDLK_RIGHT:
                    case SDLK_d:
                        direction = SDL_SCANCODE_RIGHT;
                        break;
                    case SDLK_LEFT:
                    case SDLK_a:
                        direction = SDL_SCANCODE_LEFT;
                        break;
                    case SDLK_UP:
                    case SDLK_SPACE:
                        if (!isJumping && onGround) {
                            playerVelY = jumpStrength;
                            Mix_PlayChannel(-1, music, 0);
                            onGround = false;
                            isJumping = true;
                        }
                        break;
                }
            }
        }

        // Update player velocity based on the most recent direction pressed
        playerVelX = 0;
        if (state[SDL_SCANCODE_LEFT]) {
            playerVelX = -playerSpeed;
        } else if (state[SDL_SCANCODE_RIGHT]) {
            playerVelX = playerSpeed;
        } else {
            playerVelX = 0;
        }


        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastUpdateTime;
        lastUpdateTime = currentTime;








        // Update the player's position
        r.x += playerVelX * deltaTime;
        r.y += playerVelY * deltaTime;

        // Apply gravity
        if (!onGround) {
            playerVelY += gravity;
        }

        if(onGround){
            isJumping = false;
        }


        // Clamp the player's position within the window bounds
        if (r.x < 0) r.x = 0;
        if (r.x + r.w > WIDTH) r.x = WIDTH - r.w;
        if (r.y + r.h > HEIGHT) {
            r.y = HEIGHT - r.h;
            playerVelY = 0;
            onGround = true;
        }

        // Check for collision with the platform
        if (checkRectCollision(r, r2)) {
            // Check if the player is falling and colliding with the top of the platform
            if (playerVelY > 0 && r.y + r.h <= r2.y + 10) {
                r.y = r2.y - r.h; // Place player on top of the platform
                playerVelY = 0.5;
                isJumping = false; // Player is no longer jumping
                onGround = true;
            }
        }

                // Check for collision with the platform
        if (checkRectCollision2(r, r3)) {
            // Check if the player is falling and colliding with the top of the platform
            if (playerVelY > 0 && r.y + r.h <= r3.y + 10) {
                r.y = r3.y - r.h; // Place player on top of the platform
                playerVelY = 0.5;
                isJumping = false; // Player is no longer jumping
                onGround = true;
            }
        }

                        // Check for collision with the platform
        if (checkRectCollision3(r, r4)) {
            // Check if the player is falling and colliding with the top of the platform
            if (playerVelY > 0 && r.y + r.h <= r4.y + 10) {
                r.y = r4.y - r.h; // Place player on top of the platform
                playerVelY = 0.5;
                isJumping = false; // Player is no longer jumping
                onGround = true;
            }
        }

                        // Check for collision with the platform
        if (checkRectCollision4(r, r5)) {
            // Check if the player is falling and colliding with the top of the platform
            if (playerVelY > 0 && r.y + r.h <= r5.y + 10) {
                r.y = r5.y - r.h; // Place player on top of the platform
                playerVelY = 0.5;
                isJumping = false; // Player is no longer jumping
                onGround = true;
            }
        }

                if (checkRectCollision5(r, r6)) {
            // Check if the player is falling and colliding with the top of the platform
            if (playerVelY > 0 && r.y + r.h <= r6.y + 10) {
                r.y = r6.y - r.h; // Place player on top of the platform
                playerVelY = 0.5;
                isJumping = false; // Player is no longer jumping
                onGround = true;
            }
        }

        if (checkRectCollision5(r, r7)) {
            // Check if the player is falling and colliding with the top of the platform
            if (playerVelY > 0 && r.y + r.h <= r7.y + 10) {
                r.y = r7.y - r.h; // Place player on top of the platform
                playerVelY = 0.5;
                isJumping = false; // Player is no longer jumping
                onGround = true;
            }
        }

        if (checkRectCollision5(r, r8)) {
            // Check if the player is falling and colliding with the top of the platform
            if (playerVelY > 0 && r.y + r.h <= r8.y + 10) {
                r.y = r8.y - r.h; // Place player on top of the platform
                playerVelY = 0.5;
                isJumping = false; // Player is no longer jumping
                onGround = true;
            }
        }        
        
        if (checkRectCollision5(r, r9)) {
            // Check if the player is falling and colliding with the top of the platform
            if (playerVelY > 0 && r.y + r.h <= r9.y + 10) {
                r.y = r9.y - r.h; // Place player on top of the platform
                playerVelY = 0.5;
                isJumping = false; // Player is no longer jumping
                onGround = true;
            }
        }

        


        r9.y += RectsSpeed * deltaTime + 2;

        

        


        if(rectMoves){
            // Update the rectangle's position
            r2.y += RectsSpeed * deltaTime;
            r3.y += RectsSpeed * deltaTime;
            r4.y += RectsSpeed * deltaTime;
            r5.y += RectsSpeed * deltaTime;

            r6.y += RectsSpeed * deltaTime;
            r7.y += RectsSpeed * deltaTime;
            r8.y += RectsSpeed * deltaTime;
        }



        
        if (r2.y > HEIGHT + 50){

            
            r2.x = rand() % (WIDTH - r2.w);
            r2.y = -10;
        }
        if (r3.y > HEIGHT ){
            r3.x = rand() % (WIDTH - r3.w);
            r3.y = -10;
        }
        if (r4.y > HEIGHT ){
            r4.x = rand() % (WIDTH - r4.w);
            r4.y = -10;
        }
        if (r5.y > HEIGHT ){
            r5.x = rand() % (WIDTH - r5.w);
            r5.y = -10;
        }
        if (r6.y > HEIGHT ){
            r6.x = rand() % (WIDTH - r6.w);
            r6.y = -10;
        }
        if (r7.y > HEIGHT ){
            r7.x = rand() % (WIDTH - r7.w);
            r7.y = -10;
        }
        if (r8.y > HEIGHT ){
            r8.x = rand() % (WIDTH - r8.w);
            r8.y = -10;
        
        }
        if (r9.y > HEIGHT ){
            r9.x = rand() % (WIDTH - r9.w);
            r9.y = -10;
        
        }


        

        // Update the triangle's position
        if (triangleMovingLeft) {
            triangleX -= triangleSpeed * deltaTime;
            if (triangleX < 0) {
                triangleX = 0;
                triangleMovingLeft = false;
            }
        } else {
            triangleX += triangleSpeed * deltaTime;
            if (triangleX + triangleWidth > WIDTH) {
                triangleX = WIDTH - triangleWidth;
                triangleMovingLeft = true;
            }
        }






        // Update the triangle's vertices
        verts[0] = {SDL_FPoint{triangleX + 10, triangleY - 20}, SDL_Color{255, 0, 0, 255}, SDL_FPoint{0}};
        verts[1] = {SDL_FPoint{triangleX, triangleY}, SDL_Color{0, 0, 255, 255}, SDL_FPoint{0}};
        verts[2] = {SDL_FPoint{triangleX + 20, triangleY}, SDL_Color{0, 255, 0, 255}, SDL_FPoint{0}};


        

        



        

        // Check for collision with the triangle
        if (checkRectCollision(r, {static_cast<int>(triangleX), static_cast<int>(triangleY - triangleHeight), triangleWidth, triangleHeight})) {
            // Collision detected, reset positions
            r.x = 50;
            r.y = 280;
            r2.x = 250;
            r2.y = 260;
            r3.x = 100;
            r3.y = 200;
            r4.x = 230;
            r4.y = 150;
            r5.x = 10;
            r5.y = 100;
            r6.x = 200;
            r6.y = 30;
            r7.x = 150;
            r7.y = 50;
            r8.x = 120;
            r8.y = 200;
            r9.x = rand() % WIDTH;
            r9.y = rand() % HEIGHT;

            triangleX = WIDTH - 70;
            triangleY = HEIGHT;
            triangleMovingLeft = true;
            RectSpeed = 0.125f;
            isJumping = false;
            onGround = false;
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the player rectangle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &r);

        // Draw the small triangle
        SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);

        // Draw the platform
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &r2);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &r3);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &r4);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &r5);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &r6);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &r7);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &r8);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &r9);



        // Present the rendered frame
        SDL_RenderPresent(renderer);

        // Delay to cap the frame rate
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

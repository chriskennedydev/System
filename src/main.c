#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>

#include <stdio.h>

int character_creation();
int better_character_creation();

int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *bitmap = NULL;
    SDL_Surface *surface = NULL;
    int pos_x = 100, pos_y = 100, width = 640, height = 480;

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        SDL_Log("Unable to init SDL: %s\n", SDL_GetError());


    window = SDL_CreateWindow("Muh Game", pos_x, pos_y, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    surface = SDL_LoadBMP("../img/hello.bmp");
    bitmap = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    while(1) 
    {
        SDL_Event e;
        if(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                break;
            }
            if((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE)) {
                int better = better_character_creation();
                if(better == 2) 
                    break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bitmap, NULL, NULL);
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyTexture(bitmap);
    SDL_DestroyRenderer(renderer);

    int msg_box = character_creation();

    printf("Recommended class: ");

    if(msg_box < 0) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Missing File", "A file is missing, please reinstall the program.", NULL);
    }
    if(msg_box == 1) {
       printf("Fighter\n");
    }
    if(msg_box == 2) {
        printf("Barbarian\n");
    }
    if(msg_box == 3) {
        printf("Pit Fighter\n");
    }
    if(msg_box == 4) {
        printf("Ranger\n");
    }
    if(msg_box == 5) {
        printf("Monk\n");
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int character_creation()
{
    const SDL_MessageBoxButtonData buttons[] = {
        { 0, 0, "Sword and Shield" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Axe and Shield" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 2, "War Hammer" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 3, "Battle Axe" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 4, "Bow and Arrow" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 5, "Fists and Feet" },
    };

    const SDL_MessageBoxColorScheme color_scheme = {
        {
            { 55, 55, 55 },
            { 0, 255, 0 },
            { 255, 255, 0 },
            { 0, 0, 255 },
            { 255, 0, 255 }
        }
    };

    const SDL_MessageBoxData message_box_data = {
        SDL_MESSAGEBOX_INFORMATION,
        NULL,
        "Character Creation",
        "Choose Your Weapon",
        SDL_arraysize(buttons),
        buttons,
        &color_scheme
    };

    int button_id;
    if(SDL_ShowMessageBox(&message_box_data, &button_id) < 0) {
        SDL_Log("Error displaying message box: %s\n", SDL_GetError());
        return 1;
    }

    if(button_id == -1) {
        SDL_Log("No selection.");
    }

    return button_id;
}

int better_character_creation()
{
    const SDL_MessageBoxButtonData buttons[] = {
        { 0, 0, "No" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 2, "Yes" },
    };

    const SDL_MessageBoxColorScheme color_scheme = {
        {
            { 55, 55, 55 },
            { 0, 255, 0 },
            { 255, 255, 0 },
            { 0, 0, 255 },
            { 255, 0, 255 }
        }
    };

    const SDL_MessageBoxData message_box_data = {
        SDL_MESSAGEBOX_INFORMATION,
        NULL,
        "Quit",
        "Are you sure you want to quit?",
        SDL_arraysize(buttons),
        buttons,
        &color_scheme
    };

    int button_id;

    if(SDL_ShowMessageBox(&message_box_data, &button_id) < 0) {
        SDL_Log("Error displaying message box");
        return 1;
    }
    if(button_id == -1) {
        SDL_Log("No selection");
    }
        
    return button_id;
}

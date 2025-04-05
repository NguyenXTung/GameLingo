#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Begin.h"
#include "Constant.h"
#include "DrawGraphic.h"
#include "modegame.h"
using namespace std;
// chon che do choi
int modegame(SDL_Window* window, SDL_Renderer* renderer){
    system("cls");
    SDL_Texture* background = loadTexture("Gpx/BgLingo.png", renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
    SDL_Rect optionA;
    optionA.w = 300;
    optionA.h = 60;
    optionA.x = SCREEN_WIDTH / 2 -optionA.w/2;
    optionA.y = SCREEN_HEIGHT / 2 + optionA.h/2-150;
    SDL_Texture* BarA = loadTexture("Gpx/Bar.png", renderer);
    renderTexture(BarA,renderer, optionA.w, optionA.h, optionA.x, optionA.y);
    renderTextToCenterOfRect(renderer, "EASY", "KeedySans.ttf", {255, 255, 255, 255}, 60, optionA);
    SDL_Rect optionB;
    optionB.w = 300;
    optionB.h = 60;
    optionB.x = SCREEN_WIDTH / 2 -optionB.w/2;
    optionB.y = SCREEN_HEIGHT / 2 + optionB.h/2-80;
    SDL_Texture* BarB = loadTexture("Gpx/Bar.png", renderer);
    renderTexture(BarB,renderer, optionB.w, optionB.h, optionB.x, optionB.y);
    renderTextToCenterOfRect(renderer, "MEDIUM", "KeedySans.ttf", {255, 255, 255, 255}, 60, optionB);
    SDL_Rect optionC;
    optionC.w = 300;
    optionC.h = 60;
    optionC.x = SCREEN_WIDTH / 2 -optionC.w/2;
    optionC.y = SCREEN_HEIGHT / 2 + optionC.h/2-10;
    SDL_Texture* BarC = loadTexture("Gpx/Bar.png", renderer);
    renderTexture(BarC,renderer, optionC.w, optionC.h, optionC.x, optionC.y);
    renderTextToCenterOfRect(renderer, "HARD", "KeedySans.ttf", {255, 255, 255, 255}, 60, optionC);
    SDL_RenderPresent( renderer );
    SDL_Event e;
    while(true){
    if ( SDL_WaitEvent(&e) == 0) SDL_Delay(100);
        else if(e.type == SDL_QUIT){
            quitSDL(window, renderer);
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN){
                int x, y;
                SDL_GetMouseState(&x, &y);
                if((x >= optionA.x && x <= optionA.x+optionA.w)&&(y >= optionA.y && y <= optionA.y + optionA.h)){
                        return 0;
                        break;
                }
                if((x >= optionB.x && x <= optionB.x+optionB.w)&&(y >= optionB.y && y <= optionB.y + optionB.h)){
                        return 1;
                        break;
                }
                if((x >= optionC.x && x <= optionC.x+optionC.w)&&(y >= optionC.y && y <= optionC.y + optionC.h)){
                        return 2;
                        break;
        }
    }
}
}

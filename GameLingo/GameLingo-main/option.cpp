#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Begin.h"
#include "Constant.h"
#include "DrawGraphic.h"
#include "option.h"
using namespace std;
// dieu chinh tro choi (dieu chinh do dai tu khoa, toi thieu 4 chu, toi da 9 chu)
int option(SDL_Window* window, SDL_Renderer* renderer){
        int ROW = 4;
        SDL_RenderClear(renderer);
        SDL_Texture* background = loadTexture("Gpx/BgLingo.png", renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
        SDL_Rect infor;
        infor.w = 700;
        infor.h = 80;
        infor.x = SCREEN_WIDTH / 2 - infor.w/2;
        infor.y = 0;
        SDL_Texture* BarA = loadTexture("Gpx/Bar2.png", renderer);
        renderTexture(BarA,renderer, infor.w, infor.h, infor.x, infor.y);
        SDL_Rect text;
        text.w = 300;
        text.h = 60;
        text.x = 450;
        text.y = 600;
        renderTextToCenterOfRect(renderer, "[ENTER] or [ESC] to return", "KeedySans.ttf", {255, 255, 255, 255}, 50, text);
        SDL_Rect helps;
        helps.w = 300;
        helps.h = 60;
        helps.x = 850;
        helps.y = 300;
        renderTextToRightOfRect(renderer, "[UP]: +1 LETTER", "KeedySans.ttf", {255, 255, 255, 255}, 30, helps);
        helps.y += 40;
        renderTextToRightOfRect(renderer, "[DOWN]: -1 LETTER", "KeedySans.ttf", {255, 255, 255, 255}, 30, helps);
        SDL_Event e;
        while(true){
        if ( SDL_WaitEvent(&e) == 0) SDL_Delay(100);
            else if(e.type == SDL_QUIT){
                    quitSDL(window, renderer);
            }
            else if(e.type == SDL_KEYDOWN){
                    if(e.key.keysym.sym == SDLK_UP){
                            if(ROW < 9){
                                ROW++;
                                SDL_Texture* BarA = loadTexture("Gpx/Bar2.png", renderer);
                                renderTexture(BarA,renderer, infor.w, infor.h, infor.x, infor.y);
                            }
                            if(ROW >= 9) ROW = 9;
                    }
                    if(e.key.keysym.sym == SDLK_DOWN){
                            if(ROW > 4){
                                ROW--;
                                SDL_Texture* BarA = loadTexture("Gpx/Bar2.png", renderer);
                                renderTexture(BarA,renderer, infor.w, infor.h, infor.x, infor.y);
                            }
                            if(ROW <= 4) ROW = 4;
                    }
                    if(e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_ESCAPE){
                            break;
                    }
            }
    drawBoard(window, renderer, ROW);
    string text = "Number of letters: " + to_string(ROW);
    renderTextToCenterOfRect(renderer, text, "KeedySans.ttf", {255, 255, 255, 255}, 60, infor);
    SDL_RenderPresent(renderer);
    }
    return ROW;
    SDL_RenderClear(renderer);
}

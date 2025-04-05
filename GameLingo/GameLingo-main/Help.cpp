#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Begin.h"
using namespace std;
void help(SDL_Window* window, SDL_Renderer* renderer){
    SDL_Rect infor;
    infor.w = 300;
    infor.h = 60;
    infor.x = 880;
    infor.y = 250;
    renderTextToRightOfRect(renderer, "[SPACE]: Retype", "KeedySans.ttf", {255, 255, 255, 255}, 30, infor);
    infor.y += 40;
    renderTextToRightOfRect(renderer, "[SHIFT]: Hint", "KeedySans.ttf", {255, 255, 255, 255}, 30, infor);
    infor.y += 40;
    renderTextToRightOfRect(renderer, "[ENTER]: Guess", "KeedySans.ttf", {255, 255, 255, 255}, 30, infor);
    infor.y += 40;
    renderTextToRightOfRect(renderer, "[DELETE]: Pass", "KeedySans.ttf", {255, 255, 255, 255}, 30, infor);
    infor.y += 40;
    renderTextToRightOfRect(renderer, "[BACKSPACE]: Erase", "KeedySans.ttf", {255, 255, 255, 255}, 30, infor);
    infor.y += 40;
    renderTextToRightOfRect(renderer, "[ESC]: Quit game", "KeedySans.ttf", {255, 255, 255, 255}, 30, infor);
    SDL_RenderPresent(renderer);
}

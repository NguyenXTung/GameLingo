#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Begin.h"
#include "Constant.h"
#include "DrawGraphic.h"
using namespace std;
// ve bang ROW*ROW
void drawBoard(SDL_Window* window, SDL_Renderer* renderer, int ROW){
    SDL_Rect filled_rect;
    filled_rect.x = SCREEN_WIDTH / 2 + 10 - 60 * (8+1)/2;
    filled_rect.y = SCREEN_HEIGHT / 2 + 10 - 60 * (8+1)/2;
    filled_rect.h = 20+8*60;
    filled_rect.w = 20+8*60;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &filled_rect);
    filled_rect.x = SCREEN_WIDTH / 2 + 15 - 60 * (8+1)/2;
    filled_rect.y = SCREEN_HEIGHT / 2 + 15 - 60 * (8+1)/2;
    filled_rect.h = 10+8*60;
    filled_rect.w = 10+8*60;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &filled_rect);
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < ROW; j++){
    filled_rect.w = (490-(ROW+1)*10)/ROW;
    filled_rect.h = filled_rect.w;
    filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + j*(filled_rect.w+10);
    filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + i*(filled_rect.w+10);
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &filled_rect);
        }
    }
}
// hien thi hang dang nhap
void drawActivateRow(SDL_Window* window, SDL_Renderer* renderer, int ROW, int k, string guess) {
    SDL_Rect filled_rect;
    for(int j = 0; j < ROW; j++){
    filled_rect.w = (490-(ROW+1)*10)/ROW;
    filled_rect.h = filled_rect.w;
    filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + j*(filled_rect.w+10);
    filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
    SDL_SetRenderDrawColor(renderer, 0, 0, 250, 255);
    SDL_RenderFillRect(renderer, &filled_rect);
    string letter = "";
    letter += guess[j];
    renderTextToCenterOfRect(renderer, letter,FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
    SDL_RenderPresent(renderer);
    Sleep(50);
    }
}
// hien thi o dang nhap
void drawActivateRect(SDL_Window* window, SDL_Renderer* renderer, int ROW, int k, int j, string guess) {
    SDL_Rect filled_rect;
    filled_rect.w = (490-(ROW+1)*10)/ROW;
    filled_rect.h = filled_rect.w;
    filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + j*(filled_rect.w+10);
    filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
    SDL_SetRenderDrawColor(renderer, 120, 0, 250, 255);
    SDL_RenderFillRect(renderer, &filled_rect);
    string letter = "";
    letter += guess[j];
    if(j < ROW){
        renderTextToCenterOfRect(renderer, letter,FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
    }
    else renderTextToCenterOfRect(renderer, "",FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
    SDL_RenderPresent(renderer);
}

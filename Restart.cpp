#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Begin.h"
#include "Constant.h"
#include "DrawGraphic.h"
#include "Restart.h"
using namespace std;
// trang thong bao diem sau khi ket thuc game
int restartgame(SDL_Window* window, SDL_Renderer* renderer, int point, int highest){
    SDL_Texture* background = loadTexture("BgLingo.png", renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
    SDL_Rect optionA;
    optionA.w = 300;
    optionA.h = 60;
    optionA.x = SCREEN_WIDTH / 2 -optionA.w/2;
    optionA.y = SCREEN_HEIGHT / 2 + optionA.h/2-50;
    SDL_Texture* BarA = loadTexture("Bar.png", renderer);
    renderTexture(BarA,renderer, optionA.w, optionA.h, optionA.x, optionA.y);
    renderTextToCenterOfRect(renderer, "PLAY AGAIN", "KeedySans.ttf", {255, 255, 255, 255}, 40, optionA);
    SDL_Rect optionB;
    optionB.w = 300;
    optionB.h = 60;
    optionB.x = SCREEN_WIDTH / 2 -optionB.w/2;
    optionB.y = SCREEN_HEIGHT / 2 + optionB.h/2+20;
    SDL_Texture* BarB = loadTexture("Bar.png", renderer);
    renderTexture(BarB,renderer, optionB.w, optionB.h, optionB.x, optionB.y);
    renderTextToCenterOfRect(renderer, "MAIN MENU", "KeedySans.ttf", {255, 255, 255, 255}, 40, optionB);
    double p;
    if(highest == 0 || point >= highest){
        p = 680;
    } else{
        p = 680*point/highest;
    }
    SDL_Rect points;
    points.w = 700;
    points.h = 90;
    points.x = SCREEN_WIDTH / 2 - points.w/2-30;
    points.y = SCREEN_HEIGHT / 2 + points.h/2-170;
    SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
    SDL_RenderFillRect(renderer, &points);
    SDL_Rect points2;
    points2.w = p;
    points2.h = 70;
    points2.x = SCREEN_WIDTH / 2 - 680/2-30;
    points2.y = SCREEN_HEIGHT / 2 + points2.h/2-150;
    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
    SDL_RenderFillRect(renderer, &points2);
    if(point >= highest){
    SDL_Texture* NewRec = loadTexture("NewRecord.png", renderer);
    renderTexture(NewRec,renderer, 210, 70, points.x + 10, points.y + 10);
    }
    string text = to_string(highest);
    renderTextToLeftOfRect(renderer, text, "KeedySans.ttf", {255, 255, 255, 255}, 60, points);
    points.y -= points.h - 10;
    renderTextToCenterOfRect(renderer, "SCORE", "KeedySans.ttf", {255, 255, 255, 255}, 60, points);
    points.y += 30;
    renderTextToLeftOfRect(renderer, "HIGHSCORES", "KeedySans.ttf", {255, 255, 255, 255}, 20, points);
    text = to_string(point);
    renderTextToRightOfRect(renderer, text, "KeedySans.ttf", {255, 255, 255, 255}, 60, points2);
    SDL_RenderPresent(renderer);
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
                    return 1;
                    break;
            }
            if((x >= optionB.x && x <= optionB.x+optionB.w)&&(y >= optionB.y && y <= optionB.y + optionB.h)){
                    return 2;
                    break;
            }
        }
    }
}

#include <iostream>
#include <string>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Begin.h"
#include "Constant.h"
#include "option.h"
#include "DrawGraphic.h"
#include "Restart.h"
using namespace std;
// trang thong bao diem sau khi ket thuc game
int restartgame(SDL_Window* window, SDL_Renderer* renderer, int point, int highest){
    SDL_Texture* background = loadTexture("Gpx/BgLingo.png", renderer);
    SDL_Texture* Bar = loadTexture("Gpx/Bar.png", renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
    SDL_Rect optionA;
    optionA.w = 300;
    optionA.h = 60;
    optionA.x = SCREEN_WIDTH / 2 -optionA.w/2;
    optionA.y = SCREEN_HEIGHT / 2 + optionA.h/2-50;
    renderTexture(Bar,renderer, optionA.w, optionA.h, optionA.x, optionA.y);
    if(language == 0) renderTextToCenterOfRect(renderer, "PLAY AGAIN", FONT2, {255, 255, 255, 255}, 40, optionA);
    else renderTextToCenterOfRect(renderer, "CHƠI LẠI", FONT2, {255, 255, 255, 255}, 40, optionA);
    SDL_Rect optionB;
    optionB.w = 300;
    optionB.h = 60;
    optionB.x = SCREEN_WIDTH / 2 -optionB.w/2;
    optionB.y = SCREEN_HEIGHT / 2 + optionB.h/2+20;
    renderTexture(Bar,renderer, optionB.w, optionB.h, optionB.x, optionB.y);
    if(language == 0) renderTextToCenterOfRect(renderer, "MAIN MENU", FONT2, {255, 255, 255, 255}, 40, optionB);
    else renderTextToCenterOfRect(renderer, "TRANG CHỦ", FONT2, {255, 255, 255, 255}, 40, optionB);
    double p;
    if(highest == 0 || point >= highest){
        p = 680;
    } else{
        p = 680*point/highest;
    }
    SDL_Rect points;
    points.w = 700;
    points.h = 70;
    points.x = SCREEN_WIDTH / 2 - points.w/2-30;
    points.y = SCREEN_HEIGHT / 2 + points.h/2-150;
    SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
    SDL_RenderFillRect(renderer, &points);
    SDL_Rect points2;
    points2.w = p;
    points2.h = 50;
    points2.x = SCREEN_WIDTH / 2 - 680/2-30;
    points2.y = SCREEN_HEIGHT / 2 + points2.h/2-130;
    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
    SDL_RenderFillRect(renderer, &points2);
    if(point >= highest && point != 0){
    SDL_Texture* NewRec = loadTexture("Gpx/NewRecord.png", renderer);
    renderTexture(NewRec,renderer, 150, 50, points.x + 10, points.y + 10);
    }
    string text = to_string(highest);
    renderTextToLeftOfRect(renderer, text, FONT, {255, 255, 255, 255}, 60, points);
    points.y -= points.h + 10;
    if(language == 0) renderTextToCenterOfRect(renderer, "SCORE", FONT2, {255, 255, 255, 255}, 60, points);
    else renderTextToCenterOfRect(renderer, "ĐIỂM", FONT2, {255, 255, 255, 255}, 60, points);
    points.y += 30;
    if(language == 0) renderTextToLeftOfRect(renderer, "HIGHSCORE", FONT2, {255, 255, 255, 255}, 20, points);
    else renderTextToLeftOfRect(renderer, "KỶ LỤC ", FONT2, {255, 255, 255, 255}, 35, points);
    text = to_string(point);
    renderTextToRightOfRect(renderer, text, FONT, {255, 255, 255, 255}, 60, points2);
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

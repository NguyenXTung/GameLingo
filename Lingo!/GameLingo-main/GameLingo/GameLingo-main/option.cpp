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
#include "modegame.h"
using namespace std;
// dieu chinh tro choi (dieu chinh do dai tu khoa, toi thieu 4 chu, toi da 9 chu)
int language = 0;
int ROW = 4;
void editboard(SDL_Window* window, SDL_Renderer* renderer){
    SDL_RenderClear(renderer);
    SDL_Texture* background = loadTexture("Gpx/BgLingo.png", renderer);
    SDL_Texture* Bar = loadTexture("Gpx/Bar2.png", renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
    string text[4];
    if(language == 0){
        text[0] = "[ENTER] or [ESC] to return";
        text[1] = "[UP]: +1 LETTER";
        text[2] = "[DOWN]: -1 LETTER";
        text[3] = "NUMBER OF LETTER: ";
    } else{
        text[0] = "[ENTER] hoặc [ESC] để trở về";
        text[1] = "[UP]: +1 CHỮ CÁI";
        text[2] = "[DOWN]: -1 CHỮ CÁI";
        text[3] = "SỐ CHỮ CÁI: ";
    }
    SDL_Rect infor;
    infor.w = 700;
    infor.h = 80;
    infor.x = SCREEN_WIDTH / 2 - infor.w/2;
    infor.y = 0;
    renderTexture(Bar,renderer, infor.w, infor.h, infor.x, infor.y);
    SDL_Rect helps;
    helps.w = 300;
    helps.h = 60;
    helps.x = 450;
    helps.y = 580;
    renderTextToCenterOfRect(renderer, text[0], FONT2, {255, 255, 255, 255}, 50, helps);
    helps.w = 500;
    helps.h = 60;
    helps.x = 680;
    helps.y = 300;
    renderTextToRightOfRect(renderer, text[1], FONT2, {255, 255, 255, 255}, 30, helps);
    helps.y += 40;
    renderTextToRightOfRect(renderer, text[2], FONT2, {255, 255, 255, 255}, 30, helps);

    bool edit = true;
    while(edit){
    drawBoard(window, renderer, ROW);
    renderTexture(Bar,renderer, infor.w, infor.h, infor.x, infor.y);
    string tex = text[3] + to_string(ROW);
    renderTextToCenterOfRect(renderer, tex, FONT2, {255, 255, 255, 255}, 50, infor);
    SDL_RenderPresent(renderer);
    SDL_Event t;
    while(true){
    if ( SDL_WaitEvent(&t) == 0) SDL_Delay(100);
        else if(t.type == SDL_QUIT){
                quitSDL(window, renderer);
        }
        else if(t.type == SDL_KEYDOWN){
                if(t.key.keysym.sym == SDLK_UP){
                        if(ROW < 9){
                            ROW++;
                        }
                        if(ROW >= 9) ROW = 9;
                        break;
                }
                if(t.key.keysym.sym == SDLK_DOWN){
                        if(ROW > 4){
                            ROW--;
                        }
                        if(ROW <= 4) ROW = 4;
                        break;
                }
                if(t.key.keysym.sym == SDLK_RETURN || t.key.keysym.sym == SDLK_ESCAPE){
                        edit = false;
                        break;
                }
        }
    }
    }
}
void option(SDL_Window* window, SDL_Renderer* renderer){
        bool op = true;
        string text[4];
        while(op){
        if(language == 0){
            text[0] = "EDIT BOARD";
            text[1] = "MODE";
            text[2] = "LANGUAGE: ENGLISH";
            text[3] = "MENU";
        } else{
            text[0] = "CÀI ĐẶT BẢNG";
            text[1] = "CHẾ ĐỘ";
            text[2] = "NGÔN NGỮ: TIẾNG VIỆT";
            text[3] = "TRANG CHỦ";
        }
        SDL_RenderClear(renderer);
        SDL_Texture* background = loadTexture("Gpx/BgLingo.png", renderer);
        SDL_Texture* Bar = loadTexture("Gpx/Bar2.png", renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
        SDL_Rect optionA;
        optionA.w = 525;
        optionA.h = 60;
        optionA.x = SCREEN_WIDTH / 2 -optionA.w/2;
        optionA.y = SCREEN_HEIGHT / 2 + optionA.h/2-180;
        renderTexture(Bar,renderer, optionA.w, optionA.h, optionA.x, optionA.y);
        renderTextToCenterOfRect(renderer, text[0], FONT2, {255, 255, 255, 255}, 45, optionA);
        SDL_Rect optionB;
        optionB.w = 525;
        optionB.h = 60;
        optionB.x = SCREEN_WIDTH / 2 -optionB.w/2;
        optionB.y = SCREEN_HEIGHT / 2 + optionB.h/2-110;
        renderTexture(Bar,renderer, optionB.w, optionB.h, optionB.x, optionB.y);
        renderTextToCenterOfRect(renderer, text[1], FONT2, {255, 255, 255, 255}, 45, optionB);
        SDL_Rect optionC;
        optionC.w = 525;
        optionC.h = 60;
        optionC.x = SCREEN_WIDTH / 2 -optionC.w/2;
        optionC.y = SCREEN_HEIGHT / 2 + optionC.h/2-40;
        renderTexture(Bar,renderer, optionC.w, optionC.h, optionC.x, optionC.y);
        renderTextToCenterOfRect(renderer, text[2], FONT2, {255, 255, 255, 255}, 40, optionC);
        SDL_Rect optionD;
        optionD.w = 525;
        optionD.h = 60;
        optionD.x = SCREEN_WIDTH / 2 -optionD.w/2;
        optionD.y = SCREEN_HEIGHT / 2 + optionD.h/2+30;
        renderTexture(Bar,renderer, optionD.w, optionD.h, optionD.x, optionD.y);
        renderTextToCenterOfRect(renderer, text[3], FONT2, {255, 255, 255, 255}, 45, optionD);
        SDL_RenderPresent(renderer);
        // nhap chuot trang option
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
                        editboard(window, renderer);
                        break;
                    }
                    if((x >= optionB.x && x <= optionB.x+optionB.w)&&(y >= optionB.y && y <= optionB.y + optionB.h)){
                        modegame(window, renderer);
                        break;
                    }
                    if((x >= optionC.x && x <= optionC.x+optionC.w)&&(y >= optionC.y && y <= optionC.y + optionC.h)){
                            if(language == 0) language = 1;
                            else if(language == 1) language = 0;
                            break;
                    }
                    if((x >= optionD.x && x <= optionD.x+optionD.w)&&(y >= optionD.y && y <= optionD.y + optionD.h)){
                        op = false;
                        break;
                    }
            }
        }
    SDL_RenderPresent(renderer);
    }
}

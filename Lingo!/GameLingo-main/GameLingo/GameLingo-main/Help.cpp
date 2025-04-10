#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Begin.h"
#include "Constant.h"
#include "Option.h"
using namespace std;
void help(SDL_Window* window, SDL_Renderer* renderer){
    string text[6];
    if(language == 0){
        text[0] = "[SPACE]: Retype";
        text[1] = "[SHIFT]: Hint";
        text[2] = "[ENTER]: Guess";
        text[3] = "[DELETE]: Pass";
        text[4] = "[BACKSPACE]: Erase";
        text[5] = "[ESC]: Quit";
    } else{
        text[0] = "[SPACE]: Gõ lại";
        text[1] = "[SHIFT]: Gợi ý";
        text[2] = "[ENTER]: Đoán";
        text[3] = "[DELETE]: Bỏ qua";
        text[4] = "[BACKSPACE]: Xóa";
        text[5] = "[ESC]: Thoát";
    }
    SDL_Rect infor;
    infor.w = 800;
    infor.h = 60;
    infor.x = 380;
    infor.y = 250;
    renderTextToRightOfRect(renderer, text[0], FONT2, {255, 255, 255, 255}, 30, infor);
    infor.y += 40;
    renderTextToRightOfRect(renderer, text[1], FONT2, {255, 255, 255, 255}, 30, infor);
    infor.y += 40;
    renderTextToRightOfRect(renderer, text[2], FONT2, {255, 255, 255, 255}, 30, infor);
    infor.y += 40;
    renderTextToRightOfRect(renderer, text[3], FONT2, {255, 255, 255, 255}, 30, infor);
    infor.y += 40;
    renderTextToRightOfRect(renderer, text[4], FONT2, {255, 255, 255, 255}, 30, infor);
    infor.y += 40;
    renderTextToRightOfRect(renderer, text[5], FONT2, {255, 255, 255, 255}, 30, infor);
    SDL_RenderPresent(renderer);
}

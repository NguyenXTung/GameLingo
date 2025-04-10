#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Begin.h"
#include "Constant.h"
#include "Randomword.h"
#include "DrawGraphic.h"
#include "option.h"
#include "Restart.h"
#include "Help.h"
#include "modegame.h"
using namespace std;
int point = 0; // so diem dau game
int lives = 3; // so mang choi dau game
int lifeline; //so goi y
int a; //a: bien dem so diem da dat de cong goi y (a > 500) thi se cong 1 goi y
int Highest; //diem cao nhat
string keyword;
string beginword = "";
string guess;
vector<string> words; // mang chua cac tu co trong tu dien
vector<string> keywords; // mang chua cac tu trong kho tu khoa
void nhaptudien(){
    ifstream file1("words.txt");
    ifstream file2("words3.txt");
    if (!file1.is_open() || !file2.is_open()) {
        cerr << "Không thể mở file từ điển!" << endl;
    }
    string word;
    while (getline(file1, word)) {
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        words.push_back(word);
    }
    file1.close();
    string keyword;
    while (getline(file2, keyword)) {
        transform(keyword.begin(), keyword.end(), keyword.begin(), ::toupper);
        keywords.push_back(keyword);
    }
    file2.close();
}
void checkword(SDL_Window* window, SDL_Renderer* renderer, int ROW, int k){
    //invalidword
    Mix_Chunk* sound1 = Mix_LoadWAV("Sound/Green.wav");
    Mix_Chunk* sound2 = Mix_LoadWAV("Sound/Yellow.wav");
    Mix_Chunk* sound3 = Mix_LoadWAV("Sound/Blue.wav");
    Mix_Chunk* sound4 = Mix_LoadWAV("Sound/Invalid.wav");
    if (!sound1 || !sound2 || !sound3 || !sound4) {
        cerr << "Failed to load sound effects! Mix_Error: " << Mix_GetError() << endl;
    }
    bool valid = true; // bien kiem tra hop le (true: hop le; false: khong hop le);
    // kiem tra tu duoc nhap da du chu cai chua (neu chua se tinh la khong hop le)
    for(int i = 0; i < ROW; i++){
        if(guess[i] == '.'){
            valid = false;
            break;
        }
    }
    // kiem tra tu duoc nhap co trong tu dien khong (neu khong co se tinh la khong hop le)
    vector<string>::iterator it;
    it = find (words.begin(), words.end(), guess);
    vector<string>::iterator it2;
    it2 = find (keywords.begin(), keywords.end(), guess);
    if (it != words.end() || it2 != keywords.end()) valid = true;
    else valid = false;
    //animation hang khong hop le
    if(!valid){
    int channel = Mix_PlayChannel(-1, sound4, 0);
    if (channel == -1 ) {
        cerr << "Failed to play sound effects! Mix_Error: " << Mix_GetError() << endl;
    }
    for(int j = 0; j < ROW; j++){
        SDL_Rect filled_rect;
        filled_rect.w = (490-(ROW+1)*10)/ROW;
        filled_rect.h = filled_rect.w;
        filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + j*(filled_rect.w+10);
        filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
        SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
        SDL_RenderFillRect(renderer, &filled_rect);
        string letter = "";
        letter += guess[j];
        renderTextToCenterOfRect(renderer, letter,FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
        SDL_RenderPresent(renderer);
    }
    }
    // neu tu duoc nhap hop le, bat dau kiem tra tung chu cai
    if(valid){
    int a[26] = {0};
    for(int i = 0; i < ROW; i++){
        a[(keyword[i]) - 'A']++;
    }
    int b[26] = {0};
    int tthai[ROW] = {0}; //trang thai cac chu cai (0: chu cai khong xuat hien trong tu khoa; 1: chu cai co xuat hien nhung sai vi tri; 2: chu cai co xuat hien va dung vi tri)
    // xet cac chu cai co xuat hien va dung vi tri truoc
    for(int i = 0; i < ROW; i++){
        if(guess[i] == keyword[i]){
            b[guess[i]-'A']++;
            tthai[i] = 2;
            beginword[i] = keyword[i];
        }
    }
    // xet cac chu cai co xuat hien nhung sai vi tri
    for(int i = 0; i < ROW; i++){
        if(tthai[i] != 2){
        bool check = false;
        for(int j = 0; j < ROW; j++){
            if(guess[i] == keyword[j] && tthai[j] != 2 && (b[guess[i]-'A'] < a[guess[i]-'A'])){
                check = true;
                b[guess[i] - 'A']++;
                break;
            }
        }
        if(check){ tthai[i] = 1;}
        else{tthai[i] = 0;}
        }
    }
    // hien thi trang thai va chay am thanh cua tung chu cai
    for(int i = 0; i < ROW; i++){
            SDL_Rect filled_rect;
            filled_rect.w = (490-(ROW+1)*10)/ROW;
            filled_rect.h = filled_rect.w;
            filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + i*(filled_rect.w+10);
            filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
            if(tthai[i] == 0){
            SDL_SetRenderDrawColor(renderer, 0, 0, 150, 255);
            int channel = Mix_PlayChannel(-1, sound3, 0);
            if (channel == -1 ) {
                cerr << "Failed to play sound effects! Mix_Error: " << Mix_GetError() << endl;
            }
            }
            if(tthai[i] == 1){
            SDL_SetRenderDrawColor(renderer, 150, 150, 0, 255);
            int channel = Mix_PlayChannel(-1, sound2, 0);
            if (channel == -1 ) {
                cerr << "Failed to play sound effects! Mix_Error: " << Mix_GetError() << endl;
            }
            }
            if(tthai[i] == 2){
            SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
            int channel = Mix_PlayChannel(-1, sound1, 0);
            if (channel == -1 ) {
                cerr << "Failed to play sound effects! Mix_Error: " << Mix_GetError() << endl;
            }
            }
            SDL_RenderFillRect(renderer, &filled_rect);
            string letter = "";
            letter += guess[i];
            renderTextToCenterOfRect(renderer, letter,FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
            SDL_RenderPresent(renderer);
    Sleep(200);
    }
    }
}
// hien tu khoa
void showkeyword(SDL_Window* window, SDL_Renderer* renderer, int ROW, int k){
    for(int i = 0; i < ROW; i++){
        SDL_Rect filled_rect;
        filled_rect.w = (490-(ROW+1)*10)/ROW;
        filled_rect.h = filled_rect.w;
        filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + i*(filled_rect.w+10);
        filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
        SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
        SDL_RenderFillRect(renderer, &filled_rect);
        string letter = "";
        letter += keyword[i];
        renderTextToCenterOfRect(renderer, letter,FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
        SDL_RenderPresent(renderer);
    }
    Sleep(150);
}
// hien thi so diem, so mang, so goi y
void showpoint(SDL_Window* window, SDL_Renderer* renderer, int point, int lives){
    SDL_Rect filled_rect;
    filled_rect.w = 150;
    filled_rect.h = 60;
    filled_rect.x = 50;
    filled_rect.y = 30;
    SDL_SetRenderDrawColor(renderer, 0, 0, 150, 255);
    SDL_RenderFillRect(renderer, &filled_rect);
    string text = to_string(point);
    int size = 60;
    if(text.size() > 3) size = 60 - (text.size()-3)*8;
    renderTextToCenterOfRect(renderer, text,FONT, SDL_Color{255,255,255}, size, filled_rect);

    SDL_Rect box;
    box.w = 95;
    box.h = 50;
    box.x = 105;
    box.y = 90;
    SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
    SDL_RenderFillRect(renderer, &box);
    string textlives = to_string(lives);
    renderTextToCenterOfRect(renderer, textlives,FONT, SDL_Color{255,255,255}, 60, box);


    box.w = 95;
    box.h = 50;
    box.x = 105;
    box.y = 140;
    SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
    SDL_RenderFillRect(renderer, &box);
    string texthints = to_string(lifeline);
    renderTextToCenterOfRect(renderer, texthints,FONT, SDL_Color{255,255,255}, 60, box);

    SDL_RenderPresent(renderer);
}
// chuan bi cho tro choi
void setup(SDL_Window* window, SDL_Renderer* renderer){
    help(window, renderer);
    showpoint(window, renderer, point, lives);
    SDL_Rect box;
    box.w = 55;
    box.h = 50;
    box.x = 50;
    box.y = 90;
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    SDL_RenderFillRect(renderer, &box);
    SDL_Texture* Heart = loadTexture("Gpx/Heart.png", renderer);
    renderTexture(Heart,renderer, 45, 40, 55, 95);
    box.w = 55;
    box.h = 50;
    box.x = 50;
    box.y = 140;
    SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
    SDL_RenderFillRect(renderer, &box);
    SDL_Texture* Goiy = loadTexture("Gpx/Hints.png", renderer);
    renderTexture(Goiy,renderer, 45, 40, 55, 145);
    SDL_RenderPresent(renderer);
    nhaptudien();
    keyword = randomkeyword(ROW);
    beginword = "";
    for(int i = 0; i < ROW; i++){
        beginword += ".";
    }
    if(mode == 1){
    beginword[0] = keyword[0];
    }
    if(mode == 0){
    beginword[0] = keyword[0];
    beginword[ROW-1] = keyword[ROW-1];
    }
    int j = 0;
    for(int w = 0; w < ROW; w++){
        if(beginword[w] != '.') j++;
        else break;
    }
    guess = beginword;
    drawBoard(window, renderer, ROW);
    drawActivateRow(window, renderer, ROW, 0, guess);
    drawActivateRect(window, renderer, ROW, 0, j,guess);
}
// dung goi y
void hint(SDL_Window* window, SDL_Renderer* renderer, int k){
    Mix_Chunk* sfxhint = Mix_LoadWAV("Sound/Hint.wav");
    if (!sfxhint) {
        cerr << "Failed to load sound effects! Mix_Error: " << Mix_GetError() << endl;
    }
    int channel = Mix_PlayChannel(-1, sfxhint, 0);
    if (channel == -1 ) {
        cerr << "Failed to play sound effects! Mix_Error: " << Mix_GetError() << endl;
    }
    for(int i = 0; i < ROW; i++){
        if(beginword[i] != keyword[i]){
            guess[i] = keyword[i];
            beginword[i] = keyword[i];
            for(int t = 0; t < 6; t++){
                SDL_Rect filled_rect;
                filled_rect.w = (490-(ROW+1)*10)/ROW;
                filled_rect.h = filled_rect.w;
                filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + i*(filled_rect.w+10);
                filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
                if(t % 2 == 0) SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
                else if(t == 5) SDL_SetRenderDrawColor(renderer, 0, 0, 250, 255);
                else SDL_SetRenderDrawColor(renderer, 0, 0, 150, 255);
                SDL_RenderFillRect(renderer, &filled_rect);
                string letter = "";
                letter += keyword[i];
                renderTextToCenterOfRect(renderer, letter,FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
                SDL_RenderPresent(renderer);
                Sleep(100);
            }
            break;
        }
    }
    drawActivateRow(window, renderer, ROW, k, guess);
}
// lay highscore tu file diem
void loadMaxScore() {
    ifstream file("HighScore.txt");
    if (file.is_open()) {
        file >> Highest;
        file.close();
    } else {
        Highest = 0; // Neu file rong, bien mang gtri = 0
    }
}

// Luu gtri highscore ve file diem
void saveMaxScore() {
    ofstream file("HighScore.txt");
    if (file.is_open()) {
        file << Highest;
        file.close();
    } else {
        cerr << "Failed to save highest score!" << endl;
    }
}
// trochoi
void game(SDL_Window* window, SDL_Renderer* renderer){
    SDL_RenderClear(renderer);
    Mix_Music* music = Mix_LoadMUS("Sound/BedTheme.mp3");
    if (!music) {
        cerr << "Failed to load music! Mix_Error: " << Mix_GetError() << endl;
    }
    Mix_Chunk* win = Mix_LoadWAV("Sound/WinnerTheme.wav");
    Mix_Chunk* lose = Mix_LoadWAV("Sound/LoserTheme.wav");
    if (!win || !lose) {
        cerr << "Failed to load sound effects! Mix_Error: " << Mix_GetError() << endl;
    }
    lives = 3;
    point = 0;
    lifeline = 1;
    a = 0;
    bool game = true;
    while(game){
    SDL_Texture* background = loadTexture("Gpx/BgLingo.png", renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
    Mix_PlayMusic(music, -1);
    loadMaxScore();
    setup(window, renderer);
    int k = 0, j = 0;
    for(int w = 0; w < ROW; w++){
        if(beginword[w] != '.') j++;
        else break;
    }
    bool play = true;
    SDL_Event e;
    while (play) {
        if ( SDL_WaitEvent(&e) == 0) SDL_Delay(100);
        else if(e.type == SDL_QUIT) quitSDL(window, renderer);
        else if(e.type == SDL_KEYDOWN){
                //input word
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    play = false;
                    game = false;
                }
                if((e.key.keysym.sym) >= SDLK_a && (e.key.keysym.sym) <= SDLK_z){
                    guess[j] = (SDL_GetKeyName(e.key.keysym.sym))[0];
                    SDL_Rect filled_rect;
                    filled_rect.w = (490-(ROW+1)*10)/ROW;
                    filled_rect.h = filled_rect.w;
                    filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + j*(filled_rect.w+10);
                    filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 250, 255);
                    SDL_RenderFillRect(renderer, &filled_rect);
                    j++;
                    if(j >= ROW){
                        j = ROW-1;
                    }
                    drawActivateRect(window, renderer, ROW, k, j,guess);
                    renderTextToCenterOfRect(renderer, SDL_GetKeyName(e.key.keysym.sym), FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
                    SDL_RenderPresent(renderer);
                }
                //fix word
                else if((e.key.keysym.sym) == SDLK_BACKSPACE){
                    guess[j] = '.';
                    SDL_Rect filled_rect;
                    filled_rect.w = (490-(ROW+1)*10)/ROW;
                    filled_rect.h = filled_rect.w;
                    filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + j*(filled_rect.w+10);
                    filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 250, 255);
                    SDL_RenderFillRect(renderer, &filled_rect);
                    renderTextToCenterOfRect(renderer, ".", FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
                    SDL_RenderPresent(renderer);
                    j--;
                    if(j < 0){
                        j = 0;
                    }
                    drawActivateRect(window, renderer, ROW, k, j,guess);
                }
                else if((e.key.keysym.sym) == SDLK_LEFT){
                    SDL_Rect filled_rect;
                    filled_rect.w = (490-(ROW+1)*10)/ROW;
                    filled_rect.h = filled_rect.w;
                    filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + j*(filled_rect.w+10);
                    filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 250, 255);
                    SDL_RenderFillRect(renderer, &filled_rect);
                    string letter = "";
                    letter += guess[j];
                    renderTextToCenterOfRect(renderer, letter, FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
                    SDL_RenderPresent(renderer);
                    j--;
                    if(j < 0){
                        j = ROW-1;
                    }
                    drawActivateRect(window, renderer, ROW, k, j,guess);
                }
                else if((e.key.keysym.sym) == SDLK_RIGHT){
                    SDL_Rect filled_rect;
                    filled_rect.w = (490-(ROW+1)*10)/ROW;
                    filled_rect.h = filled_rect.w;
                    filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + j*(filled_rect.w+10);
                    filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 250, 255);
                    SDL_RenderFillRect(renderer, &filled_rect);
                    string letter = "";
                    letter += guess[j];
                    renderTextToCenterOfRect(renderer, letter, FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
                    SDL_RenderPresent(renderer);
                    j++;
                    if(j >= ROW){
                        j = 0;
                    }
                    drawActivateRect(window, renderer, ROW, k, j,guess);
                }
                //guess word, next turn
                else if((e.key.keysym.sym) == SDLK_RETURN){
                    bool nextrow = true;
                    checkword(window, renderer, ROW, k);
                    k++;
                    j = 0;
                    if(k >= ROW){
                        nextrow = false;
                        if(guess != keyword){
                        //in ra thông báo thua cuộc
                        Mix_HaltMusic();
                        int channel = Mix_PlayChannel(-1, lose, 0);
                        if (channel == -1 ) {
                            cerr << "Failed to play sound effects! Mix_Error: " << Mix_GetError() << endl;
                        }
                        lives--;
                        if(lives <= 0) lives = 0;
                        showpoint(window, renderer, point,lives);
                        Sleep(1000);
                        showkeyword(window, renderer, ROW, ROW-1);
                        if(lives > 0) Sleep(2000);
                        if(lives <= 0){
                        // in ra thông báo kết thúc game
                        SDL_Texture* logo = loadTexture("Gpx/Loser.png", renderer);
                        renderTexture(logo,renderer, 600, 290, SCREEN_WIDTH/2-300, SCREEN_HEIGHT/2-145);
                        SDL_RenderPresent( renderer );
                        Sleep(3000);
                        if (point > Highest){
                            Highest = point;
                            saveMaxScore();
                        }
                        int check = restartgame(window, renderer, point, Highest);
                        if(check == 1){
                            play = false;
                            point = 0;
                            lives = 3;
                            lifeline = 1;
                            a = 0;
                        }
                        else{
                            play = false;
                            game = false;
                        }
                        } else{
                            play = false;
                            }
                        }
                    }
                    if(guess == keyword){
                        nextrow = false;
                        //in ra thông báo thắng game
                        Mix_HaltMusic();
                        int channel = Mix_PlayChannel(-1, win, 0);
                        if (channel == -1 ) {
                            cerr << "Failed to play sound effects! Mix_Error: " << Mix_GetError() << endl;
                        }
                        k--;
                        // cong thuc cong diem
                        int plus = (ROW+mode)*5 + ROW*(ROW-k-1)*(2+(mode-1)*1);
                        point += plus;
                        a += plus;
                        SDL_Rect filled_rect;
                        filled_rect.w = 150;
                        filled_rect.h = 60;
                        filled_rect.x = 50;
                        filled_rect.y = 30;
                        string text = "+" + to_string(plus);
                        renderTextToLeftOfRect(renderer, text,FONT, SDL_Color{0,255,0}, 50, filled_rect);
                        if(a > 500){
                            a -= 500;
                            if(lifeline >= 3) lifeline = 3; //gioi han so lifeline
                            if(lifeline < 3){
                            lifeline++;
                            SDL_Rect box;
                            box.w = 150;
                            box.h = 50;
                            box.x = 50;
                            box.y = 190;
                            if(language == 0) renderTextToCenterOfRect(renderer, "+1 HINT",FONT2, SDL_Color{0,255,0}, 35, box);
                            else renderTextToCenterOfRect(renderer, "+1 GỢI Ý",FONT2, SDL_Color{0,255,0}, 30, box);
                            }
                        }
                        showpoint(window, renderer, point, lives);
                        //animation win
                        for(int x = 0; x < 3; x++){
                        for(int t = 0; t <= ROW+2; t++){
                            SDL_Rect filled_rect;
                            filled_rect.w = (490-(ROW+1)*10)/ROW;
                            filled_rect.h = filled_rect.w;
                            for(int e = 0; e < ROW; e++){
                            filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + e*(filled_rect.w+10);
                            filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
                            SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
                            SDL_RenderFillRect(renderer, &filled_rect);
                            string letter = "";
                            letter += guess[e];
                            renderTextToCenterOfRect(renderer, letter, FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
                            }
                            if(t < ROW){
                            filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + t*(filled_rect.w+10);
                            filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
                            SDL_SetRenderDrawColor(renderer, 150, 255, 150, 255);
                            SDL_RenderFillRect(renderer, &filled_rect);
                            string letter = "";
                            letter += guess[t];
                            renderTextToCenterOfRect(renderer, letter, FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
                            }
                            if(t > 0 && t <= ROW){
                            filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + (t-1)*(filled_rect.w+10);
                            filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
                            SDL_SetRenderDrawColor(renderer, 0, 250, 0, 255);
                            SDL_RenderFillRect(renderer, &filled_rect);
                            string letter = "";
                            letter += guess[t-1];
                            renderTextToCenterOfRect(renderer, letter, FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
                            }
                            if(t > 1 && t <= ROW+1){
                            filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + (t-2)*(filled_rect.w+10);
                            filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + k*(filled_rect.w+10);
                            SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
                            SDL_RenderFillRect(renderer, &filled_rect);
                            string letter = "";
                            letter += guess[t-2];
                            renderTextToCenterOfRect(renderer, letter, FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
                            }
                            SDL_RenderPresent(renderer);
                            Sleep(50);
                        }
                        }
                        //SDL_Texture* win = loadTexture("Winner.png", renderer);
                        //renderTexture(win,renderer, 876, 140, SCREEN_WIDTH/2-438, SCREEN_HEIGHT/2-70);
                        SDL_RenderPresent( renderer );
                        Sleep(2000-150*ROW);
                        play = false;
                        }
                    if(nextrow){
                    j = 0;
                    for(int w = 0; w < ROW; w++){
                        if(beginword[w] != '.') j++;
                        else break;
                    }
                    if(j >= ROW) j = ROW-1;
                    guess = beginword;
                    drawActivateRow(window, renderer, ROW, k, guess);
                    drawActivateRect(window, renderer, ROW, k, j,guess);
                    }
                }
                else if((e.key.keysym.sym) == SDLK_DELETE){
                        //in ra thông báo thua cuộc
                        Mix_HaltMusic();
                        int channel = Mix_PlayChannel(-1, lose, 0);
                        if (channel == -1 ) {
                            cerr << "Failed to play sound effects! Mix_Error: " << Mix_GetError() << endl;
                        }
                        SDL_Rect filled_rect;
                        for(int a = k; a < ROW; a++){
                        for(int j = 0; j < ROW; j++){
                            filled_rect.w = (490-(ROW+1)*10)/ROW;
                            filled_rect.h = filled_rect.w;
                            filled_rect.x = SCREEN_WIDTH / 2 +25 - 60 * (8+1)/2 + j*(filled_rect.w+10);
                            filled_rect.y = SCREEN_HEIGHT / 2 + 25 - 60 * (8 + 1)/2 + a*(filled_rect.w+10);
                            SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
                            SDL_RenderFillRect(renderer, &filled_rect);
                            renderTextToCenterOfRect(renderer, ".",FONT, SDL_Color{255,255,255}, 36*8/ROW, filled_rect);
                            SDL_RenderPresent(renderer);
                            //Sleep(20);
                        }
                        }
                        lives--;
                        if(lives <= 0) lives = 0;
                        showpoint(window, renderer, point,lives);
                        Sleep(1000);
                        showkeyword(window, renderer, ROW, ROW-1);
                        if(lives > 0) Sleep(2000);
                        if(lives <= 0){
                        // in ra thông báo kết thúc game
                        SDL_Texture* logo = loadTexture("Gpx/Loser.png", renderer);
                        renderTexture(logo,renderer, 600, 290, SCREEN_WIDTH/2-300, SCREEN_HEIGHT/2-145);
                        SDL_RenderPresent( renderer );
                        Sleep(3000);
                        if (point > Highest){
                            Highest = point;
                            saveMaxScore();
                        }
                        int check = restartgame(window, renderer, point, Highest);
                        if(check == 1){
                            play = false;
                            point = 0;
                            lives = 3;
                            lifeline = 1;
                            a = 0;
                        }
                        else{
                            play = false;
                            game = false;
                        }
                        } else{
                                play = false;
                            }
                    }
                //clear word
                else if((e.key.keysym.sym) == SDLK_SPACE){
                    j = 0;
                    for(int w = 0; w < ROW; w++){
                        if(beginword[w] != '.') j++;
                        else break;
                    }
                    guess = beginword;
                    drawActivateRow(window, renderer, ROW, k, guess);
                    drawActivateRect(window, renderer, ROW, k, j,guess);
                }
                else if((e.key.keysym.sym) == SDLK_LSHIFT){
                    if(lifeline > 0){
                    hint(window, renderer, k);
                    drawActivateRow(window, renderer, ROW, k, guess);
                    j = 0;
                    for(int w = 0; w < ROW; w++){
                        if(beginword[w] != '.') j++;
                        else break;
                    }
                    if(j >= ROW) j = ROW-1;
                    drawActivateRect(window, renderer, ROW, k, j, guess);
                    lifeline--;
                    showpoint(window, renderer, point, lives);
                    } else{

                    }
                }
            }
        }
    }
    SDL_RenderPresent(renderer);
    Mix_FreeMusic(music);
    SDL_RenderClear(renderer);
}
// trang chu chinh
void menu(SDL_Window* window, SDL_Renderer* renderer){
    string text[4];
    if(language == 0){
        text[0] = "PLAY";
        text[1] = "OPTION";
        text[2] = "QUIT";
    } else{
        text[0] = "CHƠI";
        text[1] = "CÀI ĐẶT";
        text[2] = "THOÁT";
    }
    SDL_Texture* background = loadTexture("Gpx/BgLingo.png", renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
    SDL_Texture* logo = loadTexture("Gpx/logoLingo.png", renderer);
    renderTexture(logo,renderer, 876, 168, SCREEN_WIDTH/2-438, SCREEN_HEIGHT/2-184);
    SDL_Rect optionA;
    optionA.w = 300;
    optionA.h = 60;
    optionA.x = SCREEN_WIDTH / 2 -optionA.w/2;
    optionA.y = SCREEN_HEIGHT / 2 + optionA.h/2;
    SDL_Texture* Bar = loadTexture("Gpx/Bar.png", renderer);
    renderTexture(Bar,renderer, optionA.w, optionA.h, optionA.x, optionA.y);
    renderTextToCenterOfRect(renderer, text[0], FONT2, {255, 255, 255, 255}, 45, optionA);
    SDL_Rect optionB;
    optionB.w = 300;
    optionB.h = 60;
    optionB.x = SCREEN_WIDTH / 2 -optionB.w/2;
    optionB.y = SCREEN_HEIGHT / 2 + optionB.h/2+70;
    renderTexture(Bar,renderer, optionB.w, optionB.h, optionB.x, optionB.y);
    renderTextToCenterOfRect(renderer, text[1], FONT2, {255, 255, 255, 255}, 45, optionB);
    SDL_Rect optionC;
    optionC.w = 300;
    optionC.h = 60;
    optionC.x = SCREEN_WIDTH / 2 -optionC.w/2;
    optionC.y = SCREEN_HEIGHT / 2 + optionC.h/2+140;
    renderTexture(Bar,renderer, optionC.w, optionC.h, optionC.x, optionC.y);
    renderTextToCenterOfRect(renderer, text[2], FONT2, {255, 255, 255, 255}, 45, optionC);
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
                        game(window, renderer);
                        menu(window, renderer);
                }
                if((x >= optionB.x && x <= optionB.x+optionB.w)&&(y >= optionB.y && y <= optionB.y + optionB.h)){
                        option(window, renderer);
                        menu(window, renderer);
                }
                if((x >= optionC.x && x <= optionC.x+optionC.w)&&(y >= optionC.y && y <= optionC.y + optionC.h)){
                        quitSDL(window, renderer);
                }
        }
    }
}
int main(int argc, char* argv[]){
    const char* WINDOW_TITLE = "Lingo!";
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);
    SDL_RenderClear(renderer);
    menu(window, renderer);
    quitSDL(window, renderer);
    return 0;
}

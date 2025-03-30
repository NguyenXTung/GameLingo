#ifndef DRAWGRAPHIC__H
#define DRAWGRAPHIC__H
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;
void drawBoard(SDL_Window* window, SDL_Renderer* renderer, int ROW);
void drawActivateRow(SDL_Window* window, SDL_Renderer* renderer, int ROW, int k, string guess);
void drawActivateRect(SDL_Window* window, SDL_Renderer* renderer, int ROW, int k, int j, string guess);
#endif // DRAWGRAPHIC__H

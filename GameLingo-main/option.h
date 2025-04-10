#ifndef OPTION__H
#define OPTION__H

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
using namespace std;
extern int ROW;
extern int language;
void editboard(SDL_Window* window, SDL_Renderer* renderer);
void option(SDL_Window* window, SDL_Renderer* renderer);
#endif // OPTION__H

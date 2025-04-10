#ifndef BEGIN__H
#define BEGIN__H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;
void logErrorAndExit(const char* msg, const char* error);
SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);
SDL_Texture* textTexture(SDL_Renderer *renderer, const string &message, const string &fontFile, const SDL_Color color, const int fontSize);
SDL_Renderer* createRenderer(SDL_Window* window);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void renderTexture(SDL_Texture *texture,SDL_Renderer* renderer, int w, int h, int a, int b);
void renderTextureToCenterOfRect(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect rect);
void renderTextToCenterOfRect(SDL_Renderer *renderer, const string &message, const string &fontFile, const SDL_Color color, const int fontSize, const SDL_Rect rect);
void renderTextureToRightOfRect(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect rect);
void renderTextToRightOfRect(SDL_Renderer *renderer, const string &message, const string &fontFile, const SDL_Color color, const int fontSize, const SDL_Rect rect);
void renderTextureToLeftOfRect(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect rect);
void renderTextToLeftOfRect(SDL_Renderer *renderer, const string &message, const string &fontFile, const SDL_Color color, const int fontSize, const SDL_Rect rect);
SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer);
#endif // BEGIN__H

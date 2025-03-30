#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Begin.h"
#include "Constant.h"
using namespace std;
void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());
    if (TTF_Init() == -1) {
        cerr << "TTF could not initialize! TTF_Error: " << TTF_GetError() << endl;
        return 0;
    }

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 0;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
       cerr << "SDL_mixer could not initialize! Mix_Error: " << Mix_GetError() << endl;
        return 0;
    }

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //full screen
    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    return window;
}
SDL_Texture* textTexture(SDL_Renderer *renderer, const string &message, const string &fontFile, const SDL_Color color, const int fontSize)
{
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);

	SDL_Surface *surface = TTF_RenderUTF8_Blended(font, message.c_str(), color);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	return texture;
}
SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    //showText
    TTF_Font* font = TTF_OpenFont("KeedySans.ttf", 40);
    if (font == nullptr) {
        cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << endl;
        return 0;
    }
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello, SDL2!", textColor);
    if (textSurface == nullptr) {
        cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << endl;
        return 0;
    }
    return renderer;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void renderTexture(SDL_Texture *texture,SDL_Renderer* renderer, int w, int h, int a, int b)
{
	SDL_Rect dest;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	dest.w = w;
	dest.h = h;
	dest.x = a;
	dest.y = b;
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}
void renderTextureToCenterOfRect(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect rect)
{
	SDL_Rect texRect;
	SDL_QueryTexture(texture, NULL, NULL, &texRect.w, &texRect.h);
	texRect.x = rect.x + (rect.w - texRect.w) / 2;
	texRect.y = rect.y + (rect.h - texRect.h) / 2;

	SDL_RenderCopy(renderer, texture, NULL, &texRect);
}
void renderTextureToRightOfRect(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect rect)
{
	SDL_Rect texRect;
	SDL_QueryTexture(texture, NULL, NULL, &texRect.w, &texRect.h);
	texRect.x = rect.x + (rect.w - texRect.w) - 10;
	if(rect.w - texRect.w - 10 < 0) texRect.x = rect.x;
	texRect.y = rect.y + (rect.h - texRect.h) / 2;

	SDL_RenderCopy(renderer, texture, NULL, &texRect);
}
void renderTextureToLeftOfRect(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect rect)
{
	SDL_Rect texRect;
	SDL_QueryTexture(texture, NULL, NULL, &texRect.w, &texRect.h);
	texRect.x = rect.x + rect.w + 10;
	texRect.y = rect.y + (rect.h - texRect.h) / 2;

	SDL_RenderCopy(renderer, texture, NULL, &texRect);
}
void renderTextToCenterOfRect(SDL_Renderer *renderer, const string &message, const string &fontFile, const SDL_Color color, const int fontSize, const SDL_Rect rect)
{
	SDL_Texture* texture = textTexture(renderer, message, fontFile, color, fontSize);
	renderTextureToCenterOfRect(renderer, texture, rect);
	SDL_DestroyTexture(texture);
}
void renderTextToRightOfRect(SDL_Renderer *renderer, const string &message, const string &fontFile, const SDL_Color color, const int fontSize, const SDL_Rect rect)
{
	SDL_Texture* texture = textTexture(renderer, message, fontFile, color, fontSize);
	renderTextureToRightOfRect(renderer, texture, rect);
	SDL_DestroyTexture(texture);
}
void renderTextToLeftOfRect(SDL_Renderer *renderer, const string &message, const string &fontFile, const SDL_Color color, const int fontSize, const SDL_Rect rect)
{
	SDL_Texture* texture = textTexture(renderer, message, fontFile, color, fontSize);
	renderTextureToLeftOfRect(renderer, texture, rect);
	SDL_DestroyTexture(texture);
}
SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

	return texture;
}

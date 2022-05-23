#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class MyWindow
{
private:
	SDL_Window* mwindow;
	SDL_Renderer* mrenderer;
	int mwidth;
	int mheight;
public:
	MyWindow();
	bool init();
	void free();
	const int getWidth() const;
	const int getHeight() const;
	SDL_Renderer* getRenderer();
};

MyWindow::MyWindow() {
	mwindow = NULL;
	mrenderer = NULL;
	mwidth = SCREEN_WIDTH;
	mheight = SCREEN_HEIGHT;
}
bool MyWindow::init() {
	int success = true;
	mwindow = SDL_CreateWindow("in summary", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mwidth, mheight, SDL_WINDOW_SHOWN);
	if (mwindow == NULL) {
		printf("Create window is failure. %s", SDL_GetError());
		success = false;
	}
	else {
		mrenderer = SDL_CreateRenderer(mwindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
		if (mrenderer == NULL) {
			printf("Create renderer is failure. %s", SDL_GetError());
			success = false;
		}
		else {
			SDL_SetRenderDrawColor(mrenderer, 0xff, 0xff, 0xff, 0xff);

			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
				printf("Init image is failure. %s", IMG_GetError());
				success = false;
			}
		}
	}
	return success;
}
void MyWindow::free() {
	if (mwindow != NULL) {
		SDL_DestroyWindow(mwindow);
		mwindow = NULL;
	}
	if (mrenderer != NULL) {
		SDL_DestroyRenderer(mrenderer);
		mrenderer = NULL;
	}
	IMG_Quit();
	SDL_Quit();
}
const int MyWindow::getWidth() const {
	return mwidth;
}
const int MyWindow::getHeight() const {
	return mheight;
}
SDL_Renderer* MyWindow::getRenderer() {
	return mrenderer;
}

class MyTexture
{
private:
	SDL_Texture* mtexture;
	MyWindow* mwindow;
	int mwidth;
	int mheight;
public:
	MyTexture();
	~MyTexture();
	bool loadFromFile(std::string path);
	bool loadFromRenderedText(TTF_Font* gFont, std::string textureText, SDL_Color textColor);
	void free();
	void rend(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	const int getWidth() const;
	const int getHeight() const;
};

MyTexture::MyTexture() {
	mtexture = NULL;
	mwindow = NULL;
	mwidth = 0;
	mheight = 0;
}
MyTexture::~MyTexture() {
	free();
	mwindow->free();
	mwindow = NULL;
}

bool MyTexture::loadFromFile(std::string path) {
	free();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(mwindow->getRenderer(), loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else {
			mwidth = loadedSurface->w;
			mheight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mtexture = newTexture;
	return mtexture != NULL;
}

bool MyTexture::loadFromRenderedText(TTF_Font* gFont, std::string textureText, SDL_Color textColor) {
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL) {
		mtexture = SDL_CreateTextureFromSurface(mwindow->getRenderer(), textSurface);
		if (mtexture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			mwidth = textSurface->w;
			mheight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	else {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	return mtexture != NULL;
}

void MyTexture::free() {
	if (mtexture != NULL)
	{
		SDL_DestroyTexture(mtexture);
		mtexture = NULL;
		mwidth = 0;
		mheight = 0;
	}
}

void MyTexture::rend(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, mwidth, mheight };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(mwindow->getRenderer(), mtexture, clip, &renderQuad, angle, center, flip);
}
void MyTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(mtexture, red, green, blue);
}
void MyTexture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(mtexture, blending);
}
void MyTexture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(mtexture, alpha);
}
const int MyTexture::getWidth() const {
	return mwidth;
}
const int MyTexture::getHeight() const {
	return mheight;
}

bool init();

bool loadMedia();

void close();

MyWindow gwindow;
MyTexture gtexture;

bool init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		if (!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))) {
			printf("Warning: Linear texture filtering not enabled!");
			success = false;
		}

		if (!(gwindow.init())) {
			printf("Init Window is failure!");
			success = false;
		}
	}
	return success;
}

bool loadMedia() {
	bool success = true;
	if (!gtexture.loadFromFile("./resources/bg.png")) {
		printf("Failed to load dot texture!\n");
		success = false;
	}
	return success;
}

void close() {
	gtexture.free();
	gwindow.free();
}

int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				SDL_SetRenderDrawColor(gwindow.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gwindow.getRenderer());

				gtexture.rend(0, 0);

				//Update screen
				SDL_RenderPresent(gwindow.getRenderer());
			}
		}

		close();
	}

	return 0;
}

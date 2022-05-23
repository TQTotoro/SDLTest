# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <stdio.h>
# include <string >

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 1024;

enum KeyPressSurfaces
{
KEY_PRESS_SURFACE_DEFAULT, 
KEY_PRESS_SURFACE_UP, 
KEY_PRESS_SURFACE_DOWN, 
KEY_PRESS_SURFACE_LEFT,
KEY_PRESS_SURFACE_RIGHT,
KEY_PRESS_SURFACE_TOTAL
};

bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(std::string path);

SDL_Window * gWindow = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface * gScreenSurface = NULL;

SDL_Texture* gKeyPressTextures[KEY_PRESS_SURFACE_TOTAL];
SDL_Texture* gCurrentTexture = NULL;
SDL_Texture* texture = NULL;
SDL_Rect src = {0,0,64,64};
SDL_Rect dest = { 0,128,64,64};


// 创建window和窗口renderer
bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf(" SDL could not initialize ! SDL Error : %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("SDL Tutorial ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf(" Window could not be created ! SDL Error : %s\n", SDL_GetError () );
			success = false;
		}
		else
		{
			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) success = false;
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == nullptr)
				success = false;
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;

	gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT] = loadTexture("resources/1.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf(" Failed to load default image !\n");
		success = false;
	}

	gKeyPressTextures[KEY_PRESS_SURFACE_UP] = loadTexture("resources/2.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf(" Failed to load up image !\n");
		success = false;
	 }

	gKeyPressTextures[KEY_PRESS_SURFACE_DOWN] = loadTexture("resources/3.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf(" Failed to load down image !\n");
		success = false;
	}

	gKeyPressTextures[KEY_PRESS_SURFACE_LEFT] = loadTexture("resources/4.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf(" Failed to load left image !\n");
		success = false;
	}

	gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT] = loadTexture("resources/5.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf(" Failed to load right image !\n");
		success = false;
	}
	return success;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	gScreenSurface = IMG_Load(path.c_str());
	if (gScreenSurface == NULL)
	{
		printf(" Unable to load image %s! SDL Error : %s\n", path.c_str(), SDL_GetError());
	}
	texture = SDL_CreateTextureFromSurface(renderer, gScreenSurface);
	SDL_FreeSurface(gScreenSurface);
	return texture;
}

int main(int argc, char* args[])
{
	if (!init())
	{
		printf(" Failed to initialize !\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf(" Failed to load media !\n");
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT];
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_LEFT:
							gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT];
							break;
						default:
							gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}

				}
				SDL_SetRenderDrawColor(renderer, 110, 110, 110, 255);
				SDL_RenderClear(renderer); //czyścimy tylny bufor
				SDL_RenderCopy(renderer, gCurrentTexture, &src, &dest);
				SDL_RenderPresent(renderer);
			}

		}

	}
	close();
	return 0;
}
			
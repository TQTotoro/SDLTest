# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <stdio.h>
# include <string >

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 1024;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_1,
	KEY_PRESS_SURFACE_2,
	KEY_PRESS_SURFACE_3,
	KEY_PRESS_SURFACE_4,
	KEY_PRESS_SURFACE_TOTAL
};

bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(std::string path);

SDL_Window* gWindow = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* gScreenSurface = NULL;

SDL_Texture* gKeyPressTextures[KEY_PRESS_SURFACE_TOTAL];
SDL_Texture* gCurrentTexture = NULL;
SDL_Texture* texture = NULL;
SDL_Rect src = { 0, 0, 256, 816 };
SDL_Rect dest = { (SCREEN_WIDTH - src.w) / 2, (SCREEN_HEIGHT - src.h) / 2, src.w, src.h };


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
			printf(" Window could not be created ! SDL Error : %s\n", SDL_GetError());
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

bool loadMedia()
{
	bool success = true;

	gKeyPressTextures[KEY_PRESS_SURFACE_1] = loadTexture("resources/walk1.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_1] == NULL)
	{
		printf(" Failed to load default image !\n");
		success = false;
	}

	gKeyPressTextures[KEY_PRESS_SURFACE_2] = loadTexture("resources/walk2.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_2] == NULL)
	{
		printf(" Failed to load up image !\n");
		success = false;
	}

	gKeyPressTextures[KEY_PRESS_SURFACE_3] = loadTexture("resources/walk3.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_3] == NULL)
	{
		printf(" Failed to load down image !\n");
		success = false;
	}

	gKeyPressTextures[KEY_PRESS_SURFACE_4] = loadTexture("resources/walk4.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_4] == NULL)
	{
		printf(" Failed to load left image !\n");
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


int main_4(int argc, char* args[])
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
			gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_1];
			int frame_index = 0;
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
							gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_2];
							break;
						case SDLK_DOWN:
							gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_3];
							break;
						case SDLK_LEFT:
							gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_4];
							break;
						default:
							gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_1];
							break;
						}
					}
				}
//				SDL_SetRenderDrawColor(renderer, 110, 110, 110, 255);
//				SDL_RenderClear(renderer); 
				gCurrentTexture = gKeyPressTextures[frame_index / 8];
				frame_index++;
				if (frame_index == KEY_PRESS_SURFACE_TOTAL * 8 - 1)
					frame_index = 0;
				SDL_RenderCopy(renderer, gCurrentTexture, &src, &dest);
				SDL_RenderPresent(renderer);
				SDL_Delay(20);
			}

		}

	}
	close();
	return 0;
}

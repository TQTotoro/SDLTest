#include <iostream>
#include "SDL2/SDL.h"

//屏幕宽度
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//全局窗口和渲染器
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

//加载图片, 返回纹理
SDL_Texture* LoadImage(std::string file)
{
    SDL_Surface* loadedImage = nullptr;
    SDL_Texture* texture = nullptr;

    loadedImage = SDL_LoadBMP(file.c_str());
    if (loadedImage != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    else
        std::cout << SDL_GetError() << std::endl;
    return texture;
}

//将表面应用到渲染器
void ApplySurface(int x, int y, SDL_Texture* tex, SDL_Renderer* rend)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(rend, tex, NULL, &pos);
}

int main_3(int argc, char** argv)
{
    //初始化SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    //创建窗口
    window = SDL_CreateWindow("Lesson 2",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
        return 2;
    }

    //创建渲染器
    renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
        return 3;
    }

    //创建背景和前景纹理
    SDL_Texture* background = nullptr, * image = nullptr;
    background = LoadImage("background.bmp");
    image = LoadImage("image.bmp");
    if (background == nullptr || image == nullptr)
        return 4;

    //清空渲染器
    SDL_RenderClear(renderer);

    //在渲染器内平铺背景
    int bW, bH;
    SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
    ApplySurface(0, 0, background, renderer);
    ApplySurface(bW, 0, background, renderer);
    ApplySurface(0, bH, background, renderer);
    ApplySurface(bW, bH, background, renderer);

    //在渲染器中央放置前景
    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;
    ApplySurface(x, y, image, renderer);

    //呈现渲染器
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    //释放资源
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
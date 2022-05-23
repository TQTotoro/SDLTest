#include <iostream>
#include <SDL2/SDL.h>

int main_1(int argc, char** argv)
{
    //初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //创建窗口
    SDL_Window* win = nullptr;
    win = SDL_CreateWindow("Hello World!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    //创建渲染器
    SDL_Renderer* ren = nullptr;
    ren = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    //创建表面
    SDL_Surface* bmp = nullptr;
    bmp = SDL_LoadBMP("hello.bmp");
    if (bmp == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    //创建材质
    SDL_Texture* tex = nullptr;
    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp); // 释放表面，后续由窗口摧毁，我们不用管

    //清空渲染器
    SDL_RenderClear(ren);
    //将材质复制到渲染器
    SDL_RenderCopy(ren, tex, NULL, NULL);
    //呈现渲染器
    SDL_RenderPresent(ren);
    //窗口延时
    SDL_Delay(30000);

    //释放资源
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    //退出SDL
    SDL_Quit();

    return 0;
}
#include <iostream>
#include <SDL2/SDL.h>

int main_1(int argc, char** argv)
{
    //��ʼ��SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //��������
    SDL_Window* win = nullptr;
    win = SDL_CreateWindow("Hello World!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    //������Ⱦ��
    SDL_Renderer* ren = nullptr;
    ren = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    //��������
    SDL_Surface* bmp = nullptr;
    bmp = SDL_LoadBMP("hello.bmp");
    if (bmp == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    //��������
    SDL_Texture* tex = nullptr;
    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp); // �ͷű��棬�����ɴ��ڴݻ٣����ǲ��ù�

    //�����Ⱦ��
    SDL_RenderClear(ren);
    //�����ʸ��Ƶ���Ⱦ��
    SDL_RenderCopy(ren, tex, NULL, NULL);
    //������Ⱦ��
    SDL_RenderPresent(ren);
    //������ʱ
    SDL_Delay(30000);

    //�ͷ���Դ
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    //�˳�SDL
    SDL_Quit();

    return 0;
}
#include <stdexcept>
#include <string>
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

//��Ļ���
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

//ȫ�ִ��ں���Ⱦ��
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

//����ͼƬ, ��������
SDL_Texture* LoadImage(std::string file)
{
    SDL_Texture* tex = nullptr;
    tex = IMG_LoadTexture(renderer, file.c_str());
    if (tex == nullptr)
        throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
    return tex;
}

//������Ӧ�õ���Ⱦ��
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
    //��ʼ��SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    //��������
    window = SDL_CreateWindow("Lesson 3",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
        return 2;
    }

    //������Ⱦ��
    renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
        return 3;
    }

    //����������ǰ������
    SDL_Texture* background = nullptr, * image = nullptr;
    try {
        background = LoadImage("background.png");
        image = LoadImage("image.png");
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 4;
    }

    //�����Ⱦ��
    SDL_RenderClear(renderer);

    //����Ⱦ����ƽ�̱���
    int bW, bH;
    SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
    for (int y = 0; y <= SCREEN_HEIGHT; y += bH)
        for (int x = 0; x <= SCREEN_WIDTH; x += bW)
            ApplySurface(x, y, background, renderer);


    //����Ⱦ���������ǰ��
    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;
    ApplySurface(x, y, image, renderer);

    //������Ⱦ��
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    //�ͷ���Դ
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
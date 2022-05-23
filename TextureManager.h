#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <string>
#include <map>
#include "SDL2/SDL.h"

// 把 texture 单独划分成一个类是合理的，因为 texture 的来源很多
class TextureManager
{
public:
	static TextureManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	// texture的哪一部分渲染到哪里
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// 哪一帧被渲染
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// 只释放 s_pInstance 指向的资源即可
	void free() {
		if (s_pInstance != NULL) {
			delete s_pInstance;
			s_pInstance = NULL;
		}
	}

	void clearFromTextureMap(std::string id);

	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, 
		int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer);


private:
	TextureManager() {} // 单例模式，管理不同类型的 Texture

	// 松耦合设计，Renderer 需要的时候才调用，且只有一个实例对象
	static TextureManager* s_pInstance;
	std::map<std::string, SDL_Texture*> m_textureMap; // 记录不同 id 类型的 texture
};

typedef TextureManager TheTextureManager;

#endif // __TEXTUREMANAGER_H__
#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <string>
#include <map>
#include "SDL2/SDL.h"

// �� texture �������ֳ�һ�����Ǻ���ģ���Ϊ texture ����Դ�ܶ�
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

	// texture����һ������Ⱦ������
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// ��һ֡����Ⱦ
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// ֻ�ͷ� s_pInstance ָ�����Դ����
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
	TextureManager() {} // ����ģʽ������ͬ���͵� Texture

	// �������ƣ�Renderer ��Ҫ��ʱ��ŵ��ã���ֻ��һ��ʵ������
	static TextureManager* s_pInstance;
	std::map<std::string, SDL_Texture*> m_textureMap; // ��¼��ͬ id ���͵� texture
};

typedef TextureManager TheTextureManager;

#endif // __TEXTUREMANAGER_H__
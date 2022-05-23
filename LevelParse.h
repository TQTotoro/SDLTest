#ifndef __LEVELPARSE_H__
#define __LEVELPARSE_H__

#include "Level.h"
#include <SDL2/tinyxml.h>
#include <SDL2/tinystr.h>

class LevelParser
{
public:
	Level* parseLevel(const char* levelFile);

private:
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets);

	int m_tileSize;
	int m_width;
	int m_height;
};

#endif // __LEVELPARSE_H__
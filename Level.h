#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <iostream>
#include <vector>
#include "Layer.h"

struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};

// hold tilesets & layers
class Level
{
public:
	~Level() {};

	void update();
	void render();

	std::vector<Tileset>* getTilesets() {
		return &m_tilesets;
	}

	std::vector<Layer*>* getLayers() {
		return &m_layers;
	}


private:
	Level() {};
	friend class LevelParser;

	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;
};


#endif

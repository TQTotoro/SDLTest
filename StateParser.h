#ifndef __STATEPARSER_H__
#define __STATEPARSER_H__

#include <iostream>
#include <vector>
#include "SDL2/tinyxml.h"
#include "SDL2/tinystr.h"

class GameObject;

// ×´Ì¬½âÎöÆ÷£¬½âÎö xml ÎÄµµ
class StateParser
{
public:
	bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs);

private:
	void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*>* pObjects);
	void parseTextures(TiXmlElement* psStateRoot, std::vector<std::string>* pTextureIDs);
};

#endif /* defined(__STATEPARSER_H__) */

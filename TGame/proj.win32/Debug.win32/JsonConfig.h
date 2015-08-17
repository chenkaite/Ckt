#include "json/rapidjson.h" 
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;
class JsonConfig
{
	static JsonConfig* jsonConfig;
	static JsonConfig* create(String filename);

};
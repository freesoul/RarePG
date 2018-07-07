#ifndef _GFX_H_
#define _GFX_H_

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include <map>
#include <string>

using namespace std;

class Gfx {

private:
	static map<string, sf::Texture*> textures;

public:
	Gfx() { }
	
	~Gfx();

	static bool load(); // Fills a string-texture map from the info of a json file.

	static bool loadGfx(const string&, const string& filepath);

	static sf::Texture& getGfx(const string& name);

};

#endif
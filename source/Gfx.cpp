
#include "include/Gfx.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include <map>
#include <string>


using namespace std;



map<string, sf::Texture*> Gfx::textures;



Gfx::~Gfx()
{
	sf::Texture *texture;
	map<string, sf::Texture*>::iterator iter = textures.begin();
	while(iter != textures.end())
	{
	    texture = iter->second;
	    delete texture;
	    iter++;
	}
}


bool Gfx::load()
{
	///////////////////////////////////////////////
	// Load JSON with gfx files data
	///////////////////////////////////////////////

	// Read json as string
	std::ifstream t("data/gfx.json");
	std::stringstream buffer;
	buffer << t.rdbuf();

	// Get pointer to const char
	const std::string level_json_str_tmp = buffer.str();
	const char* level_json_str = level_json_str_tmp.c_str();

	// Parse json
	rapidjson::Document level_json_document;
	rapidjson::ParseResult result = level_json_document.Parse(level_json_str);

	// Error parsing?
	if(!result){
		fprintf(stderr, "JSON parse error: %s (%u)",
		rapidjson::GetParseError_En(result.Code()), result.Offset());
		exit(-1);
	}

	std::cout<<"Loading textures..."<<std::endl;

	// Fill the map
	for (rapidjson::Value::ConstMemberIterator iter = level_json_document.MemberBegin(); iter != level_json_document.MemberEnd(); ++iter){
		loadGfx(iter->name.GetString(), iter->value.GetString());
		std::cout << "Loaded " << iter->name.GetString() << " at " << iter->value.GetString() << std::endl;
	}
	return true;
}


bool Gfx::loadGfx(const string& name, const string& filepath)
{
    sf::Texture *texture = new sf::Texture();
    if(texture->loadFromFile(filepath))
    {
        textures[name] = texture;
        return textures[name];
    } else {
        delete texture;
        return false;
    }
}


sf::Texture& Gfx::getGfx(const string& name)
{
	return *textures[name];
    //if(textures.find(name) != textures.end()){
    //    return *textures[name];
    //}
}



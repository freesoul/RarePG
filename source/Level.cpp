#include <SFML/Graphics.hpp>
#include "include/Game.h"
#include "include/Level.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
// #include <rapidjson/writer.h>
// #include <rapidjson/stringbuffer.h>

#include "Pulpo.h"
// #include "Rocket.h"
#include "Palomitas.h"
#include "Fruit.h"
#include "Yoda.h"
#include "MonoSmall.h"
// #include "Mono.h"
// #include "star.h"
#include "Pollito.h"
//
#include "Character.h"

#include "Obstacle.h"



Level::Level(){
		// Prepare buffer for applying shaders
		renderer_shader.create(
			VIEW_WIDTH,
			VIEW_HEIGHT
		);

		// Sun rays shader
		if (!shaderSunRays.loadFromFile("shaders/sunrays", sf::Shader::Fragment)) {
			// handle this
		}

		shaderSunRays.setParameter("texture", sf::Shader::CurrentTexture);
		// shaderSunRays.setParameter("resolution", sf::Vector2f(WORLD_WIDTH,WORLD_HEIGHT));

		// shaderSpawn->setParameter("exposure", 0.25f);

}


void Level::Load(int level)
{
	///////////////////////////////////////////////
	// Load JSON with level waves data
	///////////////////////////////////////////////

	// Read json as string
	std::stringstream file_path;
	file_path << "data/level/" << level << ".json";
	std::ifstream t(file_path.str());
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

	///////////////////////////////////////////////
	// Clear and fill up waves
	///////////////////////////////////////////////

	eventQueue.clear();
	waves.clear();

	levelName = level_json_document["name"].GetString();
	rapidjson::Value& json_waves = level_json_document["waves"];

	std::string monster_class;
	int repeat;
	int monster_number;
	std::string wave_type;
	Wave wave;

	for(rapidjson::SizeType i = 0; i < json_waves.Size(); i++){

		rapidjson::Value& json_wave = json_waves[i];
		wave_type = json_wave["type"].GetString();

		if(wave_type=="monster"){

			monster_class = json_wave["monster_class"].GetString();
			monster_number = json_wave["number"].GetInt();

			repeat = 1;
			if (json_wave.HasMember("repeat"))
				repeat = json_wave["repeat"].GetInt();

			wave.monster_class = monster_class;
			wave.number = monster_number;

			// std::cout << wave.monster_class << "\n";

			for(int i=0;i<repeat;i++)
				AddWave(wave);

		} else if(wave_type=="wait_seconds"){

			int seconds = json_wave["seconds"].GetInt();
			AddWait(seconds);

		} else if(wave_type=="wait_all_dead"){

			AddWaitForAllDead();

		} else {
			std::cout << std::string("Error parsing wave type: ") + wave_type;
		}

	}

	// Spawn character
	Game::s_game->character = new Character(Character::Guy);

	// Set level ambient
	SetBackground(Game::s_game->gfx.getGfx("Background1"));
	Game::s_game->audio.muFarm.play();

	// Start ambient effects
	nextAmbientEffect = MIN_AMBIENT_EVENT_DELAY;
	nextAmbientEffect += std::rand()%(MAX_AMBIENT_EVENT_DELAY-MIN_AMBIENT_EVENT_DELAY);

	// Start timer
	levelElapsed.restart();
	wait = 0;

}

bool Level::Update() {

	float elapsed_seconds = levelElapsed.getElapsedTime().asSeconds();

	// Ambient

	if (elapsed_seconds > nextAmbientEffect){
		nextAmbientEffect = elapsed_seconds;
		nextAmbientEffect += MIN_AMBIENT_EVENT_DELAY;
		nextAmbientEffect += std::rand()%(MAX_AMBIENT_EVENT_DELAY-MIN_AMBIENT_EVENT_DELAY);

		new Palomita();
	}

	// CHARACTER DEAD


	// ...


	///////////////////////////////////////////////
	// Level event handling
	///////////////////////////////////////////////

	if (!eventQueue.empty())
		switch (eventQueue.front().levelEvent)
		{
			///////////////////////////////////////////////
			// Wait time
			///////////////////////////////////////////////
			case LevelEvent::Wait:
			{
				if (wait == 0)
				{
					wait = elapsed_seconds + eventQueue.front().info;
				}
				else if (elapsed_seconds > wait)
				{
					wait = 0;
					eventQueue.pop_front();
				}

			} break;

			///////////////////////////////////////////////
			// Wait clean
			///////////////////////////////////////////////
			case LevelEvent::WaitForAllDead:
			{
	 			 if (Game::s_game->colliders.EnemiesDead())
					eventQueue.pop_front();
			} break;

			///////////////////////////////////////////////
			// Do wave
			///////////////////////////////////////////////
			case LevelEvent::Wave:
			{
				eventQueue.pop_front();
				DoWave();
			}	break;

			default:
				break;
		}
	else {
		// LEVEL FINISHED


		return true;
	}

	// Normal update
	return true;
}

void Level::DrawBackground() {
	Game::s_game->renderer.draw(background);
}


void Level::DoWave()
{

	if(waves.empty())
		return;	// should not happen

	Wave* wave = &waves.front();

	for(int i=0; i<wave->number; i++){

		if(wave->monster_class=="pollito"){
			new Pollito();
		} else if(wave->monster_class=="pulpo"){
			new Pulpo();
		} else if(wave->monster_class=="mono_peque"){
			new MonoSmall();
		} else if(wave->monster_class=="yoda"){
			new Yoda();
		} else if(wave->monster_class=="fruta"){
			new Fruit();
		}

	}

	waves.pop_front();

}


void Level::AddWait(float time)
{
	LevelEvent tmp;
	tmp.levelEvent = LevelEvent::Wait;
	tmp.info = time;
	eventQueue.push_back(tmp);
}

void Level::AddWave(Wave wave) {
	LevelEvent tmp;
	waves.push_back(wave);
	tmp.levelEvent = LevelEvent::Wave;
	eventQueue.push_back(tmp);
}

void Level::AddWaitForAllDead() {
	LevelEvent tmp;
	tmp.levelEvent = LevelEvent::WaitForAllDead;
	eventQueue.push_back(tmp);
}


void Level::AddObstacle(Obstacle* obstacle) {
	obstacles.push_back(obstacle);
}

void Level::RemoveObstacle(Obstacle* obstacle) {
	std::vector<Obstacle*>::iterator it;
	for (it = obstacles.begin(); it != obstacles.end(); it++)
		if ((*it) == obstacle)
		{
			obstacles.erase(it);
			return;
		}
}


bool Level::separate_from_obstacles(D3D* who, Obstacle::Entity who_to_move){
	bool separated=false;
	std::vector<Obstacle*>::iterator it;
	for(it=obstacles.begin(); it!=obstacles.end(); it++)
		// if((*it)->is_obstacle(who))
		if((*it)->separate_from(who, who_to_move))
			separated=true;
	return separated;
}


bool Level::is_obstacle(D3D* who){
	std::vector<Obstacle*>::iterator it;
	for(it=obstacles.begin(); it!=obstacles.end(); it++)
		if((*it)->is_obstacle(who))
			return true;
	return false;
}


void Level::applySceneShaders() {
/*
There are two ways:
- draw everything to a render-texture, then draw this render-texture with a fullscreen sprite and apply the shader
- use sf::Texture::update(Window&) to get the content of the framebuffer into a texture, then draw this texture with a fullscreen sprite and apply the shader
*/

shaderSunRays.setParameter("time", levelElapsed.getElapsedTime().asSeconds());
shaderSunRays.setParameter(
	"char_x",
	5 * Game::s_game->character->getPosition().x / VIEW_WIDTH
);

Game::s_game->renderer.display();

sf::RenderTexture* window_renderer = &Game::s_game->renderer;

// tmp->clear();
renderer_shader.draw(sf::Sprite(window_renderer->getTexture()), &shaderSunRays);
renderer_shader.display();

window_renderer->draw(sf::Sprite(renderer_shader.getTexture()));


}

#ifndef _ANIMATED_SPRITE_
#define _ANIMATED_SPRITE_

#include <SFML/Graphics.hpp>
#include "Drawable2D.h"
#include <unordered_map>
#include "Game.h"
// #include "Debug.h"

#ifdef DBG
#include <stdio.h>
#endif

struct AnimationItem {
	sf::IntRect rect;
	sf::Vector2f origin;
};

typedef std::vector<AnimationItem> AnimationSequence;

class AnimatedSprite : 	virtual public D2D {
protected:

	bool paused;

	float frameTime;
	float lastTime;
	bool bLoop;

	AnimationSequence::iterator itCurrentFrame;

	AnimationSequence* currentSequence;
	int currentSequenceId;

	const sf::Texture* m_texture;
	sf::Vertex m_vertices[4];

	void UpdateFrame();

	bool fixedOrigin;

public:

	// // D2D methods
	// void setOrigin(float x, float y) { setOrigin(x, y); };
	// sf::Vector2f GetOrigin() { return getOrigin(); };
	void setCustomOrigin() { fixedOrigin = false; };
	//
	// void setScale(sf::Vector2f scale) { setScale(scale); };
	// sf::Vector2f GetScale() { return getScale(); };
	//
	// void Move(float x, float y) { move(x, y); };
	//
	//
	// void SetRotation(float r) { setRotation(r); };
	// float GetRotation() { return getRotation(); };
	//
	// sf::Transform GetTransform()
	// {
	// 	return getTransform();
	// }

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	void setColor(const sf::Color& color);

	// SFML basic methods
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	AnimatedSprite(sf::Texture& tx, bool bshadow=false, float _frameTime = 0.2, float currentElapsed = 0) : frameTime(_frameTime), lastTime(currentElapsed)
	{
		m_texture = &tx;
		paused = true;
		Game::s_game->objects.AddAnimatedSprite(this);
		fixedOrigin = true;
	};
	~AnimatedSprite()
	{
#ifdef DBG

		std::printf("Destroyed Animated Sprite\n");
#endif
		Game::s_game->objects.RemoveAnimatedSprite(this);
	}
	void SetTexture(sf::Texture& tx) { m_texture = &tx; };

	// Animation methods
	void AddFrame(int sequenceId, sf::IntRect rect, float origin_x=0, float origin_y=0);
	void RunSequence(int id, bool loop=true);
	void UpdateSprite(float elapsed);

	short GetFrameNumber() { return currentSequence->size(); };
	int GetCurrentSequenceId() { return currentSequenceId; };

	bool AnimationPaused() { return paused; };

	std::unordered_map<int, AnimationSequence> animationSequences;


};

#endif

#include "include/AnimatedSprite.h"
#include "include/Game.h"
#include "include/Constants.h"//z


sf::FloatRect AnimatedSprite::GetLocalBounds()
{
	sf::IntRect rect = itCurrentFrame->rect;
	return sf::FloatRect(0, 0, std::abs(rect.width), std::abs(rect.height));
}

sf::FloatRect AnimatedSprite::GetGlobalBounds()
{
	return getTransform().transformRect(GetLocalBounds());
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_texture)
	{
		states.transform *= getTransform();
		states.texture = m_texture;
		target.draw(m_vertices, 4, sf::Quads, states);
	}
}

void AnimatedSprite::AddFrame(int sequenceId, sf::IntRect rect, float origin_x, float origin_y)
{
	AnimationItem item;
	item.rect = rect;
	item.origin = sf::Vector2f(origin_x, origin_y);

	AnimationSequence tmp;
	std::unordered_map<int, AnimationSequence>::iterator it;
	it = animationSequences.find(sequenceId);

	if(it==animationSequences.end())
	{
		tmp.push_back(item);
		animationSequences[sequenceId]=tmp;
	} else {
		it->second.push_back(item);
	}

}

void AnimatedSprite::RunSequence(int id, bool loop)
{
	paused=false;
	bLoop = loop;
	currentSequenceId=id;
	currentSequence=&animationSequences[id];
	itCurrentFrame=currentSequence->begin();
}


void AnimatedSprite::UpdateSprite(float time)
{
	if(!paused)
		if(time-lastTime>frameTime)
		{
			lastTime=time;

			// Change frame
			if(itCurrentFrame!=currentSequence->end())
				itCurrentFrame++;

			if(itCurrentFrame==currentSequence->end())
			{
				if(!bLoop)
				{
					paused = true;
					itCurrentFrame--;
				} else {
					itCurrentFrame=currentSequence->begin();
				}
			}

			UpdateFrame();

		}

}

void AnimatedSprite::UpdateFrame()
{
	sf::IntRect &rect = (*itCurrentFrame).rect;

	m_vertices[0].position = sf::Vector2f(0.f, 0.f);
	m_vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
	m_vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
	m_vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

	float left = static_cast<float>(rect.left) + 0.0001f;
	float right = left + static_cast<float>(rect.width);
	float top = static_cast<float>(rect.top);
	float bottom = top + static_cast<float>(rect.height);

	m_vertices[0].texCoords = sf::Vector2f(left, top);
	m_vertices[1].texCoords = sf::Vector2f(left, bottom);
	m_vertices[2].texCoords = sf::Vector2f(right, bottom);
	m_vertices[3].texCoords = sf::Vector2f(right, top);

	if (!fixedOrigin)
		SetOrigin(itCurrentFrame->origin.x, itCurrentFrame->origin.y);

}

void AnimatedSprite::SetColor(const sf::Color& color)
{
	m_vertices[0].color = color;
	m_vertices[1].color = color;
	m_vertices[2].color = color;
	m_vertices[3].color = color;

}

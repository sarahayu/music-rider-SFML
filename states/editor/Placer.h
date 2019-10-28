#pragma once
#include <SFML\Graphics.hpp>
#include "Tool.h"
#include "../../utils/MathUtils.h"

template <typename T>
class Placer : public Tool
{
public:
	Placer(std::unique_ptr<T> obstacle);

	virtual const void update(const sf::RenderWindow &window, std::vector<Entity::Ptr> &obstacles, const bool &isClicked);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::unique_ptr<T> m_obstacle;
};

template<typename T>
inline Placer<T>::Placer(std::unique_ptr<T> obstacle)
	: m_obstacle(std::move(obstacle))
{
}

template<typename T>
inline const void Placer<T>::update(const sf::RenderWindow &window, std::vector<Entity::Ptr>& obstacles, const bool &isClicked)
{
	m_obstacle->setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

	sf::Vector2f size = m_obstacle->getSize();
	if (m_obstacle->getGlobalBounds().top + size.y > 0.f)
		m_obstacle->setPosition({ m_obstacle->getPosition().x, 0.f - size.y / 2 });

	float closestDistance = 40.f*40.f;
	Entity *closest = nullptr;
	sf::Vector2f pos = m_obstacle->getPosition();
	for (const auto &obstacle : obstacles)
	{
		sf::Vector2f other = obstacle->getPosition();
		const float distance = mu::distanceSquared(pos, other);
		if (distance < closestDistance)
		{
			if (closest != nullptr && mu::getCollision(m_obstacle->getGlobalBounds(), closest->getGlobalBounds()).side != CollisionInfo::None) return;	// overlapping
			closestDistance = distance;
			closest = obstacle.get();
		}
	}

	if (closest != nullptr)
	{
		sf::Vector2f half = m_obstacle->getSize() / 2.f, otherHalf = closest->getSize() / 2.f;
		sf::Vector2f other = closest->getPosition();
		float xDist = other.x - pos.x, yDist = other.y - pos.y;

		if (std::abs(xDist) > std::abs(yDist))
		{
			if (xDist > 0.f) m_obstacle->setPosition(other - sf::Vector2f(half.x + otherHalf.x, 0.f));
			else m_obstacle->setPosition(other + sf::Vector2f(half.x + otherHalf.x, 0.f));
		}
		else
		{
			if (yDist > 0.f) m_obstacle->setPosition(other - sf::Vector2f(0.f, half.y + otherHalf.y));
			else m_obstacle->setPosition(other + sf::Vector2f(0.f, half.y + otherHalf.y));
		}
	}

	if (isClicked)
		obstacles.push_back(std::make_unique<T>(*m_obstacle.get()));
}

template<typename T>
inline void Placer<T>::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*m_obstacle, states);
}

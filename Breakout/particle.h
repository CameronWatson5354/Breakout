#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
public:
	Particle(sf::RenderWindow* _window);

	void update(const float dt);
	void render();

	void setPosition(const sf::Vector2f& position);

	bool getActive() const;

private:

	sf::RenderWindow* window;

	sf::CircleShape sprite;

	std::unique_ptr<sf::Clock> timer{ nullptr };
	float timeLimit{ 0.6f };
	float timeVariation{ 0.2f };

	float radius{ 10.0f };
	float radiusVariation{ 5.0f };


	sf::Vector2f direction;
	float ejectSpeed{ 100.0f };

	bool active{ true };
};


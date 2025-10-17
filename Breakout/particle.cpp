#include "particle.h"

#include "math.h"

#include <random>

Particle::Particle(sf::RenderWindow* _window)
{
	window = _window;


	sprite.setRadius(radius);
	sprite.setFillColor(sf::Color::White);

	timer = std::make_unique<sf::Clock>();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution dis{ -1.0f, 1.0f };

	std::uniform_real_distribution sizeDis{ 0.0f, radiusVariation };

	std::uniform_real_distribution speedDis{ 0.0f, ejectSpeed };

	std::uniform_real_distribution timeDis{ -timeVariation, timeVariation };

	float random{ dis(gen)};

	direction.x = random;

	random = dis(gen);

	direction.y = random;

	radius += sizeDis(gen);
	sprite.setRadius(radius);

	ejectSpeed = speedDis(gen);

	timeLimit += timeDis(gen);
}

void Particle::update(const float dt)
{
	if (timer.get()->getElapsedTime().asSeconds() >= timeLimit)
	{
		active = false;
	}

	float alpha{ Math::normalizeRange(0.0f, timeLimit, timer->getElapsedTime().asSeconds()) };

	float newSize{ Math::lerp(radius, 0.0f, alpha) };

	sprite.setRadius(newSize);

	sf::Vector2f position{ sprite.getPosition() };

	position.x += direction.x * ejectSpeed * dt;
	position.y += direction.y * ejectSpeed * dt;

	sprite.setPosition(position);
}

void Particle::render()
{
	if (window)
	{
		window->draw(sprite);
	}
}

void Particle::setPosition(const sf::Vector2f& position)
{
	sf::Vector2f newPosition{ position };
	newPosition.x -= sprite.getRadius();
	newPosition.y -= sprite.getRadius();

	sprite.setPosition(newPosition);
}

bool Particle::getActive() const
{
	return active;
}

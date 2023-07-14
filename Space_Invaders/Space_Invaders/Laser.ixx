module;
#include "SFML/Graphics.hpp"

export module Laser;
import Graphic_object;


export class Laser :
	public Graphic_object
{
	const int damage;
	const float speed;
	sf::Sprite laser_sprite;

	void update_movement(float dt_frame);

public:
	Laser(int _damage, float _speed, sf::Texture* laser_texture, int resX, int resY, const sf::Vector2f& _position, float _scale) :
		damage(_damage), speed(_speed), Graphic_object(laser_texture, resX, resY, _scale) {
		laser_sprite.setTexture(*texture);
		laser_sprite.setScale(scale * 0.067f, scale * 0.067f);
		laser_sprite.setPosition(_position.x - laser_sprite.getGlobalBounds().width / 2, _position.y - laser_sprite.getGlobalBounds().height);
	};

	void update(float dt);
	void render(sf::RenderTarget* target);
	sf::FloatRect get_bounds() const;
	sf::Vector2f get_position() const;

	int get_damage() const;
};


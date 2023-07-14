module;

#include "SFML/Graphics.hpp"

export module Fortification;
import Graphic_object;

export class Fortification :
	public Graphic_object
{
	sf::Sprite fortification_sprite;
	int hp = 3;
public:
	Fortification(sf::Texture* fortifiaction_texture, int resX, int resY, const sf::Vector2f& _position, float _scale) :
		Graphic_object(fortifiaction_texture, resX, resY, _scale) {
		fortification_sprite.setTexture(*texture);
		fortification_sprite.setScale(scale * 0.37f, scale * 0.37f);
		fortification_sprite.setPosition(_position.x - fortification_sprite.getGlobalBounds().width / 2, _position.y - fortification_sprite.getGlobalBounds().height);
	};

	void update(float dt);
	void render(sf::RenderTarget* target);
	sf::FloatRect get_bounds() const;
	sf::Vector2f get_position() const;

	void lose_hp();
	int get_hp();
};
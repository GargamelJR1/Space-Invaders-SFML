#include "SFML/Graphics.hpp"
import Fortification;

void Fortification::update(float dt) {
	// nothing to update
}

void Fortification::render(sf::RenderTarget* target) {
	target->draw(fortification_sprite);
}

sf::FloatRect Fortification::get_bounds() const {
	return fortification_sprite.getGlobalBounds();
}

sf::Vector2f Fortification::get_position() const {
	return fortification_sprite.getPosition();
}

void Fortification::lose_hp() {
	hp -= 1;
}

int Fortification::get_hp() {
	return hp;
}
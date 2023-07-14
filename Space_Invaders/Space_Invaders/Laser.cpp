#include "SFML/Graphics.hpp"
import Laser;

void Laser::update(float dt) {
	update_movement(dt);
}

void Laser::render(sf::RenderTarget* target) {
	target->draw(laser_sprite);
}

sf::FloatRect Laser::get_bounds() const {
	return laser_sprite.getGlobalBounds();
}

sf::Vector2f Laser::get_position() const {
	return laser_sprite.getPosition();
}

void Laser::update_movement(float dt_frame) {
	laser_sprite.move(0, -speed * dt_frame * scale);
}

int Laser::get_damage() const {
	return damage;
}
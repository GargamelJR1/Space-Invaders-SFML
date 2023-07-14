module;

#include "SFML/Graphics.hpp"

export module Enemy_laser_parameters;

export class Enemy_laser_parameters {
	int enemy_laser_damage;
	float enemy_laser_speed;
	sf::Texture* enemy_laser_texture;
public:
	Enemy_laser_parameters(int damage, float speed, sf::Texture* texture) :enemy_laser_damage(damage), enemy_laser_speed(speed), enemy_laser_texture(texture) {};
	Enemy_laser_parameters() : enemy_laser_damage(0), enemy_laser_speed(0.0f), enemy_laser_texture(nullptr) {};

	Enemy_laser_parameters& operator=(Enemy_laser_parameters& elp);

	void set_damage(int damage);
	void set_speed(float speed);
	void set_texture(sf::Texture* texture);

	int get_damage() const;
	float get_speed() const;
	sf::Texture* get_texture() const;
};

Enemy_laser_parameters& Enemy_laser_parameters::operator=(Enemy_laser_parameters& elp) {
	enemy_laser_damage = elp.enemy_laser_damage;
	enemy_laser_speed = elp.enemy_laser_speed;
	enemy_laser_texture = elp.enemy_laser_texture;
	return *this;
}

void Enemy_laser_parameters::set_damage(int damage) {
	enemy_laser_damage = damage;
}

void Enemy_laser_parameters::set_speed(float speed) {
	enemy_laser_speed = speed;
}

void Enemy_laser_parameters::set_texture(sf::Texture* texture) {
	enemy_laser_texture = texture;
}

int Enemy_laser_parameters::get_damage() const {
	return enemy_laser_damage;
}

float Enemy_laser_parameters::get_speed() const {
	return enemy_laser_speed;
}

sf::Texture* Enemy_laser_parameters::get_texture() const {
	return enemy_laser_texture;
}
#include "SFML/Graphics.hpp"
import Enemy;
import Enemy_laser_parameters;

void Enemy::render(sf::RenderTarget* target) {
	target->draw(enemy_sprite);
}

sf::FloatRect Enemy::get_bounds() const {
	return enemy_sprite.getGlobalBounds();
}

sf::Vector2f Enemy::get_position() const {
	return enemy_sprite.getPosition();
}

void Enemy::move(const sf::Vector2f& mov, float dt) {
	enemy_sprite.move(mov.x * dt, mov.y * dt);
}

int Enemy::get_points() const {
	return points;
}

void Enemy::set_enemy_laser_parameters(int damage, float speed, sf::Texture* texture) {
	enemy_laser_parameters.set_damage(damage);
	enemy_laser_parameters.set_speed(speed);
	enemy_laser_parameters.set_texture(texture);
}

void Enemy::set_enemy_laser_parameters(Enemy_laser_parameters parameters) {
	enemy_laser_parameters = parameters;
}


int Enemy::get_enemy_laser_damage() const {
	return enemy_laser_parameters.get_damage();
}

float Enemy::get_enemy_laser_speed() const {
	return enemy_laser_parameters.get_speed();
}

sf::Texture* Enemy::get_enemy_laser_texture() const {
	return enemy_laser_parameters.get_texture();
}

void Enemy::update(float dt) {
	if (vertical_move_timer >= vertical_move_timer_max) {
		enemy_sprite.move(0, move_down_pixels);
		vertical_move_timer = 0.0f;
	}
	else {
		vertical_move_timer += dt;

		if (horizontal_move_timer >= horizontal_move_timer_max) {
			if (next_move_center) {
				next_move_center = false;
				if (next_move_right)
					enemy_sprite.move(move_right_left_pixels, 0);
				else
					enemy_sprite.move(-move_right_left_pixels, 0);
			}
			else {
				if (next_move_right) {
					enemy_sprite.move(move_right_left_pixels, 0);
					next_move_right = false;
					next_move_center = true;
				}
				else {
					enemy_sprite.move(-move_right_left_pixels, 0);
					next_move_right = true;
					next_move_center = true;
				}
			}
			horizontal_move_timer = 0.0f;
		}
		else
			horizontal_move_timer += dt;
	}
}
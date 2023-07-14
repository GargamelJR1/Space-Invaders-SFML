#include "SFML/Graphics.hpp"
import Player;

void Player::update(float dt) {
	update_shooting_timer(dt);
	update_movement_and_shoot(dt);
	update_lasers(dt);
	update_player_hit_color(dt);
}

void Player::render(sf::RenderTarget* target) {
	target->draw(player_sprite);
	render_lasers(target);
}

sf::FloatRect Player::get_bounds() const {
	return player_sprite.getGlobalBounds();
}

sf::Vector2f Player::get_position() const {
	return player_sprite.getPosition();
}

int Player::get_hp() const {
	return hp;
}

void Player::add_score(int _score) {
	score += _score;
}

void Player::set_hit() {
	get_hit = true;
	player_sprite.setColor(sf::Color::Red);
}

int Player::get_score() const {
	return score;
}

void Player::lose_hp(int _hp) {
	hp -= _hp;
	if (hp < 0)
		hp = 0;
}

Player::~Player() {
	for (auto& laser : lasers) {
		delete laser;
	}
}

void Player::render_lasers(sf::RenderTarget* target) {
	for (auto& laser : lasers) {
		laser->render(target);
	}
}

void Player::update_lasers(float dt) {
	for (auto& laser : lasers) {
		laser->update(dt);
	}

	for (size_t i = 0; i < lasers.size(); i++) {
		if (lasers[i]->get_position().y + lasers[i]->get_bounds().height < 0) {
			delete lasers[i];
			lasers.erase(lasers.begin() + i);
		}
	}
}

void Player::update_shooting_timer(float dt) {
	if (player_shooting_timer > player_shooting_timer_max + dt)
		player_shooting_timer = player_shooting_timer_max + dt;
	else if (player_shooting_timer < player_shooting_timer_max + dt)
		player_shooting_timer += dt;
}

void Player::update_player_hit_color(float dt) {
	if (get_hit) {
		player_hit_timer += dt;
		if (player_hit_timer >= player_hit_timer_max) {
			get_hit = false;
			player_hit_timer = 0.0f;
			player_sprite.setColor(sf::Color::White);
		}
	}
}

void Player::move_left(float dt) {
	player_sprite.move(dt * scale * (-1), 0);

	if (player_sprite.getPosition().x < 0) {
		auto current_position = player_sprite.getPosition();
		player_sprite.setPosition(0, current_position.y);
	}
}

void Player::move_right(float dt) {
	player_sprite.move(dt * scale * 1, 0);

	if (player_sprite.getPosition().x + player_sprite.getGlobalBounds().width > window_resX) {
		auto current_position = player_sprite.getPosition();
		player_sprite.setPosition(window_resX - player_sprite.getGlobalBounds().width, current_position.y);
	}
}

void Player::update_movement_and_shoot(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		move_right(dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		move_left(dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		shoot(dt);
	}
}

void Player::shoot(float dt) {
	if (player_shooting_timer >= (player_shooting_timer_max)) {
		auto pos = player_sprite.getPosition();
		auto bounds = player_sprite.getGlobalBounds();
		lasers.push_back(new Laser(5, 0.5f, laser_texture, window_resX, window_resY, { pos.x + bounds.width / 2,pos.y }, scale));
		player_shooting_timer = 0.0f;
	}
}

std::vector<Laser*>& Player::get_player_lasers_vector() {
	return lasers;
}
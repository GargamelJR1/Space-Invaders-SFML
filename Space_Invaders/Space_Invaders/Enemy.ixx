module;

#include "SFML/Graphics.hpp"

export module Enemy;
import Graphic_object;
import Enemy_laser_parameters;

export class Enemy :
	public Graphic_object
{
	sf::Sprite enemy_sprite;
	float vertical_move_timer;
	const float vertical_move_timer_max;
	float horizontal_move_timer;
	const float horizontal_move_timer_max;
	bool next_move_right;
	bool next_move_center;
	const float move_down_pixels;
	const float move_right_left_pixels;

	const int points;

	Enemy_laser_parameters enemy_laser_parameters;

	void move(const sf::Vector2f& mov, float dt);

public:
	Enemy(int _points, sf::Texture* enemy_texture, int resX, int resY, const sf::Vector2f& enemy_position, const Enemy_laser_parameters& laser_parameters,
		float _scale) : Graphic_object(enemy_texture, resX, resY, _scale), points(_points), vertical_move_timer_max(5400.0f), horizontal_move_timer_max(1000.0f),
		vertical_move_timer(0.0f), horizontal_move_timer(0.0f), next_move_right(true), next_move_center(false),
		move_down_pixels(50.0f * _scale), move_right_left_pixels(30.0f * _scale), enemy_laser_parameters(laser_parameters) {
		enemy_sprite.setTexture(*texture);
		enemy_sprite.setOrigin(enemy_sprite.getGlobalBounds().width / 2, enemy_sprite.getGlobalBounds().height / 2);
		enemy_sprite.setScale(scale * 0.70f, -scale * 0.70f);
		enemy_sprite.setPosition(enemy_position);
	};

	void update(float dt);
	void render(sf::RenderTarget* target);
	sf::FloatRect get_bounds() const;
	sf::Vector2f get_position() const;

	int get_points() const;

	void set_enemy_laser_parameters(int damage, float speed, sf::Texture* texture);
	void set_enemy_laser_parameters(Enemy_laser_parameters parameters);
	int get_enemy_laser_damage() const;
	float get_enemy_laser_speed() const;
	sf::Texture* get_enemy_laser_texture() const;
};
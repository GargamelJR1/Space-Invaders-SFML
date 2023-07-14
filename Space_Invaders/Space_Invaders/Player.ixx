module;

#include "SFML/Graphics.hpp"

export module Player;
import Graphic_object;
import Laser;

export class Player :
	public Graphic_object
{
	int hp;
	const int hp_max;
	int score;
	const int speed;
	sf::Sprite player_sprite;
	sf::Texture* laser_texture;

	void move_left(float dt);
	void move_right(float dt);

	std::vector<Laser*> lasers;
	const float player_shooting_timer_max = 270.0f;
	float player_shooting_timer = 0.0f;

	bool get_hit = false;
	const float player_hit_timer_max = 50.0f;
	float player_hit_timer = 0.0f;

	void update_movement_and_shoot(float dt);
	void update_shooting_timer(float dt);
	void update_player_hit_color(float dt);
	void shoot(float dt);

	void render_lasers(sf::RenderTarget* target);
	void update_lasers(float dt);
public:
	Player(int _hpmax, int _speed, sf::Texture* player_texture, sf::Texture* player_laser_texture, int resX, int resY, float _scale) :hp_max(_hpmax), hp(_hpmax),
		score(0), speed(_speed), Graphic_object(player_texture, resX, resY, _scale), laser_texture(player_laser_texture) {
		player_sprite.setTexture(*texture);
		player_sprite.setScale(scale * 0.71f, scale * 0.71f);
		player_sprite.setPosition((resX / 2.0f) - player_sprite.getGlobalBounds().width / 2.0f, resY - player_sprite.getGlobalBounds().height - 35.0f * scale);
	};

	void update(float dt);
	void render(sf::RenderTarget* target);
	sf::FloatRect get_bounds() const;
	sf::Vector2f get_position() const;

	int get_hp() const;
	int get_score() const;
	void lose_hp(int _hp);
	void add_score(int _score);
	void set_hit();

	std::vector<Laser*>& get_player_lasers_vector();

	~Player();
};
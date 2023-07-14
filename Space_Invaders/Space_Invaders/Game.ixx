module;

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

export module Game;

import Graphic_object;
import Collider;
import Random_number;
import Resource_manager;
import Player;
import Enemy;
import Laser;
import Health_bar;
import Points_bar;
import Fortification;
import End_screen;
import Splash_screen;

import <vector>;
import <thread>;
import <algorithm>;
import <deque>;
import <ranges>;
import <execution>;
import <mutex>;

export	class Game
{
	const float scale;
	Random_number random_number;
	Resource_manager resources;
	sf::Clock clock;
	sf::RenderWindow window;
	sf::Event event;
	sf::Music* music;
	Player player;
	std::vector<Enemy*> enemies;
	std::vector<Laser*> enemy_lasers;
	std::vector <Fortification*> fortifications;
	std::deque<Graphic_object*> graphic_objects;
	Collider collider;
	Health_bar health_bar;
	Points_bar points_bar;
	const int nr_cols, nr_rows;
	bool defeat = false;
	bool victory = false;
	bool game_over = false;
	bool game_started = false;

	float enemies_shooting_timer;
	float enemies_shooting_timer_max = 200.0f;
	const int enemy_tier1_damage = 8, enemy_tier2_damage = 13, enemy_tier3_damage = 17;
	const int enemy_tier1_points = 10, enemy_tier2_points = 20, enemy_tier3_points = 30;
	const float enemy_tier1_laser_speed = -0.6f, enemy_tier2_laser_speed = -0.75f, enemy_tier3_laser_speed = -0.9f;

	void init();
	void init_enemies(std::mutex& mtx);
	void init_fortifications(std::mutex& mtx);

	void render();

	void update(float dt_frame);
	void update_game_state();
	void update_enemies_shooting(float dt);

	void erase_graphic_object_from_vector(const Graphic_object* object_to_erase);
	void fortification_collide(Fortification* fortification_to_erase, int index);
	void delete_enemy_laser(Laser* laser_to_erase, int index);

	void update_collisions();
	void update_player_shooting_enemies_collisions();
	void update_enemies_shooting_window_collision();
	void update_enemies_shooting_player_collision();
	void update_enemies_shooting_fortifications_collision();
	void update_player_shooting_fortifications_collision();
	void update_enemies_fortification_collision();
	void update_enemies_player_and_window_collision();

	void processEvents();

	void show_splash_screen();
	void show_victory_screen();
	void show_defeat_screen();

	void delete_enemies();
	void delete_enemy_lasers();
	void delete_fortifications();

	int count_existing_enemies();

public:
	Game(int _resX, int _resY, int player_hp, int player_speed, float _scale)
		: scale(_scale), resources(), window(sf::VideoMode(static_cast<unsigned int>(_resX* _scale), static_cast<unsigned int>(_resY* _scale)), "Space Invaders", sf::Style::Titlebar | sf::Style::Close),
		health_bar(player_hp, resources.get_font("main_font"), static_cast<int>(_resX* _scale), static_cast<int>(_resY* _scale), _scale),
		points_bar(1170, resources.get_font("main_font"), static_cast<int>(_resX* _scale), static_cast<int>(_resY* _scale), _scale),
		player(player_hp, player_speed, resources.get_texture("player_texture"), resources.get_texture("red_laser_texture"), static_cast<int>(_resX* _scale),
			static_cast<int>(_resY* _scale), _scale), nr_rows(7), nr_cols(9), enemies_shooting_timer(enemies_shooting_timer_max), music(resources.get_music("background_music")) {
		show_splash_screen();
		init();
	};

	void run();

	~Game();
};
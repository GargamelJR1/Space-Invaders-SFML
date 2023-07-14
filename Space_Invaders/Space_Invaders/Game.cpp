#include "SFML/Graphics.hpp"

import Game;

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
import Enemy_laser_parameters;

import <vector>;
import <thread>;
import <algorithm>;
import <deque>;
import <ranges>;
import <execution>;
import <mutex>;


void Game::init() {
	window.setFramerateLimit(500);
	window.setMouseCursorVisible(false);
	graphic_objects.push_back(&player);
	graphic_objects.push_back(&health_bar);
	graphic_objects.push_back(&points_bar);

	music->setLoop(true);
	music->setVolume(20.0f);
	music->play();

	std::mutex mtx;
	std::thread t1(&Game::init_enemies, this, std::ref(mtx));
	std::thread t2(&Game::init_fortifications, this, std::ref(mtx));

	t1.join();
	t2.join();
}

void Game::init_enemies(std::mutex& mtx) {
	float distance_between_enemies = 8.34f * scale;
	float enemy_width = 89.32f * scale;
	float enemy_offset = 7.5f * scale;
	sf::Vector2f enemy_pos = { distance_between_enemies,70.0f * scale };
	int enemy_points = 10;
	sf::Texture* enemy_texture(nullptr);
	Enemy_laser_parameters enemy_laser_parameters;

	for (int j = 0; j < nr_rows; j++) {
		if (j % 2 == 0)
			enemy_pos.x += enemy_offset;
		else
			enemy_pos.x -= enemy_offset;

		if (j < 2) {
			enemy_texture = resources.get_texture("enemy_tier3_texture");
			enemy_points = enemy_tier3_points;
			enemy_laser_parameters.set_damage(enemy_tier3_damage);
			enemy_laser_parameters.set_speed(enemy_tier3_laser_speed);
			enemy_laser_parameters.set_texture(resources.get_texture("purple_laser_texture"));
		}
		else if (j >= 2 && j < 4) {
			enemy_texture = resources.get_texture("enemy_tier2_texture");
			enemy_points = enemy_tier2_points;
			enemy_laser_parameters.set_damage(enemy_tier2_damage);
			enemy_laser_parameters.set_speed(enemy_tier2_laser_speed);
			enemy_laser_parameters.set_texture(resources.get_texture("green_laser_texture"));
		}
		else if (j >= 4) {
			enemy_texture = resources.get_texture("enemy_tier1_texture");
			enemy_points = enemy_tier1_points;
			enemy_laser_parameters.set_damage(enemy_tier1_damage);
			enemy_laser_parameters.set_speed(enemy_tier1_laser_speed);
			enemy_laser_parameters.set_texture(resources.get_texture("blue_laser_texture"));
		}

		for (int i = 0; i < nr_cols; i++) {
			enemy_pos.x += distance_between_enemies + enemy_width;
			enemies.push_back(new Enemy(enemy_points, enemy_texture, static_cast<int>(window.getSize().x), static_cast<int>(window.getSize().y), enemy_pos, enemy_laser_parameters, scale));
			int enemy_index = i + j * nr_cols;

			// add enemies to graphic_objects in a thread-safe manner
			std::lock_guard<std::mutex> lock(mtx);
			graphic_objects.push_front(enemies[enemy_index]);
		}
		enemy_pos.x = distance_between_enemies;
		enemy_pos.y += 82.0f * scale;
	}
}

void Game::init_fortifications(std::mutex& mtx) {
	for (int k = 0; k < 2; k++) {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				fortifications.push_back(new Fortification(resources.get_texture("fortification_texture"), static_cast<int>(window.getSize().x), static_cast<int>(window.getSize().y), { (50.0f + i * 50 + j * 400) * scale, (1020.0f - k * 50) * scale }, scale));
			}
		}
	}

	// add fortifications to graphic_objects in a thread-safe manner
	std::lock_guard<std::mutex> lock(mtx);
	graphic_objects.insert(graphic_objects.end(), fortifications.begin(), fortifications.end());
}

void Game::run() {
	while (window.isOpen()) {
		processEvents();
		if (window.hasFocus()) {


			if (!victory && !defeat) {
				float dt = static_cast<float>(clock.restart().asMilliseconds());
				update(dt);
			}
			else if (!game_over) {
				music->stop();
				if (victory) {
					show_victory_screen();
					game_over = true;
				}
				else if (defeat) {
					show_defeat_screen();
					game_over = true;
				}
			}
			render();
		}
	}
}

void Game::show_victory_screen() {
	const std::vector<std::string> victory_sub_text = { "Congratulations!","remaining health : " + std::to_string(player.get_hp()) };
	static End_screen end_screen("VICTORY", victory_sub_text,
		resources.get_font("main_font"), window.getSize().x, window.getSize().y, scale);
	graphic_objects.push_back(&end_screen);
}

void Game::show_defeat_screen() {
	const std::vector<std::string> defeat_sub_text = { "You have been defeated!","earned points: " + std::to_string(player.get_score()),
	"destroyed enemies: " + std::to_string(enemies.size() - count_existing_enemies()) + "/" + std::to_string(enemies.size()) };
	static End_screen end_screen("GAME OVER", defeat_sub_text,
		resources.get_font("main_font"), window.getSize().x, window.getSize().y, scale);
	graphic_objects.push_back(&end_screen);
}

void Game::show_splash_screen() {
	Splash_screen splash_screen1("SPACE INVADERS", "Press Enter to continue", { "Control:","Right/Left arrow - movement","SPACE - shooting","Escape - exit game" },
		{ "Credits: ","Game made by Gargamel JR","Enemy ships tier1 texture are from Space Ship Construction Kit made by Skorpio and shared under CC-BY-SA 3.0",
		"Enemy ships tier2 & tier3 are based on Skorpio textures", "Laser textures are based on textures made by CruzR under CC0",
		"Fortification texture is based on texture made by Wenrexa under CC0","Background music made by SubspaceAudio and shared under CC0",
		"Font used in game is SairaCondensed made by The Saira Project Authors","Font is shared under SIL Open Font License v. 1.1",
		"Game code is shared under GPLv3 license (resources licenses files are in their directiories)",
		"This game is made with use of SFML" }
	, resources.get_font("main_font"), window.getSize().x, window.getSize().y, scale);
	graphic_objects.push_back(&splash_screen1);

	while (window.isOpen() && !game_started) {
		processEvents();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			game_started = true;
		}
		render();
	}
	graphic_objects.erase(graphic_objects.begin());
}

void Game::render() {
	window.clear(sf::Color::Black);

	const auto& windowr = &window;
	std::ranges::for_each(graphic_objects, [windowr](Graphic_object* object) {object->render(windowr); });

	window.display();
}

void Game::update(float dt_frame) {
	update_game_state();
	health_bar.set_hp(player.get_hp());
	points_bar.set_points(player.get_score());
	update_enemies_shooting(dt_frame);
	update_collisions();

	std::for_each(std::execution::parallel_unsequenced_policy(), graphic_objects.begin(), graphic_objects.end(), [dt_frame](Graphic_object* object) {object->update(dt_frame); });
}

void Game::update_collisions() {
	update_player_shooting_enemies_collisions();
	update_enemies_shooting_window_collision();
	update_enemies_shooting_player_collision();
	update_enemies_shooting_fortifications_collision();
	update_player_shooting_fortifications_collision();
	update_enemies_fortification_collision();
	update_enemies_player_and_window_collision();
}

void Game::update_player_shooting_enemies_collisions() {
	std::vector<Laser*>& player_lasers = player.get_player_lasers_vector();
	for (int i = 0; i < enemies.size(); i++) {
		for (int j = 0; j < player_lasers.size(); j++) {
			if (enemies[i] != nullptr) {
				if (collider(*enemies[i], *player_lasers[j])) {
					delete player_lasers[j];
					player_lasers.erase(player_lasers.begin() + j);

					erase_graphic_object_from_vector(enemies[i]);
					player.add_score(enemies[i]->get_points());
					delete enemies[i];
					enemies.at(i) = nullptr;

					break;
				}
			}
		}
	}
}

void Game::update_enemies_shooting(float dt) {
	if (enemies_shooting_timer >= enemies_shooting_timer_max) {
		int shooting_enemy_col_index = random_number(0, (nr_cols - 1));
		shooting_enemy_col_index += (nr_rows - 1) * nr_cols;

		for (int i = (nr_rows - 1); i >= 0; i--) {
			if (enemies.at(shooting_enemy_col_index) != nullptr) {

				const sf::Vector2f enemy_laser_pos = { enemies.at(shooting_enemy_col_index)->get_position().x, enemies.at(shooting_enemy_col_index)->get_position().y + enemies.at(shooting_enemy_col_index)->get_bounds().height };
				enemy_lasers.push_back(new Laser(enemies.at(shooting_enemy_col_index)->get_enemy_laser_damage(),
					enemies.at(shooting_enemy_col_index)->get_enemy_laser_speed(), enemies.at(shooting_enemy_col_index)->get_enemy_laser_texture(),
					static_cast<int>(window.getSize().x), static_cast<int>(window.getSize().y), enemy_laser_pos, scale));
				graphic_objects.push_front(enemy_lasers.back());
				break;
			}
			shooting_enemy_col_index -= nr_cols;
		}
		enemies_shooting_timer = 0.0f;
	}
	else {
		enemies_shooting_timer += dt;
	}
}

void Game::erase_graphic_object_from_vector(const Graphic_object* object_to_erase) {
	for (int k = 0; k < graphic_objects.size(); k++) {
		if (graphic_objects[k] == object_to_erase) {
			graphic_objects.erase(graphic_objects.begin() + k);
			break;
		}
	}
}

void Game::fortification_collide(Fortification* fortification_to_erase, int index) {
	fortification_to_erase->lose_hp();
	if (fortification_to_erase->get_hp() <= 0) {
		//delete fortification
		erase_graphic_object_from_vector(fortification_to_erase);
		delete fortification_to_erase;
		fortifications.erase(fortifications.begin() + index);
	}
}

void Game::delete_enemy_laser(Laser* laser_to_erase, int index) {
	erase_graphic_object_from_vector(laser_to_erase);
	delete laser_to_erase;
	enemy_lasers.erase(enemy_lasers.begin() + index);
}

void Game::update_enemies_shooting_window_collision() {
	for (int i = 0; i < enemy_lasers.size(); i++) {
		auto& l = enemy_lasers[i];
		if ((l->get_position().y + l->get_bounds().height) >= (window.getSize().y)) {
			delete_enemy_laser(l, i);
		}
	}
}

void Game::processEvents() {
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			window.close();
		}
		else if (event.type == sf::Event::LostFocus) {
			if (game_started && !game_over)
				music->pause();
			while (true) {
				if (window.waitEvent(event) && event.type == sf::Event::GainedFocus)
					break;
			}
			if (game_started && !game_over)
				music->play();
		}
	}
}

void Game::update_enemies_shooting_player_collision() {
	for (int j = 0; j < enemy_lasers.size(); j++) {
		if (collider(player, *enemy_lasers[j])) {
			player.set_hit();
			player.lose_hp(enemy_lasers[j]->get_damage());

			//delete enemy_lasers
			delete_enemy_laser(enemy_lasers[j], j);
			enemies_shooting_timer_max -= 0.5f;
			break;
		}

	}
}

void Game::update_enemies_shooting_fortifications_collision() {
	for (int i = 0; i < fortifications.size(); i++) {
		for (int j = 0; j < enemy_lasers.size(); j++) {
			if (collider(*fortifications[i], *enemy_lasers[j])) {

				//delete enemy_lasers
				delete_enemy_laser(enemy_lasers[j], j);

				fortification_collide(fortifications[i], i);
				break;
			}
		}
	}
}

void Game::update_player_shooting_fortifications_collision() {
	std::vector<Laser*>& player_lasers = player.get_player_lasers_vector();
	for (int i = 0; i < fortifications.size(); i++) {
		for (int j = 0; j < player_lasers.size(); j++) {
			if (collider(*fortifications[i], *player_lasers[j])) {
				delete player_lasers[j];
				player_lasers.erase(player_lasers.begin() + j);

				fortification_collide(fortifications[i], i);
				break;
			}
		}
	}
}

void Game::update_enemies_fortification_collision() {
	for (int i = 0; i < enemies.size(); i++) {
		for (int j = 0; j < fortifications.size(); j++) {
			if (enemies[i] != nullptr) {
				if (collider(*enemies[i], *fortifications[j])) {

					//delete fortification
					erase_graphic_object_from_vector(fortifications[j]);
					delete fortifications[j];
					fortifications.erase(fortifications.begin() + j);

					//delete enemy
					erase_graphic_object_from_vector(enemies[i]);
					delete enemies[i];
					enemies.at(i) = nullptr;

					break;
				}
			}
		}
	}
}

void Game::update_enemies_player_and_window_collision() {
	auto existing_enemies = enemies | std::views::filter([](Enemy* enemy) { return enemy != nullptr; });

	for (const auto& enemy : existing_enemies) {
		if ((enemy->get_position().y + enemy->get_bounds().height) > player.get_position().y + 5.0f * scale) {
			player.lose_hp(100);
		}
	}
}

void Game::update_game_state() {
	if (player.get_score() >= 1170) {
		victory = true;
	}
	else if (player.get_hp() <= 0) {
		defeat = true;
	}
}

void Game::delete_enemies() {
	for (auto& enemy : enemies)
		delete enemy;
}

void Game::delete_enemy_lasers() {
	for (auto& laser : enemy_lasers)
		delete laser;
}

void Game::delete_fortifications() {
	for (auto& fortification : fortifications)
		delete fortification;
}

int Game::count_existing_enemies() {
	return static_cast<int>(std::ranges::count_if(enemies, [](const Enemy* en) {return en != nullptr; }));
}

Game::~Game() {
	std::vector<std::thread> threads;

	threads.push_back(std::thread(&Game::delete_enemies, this));
	threads.push_back(std::thread(&Game::delete_enemy_lasers, this));
	threads.push_back(std::thread(&Game::delete_fortifications, this));

	for (auto& thread : threads)
		thread.join();
}

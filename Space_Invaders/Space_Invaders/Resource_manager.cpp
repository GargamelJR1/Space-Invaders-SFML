#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

import Resource_manager;

void Resource_manager::load_resources() {
	load_textures();
	load_music();
	load_fonts();
}

void Resource_manager::load_textures() {
	if (!(
		add_texture("enemy_tier1_texture", "enemy_tier1_texture.png") &&
		add_texture("enemy_tier2_texture", "enemy_tier2_texture.png") &&
		add_texture("enemy_tier3_texture", "enemy_tier3_texture.png") &&
		add_texture("player_texture", "player_texture.png") &&
		add_texture("blue_laser_texture", "blue_laser_texture.png") &&
		add_texture("red_laser_texture", "red_laser_texture.png") &&
		add_texture("green_laser_texture", "green_laser_texture.png") &&
		add_texture("purple_laser_texture", "purple_laser_texture.png") &&
		add_texture("fortification_texture", "fortification_texture.png")
		))
		throw std::runtime_error("Failed to load textures");
}

void Resource_manager::load_music() {
	if (!(
		add_music("background_music", "background_music.wav")
		))
		throw std::runtime_error("Failed to load music");
}

void Resource_manager::load_fonts() {
	if (!(
		add_font("main_font", "main_font.ttf")
		))
		throw std::runtime_error("Failed to load fonts");
}

sf::Texture* Resource_manager::get_texture(const std::string& texture_name) {
	if (textures.find(texture_name) != textures.end()) {
		return textures.at(texture_name);
	}
	else
		return nullptr;
}

sf::Music* Resource_manager::get_music(const std::string& music_name) {
	if (music.find(music_name) != music.end()) {
		return music.at(music_name);
	}
	else
		return nullptr;
}

sf::Font* Resource_manager::get_font(const std::string& font_name) {
	if (fonts.find(font_name) != fonts.end()) {
		return fonts.at(font_name);
	}
	else
		return nullptr;
}

bool Resource_manager::add_texture(const std::string& texture_name, const std::string& filename) {
	std::filesystem::path texture_path(resources_path / "textures" / filename);
	if (std::filesystem::exists(texture_path)) {
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile(texture_path.string())) {
			return 0;
		}
		else {
			textures.emplace(texture_name, texture);
			return 1;
		}
	}
	else
		return 0;
}

bool Resource_manager::add_music(const std::string& music_name, const std::string& filename) {
	std::filesystem::path music_path(resources_path / "music" / filename);
	if (std::filesystem::exists(music_path)) {
		sf::Music* _music = new sf::Music();
		if (!_music->openFromFile(music_path.string())) {
			return 0;
		}
		else {
			music.emplace(music_name, _music);
			return 1;
		}
	}
	else
		return 0;
}

bool Resource_manager::add_font(const std::string& font_name, const std::string& filename) {
	std::filesystem::path font_path(resources_path / "fonts" / filename);
	if (std::filesystem::exists(font_path)) {
		sf::Font* font = new sf::Font();
		if (!font->loadFromFile(font_path.string())) {
			return 0;
		}
		else {
			fonts.emplace(font_name, font);
			return 1;
		}
	}
	else
		return 0;
}

Resource_manager::~Resource_manager() {
	for (auto it = textures.begin(); it != textures.end(); it++) {
		delete it->second;
	}
	for (auto it = music.begin(); it != music.end(); it++) {
		delete it->second;
	}
	for (auto it = fonts.begin(); it != fonts.end(); it++) {
		delete it->second;
	}
}
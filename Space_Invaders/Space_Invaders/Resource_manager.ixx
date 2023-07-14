module;
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

export module Resource_manager;
import <map>;
import <string>;
import <filesystem>;

export class Resource_manager
{
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::Music*> music;
	std::map<std::string, sf::Font*> fonts;

	const std::filesystem::path resources_path = "./resources";
public:
	Resource_manager() {
		load_resources();
	}

	void load_resources();
	void load_textures();
	void load_music();
	void load_fonts();

	sf::Texture* get_texture(const std::string& texture_name);
	sf::Music* get_music(const std::string& music_name);
	sf::Font* get_font(const std::string& font_name);

	bool add_texture(const std::string& texture_name, const std::string& extension);
	bool add_music(const std::string& music_name, const std::string& extension);
	bool add_font(const std::string& font_name, const std::string& extension);

	~Resource_manager();
};
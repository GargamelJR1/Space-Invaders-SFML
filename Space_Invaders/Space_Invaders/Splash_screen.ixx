module;

#include "SFML/Graphics.hpp"

export module Splash_screen;
import Graphic_object;
import <string>;
import <vector>;

export class Splash_screen :
	public Graphic_object
{
	sf::RectangleShape background;
	sf::Text title;
	sf::Text sub_text;
	std::vector<sf::Text> bottom_texts;
	std::vector<sf::Text> credits;
public:
	Splash_screen(const std::string& _title, const std::string& _subtext, const std::vector<std::string>& _bottom_texts, const  std::vector<std::string>& _credits,
		sf::Font* _font, int _resX, int _resY, float _scale) :
		Graphic_object(nullptr, _resX, _resY, _scale) {
		background.setSize(sf::Vector2f(static_cast<float>(window_resX), static_cast<float>(window_resY)));
		background.setOrigin(background.getGlobalBounds().width / 2.0f, background.getGlobalBounds().height / 2.0f);
		background.setFillColor(sf::Color::Black);
		background.setPosition(window_resX / 2.0f, window_resY / 2.0f);

		title.setString(_title);
		title.setFont(*_font);
		title.setCharacterSize(static_cast<unsigned int>(165 * scale));
		title.setFillColor(sf::Color::Black);
		title.setOutlineColor(sf::Color::White);
		title.setOutlineThickness(5.0f);
		title.setOrigin(title.getGlobalBounds().width / 2.0f, title.getGlobalBounds().height / 2.0f);
		title.setPosition(window_resX / 2.0f, window_resY / 2.0f - title.getGlobalBounds().height * 2.2f);

		sub_text.setString(_subtext);
		sub_text.setFont(*_font);
		sub_text.setCharacterSize(static_cast<unsigned int>(80 * scale));
		sub_text.setFillColor(sf::Color::White);
		sub_text.setOutlineColor(sf::Color::Black);
		sub_text.setOutlineThickness(3.0f);
		sub_text.setOrigin(sub_text.getGlobalBounds().width / 2.0f, sub_text.getGlobalBounds().height / 2.0f);
		sub_text.setPosition(window_resX / 2.0f, window_resY / 2.0f - sub_text.getGlobalBounds().height * 1.5f);

		const unsigned int bottom_texts_fontsize = 50;
		for (int i = 0; i < _bottom_texts.size(); i++) {
			sf::Text temp;
			temp.setString(_bottom_texts[_bottom_texts.size() - 1 - i]);
			temp.setFont(*_font);
			temp.setCharacterSize(static_cast<unsigned int>(bottom_texts_fontsize * scale));
			temp.setFillColor(sf::Color::White);
			temp.setOutlineColor(sf::Color::Black);
			temp.setOutlineThickness(3.0f);
			temp.setOrigin(temp.getGlobalBounds().width / 2.0f, 0.0f);
			temp.setPosition(window_resX / 2.0f, window_resY - static_cast<float>(bottom_texts_fontsize) * scale * (1.5f + i) - 330.0f * scale);
			bottom_texts.push_back(temp);
		}

		const unsigned int credits_fontsize = 20;
		for (int i = 0; i < _credits.size(); i++) {
			sf::Text temp;
			temp.setString(_credits[_credits.size() - 1 - i]);
			temp.setFont(*_font);
			temp.setCharacterSize(static_cast<unsigned int>(credits_fontsize * scale));
			temp.setFillColor(sf::Color::White);
			temp.setOutlineColor(sf::Color::Black);
			temp.setOutlineThickness(3.0f);
			temp.setOrigin(temp.getGlobalBounds().width / 2.0f, 0.0f);
			temp.setPosition(window_resX / 2.0f, window_resY - static_cast<float>(credits_fontsize) * scale * (1.5f + i) - 10.0f * scale);
			credits.push_back(temp);
		}
	}

	void update(float dt);
	void render(sf::RenderTarget* target);
	sf::FloatRect get_bounds() const;
	sf::Vector2f get_position() const;
};
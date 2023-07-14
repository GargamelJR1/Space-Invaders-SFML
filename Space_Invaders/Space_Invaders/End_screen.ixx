module;

#include "SFML/Graphics.hpp"

export module End_screen;
import Graphic_object;

export class End_screen :
	public Graphic_object
{
	sf::RectangleShape overlay;
	sf::Text main_text;
	std::vector<sf::Text> sub_texts;

public:
	End_screen(const std::string& _maintext, const std::vector<std::string>& _subtexts, sf::Font* _font, int _resX, int _resY, float _scale) :
		Graphic_object(nullptr, _resX, _resY, _scale) {
		overlay.setSize(sf::Vector2f(static_cast<float>(window_resX), static_cast<float>(window_resY - 50.0f * scale)));
		overlay.setOrigin(overlay.getGlobalBounds().width / 2.0f, overlay.getGlobalBounds().height / 2.0f);
		overlay.setFillColor(sf::Color(80, 80, 80, 200));
		overlay.setPosition(window_resX / 2.0f, window_resY / 2.0f);

		main_text.setFont(*_font);
		main_text.setString(_maintext);
		main_text.setCharacterSize(static_cast<unsigned int>(210 * scale));
		main_text.setFillColor(sf::Color::White);
		main_text.setOutlineColor(sf::Color::Black);
		main_text.setOutlineThickness(6.5f);
		main_text.setOrigin(main_text.getGlobalBounds().width / 2.0f, main_text.getGlobalBounds().height / 2.0f);
		main_text.setPosition(window_resX / 2.0f, window_resY / 2.0f - main_text.getGlobalBounds().height * 1.25f);

		for (int i = 0; i < _subtexts.size(); i++) {
			sf::Text sub_text;
			sub_text.setFont(*_font);
			sub_text.setString(_subtexts.at(i));
			sub_text.setCharacterSize(static_cast<unsigned int>(90 * scale));
			sub_text.setFillColor(sf::Color::White);
			sub_text.setOutlineColor(sf::Color::Black);
			sub_text.setOutlineThickness(3.0f);
			sub_text.setOrigin(sub_text.getGlobalBounds().width / 2.0f, sub_text.getGlobalBounds().height / 2.0f);
			sub_text.setPosition(window_resX / 2.0f, window_resY / 2.0f + i * 95.0f * scale);
			sub_texts.push_back(sub_text);
		}
	};

	void update(float dt);
	void render(sf::RenderTarget* target);
	sf::FloatRect get_bounds() const;
	sf::Vector2f get_position() const;
};
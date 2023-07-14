module;

#include "SFML/Graphics.hpp"

export module Bar;
import Graphic_object;

export class Bar :
	public Graphic_object
{
protected:
	int value;
	const int max_value;
	sf::RectangleShape bar;
	sf::RectangleShape bar_background;
	sf::Text bar_text;
	sf::Font* font;
	const float bar_height;
public:
	Bar(int _value_max, sf::Font* _font, int resX, int resY, const sf::Vector2f& _position, const sf::Color& background_color, const sf::Color& color, float _scale) :
		max_value(_value_max), font(_font), Graphic_object(nullptr, resX, resY, _scale), value(0), bar_height(25.0f * _scale) {
		bar.setFillColor(color);
		bar.setPosition(_position);
		bar.setSize({ static_cast<float>(window_resX),bar_height });
		bar_background.setFillColor(background_color);
		bar_background.setSize({ static_cast<float>(window_resX),bar_height });
		bar_background.setPosition(_position);
		bar_text.setFont(*font);
		bar_text.setCharacterSize(static_cast<unsigned int>(bar_height - (1.0f * _scale)));
		bar_text.setFillColor(sf::Color::White);
		bar_text.setOutlineColor(sf::Color::Black);
		bar_text.setOutlineThickness(1.0f);
	};

	virtual void update(float dt_frame) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
	virtual sf::FloatRect get_bounds() const = 0;
	virtual sf::Vector2f get_position() const = 0;

	virtual ~Bar() = default;
};
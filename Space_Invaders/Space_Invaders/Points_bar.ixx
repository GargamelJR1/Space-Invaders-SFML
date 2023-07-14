module;

#include "SFML/Graphics.hpp"

export module Points_bar;
import Bar;

export class Points_bar :
	public Bar
{
public:
	Points_bar(int _pointsmax, sf::Font* _font, int resX, int resY, float _scale) :
		Bar(_pointsmax, _font, resX, resY, { 0,1200.0f * _scale }, sf::Color(32, 32, 32, 255), sf::Color(196, 164, 0, 255), _scale) {
		bar_text.setString("Points: " + std::to_string(value));
		bar_text.setPosition(static_cast<float>(window_resX / 2.0f - bar_text.getGlobalBounds().width / 2), -1.8f * scale + static_cast<float>(resY) - bar_height);
	};

	virtual void update(float dt_frame);
	virtual void render(sf::RenderTarget* target);
	virtual sf::FloatRect get_bounds() const;
	virtual sf::Vector2f get_position() const;

	void set_points(int current_points);
};
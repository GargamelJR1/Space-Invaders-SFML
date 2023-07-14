module;

#include "SFML/Graphics.hpp"

export module Health_bar;
import Bar;

export class Health_bar :
	public Bar
{
public:
	Health_bar(int _hpmax, sf::Font* _font, int resX, int resY, float _scale) : Bar(_hpmax, _font, resX, resY, { 0.0f,0.0f },
		sf::Color(102, 0, 0, 255), sf::Color(0, 102, 0, 255), _scale) {
		bar_text.setString("Health: " + std::to_string(value) + "/" + std::to_string(max_value));
		bar_text.setPosition(static_cast<float>(window_resX / 2.0f - bar_text.getGlobalBounds().width / 2), -1.8f * scale);
	};

	virtual void update(float dt_frame);
	virtual void render(sf::RenderTarget* target);
	virtual sf::FloatRect get_bounds() const;
	virtual sf::Vector2f get_position() const;

	void set_hp(int current_hp);
};
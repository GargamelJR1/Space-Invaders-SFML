#include "SFML/Graphics.hpp"
import Health_bar;

void Health_bar::update(float dt_frame) {
	bar.setSize({ static_cast<float>((value / float(max_value)) * window_resX),bar_height });
	bar_text.setString("Health: " + std::to_string(value) + "/" + std::to_string(max_value));
}

void Health_bar::render(sf::RenderTarget* target) {
	target->draw(bar_background);
	target->draw(bar);
	target->draw(bar_text);
}

sf::FloatRect Health_bar::get_bounds() const {
	return bar_background.getGlobalBounds();
}

sf::Vector2f Health_bar::get_position() const {
	return bar_background.getPosition();
}

void Health_bar::set_hp(int current_hp) {
	value = current_hp;
}
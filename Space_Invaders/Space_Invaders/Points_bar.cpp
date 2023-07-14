#include "SFML/Graphics.hpp"
import Points_bar;

void Points_bar::update(float dt_frame) {
	bar.setSize({ static_cast<float>((value / float(max_value)) * window_resX),bar_height });
	bar_text.setString("Points: " + std::to_string(value));
}

void Points_bar::render(sf::RenderTarget* target) {
	target->draw(bar_background);
	target->draw(bar);
	target->draw(bar_text);
}

sf::FloatRect Points_bar::get_bounds() const {
	return bar_background.getGlobalBounds();
}

sf::Vector2f Points_bar::get_position() const {
	return bar_background.getPosition();
}

void Points_bar::set_points(int current_points) {
	value = current_points;
}
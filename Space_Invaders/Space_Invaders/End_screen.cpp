#include "SFML/Graphics.hpp"
import End_screen;

void End_screen::update(float dt) {
	// Nothing to update
}

void End_screen::render(sf::RenderTarget* target) {
	target->draw(overlay);
	target->draw(main_text);
	for (auto& sub_text : sub_texts)
		target->draw(sub_text);
}

sf::FloatRect End_screen::get_bounds() const {
	return overlay.getGlobalBounds();
}

sf::Vector2f End_screen::get_position() const {
	return overlay.getPosition();
}
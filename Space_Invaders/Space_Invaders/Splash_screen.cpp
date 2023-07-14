#include "SFML/Graphics.hpp"
import Splash_screen;

void Splash_screen::update(float dt) {
	// Nothing to update
}

void Splash_screen::render(sf::RenderTarget* target) {
	target->draw(background);
	target->draw(title);
	target->draw(sub_text);
	for (int i = 0; i < bottom_texts.size(); i++) {
		target->draw(bottom_texts[i]);
	}
	for (int i = 0; i < credits.size(); i++) {
		target->draw(credits[i]);
	}
}

sf::FloatRect Splash_screen::get_bounds() const {
	return background.getGlobalBounds();
}

sf::Vector2f Splash_screen::get_position() const {
	return background.getPosition();
}
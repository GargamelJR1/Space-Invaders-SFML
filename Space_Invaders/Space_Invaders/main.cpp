import Game;
import Logs;
#include "SFML/Graphics.hpp"

int WinMain() {

	Game* game(nullptr);

	float scale(1.0f);
	const float scale_h = (float(sf::VideoMode::getDesktopMode().height) / 1200) - 0.11f;
	const float scale_w = (float(sf::VideoMode::getDesktopMode().width) / 1000) - 0.11f;
	(scale_w > scale_h) ? scale = scale_h : scale = scale_w;

	try {
		game = new Game(1000, 1225, 100, 20, scale);
	}
	catch (const std::exception& e) {
		Logs::get_log().log(e.what(), "main Space_invaders");
		return -1;
	}

	game->run();

	delete game;
	return 0;
}
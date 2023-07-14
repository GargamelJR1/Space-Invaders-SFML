module;
#include "SFML/Graphics.hpp"

export module Graphic_object;
// Base class for all graphic objects
export class Graphic_object
{
protected:
	sf::Texture* texture;
	const int window_resX, window_resY;
	const float scale;
public:
	Graphic_object(sf::Texture* texture_ptr, int resX, int resY, float _scale) : texture(texture_ptr), window_resX(resX), window_resY(resY), scale(_scale) {};

	virtual void update(float dt_frame) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
	virtual sf::FloatRect get_bounds() const = 0;
	virtual sf::Vector2f get_position() const = 0;

	virtual ~Graphic_object() = default;
};
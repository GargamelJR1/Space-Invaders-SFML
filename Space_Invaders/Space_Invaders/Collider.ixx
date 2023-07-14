module;

#include "SFML/Graphics.hpp"

export module Collider;
import Graphic_object;

export class Collider
{
public:
	bool operator()(const Graphic_object& o1, const Graphic_object& o2) {
		return (o1.get_bounds().intersects(o2.get_bounds()));
	}
};
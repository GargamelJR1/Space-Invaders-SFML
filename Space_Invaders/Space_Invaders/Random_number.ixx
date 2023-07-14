export module Random_number;
import <random>;
import <chrono>;

export class Random_number
{
	static std::mt19937 gen;
public:
	int get_random_number(int min, int max) const;
	int operator()(int min, int max);
};

std::mt19937 Random_number::gen(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));

int Random_number::get_random_number(int min, int max) const {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

int Random_number::operator()(int min, int max) {
	return get_random_number(min, max);
}
#include <SFML/Graphics.hpp>

int main() {

	const sf::VideoMode windowVideoMode{1600, 800};
	sf::RenderWindow window{windowVideoMode, "Gulg Graphics"};

	while (window.isOpen()) { window.close(); }

	return 0;
}
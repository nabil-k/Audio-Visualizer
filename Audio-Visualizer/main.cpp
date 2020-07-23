#include "main.h"
#include "Audio.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Audio-Visualizer");
	Audio audio = Audio();
	audio.getSampleOverFrequency();
	std::vector<sf::RectangleShape> freqRangeRects = audio.getFreqRangeRects();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		

		window.clear(sf::Color::Black);

		for (int i = 0; i < freqRangeRects.size(); i++) {
			window.draw(freqRangeRects[i]);
			std::cout << freqRangeRects[i].getPosition().x << std::endl;
		}

		window.display();
	}

	return 0;
}
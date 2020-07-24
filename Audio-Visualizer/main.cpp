#include "main.h"
#include "Audio.h"
#include "Visualizer.h"


int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Audio-Visualizer");
	window.setFramerateLimit(60);

	Audio audio = Audio();
	audio.getSampleOverFrequency();

	Visualizer visualizer = Visualizer(audio.getfrequencyVisualizationVector());
	audio.playSong();
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		

		window.clear(sf::Color::Black);

		visualizer.update();

		std::vector<sf::RectangleShape> freqRangeRects = visualizer.getFreqRangeRects();

		for (int i = 0; i < freqRangeRects.size(); i++) {
			window.draw(freqRangeRects[i]);
		}

		window.display();
	}

	return 0;
}
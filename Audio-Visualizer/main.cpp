#include "main.h"
#include "Audio.h"
#include "Visualizer.h"
#include <functional>


int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Audio-Visualizer");
	window.setFramerateLimit(60);

	Audio audio = Audio();
	std::thread frequencyAnalyzationThread(&Audio::getSampleOverFrequency,&audio);
	Visualizer visualizer = Visualizer();
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear(sf::Color::Transparent);

		if (audio.getfrequencyVisualizationVector().size() > 120) {

			visualizer.update(audio.getfrequencyVisualizationVector());

			std::vector<sf::RectangleShape> freqRangeRects = visualizer.getFreqRangeRects();

			for (int i = 0; i < freqRangeRects.size(); i++) {
				window.draw(freqRangeRects[i]);
			}

			if (!audio.songPlayed()) {
				audio.playSong();
			}

		}


		window.display();
	}

	return 0;
}
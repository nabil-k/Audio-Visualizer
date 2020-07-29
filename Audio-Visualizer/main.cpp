#include "main.h"
#include "Audio.h"
#include "Visualizer.h"
#include <functional>


int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Audio-Visualizer", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	Audio audio = Audio();
	std::thread frequencyAnalyzationThread(&Audio::getSampleOverFrequency, &audio);
	Visualizer visualizer = Visualizer();
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear(sf::Color::Black);

		if (audio.getfrequencyVisualizationVector().size() > 120) {
			
			visualizer.update(audio.getfrequencyVisualizationVector(), audio.getSongPlayingOffset());

			std::vector<sf::RectangleShape> freqRangeRects = visualizer.getFreqRangeRects();

			window.draw(visualizer.getAmplitudeCircle());
			
			for (int i = 0; i < freqRangeRects.size(); i++) {
				window.draw(freqRangeRects[i]);
			}
			
			

			if (!audio.songPlayed()) {
				audio.playSong();
			}

		}
		else {
			if (audio.getfrequencyVisualizationVector().size() > 1) {
				visualizer.setLeftSamples(audio.getLeftSamples());
			}
		}


		window.display();
	}

	return 0;
}
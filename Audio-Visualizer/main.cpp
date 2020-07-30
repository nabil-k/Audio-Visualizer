#include "main.h"
#include "Audio.h"
#include "Visualizer.h"

int main() {

	srand(time(NULL)); // creates a new seed for rand()

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Audio-Visualizer", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	Audio audio = Audio();
	std::thread frequencyAnalyzationThread(&Audio::getSampleOverFrequency, &audio);
	Visualizer visualizer = Visualizer();
	
	// Window Loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);

		if (audio.getfrequencyVisualizationVector().size() > 120) {
			
			visualizer.setAmplitudeVisualizationVector(audio.getAmplitudeVisualizationVector());
			visualizer.update(audio.getfrequencyVisualizationVector(), audio.getSongPlayingOffset());
			
			// Draws particles
			std::vector <sf::CircleShape> amplitudeParticles = visualizer.getAmplitudeParticles();
			for (int i = 0; i < amplitudeParticles.size(); i++) {
				window.draw(amplitudeParticles[i]);
			}

			// Draws background for freq rect
			window.draw(visualizer.getBackgroundRect());

			// Draws freq visualizer
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
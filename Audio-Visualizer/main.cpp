#include "main.h"
#include "Audio.h"
#include "Visualizer.h"
#include <functional>


int main() {
	
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Audio-Visualizer");
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


		window.clear(sf::Color::Red);

		if (audio.getfrequencyVisualizationVector().size() > 120) {
			
			visualizer.update(audio.getfrequencyVisualizationVector(), audio.getSongPlayingOffset());

			sf::VertexArray freqCircleVertices = visualizer.getFreqCircleVertices();
			//std::cout << freqCircleVertices[32].position.y << std::endl;

			window.draw(freqCircleVertices);
			

			if (!audio.songPlayed()) {
				audio.playSong();
			}


		}


		window.display();
	}

	return 0;
}
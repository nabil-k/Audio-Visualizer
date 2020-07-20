#include "main.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(200, 200), "Audio-Visualizer");
	sf::SoundBuffer buffer;
	std::string audioFilePath = "./audio/Rival x Cadmium - Seasons (feat. Harley Bird) [NCS Release].wav";
	
	if (!buffer.loadFromFile(audioFilePath)) {
		return -1;
	}
	
	//std::cout << buffer.getSampleRate() << std::endl
	const sf::Int16* samples = buffer.getSamples();
	unsigned int sampleRate = buffer.getSampleRate();
	for (int i = 0; i < sampleRate; i += 2) {
		std::cout << samples[i] << std::endl;
	}
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		window.display();
	}

	return 0;
}
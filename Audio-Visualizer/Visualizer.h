#pragma once
#include "main.h"

class Visualizer {
	std::vector<sf::RectangleShape> freqRangeRects;
	std::vector< std::vector <double> > frequencyVisualizationVector;
	sf::Clock clock;
	int frequencyFrame = 0;

	public:
		Visualizer(std::vector< std::vector <double> > frequencyVisualizationVector) {

			this->frequencyVisualizationVector = frequencyVisualizationVector;

			// Creates Rects for freq visualization
			for (int ranges = 0; ranges < 29; ranges++) {
				sf::RectangleShape freqRangeRect = sf::RectangleShape();

				freqRangeRect.setSize(sf::Vector2f(33, 0));
				freqRangeRect.setPosition(160 + (33 * ranges), 360);

				freqRangeRect.setFillColor(sf::Color::White);
				freqRangeRect.setOutlineColor(sf::Color::Black);
				freqRangeRect.setOutlineThickness(1.f);

				freqRangeRects.push_back(freqRangeRect);
			}
		}

		std::vector<sf::RectangleShape>& getFreqRangeRects() {
			return freqRangeRects;
		}

		void update() {
			if (clock.getElapsedTime().asSeconds() > 1.0) {

				for (int freq_i = 0; freq_i < frequencyVisualizationVector[frequencyFrame].size(); freq_i++) {
					int newRectHeight = (int)frequencyVisualizationVector[frequencyFrame][freq_i];
					freqRangeRects[freq_i].setSize(sf::Vector2f(33, -newRectHeight));
				}

				frequencyFrame++;
				clock.restart();
			}
		}
};
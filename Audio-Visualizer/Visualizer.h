#pragma once
#include "main.h"

class Visualizer {
	std::vector<sf::RectangleShape> freqRangeRects;
	sf::Clock clock;
	int frequencyFrame = 0;

	public:
		Visualizer() {

			// Creates Rects for freq visualization
			for (int ranges = 0; ranges < 64; ranges++) {
				sf::RectangleShape freqRangeRect = sf::RectangleShape();

				freqRangeRect.setSize(sf::Vector2f(15, 0));
				freqRangeRect.setPosition(32 + (16 * ranges), 460);
				freqRangeRect.setFillColor(sf::Color::White);
				freqRangeRect.setOutlineColor(sf::Color::Black);
				freqRangeRect.setOutlineThickness(1.f);

				freqRangeRects.push_back(freqRangeRect);
			}
		}

		std::vector<sf::RectangleShape>& getFreqRangeRects() {
			return freqRangeRects;
		}

		void update(std::vector< std::vector <double> >& frequencyVisualizationVector, double songPlayingOffset) {
			
			frequencyFrame = (int)(songPlayingOffset * 60);

			for (int rect_i = 0; rect_i < freqRangeRects.size(); rect_i++) {
				float rectHeight = freqRangeRects[rect_i].getSize().y;
				float newRectHeight = frequencyVisualizationVector[frequencyFrame][rect_i];

				// Makes the rect's height reach the magnitude of the rect's corresponding frequency
				if (abs(rectHeight) != newRectHeight) {
					float rectHeight_velocity = ((newRectHeight - abs(rectHeight))) * -1.f;
					float rectHeight_updated = freqRangeRects[rect_i].getSize().y + rectHeight_velocity;

					// Checks if rect height is going UP
					if (rectHeight_velocity < 0) {
						if (abs(rectHeight_updated) > newRectHeight) {

							rectHeight_updated = newRectHeight * -1.f;

						}
					}
					//Checks if rect height is going DOWN
					else if (rectHeight_velocity > 0) {
						if (abs(rectHeight_updated) < newRectHeight) {

							rectHeight_updated = newRectHeight * -1.f;

						}
					}	
					freqRangeRects[rect_i].setSize(sf::Vector2f(15, rectHeight_updated));
				}
						
			}
				
			frequencyFrame++;

		}

			
};
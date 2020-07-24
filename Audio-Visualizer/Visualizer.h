#pragma once
#include "main.h"

class Visualizer {
	std::vector<sf::RectangleShape> freqRangeRects;
	std::vector< std::vector <double> > frequencyVisualizationVector;
	std::vector<int> freqRangeRectsHeightDelta;
	sf::Clock clock;
	int frequencyFrame = 0;
	int animation_frame = 1;
	int framesToReachMagnitude = 3; // the lower the faster the change

	public:
		Visualizer(std::vector< std::vector <double> > frequencyVisualizationVector) {

			this->frequencyVisualizationVector = frequencyVisualizationVector;
			freqRangeRectsHeightDelta.resize(frequencyVisualizationVector[0].size());

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

			if (clock.getElapsedTime().asSeconds() > 0.5) {

				frequencyFrame++;
				clock.restart();
				animation_frame = 1;
			}
			else {
				for (int rect_i = 0; rect_i < freqRangeRects.size(); rect_i++) {
					float rectHeight = freqRangeRects[rect_i].getSize().y;
					float newRectHeight = frequencyVisualizationVector[frequencyFrame][rect_i];
					
					// Makes the rect's height reach the magnitude of the rect's corresponding frequency
					if (animation_frame < framesToReachMagnitude) {
						if (abs(rectHeight) != newRectHeight) {
							float rectHeight_velocity = ((newRectHeight - abs(rectHeight)) / framesToReachMagnitude) * -1.f;
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

							freqRangeRects[rect_i].setSize(sf::Vector2f(33, rectHeight_updated));

						}
					}
					// Makes rect's height decay after it has reached its magnitude
					else {
						if (rectHeight <= 0) {

							float rectDecayRate = 5.f;
							float decayedRectHeight = rectHeight + rectDecayRate;
							if (decayedRectHeight >= 0) {
								decayedRectHeight = 0;
							}
							freqRangeRects[rect_i].setSize(sf::Vector2f(33, decayedRectHeight));
						}
					}

				}
			}
			
			animation_frame++;
		}
};
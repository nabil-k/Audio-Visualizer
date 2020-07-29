#pragma once
#include "main.h"

class Visualizer {
	

	int frequencyFrame = 0;
	int amplitudeFrame = 0;

	std::vector<sf::RectangleShape> freqRangeRects;
	std::vector< std::complex <double> > leftSamples;

	sf::CircleShape amplitudeCircle;

	public:
		Visualizer() {
			
			// Creates Rects for freq visualization
			for (int ranges = 0; ranges < 64; ranges++) {
				sf::RectangleShape freqRangeRect = sf::RectangleShape();

				freqRangeRect.setSize(sf::Vector2f(4, 0));
				freqRangeRect.setPosition(40 + (5 * ranges), 300.f);
				
				freqRangeRect.setFillColor(sf::Color::Black);

				freqRangeRects.push_back(freqRangeRect);
			}

			amplitudeCircle.setRadius(200);
			amplitudeCircle.setPosition(0.f, 0.f);
			amplitudeCircle.setFillColor(sf::Color::White);
			amplitudeCircle.setPointCount(100);
			

		}

		std::vector<sf::RectangleShape>& getFreqRangeRects() {
			return freqRangeRects;
		}

		sf::CircleShape& getAmplitudeCircle() {
			return amplitudeCircle;
		}

		void setLeftSamples(std::vector< std::complex <double> > leftSamples) {
			this->leftSamples = leftSamples;
		}


		void update(std::vector< std::vector <double> >& frequencyVisualizationVector, double songPlayingOffset) {
			
			frequencyFrame = (int)(songPlayingOffset * 30);
			amplitudeFrame = (int)(songPlayingOffset * 1470);
			
			for (int rect_i = 0; rect_i < freqRangeRects.size(); rect_i++) {
				float rectHeight = freqRangeRects[rect_i].getSize().y;
				float newRectHeight = frequencyVisualizationVector[frequencyFrame][rect_i] * -1;
				freqRangeRects[rect_i].setSize(sf::Vector2f(3, newRectHeight));
			}
			
			std::cout << leftSamples[amplitudeFrame].real() << std::endl;;

		}
				

			
};
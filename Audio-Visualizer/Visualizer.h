#pragma once
#include "main.h"

class Visualizer {
	
	sf::Clock clock;
	int frequencyFrame = 0;
	sf::VertexArray freqCircleVertices;
	float freqCircle_x = 640; // x coord of the center
	float freqCircle_y = 360; // y coord of the center
	float freqCircle_radius_squared = 10000;


	public:
		Visualizer() {
			
			freqCircleVertices = sf::VertexArray(sf::LineStrip);
			float lastX;
			float freqCircle_first_endpoint = freqCircle_x - sqrt(freqCircle_radius_squared); // first endpoint of semi circle
			float freqCircle_second_endpoint = freqCircle_x + sqrt(freqCircle_radius_squared); // second endpoint of semi circle
			// Constructs the circle that displays frequencies over time
			for (int ranges = 1; ranges <= 64; ranges++) {
				float x;
				float y;

				if (ranges <= 32) {

					if (ranges % 32 == 0) {
						x = freqCircle_second_endpoint;
					}
					else {
						x = freqCircle_first_endpoint + (ranges % 32 * 6.25);
					}
					
					y = sqrt((freqCircle_radius_squared - pow((x - freqCircle_x), 2))) + freqCircle_y;
					lastX = x;

				}
				else {
					
					if (ranges % 32 == 0) {
						x = freqCircle_first_endpoint;
					}
					else {
						x = freqCircle_second_endpoint - (ranges % 32 * 6.25);
					}
					
					y = -sqrt((freqCircle_radius_squared - pow((x - freqCircle_x), 2))) + freqCircle_y;

				}
				
				freqCircleVertices.append(sf::Vector2f(x, y));

			}

			freqCircleVertices.append(sf::Vector2f(freqCircleVertices[0].position.x, freqCircleVertices[0].position.y));
		}

		sf::VertexArray& getFreqCircleVertices() {
			return freqCircleVertices;
		}

		void update(std::vector< std::vector <double> >& frequencyVisualizationVector, double songPlayingOffset) {
			
			frequencyFrame = (int)(songPlayingOffset * 30);
			
			float lastX;
			freqCircleVertices.clear();

			for (int ranges = 1; ranges <= 64; ranges++) {

				float radiusChange = pow(frequencyVisualizationVector[frequencyFrame][ranges - 1], 2);
				float freqCircle_first_endpoint = freqCircle_x - sqrt(freqCircle_radius_squared + radiusChange); // first endpoint of semi circle
				float freqCircle_second_endpoint = freqCircle_x + sqrt(freqCircle_radius_squared + radiusChange); // second endpoint of semi circle
				float x;
				float y;

				if (ranges <= 32) {

					if (ranges % 32 == 0) {
						x = freqCircle_second_endpoint;
						y = sqrt( (freqCircle_radius_squared + radiusChange - pow((x - freqCircle_x), 2)) ) + freqCircle_y;
					}
					else {
						x = freqCircle_first_endpoint + (ranges % 32 * 6.25);
						y = sqrt((freqCircle_radius_squared + radiusChange - pow((x - freqCircle_x), 2))) + freqCircle_y;
					}

					
					lastX = x;


					if (ranges % 32 == 0) {
						std::cout << "freqCircle_second_endpoint " << freqCircle_second_endpoint << std::endl;

						std::cout << (freqCircle_radius_squared + radiusChange - pow((x - freqCircle_x), 2)) << std::endl;
						std::cout << x << "," << y << std::endl;
					}

				}
				else {

					if (ranges % 32 == 0) {
						x = freqCircle_first_endpoint;
					}
					else {
						x = freqCircle_second_endpoint - (ranges % 32 * 6.25);
					}

					y = -sqrt((freqCircle_radius_squared + radiusChange - pow((x - freqCircle_x), 2))) + freqCircle_y;

					if (ranges % 32 == 0) {
						//std::cout << x << "," << y << std::endl;
					}

				}
				freqCircleVertices.append(sf::Vector2f(x, y));

			}

			freqCircleVertices.append(sf::Vector2f(freqCircleVertices[0].position.x, freqCircleVertices[0].position.y));
				

		}

			
};
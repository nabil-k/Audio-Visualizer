#pragma once

class Visualizer {
	

	int frequencyFrame = 0;
	int amplitudeFrame = 0;

	std::vector<sf::RectangleShape> freqRangeRects;
	std::vector <double> amplitudeVisualizationVector;
	std::vector <sf::CircleShape> amplitudeParticles;

	sf::RectangleShape backgroundRect;

	public:
		Visualizer() {
			
			// Creates Rects for freq visualization
			for (int ranges = 0; ranges < 64; ranges++) {
				sf::RectangleShape freqRangeRect = sf::RectangleShape();

				freqRangeRect.setSize(sf::Vector2f(4, 0));
				freqRangeRect.setPosition(480.f + (5 * ranges), 450.f);
				
				freqRangeRect.setFillColor(sf::Color::Black);

				freqRangeRects.push_back(freqRangeRect);
			}

			// Creates background for freq visualizer
			backgroundRect.setSize(sf::Vector2f(400.f, 200.f));
			backgroundRect.setPosition(440.f, 260.f);
			backgroundRect.setFillColor(sf::Color::White);
			backgroundRect.setOutlineThickness(5.f);
			backgroundRect.setOutlineColor(sf::Color::Black);
	
		}

		std::vector<sf::RectangleShape>& getFreqRangeRects() {
			return freqRangeRects;
		}

		sf::RectangleShape& getBackgroundRect() {
			return backgroundRect;
		}

		std::vector <sf::CircleShape>& getAmplitudeParticles() {
			return amplitudeParticles;
		}


		void setAmplitudeVisualizationVector(std::vector<double> amplitudeVisualizationVector) {
			this->amplitudeVisualizationVector = amplitudeVisualizationVector;
		}


		void update(std::vector< std::vector <double> >& frequencyVisualizationVector, double songPlayingOffset) {
			
			// Creates up to date frames to be drawn
			frequencyFrame = (int)(songPlayingOffset * 30);
			amplitudeFrame = (int)(songPlayingOffset * 30);
			
			// Updates the frequency rects
			for (int rect_i = 0; rect_i < freqRangeRects.size(); rect_i++) {
				float rectHeight = freqRangeRects[rect_i].getSize().y;
				float newRectHeight;
				if (frequencyFrame < frequencyVisualizationVector.size()) {
					newRectHeight = frequencyVisualizationVector[frequencyFrame][rect_i] * -1;
				}
				else {
					std::cout << "Visualizer has froze because the power spectrum hasn't been calculated fast enough to be in real time. This could be the result of a slow cpu or simply running the code in Debug mode." << std::endl;
					newRectHeight = rectHeight;
				}
				
				freqRangeRects[rect_i].setSize(sf::Vector2f(3, newRectHeight));
			}
			
			
			// Generates new particles (capped by the if statement condition)
			if (amplitudeParticles.size() < 20) {
				for (int i = 0; i < amplitudeVisualizationVector[amplitudeFrame]; i++) {
					float particle_starting_pos_x = rand() % 1280;
					float particle_starting_pos_y = rand() % 720 + 720.f;


					sf::CircleShape newParticle(5);
					newParticle.setPointCount(64);
					newParticle.setFillColor(sf::Color::Black);
					newParticle.setPosition(particle_starting_pos_x, particle_starting_pos_y);
					amplitudeParticles.push_back(newParticle);
				}
			}

			// Updates all exisiting particles
			for (int particle_i = 0; particle_i < amplitudeParticles.size(); particle_i++) {

				float particle_pos_y = amplitudeParticles[particle_i].getPosition().y;
				
				if (particle_pos_y < -10) {
					amplitudeParticles.erase(amplitudeParticles.begin() + particle_i);
					
				}
				else {
					amplitudeParticles[particle_i].move(sf::Vector2f(0.f, -5.f));
					
					float particle_new_pos_y = amplitudeParticles[particle_i].getPosition().y;
					float particle_new_pos_x = 10*sin(particle_new_pos_y/100);

					amplitudeParticles[particle_i].move(sf::Vector2f(particle_new_pos_x, 0.f));
					
				}

			}
			

		}
				

			
};
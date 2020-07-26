#pragma once
#include "main.h"

class Audio {
	
	std::string audioFilePath = "./audio/Rival x Cadmium - Seasons (feat. Harley Bird) [NCS Release].wav";
	
	//std::string audioFilePath = "./audio/test4.wav";
	sf::Clock clock;
	const sf::Int16* samples;
	unsigned int sampleRate;
	sf::Uint64 sampleSize;
	int singleChannelSize;
	float timeElapsed = 0;
	bool playedSong = false;
	
	std::vector< std::complex <double> > leftSamples;
	std::vector<double> sampleFrequencyRanges;
	std::vector< std::vector <double> > frequencyVisualizationVector;
	
	sf::Sound sound;
	sf::SoundBuffer buffer;

	public:
		

		Audio() {

			if (!buffer.loadFromFile(audioFilePath)) {
				std::cout << "Couldn't load buffer" << std::endl;
			}
			else {
				sound.setBuffer(buffer);
				sampleRate = buffer.getSampleRate();
				// Original sample (unsplit: the samples holding the left and right channels)
				samples = buffer.getSamples();
				sampleSize = buffer.getSampleCount();
				singleChannelSize = sampleSize / 2;
			}

		}

		void playSong() {
			sound.play();
			playedSong = true;
		}

		bool songPlayed() {
			return playedSong;
		}

		bool splitAudioChannel() {
			// Sample arrays for left channel
			leftSamples.resize(singleChannelSize + sampleRate);
			for (int i = 0; i < singleChannelSize; ++i) {
				leftSamples[i] = samples[2 * i];
			}
			// Padding data to audio channel
			for (int i = singleChannelSize; i < leftSamples.size(); ++i) {
				leftSamples[i] = 0;
			}

			std::cout << "Finished splitting audio channels" << std::endl;

			return true;
		}

		void outputsampleOverFrequencyVector(std::vector<double> vector){
			for (int i = 0; i < vector.size(); ++i) {
				std::cout << i << " " << vector[i] << std::endl;
			}
		}

		// Creates frequency ranges for the audio samples
		void getSampleOverFrequency() {

			if (splitAudioChannel()) {
				clock.restart();
				// Gets a sample from the audio channel to process, samples are the size of the sampleRate
				int sampleWindow = sampleRate / 10;
				for (int sampleIndex = 0; sampleIndex < singleChannelSize; sampleIndex += sampleWindow/2) {
					
					//std::cout << sampleIndex << "/" << singleChannelSize << std::endl;
					
					std::vector< std::complex< double> > leftSampleHannWindowed(sampleWindow);
					
					for (int i = 0; i < sampleWindow; i++) {
						std::complex< double> amplitudeHannWindowed = HannFunction(i, sampleWindow) * leftSamples[sampleIndex + i];
						leftSampleHannWindowed.push_back(amplitudeHannWindowed);
					}
					

					std::vector< std::complex< double> > leftSampleSample_FreqBin = FFT(leftSampleHannWindowed);
					frequencyVisualizationVector.push_back(createFrequencyVisualizationVector(leftSampleSample_FreqBin));
				}
			}
			std::cout << "SampleOverFrequency Runtime: " << clock.getElapsedTime().asSeconds() << " seconds" << std::endl;

		}


		std::complex< double> HannFunction(int n, int N) {
			std::complex< double> hann = pow((sin((M_PI * n) / N)), 2);
			return hann;

		}

		std::vector< std::complex< double> > FFT(std::vector< std::complex <double> > &samples) {
			int N = samples.size();

			if (N == 1) {
				return samples;
			}

			int new_N = N / 2;

			// Splits samples for recursion
			std::vector< std::complex< double> > evenSamples(new_N, 0);
			std::vector< std::complex< double> > oddSamples(new_N, 0);

			for (int i = 0; i < new_N; ++i) {
				evenSamples[i] = samples[i * 2];
				oddSamples[i] = samples[(i * 2) + 1];
			}

			// Recursion breaks down the samples
			std::vector< std::complex< double> > Feven(new_N, 0);
			Feven = FFT(evenSamples);
			std::vector< std::complex< double> > Fodd(new_N, 0);
			Fodd = FFT(oddSamples);

			// Post recursion DFT is calculated
			std::vector< std::complex< double> > freqBins(N, 0);

			for (int k = 0; k < N / 2; ++k) {
				std::complex<double> cmplxExponential = std::polar(1.0, -2*M_PI*k/N)*Fodd[k];
				freqBins[k] = Feven[k] + cmplxExponential;
				freqBins[k+N/2] = Feven[k] - cmplxExponential;
			}

			return freqBins;

		}



		std::vector<double> createFrequencyVisualizationVector(std::vector< std::complex< double> > complexVector) {
			int samplingFrequency = complexVector.size();
			std::vector< std::complex< double> >::const_iterator first = complexVector.begin();
			std::vector< std::complex< double> >::const_iterator last = complexVector.begin() + (complexVector.size() / 2);
			std::vector< std::complex< double> > complexVector_NyquistLimited(first, last);

			std::vector<double> frequencyVisualizationVector(256);
			
			double magnitude_scaled_sum = 0;

			for (int frequency = 0; frequency < complexVector_NyquistLimited.size(); frequency++) {
				
				double magnitude_scaled;
				double magnitude_scaled_avg;

				// Calculates magnitude from freq bin
				double real = complexVector[frequency].real() * 2 / samplingFrequency;
				double imag = complexVector[frequency].imag() * 2 / samplingFrequency;
				double magnitude = sqrt(pow(real,2) + pow(imag, 2));
				
				if (magnitude == 0) {
					magnitude_scaled = 0;
				}
				else {
					magnitude_scaled = magnitude;
				}

				if (magnitude_scaled > 300.0) {
					magnitude_scaled = 500.0;
				}

				magnitude_scaled_sum += magnitude_scaled;

				// Two seperate bools for setting freq ranges to give priority to freq ranges below 1khz
				bool addLowFreqRangeValue = ((frequency % 8) == 0);

				// Sets the vector values to contain an average magnitude in a specific frequency range
				if (frequency > 0) {
					if (frequency <= 2048) {
						if (addLowFreqRangeValue) {
							magnitude_scaled_avg = magnitude_scaled_sum / 8.0;
							magnitude_scaled_sum = 0;
							frequencyVisualizationVector[(frequency / 8) - 1] = magnitude_scaled_avg;
						}
					}
				}


			}
		
			return frequencyVisualizationVector;

		}

		std::vector< std::vector <double> > getfrequencyVisualizationVector() {
			return frequencyVisualizationVector;
		}


};

#pragma once
#include "main.h"

class Audio {
	sf::SoundBuffer buffer;
	std::string audioFilePath = "./audio/Rival x Cadmium - Seasons (feat. Harley Bird) [NCS Release].wav";

	const sf::Int16* samples_unsplit;
	unsigned int sampleRate;
	sf::Uint64 sampleSize_unsplit;
	int singleChannelSize;

	sf::Int16* leftSamples;
	sf::Int16* rightSamples;
	sf::SoundBuffer leftBuffer;
	sf::SoundBuffer rightBuffer;

	public:

		Audio() {


			if (!buffer.loadFromFile(audioFilePath)) {
				std::cout << "Couldn't load buffer" << std::endl;
			}
			else {
				sampleRate = buffer.getSampleRate();

				// Original sample (unsplit denoting the samples holding the left and right channels
				samples_unsplit = buffer.getSamples();
				
				sampleSize_unsplit = buffer.getSampleCount();
				singleChannelSize = sampleSize_unsplit / 2;

				// Sample arrays for right and left channels
				sf::Int16* leftSamples{ new sf::Int16[singleChannelSize] };
				sf::Int16* rightSamples{ new sf::Int16[singleChannelSize] };
				
				// Seperates samples_unsplit into the left and right samples 
				for (int i = 0; i < singleChannelSize; ++i) {
					leftSamples[i] = samples_unsplit[i * 2];
					rightSamples[i] = samples_unsplit[(i * 2) + 1];
				}


				//leftBuffer.loadFromSamples(leftSamples, singleChannelSize, 1u, sampleRate);
				//rightBuffer.loadFromSamples(rightSamples, singleChannelSize, 1u, sampleRate);

				
			}
		}

	std::vector< std::complex< double> > FFT(std::vector< std::complex <double> > &samples) {
		int N = samples.size();

		if (N == 1) {
			return samples;
		}

		int new_N = N / 2;

		std::vector< std::complex< double> > evenSamples(new_N, 0);
		std::vector< std::complex< double> > oddSamples(new_N, 0);

		for (int i = 0; i <= new_N; i++) {
			evenSamples[i] = samples[i * 2];
			oddSamples[i] = samples[(i * 2) + 1];
		}

		std::vector< std::complex< double> > Feven(new_N, 0);
		Feven = FFT(evenSamples);
		std::vector< std::complex< double> > Fodd(new_N, 0);
		Fodd = FFT(oddSamples);

		// After recursion
		std::vector< std::complex< double> > freqBins(N, 0);

		for (int k = 0; k <= N / 2; k++) {
			std::complex<double> cmplxExponential = std::polar(1.0, -2 * M_PI*k / N)*Fodd[k];
			freqBins[k] = Feven[k] + cmplxExponential;
			freqBins[k+N/2] = Feven[k] - cmplxExponential;
		}

		return freqBins;

	}
};

#pragma once
#include "main.h"

class Audio {
	
	std::string audioFilePath = "./audio/Rival x Cadmium - Seasons (feat. Harley Bird) [NCS Release].wav";

	const sf::Int16* samples;
	unsigned int sampleRate;
	sf::Uint64 sampleSize;
	int singleChannelSize;

	sf::Sound sound;

	sf::SoundBuffer buffer;
	sf::SoundBuffer leftBuffer;
	sf::SoundBuffer rightBuffer;


	

	public:

		Audio() {
			
			sf::Sound leftPlayer;
			if (!buffer.loadFromFile(audioFilePath)) {
				std::cout << "Couldn't load buffer" << std::endl;
			}
			else {
				sampleRate = buffer.getSampleRate();
				
				
				// Original sample (unsplit denoting the samples holding the left and right channels
				samples = buffer.getSamples();
				
				sampleSize = buffer.getSampleCount();
				singleChannelSize = sampleSize / 2;

				// Sample arrays for right and left channels
				std::vector< std::complex <double> > leftSamples(singleChannelSize);
				//std::vector< std::complex <double> > rightSamples(singleChannelSize);

				// Seperates samples_unsplit into the left and right samples
				for (int i = 0; i < singleChannelSize; ++i) {
					leftSamples[i] = samples[(2*i)];
					//rightSamples[i] = samples[(2*i) + 1];
				}
				std::cout << "Done Splitting" << std::endl;

				for (int sampleIndex = 0; sampleIndex < singleChannelSize; sampleIndex += 256) {
					std::vector< std::complex< double> >::const_iterator first = leftSamples.begin() + sampleIndex;
					std::vector< std::complex< double> >::const_iterator last = leftSamples.begin() + (sampleIndex + sampleRate);
					std::vector< std::complex< double> > leftSampleSample(first, last);

					std::vector< std::complex< double> > transform = FFT(leftSampleSample);
					std::vector<double>  y = magnitudeOfComplexVector(transform);
					std::cout << y.size() << std::endl;
				}

				
		
				
				sound.setBuffer(leftBuffer);
				std::cout << "Playing sound..." << std::endl;
				//sound.play();

				//leftBuffer.loadFromSamples(leftSamples, singleChannelSize, 1u, sampleRate);
				//rightBuffer.loadFromSamples(rightSamples, singleChannelSize, 1u, sampleRate);
		

			}




	
		}
		
		void playSong() {
			//sound.setBuffer(leftBuffer);
			//sound.play();
		}

		std::vector< std::complex< double> > FFT(std::vector< std::complex <double> > &samples) {
			int N = samples.size();

			if (N == 1) {
				return samples;
			}

			int new_N = N / 2;

			std::vector< std::complex< double> > evenSamples(new_N, 0);
			std::vector< std::complex< double> > oddSamples(new_N, 0);

			for (int i = 0; i < new_N; ++i) {
				evenSamples[i] = samples[i * 2];
				oddSamples[i] = samples[(i * 2) + 1];
			}

			std::vector< std::complex< double> > Feven(new_N, 0);
			Feven = FFT(evenSamples);
			std::vector< std::complex< double> > Fodd(new_N, 0);
			Fodd = FFT(oddSamples);

			// After recursion
			std::vector< std::complex< double> > freqBins(N, 0);

			for (int k = 0; k < N / 2; ++k) {
				std::complex<double> cmplxExponential = std::polar(1.0, -2*M_PI*k/N)*Fodd[k];
				freqBins[k] = Feven[k] + cmplxExponential;
				freqBins[k+N/2] = Feven[k] - cmplxExponential;
			}

			return freqBins;

		}

		std::vector<double> magnitudeOfComplexVector(std::vector< std::complex< double> > complexVector) {
			int samplingFrequency = complexVector.size();
			std::vector< std::complex< double> >::const_iterator first = complexVector.begin();
			std::vector< std::complex< double> >::const_iterator last = complexVector.begin() + (complexVector.size()/2);
			std::vector< std::complex< double> > complexVector_NyquistLimited(first, last);

			std::vector<double> complexVectorMagnitudes(complexVector_NyquistLimited.size());
			
			for (int i = 0; i < complexVectorMagnitudes.size(); i++) {
				double real = complexVector[i].real() * 2 / samplingFrequency;
				double imag = complexVector[i].imag() * 2 / samplingFrequency;
				double magnitude = sqrt(pow(real,2) + pow(imag, 2));
				complexVectorMagnitudes[i] = magnitude;
			}
		
			return complexVectorMagnitudes;

		}

};

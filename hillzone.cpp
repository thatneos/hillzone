#include <random>
#include <ctime>
#include <vector>
#include <cmath>

class ChiptuneSynthesizer {
private:
    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;
    const float sampleRate = 44100.0f;
    
    float generateSquareWave(float time, float freq, float duty = 0.5f) {
        float period = 1.0f / freq;
        float t = fmod(time, period) / period;
        return t < duty ? 1.0f : -1.0f;
    }

    float generateNoise(float amplitude) {
        return (dist(rng) * 2.0f - 1.0f) * amplitude;
    }

public:
    ChiptuneSynthesizer() : rng(std::time(0)), dist(0.0f, 1.0f) {}

    std::vector<float> generateGlitchyMelody(float duration) {
        std::vector<float> audio;
        int numSamples = static_cast<int>(duration * sampleRate);
        audio.reserve(numSamples);

        // Basic parameters
        float baseFreq = 440.0f; // A4 note
        float glitchIntensity = 0.3f;
        
        for (int i = 0; i < numSamples; i++) {
            float time = i / sampleRate;
            
            // Generate base tone with random frequency modulation
            float freqMod = 1.0f + (dist(rng) * 2.0f - 1.0f) * glitchIntensity;
            float sample = generateSquareWave(time, baseFreq * freqMod) * 0.5f;
            
            // Add glitch noise
            if (dist(rng) < 0.05f) {
                sample += generateNoise(0.4f);
            }
            
            // Clip the sample
            sample = std::max(-1.0f, std::min(1.0f, sample));
            
            audio.push_back(sample);
        }

        return audio;
    }
};

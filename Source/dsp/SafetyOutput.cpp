#include "SafetyOutput.h"
#include "../util/ParameterLayout.h"
#include <cmath>

namespace mythodic::dsp
{
    void SafetyOutput::prepare (double, int) {}

    void SafetyOutput::updateParameters (juce::AudioProcessorValueTreeState& apvts)
    {
        ceilingDbtp_ = apvts.getRawParameterValue (mythodic::params::ceilingDbtp)->load();
        safeMode_    = apvts.getRawParameterValue (mythodic::params::safeMode)->load() > 0.5f;
    }

    void SafetyOutput::process (juce::dsp::AudioBlock<float> block) noexcept
    {
        const float ceiling = juce::Decibels::decibelsToGain (ceilingDbtp_);
        lastPeak_ = 0.0f;
        estimatedTruePeak_ = 0.0f;

        for (size_t ch = 0; ch < block.getNumChannels(); ++ch)
        {
            auto* s = block.getChannelPointer (ch);
            float prev = 0.0f;
            for (size_t i = 0; i < block.getNumSamples(); ++i)
            {
                float x = s[i];
                if (safeMode_)
                    x = std::tanh (x / juce::jmax (0.05f, ceiling)) * ceiling;
                else
                    x = juce::jlimit (-ceiling, ceiling, x);

                lastPeak_ = std::max (lastPeak_, std::abs (x));
                estimatedTruePeak_ = std::max (estimatedTruePeak_, std::max (std::abs (x), std::abs (0.5f * (x + prev))));
                prev = x;
                s[i] = x;
            }
        }
    }
}

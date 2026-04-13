#pragma once
#include <JuceHeader.h>
#include <cmath>

namespace mythodic::math
{
    template <typename T>
    inline T safeDbToGain (T db) noexcept
    {
        return juce::Decibels::decibelsToGain (db, static_cast<T> (0.0));
    }

    template <typename T>
    inline T fastAbs (T v) noexcept
    {
        return std::abs (v);
    }

    template <typename T>
    inline T mix (T dry, T wet, T amount) noexcept
    {
        return dry + (wet - dry) * amount;
    }
}

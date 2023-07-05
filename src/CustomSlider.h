#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#ifdef __GNUC__
#include <fmt/core.h>
#define stdformat fmt::format
#define stdvformat fmt::format
#define stdmakeformatargs(...) __VA_ARGS__
#else
#include <format>
#define stdformat std::format
#define stdvformat std::vformat
#define stdmakeformatargs(...) std::make_format_args( __VA_ARGS__ )
#endif

class CustomSlider : public juce::Slider
{
public:
   CustomSlider( juce::String s );
   virtual juce::String getTextFromValue( double value );
   void setPrecision( int p );

private:
   int m_Precision;
};

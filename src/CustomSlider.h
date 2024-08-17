/*******************************************************************************
 *  Copyright (c) 2024 Christian Nowak <chnowak@web.de>                        *
 *   This file is part of chnCrusher.                                          *
 *                                                                             *
 *  chnCrusher is free software: you can redistribute it and/or modify it      *
 *  under the terms of the GNU General Public License as published by the Free *
 *  Software Foundation, either version 3 of the License, or (at your option)  *
 *  any later version.                                                         *
 *                                                                             *          
 *  chnCrusher is distributed in the hope that it will be useful, but          * 
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
 *  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License    *
 *  for more details.                                                          *
 *                                                                             *
 *  You should have received a copy of the GNU General Public License along    *
 *  with chnCrusher. If not, see <https://www.gnu.org/licenses/>.              *
 *******************************************************************************/


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

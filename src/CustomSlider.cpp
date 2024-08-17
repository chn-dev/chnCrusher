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


#include "CustomSlider.h"

//==============================================================================
CustomSlider::CustomSlider( juce::String s ) : juce::Slider( s ),
                                       m_Precision( 0 )
{
}


//==============================================================================
juce::String CustomSlider::getTextFromValue( double value )
{
   std::string f = stdformat( "{{:.{}f}}{{}}", m_Precision );
   std::string s = stdvformat( f, stdmakeformatargs( value, this->getTextValueSuffix().toStdString() ) );

   return( s );
}


//==============================================================================
void CustomSlider::setPrecision( int p )
{
   m_Precision = p;
}

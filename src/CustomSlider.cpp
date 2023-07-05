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

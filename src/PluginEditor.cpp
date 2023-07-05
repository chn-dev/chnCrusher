#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <config.h>


//==============================================================================
PluginEditor::PluginEditor( PluginProcessor& p )
    : AudioProcessorEditor( &p ), processorRef( p )
{
   juce::ignoreUnused (processorRef);
   // Make sure that before the constructor has finished, you've set the
   // editor's size to whatever you need it to be.

   setTitle( stdformat( "{} v{}", PROJECT_NAME, PROJECT_VER ) );

   m_pSlQuantize = new CustomSlider( "Quantize" );
   m_pSlQuantize->setTextValueSuffix( "bit" );
   m_pSlQuantize->setPrecision( 1 );
   m_pSlQuantize->setRange( processor().getQuantizeParameter()->getNormalisableRange().getRange().getStart(),
                            processor().getQuantizeParameter()->getNormalisableRange().getRange().getEnd() );
   m_pSlQuantize->setValue( processor().getQuantize() );
   m_pSlQuantize->setTextBoxStyle( juce::Slider::TextBoxAbove, false, 96, 12 );
   m_pSlQuantize->setSliderStyle( juce::Slider::LinearVertical );
   m_pSlQuantize->setSliderSnapsToMousePosition( false );
   m_pSlQuantize->addListener( this );
   m_pSlQuantize->setSkewFactor( 0.25, false );
   addAndMakeVisible( m_pSlQuantize );

   m_pLaQuantize = new juce::Label( "Quantize" );
   m_pLaQuantize->setText( "Quantize", juce::NotificationType::dontSendNotification );
   addAndMakeVisible( m_pLaQuantize );

   m_pSlResample = new CustomSlider( "Resample" );
   m_pSlResample->setTextValueSuffix( "Hz" );
   m_pSlResample->setRange( processor().getResampleParameter()->getNormalisableRange().getRange().getStart(),
                            processor().getResampleParameter()->getNormalisableRange().getRange().getEnd() );
   m_pSlResample->setValue( processor().getResample() );
   m_pSlResample->setSliderStyle( juce::Slider::LinearVertical );
   m_pSlResample->setSliderSnapsToMousePosition( false );
   m_pSlResample->addListener( this );
   m_pSlResample->setTextBoxStyle( juce::Slider::TextBoxAbove, false, 96, 12 );
   m_pSlResample->setSkewFactor( 0.25, false );
   addAndMakeVisible( m_pSlResample );

   m_pLaResample = new juce::Label( "Resample" );
   m_pLaResample->setText( "Resample", juce::NotificationType::dontSendNotification );
   addAndMakeVisible( m_pLaResample );

   processor().setQuantize( 0.0 );
   processor().setResample( 48000 );

   setSize( 196, 166 );
}


//==============================================================================
PluginEditor::~PluginEditor()
{
   delete m_pSlQuantize;
   delete m_pLaQuantize;
   delete m_pSlResample;
   delete m_pLaResample;
}


//==============================================================================
void PluginEditor::sliderValueChanged( juce::Slider *pSlider )
{
   if( pSlider == m_pSlQuantize )
   {
      processor().setQuantize( m_pSlQuantize->getValue() );
   } else
   if( pSlider == m_pSlResample )
   {
      processor().setResample( m_pSlResample->getValue() );
   }
}


//==============================================================================
PluginProcessor &PluginEditor::processor() const
{
   return( processorRef );
}


//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
   juce::ignoreUnused( g );

   int xo = -12;

   m_pSlQuantize->setBounds( 48 + xo, 28, 48, 120 );
   m_pLaQuantize->setBounds( 44 + xo, 12, 54, 12 );

   m_pSlResample->setBounds( 24 + 96 + xo, 28, 48, 120 );
   m_pLaResample->setBounds( 24 + 84 + xo, 12, 72, 12 );
}


//==============================================================================
void PluginEditor::resized()
{
}


//==============================================================================
void PluginEditor::parameterValueChanged( int parameterIndex, float newValue )
{
   if( parameterIndex == processor().getResampleParameter()->getParameterIndex() )
   {
      m_pSlResample->setValue( processor().getResampleParameter()->convertFrom0to1( newValue ),
                               juce::NotificationType::dontSendNotification );
   } else
   if( parameterIndex == processor().getQuantizeParameter()->getParameterIndex() )
   {
      m_pSlQuantize->setValue( processor().getQuantizeParameter()->convertFrom0to1( newValue ),
                               juce::NotificationType::dontSendNotification );
   }
}


//==============================================================================
void PluginEditor::parameterGestureChanged( int parameterIndex, bool gestureIsStarting )
{
}

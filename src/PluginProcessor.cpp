#include <cstdint>
#include <algorithm>

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
PluginProcessor::PluginProcessor()
   : AudioProcessor( BusesProperties()
      .withInput( "Input",  juce::AudioChannelSet::stereo(), true )
      .withOutput( "Output", juce::AudioChannelSet::stereo(), true ) ),
      m_pEditor( 0 ),
      m_Ofs( 0.0 )
{
   addParameter( m_pQuantize = new juce::AudioParameterFloat( "quantize", "Quantize", 1.0, 16.0, 16.0 ) );
   addParameter( m_pResample = new juce::AudioParameterFloat( "resample", "Resample", 100.0, 48000.0, 48000.0 ) );
}


//==============================================================================
PluginProcessor::~PluginProcessor()
{
}


//==============================================================================
const juce::String PluginProcessor::getName() const
{
   return ( JucePlugin_Name );
}


//==============================================================================
bool PluginProcessor::acceptsMidi() const
{
   return( false );
}


//==============================================================================
bool PluginProcessor::producesMidi() const
{
   return( false );
}


//==============================================================================
bool PluginProcessor::isMidiEffect() const
{
   return( false );
}


//==============================================================================
double PluginProcessor::getTailLengthSeconds() const
{
   return( 0.0 );
}


//==============================================================================
int PluginProcessor::getNumPrograms()
{
   return( 1 ); // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}


//==============================================================================
int PluginProcessor::getCurrentProgram()
{
   return( 0 );
}


//==============================================================================
void PluginProcessor::setCurrentProgram( int index )
{
   juce::ignoreUnused( index );
}


//==============================================================================
const juce::String PluginProcessor::getProgramName( int index )
{
   juce::ignoreUnused( index );
   return {};
}


//==============================================================================
void PluginProcessor::changeProgramName( int index, const juce::String& newName )
{
   juce::ignoreUnused( index, newName );
}


//==============================================================================
void PluginProcessor::prepareToPlay( double sampleRate, int samplesPerBlock )
{
   m_sampleRate = sampleRate;
   m_samplesPerBlock = samplesPerBlock;
}


//==============================================================================
void PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}


//==============================================================================
bool PluginProcessor::isBusesLayoutSupported(  const BusesLayout& layouts ) const
{
#if JucePlugin_IsMidiEffect
   juce::ignoreUnused (layouts);
   return( true );
#else
   // This is the place where you check if the layout is supported.
   // In this template code we only support mono or stereo.
   // Some plugin hosts, such as certain GarageBand versions, will only
   // load plugins that support stereo bus layouts.
   if( ( layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() ) &&
       ( layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo() ) )
      return( false );

   // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
   if( layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet() )
      return( false );
#endif
   return( true );
#endif
}


//==============================================================================
void PluginProcessor::setPar( juce::AudioParameterFloat *pPar, double val )
{
   pPar->beginChangeGesture();

   if( val < pPar->getNormalisableRange().getRange().getStart() )
   {
      val = pPar->getNormalisableRange().getRange().getStart();
   } else
   if( val > pPar->getNormalisableRange().getRange().getEnd() )
   {
      val = pPar->getNormalisableRange().getRange().getEnd();
   }

   float v = pPar->getNormalisableRange().convertTo0to1( val );
   v = std::min( v, 1.0f );
   v = std::max( v, 0.0f );
   pPar->setValueNotifyingHost( v );
   pPar->endChangeGesture();
}


//==============================================================================
void PluginProcessor::setQuantize( double quantize )
{
   setPar( m_pQuantize, quantize );
}


//==============================================================================
juce::AudioParameterFloat *PluginProcessor::getQuantizeParameter() const
{
   return( m_pQuantize );
}


//==============================================================================
juce::AudioParameterFloat *PluginProcessor::getResampleParameter() const
{
   return( m_pResample );
}


//==============================================================================
double PluginProcessor::getQuantize() const
{
   return( m_pQuantize->get() );
}


//==============================================================================
double PluginProcessor::getResample() const
{
   return( m_pResample->get() );
}


//==============================================================================
void PluginProcessor::setResample( double resample )
{
   setPar( m_pResample, resample );
}


//==============================================================================
void PluginProcessor::processBlock( juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages )
{
   juce::ScopedNoDenormals noDenormals;
   auto totalNumInputChannels  = getTotalNumInputChannels();
   auto totalNumOutputChannels = getTotalNumOutputChannels();

   // In case we have more outputs than inputs, this code clears any output
   // channels that didn't contain input data, (because these aren't
   // guaranteed to be empty - they may contain garbage).
   // This is here to avoid people getting screaming feedback
   // when they first compile a plugin, but obviously you don't need to keep
   // this code if your algorithm always overwrites all the output channels.
   for( auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i )
   {
      buffer.clear ( i, 0, buffer.getNumSamples() );
   }

   // This is the place where you'd normally do the guts of your plugin's
   // audio processing...
   // Make sure to reset the state if your inner loop is processing
   // the samples and the outer loop is handling the channels.
   // Alternatively, you can process the samples with the channels
   // interleaved by keeping the same state.
   int32_t mv = pow( 2.0, m_pQuantize->get() - 1.0 ) + 0.5;
    
   double newSampleRate = m_pResample->get();
   double sampleRatio = newSampleRate / m_sampleRate;

   m_Vals.resize( totalNumOutputChannels );

   for( int channel = 0; channel < totalNumOutputChannels; ++channel )
   {
      double ofs = m_Ofs;

      auto *pChannelData = buffer.getWritePointer( channel );
      for( auto j = 0; j < m_samplesPerBlock; j++ )
      {
         ofs += sampleRatio;
         if( ofs >= 1.0 )
         {
            m_Vals[channel] = pChannelData[j];
            ofs -= (uint32_t)ofs;
         }

         int32_t v = ( m_Vals[channel] * mv ) + 0.5;
         pChannelData[j] = (double)v / mv;
      }
   }

   m_Ofs = m_Ofs + ( m_samplesPerBlock * sampleRatio );
   m_Ofs -= (uint32_t)m_Ofs;
}


//==============================================================================
bool PluginProcessor::hasEditor() const
{
    return( true ); // (change this to false if you choose to not supply an editor)
}


//==============================================================================
juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
   m_pEditor = new PluginEditor( *this );

   m_pQuantize->addListener( m_pEditor );
   m_pResample->addListener( m_pEditor );

   return( m_pEditor );
}


//==============================================================================
void PluginProcessor::getStateInformation( juce::MemoryBlock& destData )
{
   juce::MemoryOutputStream memOut = juce::MemoryOutputStream( destData, true );
   memOut.writeDouble( m_pQuantize->get() );
   memOut.writeDouble( m_pResample->get() );
}


//==============================================================================
void PluginProcessor::setStateInformation( const void* data, int sizeInBytes )
{
   juce::MemoryInputStream memIn = juce::MemoryInputStream( data, static_cast<size_t>( sizeInBytes ), false );
   setQuantize( memIn.readDouble() );
   setResample( memIn.readDouble() );
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
   return new PluginProcessor();
}

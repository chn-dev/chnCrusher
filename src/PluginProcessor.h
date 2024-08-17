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

#include <vector>

#include <juce_audio_processors/juce_audio_processors.h>

class PluginEditor;

//==============================================================================
class PluginProcessor  : public juce::AudioProcessor
{
public:
   //==============================================================================
   PluginProcessor();
   ~PluginProcessor() override;

   //==============================================================================
   void prepareToPlay (double sampleRate, int samplesPerBlock) override;
   void releaseResources() override;

   bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

   void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
   using AudioProcessor::processBlock;

   //==============================================================================
   juce::AudioProcessorEditor* createEditor() override;
   bool hasEditor() const override;

   //==============================================================================
   const juce::String getName() const override;

   bool acceptsMidi() const override;
   bool producesMidi() const override;
   bool isMidiEffect() const override;
   double getTailLengthSeconds() const override;

   //==============================================================================
   int getNumPrograms() override;
   int getCurrentProgram() override;
   void setCurrentProgram (int index) override;
   const juce::String getProgramName (int index) override;
   void changeProgramName (int index, const juce::String& newName) override;

   //==============================================================================
   void getStateInformation (juce::MemoryBlock& destData) override;
   void setStateInformation (const void* data, int sizeInBytes) override;

   void setQuantize( double quantize );
   double getQuantize() const;
   juce::AudioParameterFloat *getQuantizeParameter() const;
   juce::AudioParameterFloat *getResampleParameter() const;
   void setResample( double resample );
   double getResample() const;

private:
   //==============================================================================
   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( PluginProcessor )

   void setPar( juce::AudioParameterFloat *pPar, double val );

   PluginEditor *m_pEditor;

   double m_sampleRate;
   int m_samplesPerBlock;

   juce::AudioParameterFloat *m_pQuantize;
   juce::AudioParameterFloat *m_pResample;
   double m_Ofs;

   std::vector<double> m_Vals;
};

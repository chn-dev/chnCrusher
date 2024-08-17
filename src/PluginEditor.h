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

#include "PluginProcessor.h"
#include "CustomSlider.h"

//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor,
                     public juce::Slider::Listener,
                     public juce::AudioParameterFloat::Listener
{
public:
    explicit PluginEditor ( PluginProcessor& );
    ~PluginEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    virtual void sliderValueChanged( juce::Slider *pSlider );

    virtual void parameterValueChanged( int parameterIndex, float newValue );
    virtual void parameterGestureChanged( int parameterIndex, bool gestureIsStarting );
    PluginProcessor &processor() const;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor& processorRef;

    CustomSlider *m_pSlQuantize;
    juce::Label *m_pLaQuantize;
    CustomSlider *m_pSlResample;
    juce::Label *m_pLaResample;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( PluginEditor )
};

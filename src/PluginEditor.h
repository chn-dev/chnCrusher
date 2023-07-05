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

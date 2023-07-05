chnCrusher
=========

This is a simple Bit Crusher plugin written using [JUCE](https://juce.com/) as an exercise to demonstrate the effects of time quantization (aliasing) and value quantization (digital noise). The plugin has two parameters:

  - Quantize, ranging from 1.0bit to 16.0bit
  - Resample, ranging from 100Hz to 48000Hz
  
To clone and compile chnCrusher, do the following:

    git clone ssh://github.com/chn-dev/chnCrusher
    cd chnCrusher
    git submodule update --init --recursive
    cmake . -B build
    cmake --build build

By default, the plugin will be built in the formats LV2, VST3, AU and as a standalone application.

Copyright (c) 2023 by chn

http://www.chn-dev.net/

mailto:chnowak@web.de

# MIDI CONTROLLER for usage with MIXXX on Rpi, but everything else too.

## Architecture
### control element
- is a base class for implementation of control elements
- should allow to use elements within a multiplexer
#### button
- sets up a debounced button
#### pot
- sets up a pot which has sensitivity adjustment to prevent jumping around, though a 100nf cap between center and GND helps.
#### encoder
- sets up a rotary encoder, its button is separate - treated as a button
- in multiplexer, pin 1 must precede pin2, pin1->changed is set to false after get_value

## Currently working:


# Features
- environment for micro and nano
- using multiplexer for reading inputs


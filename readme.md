# Overview - Dorthy - Digital Rotary Encoder based Teensy Synth
This repo contains several PCB designs and teensy firmware for building a digital sythesiser.


**Directory structure:**
* cad (empty...)
* doc (mostly datasheets and links to research sources)
* firmware (arduino sketches)
* hardware (eagle projects)
* production (gerber zips)
* simulation (empty...)


**PCBs (see detailed descriptions below)**
* **R**otary **E**ncoder **E**xpander **M**odule (REEM)
* **G**round **I**solated **M**idi **I**nput Module (GIMI)




## Rotary Encoder Expander Module (REEM)

### Overview

This module is meant to be an expandable way to attach many rotary encoders to a single i2c master.  The idea is that it can be used in creating a nice user interface for a synthesizer.  This project is meant to be small, to keep manufacturing costs down, but also expandable so that multiple of these can be connected together to make a large io pannel. Currently limited to 8 modules or 64 knobs based on the io expander chip used.



### Hardare Features

* Voltage input 1.8 — 5.5 V
* Optional pullups on SCL and SDA, do not pupulate by default,  should be pulled up on master side.
* Chainable design, simply connect modules using the ribbon cable connectors. (VCC, GND, SCL, SDA).
* 3 address pins per chip allow up to 8 unique addresses.  
 * **The address pins are floating by default and must be tied to vcc or ground by shorting one of the two 0805 resitor pads per pin**


### Future Considerations
* If you want chainable interupts, its probably possible, especially with more io lines on the chips
* it may be nice to someday take advantage of the switches built into the encoders, but i thought i would skip for now
* Optional hardware filter circuits for each encoder might improve performance but would mean more soldering
* Instead of an encoder, We could allow switches or buttons in the same form factor.
* Consider a form factor that fits with eurorack standards.
 * The Eurorack format calls for modules of 128.5mm (slightly over 5") height. Horizontal width is measured in "horizontal pitch", where 1 HP = 5.08mm (exactly 0.2").  This is larger than eagle free can build and fab houses may charge more 
* I wonder if it would be cheaper to use JST connectors for board to board connections.  See adafruit Trellis for example.



## **G**round **I**solated **M**idi **I**nput Module (GIMI)

### 



### Overview
Classic octocoupler used for midi digitization for arduino or similar controllers.


***Warning ***
In rev 1 of producing this baord the M4 and M5 pin labels were swapped on the silkscreen.  Refer to the schematic and drawings, not the silkscreen.




### Hardare Features
* reverse polarity protection diode.
* midi in uses octocoupler preventing ground loops.  
* RX pullup does not need to be 5v.  Can be tied to 3v3, or whatever voltage the controller needs.
* Jumper for quickly disconnecting RX from the circuit.  For re-programming certain controllers Rx may need to be floating.





### Future Considerations
* It would be pretty easy to add midi through and/or midi out at some point.
* It may be nice to get board mount midi connectors at some point.
* It may be nice to start using a standard cable (like JST SH or JST PH...) rather than the 100mil pitch headers I put on.




## Dorthy Teensy Synth (work in progress)
Designed around a teensy microcontroller and some other hardware modules.  Utilizes the teensy audio libraries and some custom firmware.

### Playing the Synth
Instructions and features tbd.

## Dorthy Teensy Synth Hardare 
Take a teensy, slap 64 knobs and 16 buttons onto it, make it midi compatable and make some music

#### BOM
* 1x Teensy microcontroller, at least Rev 3.5 reccomended.
* 1x Midi in GIMI module (hardware/midi_in)
* 8x REEM modules(hardware/MultiEncoder)
* 2x large capacitors for stereo audio out, simple bypass cap to bring it to 0v centered.
* LCD display? tbd
* trellis? https://www.adafruit.com/product/3954


#### Hardware Pinouts
TBD

## Dorthy Teensy Synth Firmware
Overview TBD


#### Firmware Detailed Descriptions
TBD


#### Firmware Enviromental setup
TBD


#### Firmware Dependencies
TBD


#### Firmware Limitations
TBD

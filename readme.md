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
* **D**igital **R**otary Encoder **T**eensy S**y**nth (DRTY / DORTHY)




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
This synth will make heavy use of the teensy audio libraries and other goodies found all over the web.  Special thanks to all the contributors!


#### Firmware Detailed Descriptions (Requirments...)
* Polled processes: knobs(>100Hz), capacitive touch pads(100Hz?), midi RX(Every loop), Trellis (100Hz?), Clock Monitor(Every Loop), Touchscreen(100Hz?)
* While polling, if something is found that requires updates, the dispatcher class is called.
* When called the dispatcher will perform one or more actions such as modifying the voices or other synth parameters, and updating the display.
* The synth itself will have N voices, each with its own oscilators, LFOs?, amplitude envelope, filter and filter envelope.
* The synth will then combine all voices and send them through an effects signal chain containing delay, reverb, bitcrush, etc.
* The synth will respond to pitch bending and modwheel messages.
* The synth will be able to store up to M "note on" messages at a time, and will use the LAST N notes on the voices, upon notoffs it will go back through the list in revers chronological order.


#### Firmware Immediate Todo List
* Test what happens if the SetScalers function is passed a max smaler than min, hopefully it just reverses the knob polarity, that would be sweet
* Rewrite Midi function so that it does not take 50 ms to exxecute...
* Figure out why polyphonic note off does not often continue the release envelope if another note is hit.


#### Firmware Future Considerations
* It would be nice to have a good sequencer in the future, (keep this in mind when writing the dispatcher and voice controls)  consider things like kbd play / stack live 
* It would be nice to have a built in drum machine in the future.
* It would be nice to have the ability to save patches.  (make settings easy to get / set)
* It would be nice to be able to swap LFOs from incremental clk sync to continuous bpm sweeps.  this requires some back and forth from dispatcher to clk and lfo.
* It would be nice to be able to swap from re-triggering envelopes on each additional key to using one envelop for all voices(more smooth /legatto)





#### Firmware Enviromental setup
All you should need is arduino IDE with the teensy 3.6 board installed.
Teensy 1.53 seems to work much faster than the latest versions, Note to self: I have a copy of the 1.53 installer on my google drive main folder "installexes.rar" 
Arduino 1.8.13 works with this version of Teensy, I think I had issues with 1.8.16 and that teensy version.

#### Firmware Dependencies
TBD


#### Firmware Limitations
TBD

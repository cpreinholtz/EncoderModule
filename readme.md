Multi Encoder Module Overview

This module is meant to be an expandable way to attach many rotary encoders to a single i2c master.  The idea is that it can be used in creating a nice user interface for a synthesizer.  This project is meant to be small, to keep manufacturing costs down, but also expandable so that multiple of these can be connected together to make a full io pannel.



Features

Optional pullups on SCL and SDA, not pupulate by default,  should be pulled up on master side.
Chainable design, simply connect modules using the ribbon cable connectors. (VDD, GND, SCL, SDA, o_INT, i_INT).  5 to 10pF per chip.
4 jumper positions(VDD, VSS, SCL, SDA) and 3 address pin allow up to 64 addresses.  
    In reality we probably will only allow up to 8 (VDD GND x3).




Considerations
If you really want chainable interupts, connection then has a polarity, if not the bus is sort of omnidorectoinal
Optional filter circuits for each oncoder?  This would improve 
Instead of an encoder, We can allow 2x switches or buttons.
Form factor that fits with eurorack standards.
The Eurorack format calls for modules of 128.5mm (slightly over 5") height. Horizontal width is measured in "horizontal pitch", where 1 HP = 5.08mm (exactly 0.2"). 


Driecotry structure:

cad
doc
firmware
hardware
production
simulation






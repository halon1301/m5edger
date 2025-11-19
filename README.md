Some Ideas:
- going to take the pressure and perform a rolling average over it to smoot out the data, however, the window needs to be determined
- there needs to be a peak detection mechanism, otherwise the whole point of this is lost
- This really will need some kind of threading to keep an event loop separate from the "system" code.  Probably going to use FreeRTOS.  First I want to get *something* that works

Hardware:
motor is something?

Using https://github.com/night-howler/protogasm/ as my inspiration for the basics of the detection algorithm
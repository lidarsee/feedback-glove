# lidarsee v2 Feedback Glove


![FeedbackGlove](docs/images/feedbackGlove.jpg)

![FeedbackGloveHardware](docs/images/plainHardware.jpg)

To control the Glove you can simply send a UDP packed at the specified port. 

|The library uses a simple ASCII-protocoll to transfer data. 

| Name | : | Value |\r\n|

The UDP packed contains for example to set vibrationmotor2 to a PWM value of 0:
Vibramotor2:0<\r><\n>

PWM range is from 0 to 1023

Or use for testing the GUI 
![USAI_GUI](docs/images/USAI_GUI.jpg)
![USAI_GUI_config](docs/images/USAI_GUI_config.jpg)


#To DO:
- The power consumption of the vibration motors is quite high, additional capacitors are recomended or limiting the overall power with a software limit. 
- Connect the motors directly to the battery 


License

Hardware License: Creative Commons CC0 https://creativecommons.org/publicdomain/zero/1.0/legalcode

Software parts are licensed under MIT License
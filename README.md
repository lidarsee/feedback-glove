# lidarsee v2 Feedback Glove


![FeedbackGlove](docs/images/feedbackGlove.jpg)

![FeedbackGloveHardware](docs/images/plainHardware.jpg)

To control the Glove you can simply send a UDP packed at the specified port. 

|The library uses a simple ASCII-protocoll to transfer data. 

| Name | : | Value |\r\n|

The UDP packed contains an ASCII string to set vibrationmotor2 to a PWM value of 0:
```
Vibramotor2:0<\r><\n>
```
to Value 123:
```
Vibramotor2:123<\r><\n>
```
Multiple are also possible
```
Vibramotor1:0<\r><\n>
Vibramotor2:123<\r><\n>
Vibramotor3:456<\r><\n>
Vibramotor4:10<\r><\n>
Vibramotor5:1023<\r><\n>
```

PWM range is from 0 to 1023

Or use for testing the GUI 
![USAI_GUI](docs/images/USAI_GUI.jpg)
![USAI_GUI_config](docs/images/USAI_GUI_config.jpg)


#To DO:
- The power consumption of the vibration motors is quite high, additional capacitors are recomended or limiting the overall power with a software limit. 
- Connect the motors directly to the battery 

The Library and the GUI is under GPL 3.0 available at:

- https://github.com/4ndreas/USAI
- https://github.com/4ndreas/USAI_GUI

License

Hardware License: Creative Commons CC0 https://creativecommons.org/publicdomain/zero/1.0/legalcode

Software parts are licensed under MIT License
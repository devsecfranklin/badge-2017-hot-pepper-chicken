# hot pepper chicken

![chx](https://github.com/DEAD10C5/badge-2017-hot-pepper-chicken/blob/main/images/hot_pepper_chicken.jpg)

## Parts

[Pimoroni Blinkt](https://www.sparkfun.com/products/14038)
[NodeMCU Lua ESP8266 ESP-12E](https://www.ebay.com/i/192164536182)
[SSD1306 OLED i2c](https://www.aliexpress.com/item/Free-shipping-Yellow-blue-double-color-128X64-OLED-LCD-LED-Display-Module-For-Arduino-0-96/32233342471.html)

## Wiring

Use [a guide like this to wire OLED](http://www.instructables.com/id/Monochrome-096-i2c-OLED-display-with-arduino-SSD13/)

| ESP8266 pin | OLED pin | 
| --- | --- | 
| D2 | SDA | 
| D1 | SCK | 
| 3.3V | VDD | 
| GND | GND | 

Use [this diagram for Blinkt wiring](https://pinout.xyz/pinout/blinkt)

| ESP8266 pin | Blinkt Pin |
| --- | --- | 
| D7 | 16  |
| D8 |  18 | 
| 3.3V | 2 |
| GND | 6 | 

##  Use latest IDE

[Download the latest Arduino IDE](https://www.arduino.cc/en/Main/Software) or you will become very sad. 

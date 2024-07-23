 # AM2320 library (Raspberry Pico)

 Library for obtaining humidity/temperature data from an AM2320 sensor.

 ## Usage

 ```c
 read_sensor(&temperature, &humidity);
 ```

 Read the docstring for more information.

 ## Caveats

 - Do not try to read data at more than 13.3 Hz
 - Use a pull-up resistor, do not rely on the internal pull-ups alone
 - Set your I2C baudrate to low speed (100 KHz)

 ## Example

 In `examples/main.c`

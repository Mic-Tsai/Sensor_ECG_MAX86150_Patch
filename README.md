![*Sensor_MAX86150*](https://github.com/Mic-Tsai/Sensor_ECG_PPG_MAX86150_Patch/blob/main/res/Sensor_ECG_PPG_MAX86150_Patch-1.png)
# Sensor_ECG_PPG_MAX86150 | Patch

[![Donate](https://img.shields.io/badge/paypal-donate-yellow.svg)](https://paypal.me/mictsai?locale.x=zh_TW)

Arduino based sensor learning project. This project is further application from Health_Sensor_ecg_ppg_max86150 dev-board, plotting the ECG curve which used Processing on your computer.

 - Bias Cancellation | Store raw data in time, when new data coming that bias level will calculate as hysteresis filter.

 - Heart Rate Detect | Check windows will output the BPM results (ECG).


This board also support WiFi transmission via ESPNOW (ESP8266 Broadcast), and need power by battery. You need 2x esp8266 board.

1) Read receiver esp8266's mac address.
2) Fill it into the transmitter sketch. "ECG_ESP8266_MAX86150_V6"


** **A Known Issue** **

Sampling rate from MAX86150 set as 200sps, but ESP8266's multiplex with ESP-NOW and sensor hub reading task will low down the output sample rate to ~150sps. When you measuring your ECG in real-time plot may show the missing R-R interval. (R-peak missing!) Don't worry, it just the lower sample  caused.


```
Arduino tool kit, and require the following material:
- MCU: ESP8266 
- Sensor: MAX86150
```
##

For coding example, you need the following library:

* [protocentral_max86150_ecg_ppg](https://github.com/Protocentral/protocentral_max86150_ecg_ppg)

## 

Any question or need technical support:

* Contact me via mail (xbcke12345@gmail.com)

   [![Donate](https://img.shields.io/badge/paypal-donate-yellow.svg)](https://paypal.me/mictsai?locale.x=zh_TW)


## 
![*Sensor_MAX86150*](https://github.com/Mic-Tsai/Sensor_ECG_PPG_MAX86150_Patch/blob/main/res/Sensor_ECG_PPG_MAX86150_Patch-2.png)
![*Sensor_MAX86150*](https://github.com/Mic-Tsai/Sensor_ECG_PPG_MAX86150_Patch/blob/main/res/Sensor_ECG_PPG_MAX86150_Patch-3.png)
![*Sensor_MAX86150*](https://github.com/Mic-Tsai/Sensor_ECG_PPG_MAX86150_Patch/blob/main/res/Sensor_ECG_PPG_MAX86150_Patch-4.png)
![*Sensor_MAX86150*](https://github.com/Mic-Tsai/Sensor_ECG_PPG_MAX86150_Patch/blob/main/res/Sensor_ECG_PPG_MAX86150_Patch-5.png)
![*Sensor_MAX86150*](https://github.com/Mic-Tsai/Sensor_ECG_PPG_MAX86150_Patch/blob/main/res/Sensor_ECG_PPG_MAX86150_Patch-6.png)
![*Sensor_MAX86150*](https://github.com/Mic-Tsai/Sensor_ECG_PPG_MAX86150_Patch/blob/main/res/Sensor_ECG_PPG_MAX86150_Patch-7.png)
![*Sensor_MAX86150*](https://github.com/Mic-Tsai/Sensor_ECG_PPG_MAX86150_Patch/blob/main/res/Sensor_ECG_PPG_MAX86150_Patch-8.png)
![*Sensor_MAX86150*](https://github.com/Mic-Tsai/Sensor_ECG_PPG_MAX86150_Patch/blob/main/res/Sensor_ECG_PPG_MAX86150_Patch-9.png)
![*Sensor_MAX86150*](https://github.com/Mic-Tsai/Sensor_ECG_PPG_MAX86150_Patch/blob/main/res/Sensor_ECG_PPG_MAX86150_Patch-10.png)
![*Sensor_MAX86150*](https://github.com/Mic-Tsai/Sensor_ECG_PPG_MAX86150_Patch/blob/main/res/Sensor_ECG_PPG_MAX86150_Patch-11.png)
![*Sensor_MAX86150*](https://github.com/Mic-Tsai/Sensor_ECG_PPG_MAX86150_Patch/blob/main/res/Sensor_ECG_PPG_MAX86150_Patch-12.png)
## 


>### License Information
>>This product is open source! Both, our hardware and software are open source and licensed under the following:
>>#### Hardware
>>>All hardware is released under [Creative Commons Share-alike 4.0 International](http://creativecommons.org/licenses/by-sa/4.0/)
>>#### Software 
>>>All software is released under the MIT License [http://opensource.org/licenses/MIT](http://opensource.org/licenses/MIT)
>>#### Documentation
>>>The documentation on this page is released under [Creative Commons Share-alike 4.0 International](http://creativecommons.org/licenses/by-sa/4.0/)

// ###################################################################################
// # Project: ECG Health Sensor
// # Engineer:  Mic.Tsai
// # Date:  31 July 2020
// # Objective: Dev.board
// # Usage: ESP8266
// # Modified: Mode Select with filter and PPG
// ###################################################################################

// ########################
#include <ESP8266WiFi.h>
#include <espnow.h>
// ########################

#include <Wire.h>
#include "max86150.h"

byte TestledBrightness = 1; //Options: 0=Off to 255=50mA //0x1F

// # ECG sensor
int16_t ecgsigned16;
int16_t redunsigned16;
uint16_t ppgunsigned16;

MAX86150 max86150Sensor;

int Filter_Value;
int Filter_Value2;
int Value;
int Value2;

// ########################


// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xF4, 0xCF, 0xA2, 0x6D, 0x3B, 0xA1};
//uint8_t broadcastAddress[] = {0x5C, 0xCF, 0x7F, 0xB9, 0x8A, 0x6A};
// uint8_t broadcastAddress[] = {0xF4, 0xCF, 0xA2, 0x6D, 0x2E, 0xDF};
// uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int a;
  int b;
  int c;
  int d;
/*
  char a[32];
  int b;
  float c;
  String d;
  bool e;
*/
  
} struct_message;

// Create a struct_message called myData
struct_message myData;

unsigned long lastTime = 0;  
unsigned long timerDelay = 1;  // send readings timer

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

// ########################

void setup()
{

//~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Wire.begin(0, 2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU *////
//~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Serial.begin(38400);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~
    WiFi.mode( WIFI_OFF );
    WiFi.forceSleepBegin();
    Serial.println("WiFi is down");
//~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Serial.println("MAX86150 Basic Readings Example");

    // Initialize sensor
    if (max86150Sensor.begin(Wire, I2C_SPEED_FAST) == false)
    {
        Serial.println("MAX86150 was not found. Please check wiring/power. ");
        while (1);
    }

    //Setup to sense a nice looking saw tooth on the plotter
    byte ledBrightness = 0; //Options: 0=Off to 255=50mA
    byte sampleAverage = 1; //Options: 1, 2, 4, 8, 16, 32
    byte ledMode = 1; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
    int sampleRate = 50; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth = 69; //Options: 69, 118, 215, 411
    int adcRange = 2048; //Options: 2048, 4096, 8192, 16384
  
    max86150Sensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
//    max86150Sensor.writeRegister8(0x5E,0x11,0x00);
//    max86150Sensor.writeRegister8(0x5E,0x12,0x00);


// ########################

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

// ########################


}

void loop()
{
  
    ecgsigned16 = (int16_t) (max86150Sensor.getECG()>>1);
 //   ecgsigned16 = (int16_t) (max86150Sensor.getECG()>>2);
    Filter_Value = Filter();


// ########################

    // Set values to send
    myData.a = ecgsigned16;
    myData.b = Filter_Value;    
    
    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  
// ########################


    Serial.print(millis());
    Serial.print(",");
    Serial.print(ecgsigned16 - Filter_Value);
    Serial.print(",");
    Serial.print(ppgunsigned16 - Filter_Value2);
    Serial.println(",");

}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>> Get ECG Data >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void ECG()
{ 
      ecgsigned16 = (int16_t) (max86150Sensor.getECG()>>2);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>> Get ECG Data >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>> Get PPG Data >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void PPG()
{ 
     ppgunsigned16 = (uint16_t) (max86150Sensor.getFIFORed()>>2);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>> Get PPG Data >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void ECGFilter()
{ 
    Filter_Value = Filter();
    Serial.println(ecgsigned16 - Filter_Value); 
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// ecg data in
int Get_AD() {
  return ecgsigned16;
}

// 一階滯後濾波法
#define FILTER_A 0.01
int Filter() {
  int NewValue;
  NewValue = Get_AD();
  Value = (int)((float)NewValue * FILTER_A + (1.0 - FILTER_A) * (float)Value);
  return Value;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>> PPG  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// ecg data in
int Get_AD2() {
  return ppgunsigned16;
}

// 一階滯後濾波法
#define FILTER_A2 0.01
int Filter2() {
  int NewValue2;
  NewValue2 = Get_AD2();
  Value2 = (int)((float)NewValue2 * FILTER_A2 + (1.0 - FILTER_A2) * (float)Value2);
  return Value2;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

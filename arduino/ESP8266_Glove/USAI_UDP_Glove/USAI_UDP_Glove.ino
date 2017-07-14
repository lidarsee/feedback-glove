/*This is an example of the EasyTransfer Library 2way communications.

The sketch is for the Arduino with a potentiometer attached to analog pin 0.

This other Arduino has the servo attached to pin 9.
Both have a putton attached to pin 12 and output a status using the LED on pin 13.

The idea is each arduino will read the status of the button attached to it, and send it
to the other Arduino, which will toggle it's LED based on the others button. The button
should connect pin 12 to ground when pushed.

And the Arduino with the potentiometer will send it's value to the one with the servo.
The servo will move to the position based on the potentiometer.
*/


//#include <Ethernet.h>
//#include <EthernetUdp.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUDP.h>


#include "usai.h"

//EthernetUDP Udp;
WiFiUDP Udp;

// wifi connection variables
const char *ssid =	"Luftnetz_2GHz";
const char *pass =	"achtung!warnschuss!";

const char *ssidAP =  "FZI_Lidarsee";
const char *passAP =  "12345678";

boolean wifiConnected = false;
boolean udpConnected = false;

// All in WeMos D1 mini Pro Dx Notation
// LED D4

// Motor1 D1
// Motor1 D2
// Motor1 D3
// Motor1 D5
// Motor1 D6
// Motor1 D7


const int LEDPIN = D4;
const int Motor1Pin = D1;
const int Motor2Pin = D2;
const int Motor3Pin = D3;

const int Motor4Pin = D5;
const int Motor5Pin = D6;
const int Motor6Pin = D7;

int Vibramotor1 = 0;
int Vibramotor2 = 0;
int Vibramotor3 = 0;
int Vibramotor4 = 0;
int Vibramotor5 = 0;
int Vibramotor6 = 0;

int BatteryVoltage = 0;

int TestValue = 0;

//start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
usai Sensors(&Udp);

uValue V1("Vibramotor1",Control,&Vibramotor1);
uValue V2("Vibramotor2",Control,&Vibramotor2);
uValue V3("Vibramotor3",Control,&Vibramotor3);
uValue V4("Vibramotor4",Control,&Vibramotor4);
uValue V5("Vibramotor5",Control,&Vibramotor5);
uValue V6("Vibramotor6",Control,&Vibramotor6);

uValue V7("BatteryVoltage",Config,&BatteryVoltage);


unsigned int localPort = 8888;      // local port to listen on

void setup(){

  pinMode(A0, INPUT);
  pinMode(Motor1Pin, OUTPUT);
  pinMode(Motor2Pin, OUTPUT);
  pinMode(Motor3Pin, OUTPUT);
  pinMode(Motor4Pin, OUTPUT);
  pinMode(Motor5Pin, OUTPUT);
  pinMode(Motor6Pin, OUTPUT);

  digitalWrite(Motor1Pin, LOW);
  digitalWrite(Motor2Pin, LOW);
  digitalWrite(Motor3Pin, LOW);
  digitalWrite(Motor4Pin, LOW);
  digitalWrite(Motor5Pin, LOW);
  digitalWrite(Motor6Pin, LOW);

	Serial.begin(115200);
	Serial.println("");
	Serial.println("");
	Serial.println("StartWifi");

	
	// Initialise wifi connection
//  WiFi.begin(ssid, pass);
//  int timeout = 0;
//	while (WiFi.status() != WL_CONNECTED) {
//		delay(500);
//		Serial.print(".");
//    timeout++;
//    if (timeout > 50)
//    {
//      delay(100);
//      break;
//    }
//	}

  IPAddress myIP = WiFi.localIP();
//
//  // if connection fails open soft AP
//  if(WiFi.status() != WL_CONNECTED)
//  {
    WiFi.mode(WIFI_AP);
    Serial.println("No WiFi found open SoftAP");
    Serial.print("SSID:");Serial.println(ssidAP);
    Serial.print("Pass:");Serial.println(passAP);
    WiFi.softAP(ssidAP, passAP);
    Serial.print("AP IP address: ");
    myIP = WiFi.softAPIP();
    Serial.println(myIP);
//  }

	Serial.println("");
	Udp.begin(localPort);
	Serial.printf("Now listening at IP %s, UDP port %d\n", myIP.toString().c_str(), localPort);

  delay(100);

	Sensors.begin();
	Sensors.addValue(&V1);
	Sensors.addValue(&V2);
	//Sensors.addValue(&V3);  // not used
	Sensors.addValue(&V4);
  Sensors.addValue(&V5);
  Sensors.addValue(&V6);
  Sensors.addValue(&V7);  // Battery Voltage
  
  Sensors.sendConfig();
}

void loop(){
	
BatteryVoltage = analogRead(A0);
Sensors.processSensorData();

analogWrite(Motor1Pin, Vibramotor1);
analogWrite(Motor2Pin, Vibramotor2);
//analogWrite(Motor3Pin, Vibramotor3);
analogWrite(Motor4Pin, Vibramotor4);
analogWrite(Motor5Pin, Vibramotor5);
analogWrite(Motor6Pin, Vibramotor6);

delay(10);
}

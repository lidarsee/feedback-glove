/* This is an example of the Universal Sensor Actor Library
 * It's designed for a WeMos d1 mini pro Module. 
 * Select "WeMos D1 R2 & Mini" as board in the tools menue
 * 
 * This example connects to a local acces point and waits for data.
 * You can connect to the board with the USAI GUI from
 * 
 * 
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUDP.h>


#include "usai.h"


WiFiUDP Udp;

// wifi connection variables
//const char *ssid =	"YourSSIDHere";
//const char *pass =	"YourPSKHere";

const char *ssid =  "Luftnetz_2GHz";
const char *pass =  "achtung!warnschuss!";

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
//for network use &Udp
usai Sensors(&Udp);
unsigned int localPort = 8888;      // local port to listen on


uValue V1("Vibramotor1",Control,&Vibramotor1);
uValue V2("Vibramotor2",Control,&Vibramotor2);
uValue V3("Vibramotor3",Control,&Vibramotor3);
uValue V4("Vibramotor4",Control,&Vibramotor4);
uValue V5("Vibramotor5",Control,&Vibramotor5);
uValue V6("Vibramotor6",Control,&Vibramotor6);

uValue V7("BatteryVoltage",Config,&BatteryVoltage);

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
	WiFi.begin(ssid, pass);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
  Serial.println ("");
  Serial.println ("Wifi Connected");
  
  IPAddress myIP = WiFi.localIP();
  Serial.println(myIP);
	Serial.println("");
	Udp.begin(localPort);
	Serial.printf("Now listening at IP %s, UDP port %d\n", myIP.toString(), localPort);

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

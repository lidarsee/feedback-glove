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

#include "usai.h"   // download from https://github.com/4ndreas/USAI
// A GUI for interacting can be downloaded from https://github.com/4ndreas/USAI_GUI

WiFiUDP Udp;

// wifi connection variables
const char *ssid =	"YourSSIDHere";
const char *pass =	"YourPSKHere";

boolean wifiConnected = false;
boolean udpConnected = false;

const char *ssidAP =  "FZI_Lidarsee";
const char *passAP =  "12345678";

// All in WeMos D1 mini Pro Dx Notation
const int LEDPIN = D4;

const int Motor2Pin = D1; // Zeigefinger
const int Motor3Pin = D2; // Mittelfinger
const int Motor6Pin = D3; // not used
const int Motor4Pin = D6; // Ringfinger
const int Motor5Pin = D5; // Kleinerfinger
const int Motor1Pin = D7; // Daumen

int Vibramotor1 = 0;
int Vibramotor2 = 0;
int Vibramotor3 = 0;
int Vibramotor4 = 0;
int Vibramotor5 = 0;
int Vibramotor6 = 0;

int BatteryDigit = 0;
const float BatteryBittoV = 0.00679; //  V/bit
float BatteryVoltage = 0;

int MasterValue = 500;

boolean Finger1 = false;
boolean Finger2 = false;
boolean Finger3 = false;
boolean Finger4 = false;
boolean Finger5 = false;

//start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
//for network use &Udp
usai Sensors(&Udp);
unsigned int localPort = 8888;      // local port to listen on


uValue V1("Vibramotor1",Control,&Vibramotor1);
uValue V2("Vibramotor2",Control,&Vibramotor2);
uValue V3("Vibramotor3",Control,&Vibramotor3);
uValue V4("Vibramotor4",Control,&Vibramotor4);
uValue V5("Vibramotor5",Control,&Vibramotor5);
//uValue V6("Vibramotor6",Control,&Vibramotor6);

uValue V7("BatteryVoltageBit",Config,&BatteryDigit);
uValue V8("BatteryVoltage",Config,&BatteryVoltage);

uValue V11("Master",Control,&MasterValue);

uValue V12("Daumen",Control,&Finger1);
uValue V13("Zeigefinger",Control,&Finger2);
uValue V14("Mittelfinger",Control,&Finger3);
uValue V15("Ringfinger",Control,&Finger4);
uValue V16("Kleinerfinger",Control,&Finger5);

void setup(){

  pinMode(A0, INPUT);
  pinMode(LEDPIN, OUTPUT);
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

  Serial.println("Try to connect to:");
  Serial.print("SSID:");Serial.println(ssid);
  Serial.print("Pass:");Serial.println(pass);
  Serial.println("Try for 30 secondes than open soft AP");

  int timeoutCounter = 0;
  // Initialise wifi connection
	WiFi.begin(ssid, pass);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
    wifiConnected = true;
    timeoutCounter++;
    if(timeoutCounter > 60)
    {
      wifiConnected = false;
      break;
    }
    
	}
  
  Serial.println ("");
  IPAddress myIP;
  if(wifiConnected)
  {
    Serial.println ("Wifi Connected");
    myIP = WiFi.localIP();
    Serial.print("local IP is: "); 
  }
  else  // open soft AP 
  {
    WiFi.mode(WIFI_AP);
    Serial.println("No WiFi found open SoftAP");
    Serial.print("SSID:");Serial.println(ssidAP);
    Serial.print("Pass:");Serial.println(passAP);
    WiFi.softAP(ssidAP, passAP);
    Serial.print("AP IP address: ");
    myIP = WiFi.softAPIP();    
  }
  
  Udp.begin(localPort);
	
  Serial.println(myIP);
  Serial.print("UDP USAI port is: ");
  Serial.println(localPort);
  Serial.println("");
  delay(100);

	Sensors.begin();
	Sensors.addValue(&V1);
	Sensors.addValue(&V2);
	Sensors.addValue(&V3);
	Sensors.addValue(&V4);
  Sensors.addValue(&V5);
  //Sensors.addValue(&V6); // not used
  Sensors.addValue(&V7);  // Battery Voltage in Bit
  Sensors.addValue(&V8);  // Battery Voltage in V

  Sensors.addValue(&V11); // master control 
  Sensors.addValue(&V12);
  Sensors.addValue(&V13);
  Sensors.addValue(&V14);
  Sensors.addValue(&V15);
  Sensors.addValue(&V16);
  
  Sensors.sendConfig();
}


bool ledtoggle = false;
int ledcounter = 0;
int ledBlinkDelay = 100;
void loop(){
	
// get Battery Voltage
BatteryDigit = analogRead(A0);
BatteryVoltage =  BatteryDigit * BatteryBittoV;

// to do shutdown if Battery is to low

Sensors.processSensorData();

if(BatteryVoltage < 3.2)
{
  // shutdown
  Vibramotor1 = 0;
  Vibramotor2 = 0;
  Vibramotor3 = 0;
  Vibramotor4 = 0;
  Vibramotor5 = 0;
  Vibramotor6 = 0;
  MasterValue = 0;

  ledBlinkDelay = 30;
}

SetMotors();



delay(10);

ledcounter++;
if(ledcounter > ledBlinkDelay)
{
  ledcounter = 0;
  if(ledtoggle)
  {
    digitalWrite(LEDPIN, HIGH);
    ledtoggle = false;
  }
  else
  {
    digitalWrite(LEDPIN, LOW);
    ledtoggle = true;
  }
}

} // end Loop

void SetMotors()
{
if(Finger1)
{
  if( Vibramotor1 >0)
  {
    analogWrite(Motor1Pin, Vibramotor1);    
  }
  else
  {
    analogWrite(Motor1Pin, MasterValue);
  }
}
else
{
  analogWrite(Motor1Pin, 0);
}

if(Finger2)
{
  if( Vibramotor2 >0)
  {
    analogWrite(Motor2Pin, Vibramotor2);    
  }
  else
  {
    analogWrite(Motor2Pin, MasterValue);
  }
}
else
{
  analogWrite(Motor2Pin, 0);
}

if(Finger3)
{
  if( Vibramotor3 >0)
  {
    analogWrite(Motor3Pin, Vibramotor3);    
  }
  else
  {
    analogWrite(Motor3Pin, MasterValue);
  }
}
else
{
  analogWrite(Motor3Pin, 0);
}

if(Finger4)
{
  if( Vibramotor4 >0)
  {
    analogWrite(Motor4Pin, Vibramotor4);    
  }
  else
  {
    analogWrite(Motor4Pin, MasterValue);
  }
}
else
{
  analogWrite(Motor4Pin, 0);
}

if(Finger5)
{
  if( Vibramotor5 >0)
  {
    analogWrite(Motor5Pin, Vibramotor5);    
  }
  else
  {
    analogWrite(Motor5Pin, MasterValue);
  }
}
else
{
  analogWrite(Motor5Pin, 0);
}  
}


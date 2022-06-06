#include <AWS_IOT.h>
#include <WiFi.h>
#include <ESP32_Servo.h>
#include <Arduino_JSON.h>

Servo servo1;
AWS_IOT MOTORIOT;
const char* ssid = "SK_WiFi67AD";
const char* password = "1102000710";
char HOST_ADDRESS[]= "acj2gilk7nyok-ats.iot.ap-northeast-2.amazonaws.com";
char CLIENT_ID[]= "KAU_MOTOR";
char sTOPIC_NAME[]= "ESP32/Doorlock"; // subscribe topic name
char pTOPIC_NAME[]= "esp32/doorsensor"; // publish topic name
int status = WL_IDLE_STATUS;
int msgCount=0,msgReceived = 0;
char payload[512];
char rcvdPayload[512];
unsigned long preMil = 0; 
const long intMil = 5000;
static const int servoPin = 33; 

#define sensor 33
#define Door_sensor 25


void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
  strncpy(rcvdPayload,payLoad,payloadLen);
  rcvdPayload[payloadLen] = 0;
  msgReceived = 1;
}

void MOTOR(int door){ // 1은 열림 0은 닫힘
  if(door == 1){
    servo1.write(135);
    while(digitalRead(Door_sensor)==0);
    servo1.write(90);
  }
  if(door == 0){
    servo1.write(45);
    delay(200);
    servo1.write(90);
  }
}

void setup() {
  Serial.begin(115200);
  servo1.attach(servoPin);
  Serial.print("WIFI status = ");
  Serial.println(WiFi.getMode());
  WiFi.disconnect(true);
  delay(1000);
  WiFi.mode(WIFI_STA);
  delay(1000);
  Serial.print("WIFI status = ");
  Serial.println(WiFi.getMode()); //++choi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to wifi");
  if(MOTORIOT.connect(HOST_ADDRESS,CLIENT_ID)== 0) {
    Serial.println("Connected to AWS");
    delay(1000);
    if(0==MOTORIOT.subscribe(sTOPIC_NAME,mySubCallBackHandler)) {
    Serial.println("Subscribe Successfull");
  }
  else {
    Serial.println("Subscribe Failed, Check the Thing Name and Certificates");
    while(1);
    }
  }
else {
    Serial.println("AWS connection failed, Check the HOST Address");
    while(1);
  }
// initialize the pushbutton pin as an input
  delay(2000);
  pinMode(sensor, INPUT);
  pinMode(Door_sensor, INPUT);
}

void loop() {
  if(msgReceived == 1)
  {
    msgReceived = 0;
// Parse JSON
    JSONVar myObj = JSON.parse(rcvdPayload);
    JSONVar state = myObj["state"];
    String doormotor = (const char*) state["doormotor"]; // esp32/doorset 
    if (doormotor == "OPEN"){MOTOR(1);}
    if (doormotor == "CLOSE"){MOTOR(0);}
    Serial.println(doormotor);
  }
  if ((millis() - preMil) > intMil) {
    preMil = millis();
    JSONVar state;
    state["door_sensor"] = digitalRead(Door_sensor); //esp32/doorsensor
    JSON.stringify(state).toCharArray(payload, 512);
    
    if (MOTORIOT.publish(pTOPIC_NAME, payload) == 0) {
      Serial.print("Publish Message: ");
      Serial.println(payload);
    }
    else { Serial.println("Oops, Publish Failed."); }
  }
}

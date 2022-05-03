#include <Adafruit_VL53L0X.h>

const int ledPin = 13;  // set the test LED output pin
const int relayPin = 4; // set the logic switch output pin to relay
const int potPin = A9;  // set the potentiometer input pin

int dist = 500; // distance from sensor
int pot = 0; // raw value from potentiometer to change the thershold
int threshold = 0; // initial threshold in millimeters

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  pinMode(ledPin, OUTPUT); // test LED
  pinMode(relayPin, OUTPUT); // logic switch to relay: LOW = unmute, HIGH = mute
  pinMode(potPin, INPUT); // 100K potentiometer to set the threshold

  digitalWrite(ledPin, LOW); // reset the test LED
  digitalWrite(relayPin, LOW); // reset relay to unmute

  Serial.begin(9600);

    // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  lox.begin();


}

void loop() {
  
  pot = analogRead(potPin); // reads the potentiometer raw value (0 - 1024)

  Serial.println(pot);
  
  threshold = map(pot, 0, 1024, 50, 1200); // maps the pot value to actual distances in mm

  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout! 

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    dist = measure.RangeMilliMeter;

      
    if (dist > threshold)
    {
      digitalWrite(ledPin, HIGH); // test led
      digitalWrite(relayPin, HIGH); // actual logic output pin to relay
      }

    else
    {
      digitalWrite(ledPin, LOW); // test led
      digitalWrite(relayPin, LOW); // actual logic output pin to relay
      }

  }

  else
  {
    digitalWrite(ledPin, HIGH); // test led
    digitalWrite(relayPin, HIGH); // actual logic output pin to relay 
    
    }

  delay(50);
}

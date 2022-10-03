/* I Shawn Barrow, 000332631 certify that this material is my original work and none
other person's work has been used without due acknowledgement. 2022-10-03 **/
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <math.h>

const int oneWireBus = D3;
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);
//Hold the 8 bit address.
uint8_t address[8];

void setup() {
 Serial.begin(115200);
 DS18B20.begin();
 Serial.println();
 Serial.println("DS18B20 Application");

//Check if there is a sensor connected.
 if(DS18B20.getAddress(address, 0)) Serial.print("Found DS18B20 sensor with address:");
 else{
  Serial.println("No DS18B20 temperature sensors are installed!");
  return;
}
//Print each bit of the address
for(int i = 0; i<8; i++){
  Serial.printf("%02X",address[i]);
}
Serial.println();
}
void loop() {
 while (DS18B20.getAddress(address, 0)) {
float fTemp;
 DS18B20.requestTemperatures();
 // fetch the temperature. We only have 1 sensor, so the index is 0.
 fTemp = DS18B20.getTempCByIndex(0);
 int fTempRounded = floor(fTemp);
 String weather;
 switch (fTempRounded) {
  case 0 ... 9:
    weather = "Cold!";
    break;
  case 10 ... 15:
    weather = "Cool.";
    break;
  case 16 ... 25:
    weather = "Perfect.";
    break;
  case 26 ... 30:
    weather = "Warm.";
    break;
  case 31 ... 35:
    weather = "Hot.";
    break;
  case 36 ... 100:
    weather = "Too Hot!";
    break;
 }

 // print the temp to the USB serial monitor
 Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or "+ weather);
 // wait 5s before doing this again
 delay(5000);
 } 
 
}
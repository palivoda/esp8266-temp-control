#include <Arduino.h>
//#include "controller\BasePidCtrl.h"
#include "hardware\HardwarePoC1.h"

DS18B20 ds(PIN_TEMP_FEED);


void setup() {
  Serial.begin(115200);

  // Print number of devices on the bus.
  Serial.print("Devices: ");
  Serial.println(ds.getNumberOfDevices());
  Serial.println();


}

void loop() {

    // Iterate through all devices.
    while(ds.selectNext())
    {
      // Print family name.
      switch(ds.getFamilyCode())
      {
        case MODEL_DS18S20:
          Serial.println("Model: DS18S20");
          break;
        case MODEL_DS1820:
          Serial.println("Model: DS1820");
          break;
        case MODEL_DS18B20:
          Serial.println("Model: DS18B20");
          break;
        default:
          Serial.println("Unrecognized Device");
          break;
      }

      // Print address.
      uint8_t address[8];

      ds.getAddress(address);

      Serial.print("Address:");

      for(uint8_t i = 0; i < 8; i++)
      {
        Serial.print(" ");
        Serial.print(address[i]);
      }

      Serial.println();

      // Print resolution.
      Serial.print("Resolution: ");
      Serial.println(ds.getResolution());

      // Print power mode.
      Serial.print("Power Mode: ");

      if(ds.getPowerMode())
      {
        Serial.println("External");
      }
      else
      {
        Serial.println("Parasite");
      }

      // Print temperature in degrees Celcius and degrees Fahrenheit.
      Serial.print("Temperature: ");
      Serial.print(ds.getTempC());
      Serial.print(" C / ");
      Serial.print(ds.getTempF());
      Serial.println(" F");

      // Print an empty line.
      Serial.println();
    }

    // Wait 10 seconds.
    delay(10000);

}

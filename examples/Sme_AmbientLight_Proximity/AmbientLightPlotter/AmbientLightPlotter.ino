/*
   This example is designed to be used with the Arduino 1.6.6+ IDE Serial Plotter.
   Pass your hand in front of the sensor and you will see the ambient light value change in real time.

   From http://www.st.com/st-web-ui/static/active/en/resource/technical/document/design_tip/DM00118999.pdf
   The VL6180X can measure the incoming ambient light over a wide dynamic range. The
   ALS sensor uses a photopic filter in order to approximate the spectral response of the
   human eye. The raw data output from the ALS is a 16-bit (0 – 65,535) value that is
   proportional to the amount of light within the field of view during the integration time. The
   device has a ±42 degree field of view (FOV).
*/
#include <Wire.h>
#include <VL6180.h>
#include <Arduino.h>

unsigned int ambientLight;
unsigned int pollingInterval = 100; // in milliseconds

// The setup function runs once when you press reset or power the board
void setup() {
  Wire.begin();
  if (!smeAmbient.begin()) { // Flash red light if there is an error initializing the sensor
    flashRGBLed(PIN_LED_RED, 1000);
  }
  else {
    flashRGBLed(PIN_LED_GREEN, 1000);
  }
  SerialUSB.begin(115200);
}

// The loop function runs over and over again forever
void loop() {
  // Dividing by 160 gives us a value from 0 to 65,535 (0 = total dark, 65535 = right next to a light bulb)
  ambientLight = int(smeAmbient.lightPollingRead() / 160);
  SerialUSB.println(ambientLight);
  delay(pollingInterval);
}

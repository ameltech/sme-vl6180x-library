/*
    SmeProximity Library - Proximity.ino

    Demonstrate how to detect the proximity of an object in polling mode.

    And the ends the green led continuously blink.

    created 27 Apr 2015
    by Mik (smkk@axelelettronica.it)

    This example is in the public domain
    https://github.com/ameltech

    VL6180  more information available here:
    http://www.st.com/web/catalog/mmc/FM132/SC626/PF260441?icmp=pf260441_pron_p3609p_sep2014&sc=proximitysensor
*/

#include <Wire.h>

#include <VL6180.h>
#include <Arduino.h>


// the setup function runs once when you press reset or power the board
void setup() {
  Wire.begin();

  if (!smeProximity.begin()) {
    while (1) {
      ; // endless loop due to error on VL6180 initialization
    }
  }

  SerialUSB.begin(115200);

}

// the loop function runs over and over again forever
void loop() {
  char ligth = smeProximity.rangePollingRead();

  if (ligth == 255) {
    SerialUSB.println("Infinity");
  } else {
    SerialUSB.print(ligth, DEC);
    SerialUSB.println(" mm");
  }

  delay(2000);              // wait for 2 seconds

}

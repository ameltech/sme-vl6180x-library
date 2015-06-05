/*
    SmeProximity Library -Proximity

    Demonstrate how to detect the proximity of an object in polling mode.

    And the ends the green led continuously blink. 

    created 27 Apr 2015
    by Mik (smkk@amel-tech.com)

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
	
    // initialize digital pin 13 as an output.
    pinMode(PIN_LED_BLUE, OUTPUT);

    smeProximity.begin();

    SerialUSB.begin(115200);

}

// the loop function runs over and over again forever
void loop() {

    digitalWrite(PIN_LED_BLUE, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);             // wait for a second

    char ligth = smeProximity.rangePollingRead();    

    if (ligth == 255) {
      SerialUSB.println("Infinity");
    } else {
        SerialUSB.print(ligth, DEC);
        SerialUSB.println(" mm");
    }

    digitalWrite(PIN_LED_BLUE, HIGH);   // turn the LED off by making the voltage LOW
    delay(1000);              // wait for a second

}

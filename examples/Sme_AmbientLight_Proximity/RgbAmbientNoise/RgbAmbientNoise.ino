/*
    SmeAmbient Library -Proximity

    Show how many Lux use any part of the RGB Led.

    Consider the light ambient noise

    created 06 May 2015
    by Mik (smkk@amel-tech.com)

    This example is in the public domain
    https://github.com/ameltech

    VL6180  more information available here:
    http://www.st.com/web/catalog/mmc/FM132/SC626/PF260441?icmp=pf260441_pron_p3609p_sep2014&sc=proximitysensor
 */

#include <Wire.h>

#include <VL6180.h>
#include <Arduino.h>

float ambientLight;

// the setup function runs once when you press reset or power the board
void setup() {

    Wire.begin();

    // initialize all RGB pins as an output.
    pinMode(PIN_LED_BLUE, OUTPUT);
    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_GREEN, OUTPUT);

    // switch off all the leds
    digitalWrite(PIN_LED_GREEN, HIGH);
    digitalWrite(PIN_LED_BLUE, HIGH);
    digitalWrite(PIN_LED_RED, HIGH);

    if (!smeAmbient.begin()) {
        while(1){
            ; // endless loop due to error on VL6180 initialization
        }
    }

    SerialUSB.begin(115200);

    if (!SerialUSB) {
        ambientLight = smeAmbient.ligthPollingRead();  // store the noise of the ambient light
        delay(500); //just wait a while
    }

}

// the loop function runs over and over again forever
void loop() {

    SerialUSB.println();
    SerialUSB.print("The noise component is=");
    printDouble(ambientLight, 100);



    digitalWrite(PIN_LED_BLUE, LOW);   // turn the LED ON by making the voltage LOW
    delay(1000);             // wait for a second

    float ligth = smeAmbient.ligthPollingRead();

    SerialUSB.print("The BLUE component is=");
    printDouble(ambientLight-ligth, 100);

    digitalWrite(PIN_LED_BLUE, HIGH);   // turn the LED off by making the voltage HIGH
    delay(1000);              // wait for a second




    digitalWrite(PIN_LED_RED, LOW);   // turn the LED ON by making the voltage LOW
    delay(1000);             // wait for a second

    ligth = smeAmbient.ligthPollingRead();

    SerialUSB.print("The RED component is=");
    printDouble(ambientLight-ligth, 100);

    digitalWrite(PIN_LED_RED, HIGH);   // turn the LED off by making the voltage HIGH
    delay(1000);              // wait for a second




    digitalWrite(PIN_LED_GREEN, LOW);   // turn the LED ON by making the voltage LOW
    delay(1000);             // wait for a second

    ligth = smeAmbient.ligthPollingRead();

    SerialUSB.print("The GREEN component is=");
    printDouble(ambientLight-ligth, 100);

    digitalWrite(PIN_LED_GREEN, HIGH);   // turn the LED off by making the voltage HIGH
    delay(1000);              // wait for a second




    digitalWrite(PIN_LED_BLUE, LOW);   // turn the LED ON by making the voltage LOW
    digitalWrite(PIN_LED_GREEN, LOW);   // turn the LED ON by making the voltage LOW
    digitalWrite(PIN_LED_RED, LOW);   // turn the LED ON by making the voltage LOW
    delay(1000);             // wait for a second

    ligth = smeAmbient.ligthPollingRead();

    SerialUSB.print("The WHITE component is=");
    printDouble(ambientLight-ligth, 100);

    digitalWrite(PIN_LED_BLUE, HIGH);   // turn the LED off by making the voltage HIGH
    digitalWrite(PIN_LED_RED, HIGH);   // turn the LED off by making the voltage HIGH
    digitalWrite(PIN_LED_GREEN, HIGH);   // turn the LED off by making the voltage HIGH
    delay(1000);              // wait for a second

}




void printDouble( double val, unsigned int precision){
    // prints val with number of decimal places determine by precision
    // NOTE: precision is 1 followed by the number of zeros for the desired number of decimal places
    // example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)

    SerialUSB.print (int(val));  //prints the int part
    SerialUSB.print("."); // print the decimal point
    unsigned int frac;
    if(val >= 0)
        frac = (val - int(val)) * precision;
    else
        frac = (int(val)- val ) * precision;
    int frac1 = frac;

    while( frac1 /= 10 )
        precision /= 10;
    precision /= 10;

    while(  precision /= 10)
        SerialUSB.print("0");

    SerialUSB.println(frac,DEC) ;
}

/*
    SmeAmbient Library -Proximity

    Demonstrate how to detect the quantity of lux in a polling mode

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
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  smeAmbient.begin();

  SerialUSB.begin(115200);

}

// the loop function runs over and over again forever
void loop() {

  digitalWrite(13, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);             // wait for a second

  float ligth = smeAmbient.ligthPollingRead();

  printDouble(ligth, 100);

  digitalWrite(13, HIGH);   // turn the LED off by making the voltage LOW
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
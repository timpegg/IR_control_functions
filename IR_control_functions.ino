/* RGB Remote Control
   by: Jim Lindblom
   SparkFun Electronics
   date: October 1, 2013

   This sketch uses Ken Shirriff's *awesome* IRremote library:
       https://github.com/shirriff/Arduino-IRremote

   RGB Remote Control uses a combination of SparkFun's
   IR Remote (https://www.sparkfun.com/products/11759) and an
   IR receiver diode (https://www.sparkfun.com/products/10266) to
   control an RGB LED.

   The IR Remote's power button turns the LED on or off. The A, B,
   and C buttons select a channel (red, green, or blue). The up
   and down arrows increment or decrement the LED brightness on that channel.
   The left and right arrows turn a channel to min or max, and
   circle set it to the middle.

   Hardware setup:
     * The output of an IR Receiver Diode (38 kHz demodulating
       version) should be connected to the Arduino's pin 11.
       * The IR Receiver diode should also be powered off the
         Arduino's 5V and GND rails.
     * A common cathode RGB LED is connected to Arduino's pins
       5, 9, and 6 (red, green, and blue pins).
 */

#include <IRremote.h> // Include the IRremote library

/* Setup constants for SparkFun's IR Remote: */
#define NUM_BUTTONS 9 // The remote has 9 buttons
/* Define the IR remote button codes. We're only using the
   least signinficant two bytes of these codes. Each one
   should actually have 0x10EF in front of it. Find these codes
   by running the IRrecvDump example sketch included with
   the IRremote library.*/
const uint16_t BUTTON_POWER = 0xD827; // i.e. 0x10EFD827
const uint16_t BUTTON_A = 0xF807;
const uint16_t BUTTON_B = 0x7887;
const uint16_t BUTTON_C = 0x58A7;
const uint16_t BUTTON_UP = 0xA05F;
const uint16_t BUTTON_DOWN = 0x00FF;
const uint16_t BUTTON_LEFT = 0x10EF;
const uint16_t BUTTON_RIGHT = 0x807F;
const uint16_t BUTTON_CIRCLE = 0x20DF;

/* Connect the output of the IR receiver diode to pin 11. */
int RECV_PIN = 13;
/* Initialize the irrecv part of the IRremote  library */
IRrecv irrecv(RECV_PIN);
decode_results results; // This will store our IR received codes
uint16_t lastCode = 0; // This keeps track of the last code RX'd

const int LED_STRIP_START_PIN = 1;
const int LED_STRIPS = 8;
const int INITIAL_BRIGHTNESS = 100;
const int BUTTON_DELAY = 500;



void setup()
{
  Serial.begin(9600); // Use serial to debug.
  irrecv.enableIRIn(); // Start the receiver

  for (int currentPin = LED_STRIP_START_PIN;  currentPin < LED_STRIP_START_PIN + LED_STRIPS; currentPin++)
  {  
    pinMode(currentPin, OUTPUT);      
  }
}
// loop() constantly checks for any received IR codes. At the
// end it updates the RGB LED.
void loop()
{
  if (irrecv.decode(&results))
  {
    /* read the RX'd IR into a 16-bit variable: */
    uint16_t resultCode = (results.value & 0xFFFF);

    /* The remote will continue to spit out 0xFFFFFFFF if a
     button is held down. If we get 0xFFFFFFF, let's just
     assume the previously pressed button is being held down */
    if (resultCode == 0xFFFF)
      resultCode = lastCode;
    else
      lastCode = resultCode;

    // This switch statement checks the received IR code against
    // all of the known codes. Each button press produces a
    // serial output, and has an effect on the LED output.


/*
  TODO's
  1) May try to run a power on test with the power button.  Should start all LEDs to show they are working.
  2) Try to setup a dim/brighten function for the leds.
  3) Setup a reset function to go back to all off.
  4) Setup a timed function to cycle through all leds
  5) Setup an all on function.
*/



    switch (resultCode)
    {
      case BUTTON_POWER:
        Serial.println("Power"); // The power button shuts down all the lights -> ALL LIGHTS routine
        delay(BUTTON_DELAY);
        all_lights();
        break;
      case BUTTON_A:
        Serial.println("A");
        delay(BUTTON_DELAY);
        
        break;
      case BUTTON_B:
        Serial.println("B");
        delay(BUTTON_DELAY);

        break;
      case BUTTON_C:
        Serial.println("C");
        delay(BUTTON_DELAY);

        break;
      case BUTTON_UP:
        Serial.println("Up");
        delay(BUTTON_DELAY);
        break;
      case BUTTON_DOWN:
        Serial.println("Down");
        delay(BUTTON_DELAY);
        break;
      case BUTTON_LEFT:
        Serial.println("Left");
        delay(BUTTON_DELAY);
        break;
      case BUTTON_RIGHT:
        Serial.println("Right");
        delay(BUTTON_DELAY);
        break;
      case BUTTON_CIRCLE:
        Serial.println("Circle");
        delay(BUTTON_DELAY);

        break;
      default:
        Serial.print("Unrecognized code received: 0x");
        Serial.println(results.value, HEX);
        break;
    }
    irrecv.resume(); // Receive the next value
  }

}


void all_lights(){
  for (int currentPin = LED_STRIP_START_PIN;  currentPin < LED_STRIP_START_PIN + LED_STRIPS; currentPin++)
  {  
    digitalWrite(thisPin, LOW);      
  }
  
}

// Purpose: To power a temperature sensing circuit with an ATmega328P.
// Reference: http://darcy.rsgc.on.ca/ACES/TEI3M/1920/Tasks.html#standalone
// Author: A. Goldman
// Date: Nov. 23, 2019
// Status: Working
uint8_t voltageReadPin = A0; // Assigns A0 as the analog input reading pin.
uint8_t buttonPin = A1;      // Assigns A1 as the on button reading pin.
uint8_t segmentPins[]{2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // Maps the pins used for bar graph segments.
uint8_t numberOfSegments = 10; // Sets the number of segments being used.
uint16_t voltageReading;       // Where the analog voltage reading is stored.
uint8_t currentSegment = 0;    // A segment value to be worked with.
uint8_t mappedSegment;         // Variable voltage reading is mapped to.

void setup()
{ // Sets the segment pins to be outputs.
    for (currentSegment = 0; currentSegment < numberOfSegments;
         currentSegment++)
    {
        pinMode(segmentPins[currentSegment], OUTPUT);
    }
    pinMode(voltageReadPin, INPUT); // Sets the voltage reading pin as input.
    pinMode(buttonPin, INPUT);      // Sets the on button pin to input.
}

void loop()
{
    while (digitalRead(buttonPin) == LOW)
        ; // While button not pressed, wait.
    while (1)
    {                                                // While true; runs forever.
        voltageReading = analogRead(voltageReadPin); // Reads value on input.
        mappedSegment = map(voltageReading, 0, 1023, numberOfSegments, 0);
        for (currentSegment = 0; currentSegment < numberOfSegments;
             currentSegment++)
        { // Runs for every segment.
            if (currentSegment < mappedSegment)
            {                                                    // If map greater than segment,
                digitalWrite(segmentPins[currentSegment], HIGH); // set it to high.
            }
            if (currentSegment > mappedSegment)
            {                                                   // If map lesser than segment,
                digitalWrite(segmentPins[currentSegment], LOW); // set it to low.
            }
        }
    }
}

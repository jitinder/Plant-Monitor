/*
   Arduino Project Source Code - Arduino IDE
   By: Sidak Pasricha
   Purpose: Takes input from the Thermistor and the Light Dependent Resistor
            Outputs an estimate of the surrounding temperature in degrees Celsius and the value obtained from the LDR
            Switches on the LED circuit if the light is lower than a particular threshold.
   Application: Intended for maintaining a plant:
                The LED circuit switches on in case there is not enough light to prevent any harm to the plant growth.
                Outputs allow the creation of graphs (using Processing) to allow monitoring of plant conditions.

   Please See Processing Source Code for more
*/
#include <math.h>

const int LEDport = 13;

void setup() {
  Serial.begin(9600); //Set the Serial port at 9600 baud rate
  pinMode(LEDport, OUTPUT); //Setting LED connection as Output
}

//Use the Steinhart-Hart equation to convert to degrees C
double getTemperature(int rawADC) {
  /* Taken from the Arduino Sample Codes
      Courtesy of Professor G. Roberts */
  rawADC -= 200; // Modify the input value to calibrate the temperature.
  double temp;
  temp = log(((10240000 / rawADC) - 10000));
  temp = 1 / (0.001129148 +
              (0.000234125 + (0.0000000876741 * temp * temp )) * temp );
  return temp - 273.15; // Convert Kelvin to Celsius
}

void needExtraLight(int lightInput) {
  /* Checks if the light reaching the plant is sufficient for its growth
      The Threshold, "550", was determined for the aloe plant in my room.
      The amount of light which shines on it on a daily basis was around 580, therefore, the threshold was set to 550
  */
  if (lightInput < 550) { //Threshold for Lowest Light for Plant
    digitalWrite(LEDport, HIGH); //Switches on Lights if surrounding light is low
  } else {
    digitalWrite(LEDport, LOW); //Switches off Lights if surrounding light is good enough
  }
}

void loop() {
  int tempInput, lightInput;
  double temperature;
  lightInput = analogRead(A0); //Read the Value from the LDR
  tempInput = analogRead(A1); //Read the Value from the Thermistor
  temperature = getTemperature(tempInput);

  /* Output */
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(lightInput);

  needExtraLight(lightInput);

  delay(500); //Frequency of data collection
}


#include <math.h>
#define ThermistorPIN 0                 // Analog Pin 0
int analogPin= 0;
int raw= 0;
float vcc = 5;                       // only used for display purposes, if used
                                        // set to the measured Vcc.
float pad = 1000;                       // balance/pad resistor value, set this to
                                        // the measured resistance of your pad resistor
float thermr = 1000;                   // thermistor nominal resistance
float buffer= 0;
float Vout= 0;
float R2= 0;
float Thermistor(int RawADC) {
  raw= analogRead(analogPin);
if(raw) 
{
buffer= raw * vcc;
Vout= (buffer)/1023.0;
buffer= (vcc/Vout) -1;
R2= pad * buffer;}
  float Temp;  // Dual-Purpose variable to save space.
  Temp = log(R2); // Saving the Log(resistance) so not to calculate  it 4 times later
  Temp = 1 / (0.001358918743 + (0.0002628847468 * Temp) + (0.00000001870872475 * Temp * Temp * Temp));
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius                      

  Serial.print(R2);
  Serial.print(" , ");
  return Temp;                                      // Return the Temperature
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float temp;
  temp=Thermistor(analogRead(ThermistorPIN));       // read ADC and  convert it to Celsius
  //Serial.print("Celsius: "); 
  Serial.println(temp,1);                             // display Celsius                                   
  delay(2000);                                      // Delay a bit... 
}


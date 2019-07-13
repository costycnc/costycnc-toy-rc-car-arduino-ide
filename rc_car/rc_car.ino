/*Data Format
W2 W2 W2 W2 (n) x W1 W2 W2 W2 W2 (n) x W1 W2 W2 W2 W2
Number of Function Codes (n) W1 Function Key Decode Result
4 End Code
10 Forward Forward
16 Forward & Turbo Forward
22 Turbo Turbo
28 Turbo & Forward & Left Forward & Left
34 Turbo & Forward & Right Forward & Right
40 Backward Backward
46 Backward & Right Backward & Right
52 Backward & Left Backward & Left
58 Left Left
64 Right Right
*/

void setup()
{
 pinMode(2, OUTPUT);
}

void loop()
{
   delay(1000); 
    for(int i=0; i<=30; i++) // This starts the communication 4 W2 pulses 1KHz 75% duty cycle 
 {
 for(int i=0; i<=3; i++) // This starts the communication 4 W2 pulses 1KHz 75% duty cycle 
 {
   digitalWrite(2, HIGH);
   delayMicroseconds(1500);

   digitalWrite(2, LOW);
   delayMicroseconds(500);
 }
 for(int i=0; i<=9; i++) // This makes the car go "forward" 10 W1 pulses 500Mhz 50% duty cycle
 {
   digitalWrite(2, HIGH);
   delayMicroseconds(500);

   digitalWrite(2, LOW);
   delayMicroseconds(500);
 }
}

 delay(1000); 
    for(int i=0; i<=30; i++) // This starts the communication 4 W2 pulses 1KHz 75% duty cycle 
 {
 for(int i=0; i<=3; i++) // This starts the communication 4 W2 pulses 1KHz 75% duty cycle 
 {
   digitalWrite(2, HIGH);
   delayMicroseconds(1500);

   digitalWrite(2, LOW);
   delayMicroseconds(500);
 }
 for(int i=0; i<=39; i++) // This makes the car go "forward" 10 W1 pulses 500Mhz 50% duty cycle
 {
   digitalWrite(2, HIGH);
   delayMicroseconds(500);

   digitalWrite(2, LOW);
   delayMicroseconds(500);
 }
}
 delay(1000); 
    for(int i=0; i<=30; i++) // This starts the communication 4 W2 pulses 1KHz 75% duty cycle 
 {
 for(int i=0; i<=3; i++) // This starts the communication 4 W2 pulses 1KHz 75% duty cycle 
 {
   digitalWrite(2, HIGH);
   delayMicroseconds(1500);

   digitalWrite(2, LOW);
   delayMicroseconds(500);
 }
 for(int i=0; i<=45; i++) // This makes the car go "forward" 10 W1 pulses 500Mhz 50% duty cycle
 {
   digitalWrite(2, HIGH);
   delayMicroseconds(500);

   digitalWrite(2, LOW);
   delayMicroseconds(500);
 }
}
 delay(1000); 
    for(int i=0; i<=30; i++) // This starts the communication 4 W2 pulses 1KHz 75% duty cycle 
 {
 for(int i=0; i<=3; i++) // This starts the communication 4 W2 pulses 1KHz 75% duty cycle 
 {
   digitalWrite(2, HIGH);
   delayMicroseconds(1500);

   digitalWrite(2, LOW);
   delayMicroseconds(500);
 }
 for(int i=0; i<=63; i++) // This makes the car go "forward" 10 W1 pulses 500Mhz 50% duty cycle
 {
   digitalWrite(2, HIGH);
   delayMicroseconds(500);

   digitalWrite(2, LOW);
   delayMicroseconds(500);
 }
}
}

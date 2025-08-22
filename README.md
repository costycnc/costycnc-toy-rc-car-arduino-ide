# costycnc-rc-car-arduino-ide
https://forum.arduino.cc/index.php?topic=171238.0

rc_car1  I put D2 signal to ground and working good       
                   
                   upload to arduino rc_car1.ino
                   welding wire from arduino to rc car (ground,power and D2) same as rc_car1.jpg photo
                   send command letter under serial ... the car need to rispond with moving
                   
                   a Forward 
                   b Forward Turbo 
                   c Forward & Left 
                   d Forward & Right
                   e Backward
                   f Backward & Right
                   g Backward & Left
                   h Left
                   i Right


 code movement:

                    /*Data Format
                    W2 W2 W2 W2 (n) x W1 
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

 w2 signal(1.5ms,0.5ms):
                     digitalWrite(2, HIGH);
                     delayMicroseconds(1500);
                  
                     digitalWrite(2, LOW);
                     delayMicroseconds(500);

w1 signal(0.5ms,0.5ms):
                     digitalWrite(2, HIGH);
                     delayMicroseconds(500);
                  
                     digitalWrite(2, LOW);
                     delayMicroseconds(500);                     

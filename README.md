# costycnc-rc-car-arduino-ide
[![Demo su YouTube](https://img.youtube.com/vi/47f06ZAZPy8/0.jpg)](https://www.youtube.com/watch?v=47f06ZAZPy8)



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
                    10 Forward
                    16 Forward & Turbo
                    22 Turbo
                    28 Turbo & Forward & Left
                    34 Turbo & Forward & Right
                    40 Backward
                    46 Backward & Right
                    52 Backward & Left
                    58 Left
                    64 Right
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

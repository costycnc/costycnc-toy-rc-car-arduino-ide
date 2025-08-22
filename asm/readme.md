Put ASM code into https://costycnc.github.io/avr-compiler-js/
.

This is an online AVR ASM bare-metal compiler and uploader based on WebSerial, made by myself.

Just write your ASM code, compile it, and upload directly to an Arduino Nano, Uno, etc. (you only need a USB cable and an Arduino).

No IDE, no libraries, nothing else required.

Perfect for beginners with no programming knowledge!



![alt text](https://raw.githubusercontent.com/costycnc/costycnc-toy-rc-car-arduino-ide/refs/heads/master/foto/rc-car.jpeg)

                  /*Data Format
                  W1=0.5ms  W2=1.5ms
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



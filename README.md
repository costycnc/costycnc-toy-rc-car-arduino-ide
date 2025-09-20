# CostyCNC Toy RC Car – Arduino IDE

![RC Car](rc_car1.jpg)

**Control a toy RC car using Arduino via serial commands**  

This project enables controlling a toy RC car directly via Arduino using **serial commands and precise microsecond pulse signals**. It’s perfect for learning **Arduino programming**, **microcontroller signal timing**, and **basic RC car electronics**.

---

## Hardware Components

- Arduino Uno or compatible  
- Toy RC car chassis  
- Jumper wires for signal, power, and ground  
- Power source (battery or USB)  

---

## Wiring / Connections

1. Connect **Arduino Pin 2 (D2)** to the RC car signal input.  
2. Connect **ground and power lines** from Arduino to the car.  
3. Ensure solid connections to prevent signal errors.  

> See `rc_car1.jpg` in the repository for a visual wiring guide.

---

## Software

### Uploading the Code

1. Open `rc_car1.ino` in Arduino IDE.  
2. Select the correct board (Arduino Uno) and COM port.  
3. Upload the code to the Arduino board.

### Supported Commands (via Serial Monitor)

| Command | Action |
|---------|--------|
| a       | Forward |
| b       | Forward Turbo |
| c       | Forward & Left |
| d       | Forward & Right |
| e       | Backward |
| f       | Backward & Right |
| g       | Backward & Left |
| h       | Left |
| i       | Right |

> Commands are sent directly via Arduino Serial Monitor.

### Pulse Signal Logic

The car is controlled using precise pulse signals:

**W2 signal (1.5ms HIGH, 0.5ms LOW)**

```cpp
digitalWrite(2, HIGH);
delayMicroseconds(1500);
digitalWrite(2, LOW);
delayMicroseconds(500);
```

**W1 signal (0.5ms HIGH, 0.5ms LOW)**

```cpp
digitalWrite(2, HIGH);
delayMicroseconds(500);
digitalWrite(2, LOW);
delayMicroseconds(500);
```

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

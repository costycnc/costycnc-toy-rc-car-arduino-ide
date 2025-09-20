# costycnc-rc-car-arduino-ide

This project allows you to control a toy RC car using an Arduino by sending serial commands.
The car responds with precise movements based on microsecond-level pulse signals (W1/W2).

It’s ideal for learning Arduino programming, microcontroller signal timing, and basic RC car electronics.

🧰 Hardware Components

Arduino Uno or compatible

Toy RC car chassis

Jumper wires for signal, power, and ground

Power source (battery or USB)

⚙️ Wiring / Connections

Connect Arduino D2 pin to the RC car signal input (as in rc_car1.jpg).

Connect ground and power lines from Arduino to the car.

Ensure the connections are solid to avoid signal issues.

💻 Software
📥 Uploading Code

Open rc_car1.ino in the Arduino IDE.

Select the correct board and COM port.

Upload the code to the Arduino.

🔧 Supported Commands (via Serial Monitor)
Command	Movement
a	Forward
b	Forward Turbo
c	Forward & Left
d	Forward & Right
e	Backward
f	Backward & Right
g	Backward & Left
h	Left
i	Right
⚡ Pulse Signal Logic

W2 signal (1.5ms high, 0.5ms low)

digitalWrite(2, HIGH);
delayMicroseconds(1500);
digitalWrite(2, LOW);
delayMicroseconds(500);


W1 signal (0.5ms high, 0.5ms low)

digitalWrite(2, HIGH);
delayMicroseconds(500);
digitalWrite(2, LOW);
delayMicroseconds(500);


These signals encode movement commands to the car’s motor controller.

📷 Media

rc_car.jpg

rc_car1.jpg showing wiring

📄 Documentation

[TX RX Car Toy PDF](tx rx car toy.pdf) – includes setup and wiring diagrams

🧠 Skills Highlighted

Arduino Programming

Microcontroller Signal Timing

Embedded Systems

C++ / Assembly

RC Car Electronics

🧑‍💻 Contributions

Feel free to fork the repository, improve code timing, or add new movement commands. Pull requests are welcome.

📄 License

MIT License

Se vuoi, posso creare anche la versione pronta per LinkedIn Projects, con title, description, top 5 skills e media consigliati, pronta da copiare. Vuoi che lo faccia?

Hai detto:
ok ... riscrivimi adesso un readme senza includere bluetooth
ChatGPT ha detto:

Perfetto! Ecco un README.md completo e dettagliato per il repository costycnc-toy-rc-car-arduino-ide, completamente senza riferimenti al Bluetooth, basato sui file effettivi del progetto:

CostyCNC Toy RC Car – Arduino IDE

Control a toy RC car using Arduino via serial commands

This project enables controlling a toy RC car directly via Arduino using serial commands and precise microsecond pulse signals. It’s perfect for learning Arduino programming, microcontroller signal timing, and basic RC car electronics.

🧰 Hardware Components

Arduino Uno or compatible

Toy RC car chassis

Jumper wires for signal, power, and ground

Power source (battery or USB)

⚙️ Wiring / Connections

Connect Arduino Pin 2 (D2) to the RC car signal input.

Connect ground and power lines from Arduino to the car.

Ensure solid connections to prevent signal errors.

See rc_car1.jpg in the repository for a visual wiring guide.

💻 Software
📥 Uploading the Code

Open rc_car1.ino in Arduino IDE.

Select the correct board (Arduino Uno) and COM port.

Upload the code to the Arduino board.

🔧 Supported Commands (via Serial Monitor)
Command	Action
a	Forward
b	Forward Turbo
c	Forward & Left
d	Forward & Right
e	Backward
f	Backward & Right
g	Backward & Left
h	Left
i	Right

Commands are sent directly via Arduino Serial Monitor.

⚡ Pulse Signal Logic

The car is controlled using precise pulse signals:

W2 signal (1.5ms HIGH, 0.5ms LOW)

digitalWrite(2, HIGH);
delayMicroseconds(1500);
digitalWrite(2, LOW);
delayMicroseconds(500);


W1 signal (0.5ms HIGH, 0.5ms LOW)

digitalWrite(2, HIGH);
delayMicroseconds(500);
digitalWrite(2, LOW);
delayMicroseconds(500);


These signals encode movement commands to the car’s motor controller.

📷 Media

Wiring diagram and car setup images: rc_car.jpg, rc_car1.jpg

📄 Documentation

[TX RX Car Toy PDF](tx rx car toy.pdf) – setup instructions, wiring diagrams, and detailed movement guide.

🧠 Skills Highlighted

Arduino Programming

Microcontroller Signal Timing

Embedded Systems

C++ / Microcontroller Logic

RC Car Electronics

🧑‍💻 Contributions

Fork the repository, improve pulse timing, or add new movement commands. Pull requests are welcome.

📄 License

MIT License



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

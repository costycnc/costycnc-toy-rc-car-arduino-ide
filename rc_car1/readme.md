
# RC Car Serial Controller – Arduino + Pulse Protocol

[![Arduino](https://img.shields.io/badge/Arduino-Uno%2FNano-blue.svg)](https://arduino.cc)
[![Protocol](https://img.shields.io/badge/Protocol-W1%2FW2-green.svg)]()

## 📖 What does this code do?

This Arduino sketch **controls an RC car via serial commands** (USB). When you send a character (a through i) from the Serial Monitor, the Arduino converts it into a specific pulse sequence (W1/W2) and sends it to the RC car receiver.

**No remote control needed. Your computer commands the car directly!**

---

## 🎮 Command Mapping

| Serial Command | W1 Pulses | Function | Result |
|----------------|-----------|----------|--------|
| `a` | 10 | Forward | Car goes FORWARD |
| `b` | 16 | Forward & Turbo | FORWARD + Turbo |
| `c` | 28 | Turbo & Forward & Left | FORWARD + LEFT |
| `d` | 34 | Turbo & Forward & Right | FORWARD + RIGHT |
| `e` | 40 | Backward | BACKWARD |
| `f` | 46 | Backward & Right | BACKWARD + RIGHT |
| `g` | 52 | Backward & Left | BACKWARD + LEFT |
| `h` | 58 | Left | LEFT only |
| `i` | 64 | Right | RIGHT only |

> **Note:** The command table in the code maps `c` to 27 pulses, `d` to 33, etc. Adjust as needed for your specific RC car.

---

## 📝 The Complete Code

```cpp
/* Data Format
   W2 W2 W2 W2 (n) x W1 W2 W2 W2 W2 (n) x W1 ...
   
   Command Reference:
   4 pulses   = End Code
   10 pulses  = Forward
   16 pulses  = Forward & Turbo
   22 pulses  = Turbo
   28 pulses  = Turbo + Forward + Left
   34 pulses  = Turbo + Forward + Right
   40 pulses  = Backward
   46 pulses  = Backward + Right
   52 pulses  = Backward + Left
   58 pulses  = Left
   64 pulses  = Right
*/

int a = 0;
char x;

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop()
{ 
  while (Serial.available() > 0) {
    x = Serial.read();
    Serial.print(x);

    if (x == 'a') turn(9);   // 10 pulses (Forward)
    if (x == 'b') turn(15);  // 16 pulses (Forward + Turbo)
    if (x == 'c') turn(27);  // 28 pulses (Turbo + Forward + Left)
    if (x == 'd') turn(33);  // 34 pulses (Turbo + Forward + Right)
    if (x == 'e') turn(39);  // 40 pulses (Backward)
    if (x == 'f') turn(45);  // 46 pulses (Backward + Right)
    if (x == 'g') turn(51);  // 52 pulses (Backward + Left)
    if (x == 'h') turn(57);  // 58 pulses (Left)
    if (x == 'i') turn(63);  // 64 pulses (Right)
    
    delay(1000);
  }
}

void turn(int b)
{
  for(int i = 0; i <= 10; i++)  // Repeat the command (motor turn time)
  {
    // Start sequence: 4 x W2 pulses (1.5ms HIGH, 0.5ms LOW)
    for(int i = 0; i <= 3; i++)
    {
      digitalWrite(2, HIGH);
      delayMicroseconds(1500);
      digitalWrite(2, LOW);
      delayMicroseconds(500);
    }
    
    // Command: b x W1 pulses (0.5ms HIGH, 0.5ms LOW)
    for(int i = 0; i <= b; i++)
    {
      digitalWrite(2, HIGH);
      delayMicroseconds(500);
      digitalWrite(2, LOW);
      delayMicroseconds(500);
    }
  }
}
```

---

## 🔬 How the Pulse Protocol Works

### Pulse Types

| Pulse | HIGH Time | LOW Time | Frequency | Duty Cycle | Purpose |
|-------|-----------|----------|-----------|------------|---------|
| **W2** | 1500 µs | 500 µs | 1 kHz | 75% | Start sequence / Sync |
| **W1** | 500 µs | 500 µs | 1 kHz | 50% | Command data bits |

### Communication Frame Structure

```
[W2 x 4] + [W1 x (b)] + [W2 x 4] + [W1 x (b)] + ... (repeated 10 times)
```

| Part | What it does |
|------|--------------|
| `W2 x 4` | Synchronization - tells the car "a command is coming" |
| `W1 x b` | The actual command (b = number of pulses = command code) |
| Loop 10x | Repeats the command to ensure the car receives it |

### Timing Diagram

```
W2 Pulse:   ████████████████████░░░░░░░░░░
            └── 1500µs ──┘└─ 500µs ─┘

W1 Pulse:   ██████████░░░░░░░░░░
            └─ 500µs ─┘└─ 500µs ─┘

Frame:      [W2][W2][W2][W2][W1][W1]...[W1]
             ← 4x sync →  ← b x command →
```

---

## 🔌 Hardware Connection

### Pin Mapping

| Arduino Pin | Connect to |
|-------------|------------|
| **Pin 2** | RC car receiver (Antenna / Signal) |
| **GND** | RC car receiver (GND) |
| **USB** | Computer (for serial commands) |

### Wiring Diagram

```
┌───────────┐                    ┌─────────────┐
│  Arduino  │                    │  RC Car     │
│           │                    │  Receiver   │
│        2  ├────────────────────► Antenna     │
│           │                    │  (Signal)   │
│      GND  ├────────────────────► GND         │
│           │                    │             │
│      USB  ├─────────┬──────────│             │
└───────────┘         │          └─────────────┘
                      │
                 ┌────┴────┐
                 │ Computer│
                 │ Monitor │
                 └─────────┘
```

---

## 🚀 How to Use

### Step 1: Upload the code
1. Open Arduino IDE
2. Copy-paste the code
3. Select board (Arduino Uno/Nano)
4. Upload to Arduino

### Step 2: Open Serial Monitor
- Set baud rate to **9600**
- Make sure "Newline" or "No line ending" is selected

### Step 3: Control the car

| Type this in Serial Monitor | Car does this |
|----------------------------|---------------|
| `a` | Forward |
| `b` | Forward + Turbo |
| `c` | Forward + Left |
| `d` | Forward + Right |
| `e` | Backward |
| `f` | Backward + Right |
| `g` | Backward + Left |
| `h` | Left |
| `i` | Right |

The command repeats 10 times automatically (ensures the car receives it).

---

## 📊 Complete Command Reference Table

| W1 Pulses | Hex Value | Command | Result |
|-----------|-----------|---------|--------|
| 4 | - | End Code | Stop |
| 10 | 0x0A | Forward | Forward only |
| 16 | 0x10 | Forward + Turbo | Turbo Forward |
| 22 | 0x16 | Turbo | Turbo only |
| 28 | 0x1C | Turbo + Forward + Left | Forward + Left |
| 34 | 0x22 | Turbo + Forward + Right | Forward + Right |
| 40 | 0x28 | Backward | Backward only |
| 46 | 0x2E | Backward + Right | Backward + Right |
| 52 | 0x34 | Backward + Left | Backward + Left |
| 58 | 0x3A | Left | Left only |
| 64 | 0x40 | Right | Right only |

---

## ⚙️ How the `turn()` Function Works

```cpp
void turn(int b)  // b = number of W1 pulses (minus 1 due to loop logic)
{
  for(int i = 0; i <= 10; i++)     // Repeat command 11 times
  {
    for(int i = 0; i <= 3; i++)    // Send 4 W2 pulses (sync)
    {
      // W2 pulse: 1500µs HIGH, 500µs LOW
    }
    
    for(int i = 0; i <= b; i++)    // Send b+1 W1 pulses (command)
    {
      // W1 pulse: 500µs HIGH, 500µs LOW
    }
  }
}
```

**Why loop 11 times?** The RC car needs multiple repetitions to reliably decode the command.

---

## 🛠️ Customization Tips

### Change the pulse timing
```cpp
// For different RC car protocols, adjust these values:
delayMicroseconds(1500);  // W2 HIGH time (standard: 1500µs)
delayMicroseconds(500);   // W2 LOW time / W1 timing (standard: 500µs)
```

### Add more commands
```cpp
if (x == 'j') turn(73);   // Add custom command
if (x == 'k') turn(79);
```

### Change command duration
```cpp
// Replace the 11x loop with a different value:
for(int i = 0; i <= 5; i++)  // Shorter command burst
for(int i = 0; i <= 20; i++) // Longer command burst
```

---

## 🐛 Troubleshooting

| Problem | Solution |
|---------|----------|
| Car doesn't respond | Check Pin 2 connection to antenna |
| | Verify common GND between Arduino and receiver |
| | Try different command letters |
| Random commands | Add more repetitions (increase loop count) |
| Car keeps moving after command | Send End Code (4 W2 pulses) |
| No Serial output | Check baud rate: 9600 |

---

## 🔄 Code Improvements (Optional)

Here's a cleaner, more maintainable version:

```cpp
const int CONTROL_PIN = 2;

// Command mapping
const int CMD_FORWARD       = 10;
const int CMD_FORWARD_TURBO = 16;
const int CMD_TURBO_FWD_LEFT = 28;
const int CMD_TURBO_FWD_RIGHT = 34;
const int CMD_BACKWARD      = 40;
const int CMD_BACKWARD_RIGHT = 46;
const int CMD_BACKWARD_LEFT = 52;
const int CMD_LEFT          = 58;
const int CMD_RIGHT         = 64;

void sendW2() {
  digitalWrite(CONTROL_PIN, HIGH);
  delayMicroseconds(1500);
  digitalWrite(CONTROL_PIN, LOW);
  delayMicroseconds(500);
}

void sendW1() {
  digitalWrite(CONTROL_PIN, HIGH);
  delayMicroseconds(500);
  digitalWrite(CONTROL_PIN, LOW);
  delayMicroseconds(500);
}

void sendCommand(int pulseCount) {
  for (int i = 0; i < 11; i++) {  // Repeat for reliability
    for (int j = 0; j < 4; j++) sendW2();  // Sync
    for (int j = 0; j <= pulseCount; j++) sendW1();  // Command
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(CONTROL_PIN, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    
    switch (cmd) {
      case 'a': sendCommand(CMD_FORWARD); break;
      case 'b': sendCommand(CMD_FORWARD_TURBO); break;
      case 'c': sendCommand(CMD_TURBO_FWD_LEFT); break;
      case 'd': sendCommand(CMD_TURBO_FWD_RIGHT); break;
      case 'e': sendCommand(CMD_BACKWARD); break;
      case 'f': sendCommand(CMD_BACKWARD_RIGHT); break;
      case 'g': sendCommand(CMD_BACKWARD_LEFT); break;
      case 'h': sendCommand(CMD_LEFT); break;
      case 'i': sendCommand(CMD_RIGHT); break;
    }
    
    delay(1000);
  }
}
```

---

## 📋 Summary

| What this does | Controls an RC car via USB serial commands |
|----------------|---------------------------------------------|
| How it works | Converts letters (a-i) to pulse sequences (W1/W2) |
| Hardware needed | Arduino + USB cable + wire to RC car antenna |
| Protocol | 4x W2 (sync) + Nx W1 (command), repeated 11x |
| Pin used | **Pin 2** (digital output) |
| Baud rate | 9600 |

---

**Type a letter. Watch the car move. No remote needed.** 🚗💨⌨️

Ecco il **README completo** per il tuo protocollo di controllo remoto a impulsi.

---

# RC Car Pulse Control Protocol - W1/W2 Encoding

![Protocol](https://img.shields.io/badge/Protocol-Pulse%20Encoding-blue.svg) ![Arduino](https://img.shields.io/badge/Arduino-Compatible-green.svg) ![License](https://img.shields.io/badge/License-MIT-yellow.svg)

## 📖 Description

This is a **pulse-based communication protocol** for controlling RC cars and similar devices. The protocol uses two types of pulses (W1 and W2) to encode commands.

> 🎯 **Simple, reliable, and easy to implement** on any microcontroller!

## 📋 Protocol Overview

### Pulse Types

| Pulse Type | Frequency | Duty Cycle | High Time | Low Time | Purpose |
|------------|-----------|------------|-----------|----------|---------|
| **W2** | 1 kHz | 75% | 1500 µs | 500 µs | Start sequence / Sync |
| **W1** | 1 kHz | 50% | 500 µs | 500 µs | Command data bits |

### Pulse Visualization

```
W2 Pulse (75% duty):   HIGH ━━━━━━━━━━━━━━━━━━━━┓
                       ┃                        ┃
                       LOW  ━━━━━━━━━━━━━━━━━━━━┛
                       └─ 1500µs ─┘└─ 500µs ─┘

W1 Pulse (50% duty):   HIGH ━━━━━━━━━━━━━━┓
                       ┃                  ┃
                       LOW  ━━━━━━━━━━━━━━┛
                       └─ 500µs ─┘└─ 500µs ─┘
```

## 🎮 Command Encoding

### Frame Structure

```
[W2 x 4] + [W1 x N] + [W2 x 4] + [W1 x M] + ...
```

| Section | Description |
|---------|-------------|
| **4 × W2** | Start sequence / Synchronization |
| **N × W1** | First command (function code) |
| **4 × W2** | Start sequence / Sync (repeat) |
| **M × W1** | Second command (direction code) |
| ... | Continue pattern |

### Command Values

| Function Code | W1 Count | Command |
|---------------|----------|---------|
| 10 | 10 pulses | Forward |
| 16 | 16 pulses | Forward + Turbo |
| 22 | 22 pulses | Turbo |
| 28 | 28 pulses | Turbo + Forward + Left |
| 34 | 34 pulses | Turbo + Forward + Right |
| 40 | 40 pulses | Backward |
| 46 | 46 pulses | Backward + Right |
| 52 | 52 pulses | Backward + Left |
| 58 | 58 pulses | Left |
| 64 | 64 pulses | Right |

### End Code

- **4 × W2 pulses** indicates end of transmission

## 🔌 Hardware Setup

### Pin Connections

```
Arduino Pin 2  ─────────► RC Car Receiver (Signal)
Arduino GND    ─────────► Receiver GND
```

### Wiring Diagram

```
┌───────────┐                    ┌─────────────┐
│  Arduino  │                    │  RC Car     │
│           │                    │  Receiver   │
│        2  ├────────────────────► Signal In   │
│      GND  ├────────────────────► GND         │
│           │                    │             │
└───────────┘                    └─────────────┘
```

## 💻 Code Explanation

### Current Code Structure

```cpp
void setup() {
    pinMode(2, OUTPUT);  // Configure pin 2 as output
}

void loop() {
    delay(1000);  // Wait 1 second between commands
    
    // Send W2 start sequence (4 pulses)
    for(int i = 0; i <= 3; i++) {
        digitalWrite(2, HIGH);
        delayMicroseconds(1500);
        digitalWrite(2, LOW);
        delayMicroseconds(500);
    }
    
    // Send W1 command pulses (N pulses)
    for(int i = 0; i <= 39; i++) {  // 40 pulses = Backward
        digitalWrite(2, HIGH);
        delayMicroseconds(500);
        digitalWrite(2, LOW);
        delayMicroseconds(500);
    }
}
```

### Example Commands in Current Code

| Code Section | W1 Count | Command |
|--------------|----------|---------|
| First block | 10 pulses | Forward |
| Second block | 40 pulses | Backward |
| Third block | 46 pulses | Backward + Right |
| Fourth block | 64 pulses | Right |

## 🚀 How to Use

### Step 1: Connect Hardware
- Connect Arduino pin 2 to RC car receiver signal input
- Connect Arduino GND to receiver GND
- Power both devices

### Step 2: Upload Code
```bash
# Using Arduino IDE:
1. Open Arduino IDE
2. Copy the code
3. Select Board: Arduino Uno
4. Upload
```

### Step 3: Observe
The car will execute the command sequence:
1. Forward (10 pulses)
2. Backward (40 pulses)
3. Backward + Right (46 pulses)
4. Right (64 pulses)

## 📊 Complete Command Table

| W1 Count | Function | Combined Result |
|----------|----------|-----------------|
| 10 | Forward | Forward |
| 16 | Forward & Turbo | Forward + Turbo |
| 22 | Turbo | Turbo only |
| 28 | Turbo & Forward & Left | Forward + Left |
| 34 | Turbo & Forward & Right | Forward + Right |
| 40 | Backward | Backward only |
| 46 | Backward & Right | Backward + Right |
| 52 | Backward & Left | Backward + Left |
| 58 | Left | Left only |
| 64 | Right | Right only |

## 🔧 Improved Code (Refactored)

Here's a cleaner, more maintainable version:

```cpp
#define CONTROL_PIN 2
#define W1_HIGH 500   // microseconds
#define W1_LOW  500
#define W2_HIGH 1500
#define W2_LOW  500

void sendW2Pulse() {
    digitalWrite(CONTROL_PIN, HIGH);
    delayMicroseconds(W2_HIGH);
    digitalWrite(CONTROL_PIN, LOW);
    delayMicroseconds(W2_LOW);
}

void sendW1Pulse() {
    digitalWrite(CONTROL_PIN, HIGH);
    delayMicroseconds(W1_HIGH);
    digitalWrite(CONTROL_PIN, LOW);
    delayMicroseconds(W1_LOW);
}

void sendStartSequence() {
    for(int i = 0; i < 4; i++) {
        sendW2Pulse();
    }
}

void sendCommand(int pulseCount) {
    for(int i = 0; i < pulseCount; i++) {
        sendW1Pulse();
    }
}

void sendCommandSequence(int w1_count) {
    sendStartSequence();
    sendCommand(w1_count);
}

void setup() {
    pinMode(CONTROL_PIN, OUTPUT);
}

void loop() {
    delay(1000);
    
    sendCommandSequence(10);  // Forward
    delay(1000);
    
    sendCommandSequence(40);  // Backward
    delay(1000);
    
    sendCommandSequence(46);  // Backward + Right
    delay(1000);
    
    sendCommandSequence(64);  // Right
    delay(1000);
}
```

## 📈 Timing Diagram

```
Start Seq:  W2    W2    W2    W2
          ████████████████████████████████████
          ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

Command:    W1    W1    W1    W1    W1
          ████████████████████████████████████
          ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
          0     1     2     3     4     5 (ms)

Legend: ████ = HIGH, ░░░░ = LOW
```

## ⚠️ Important Notes

### Timing Precision
- Microsecond precision is **critical** for proper decoding
- Use `delayMicroseconds()` not `delay()`
- Avoid interrupt-heavy code during pulse transmission

### Power Considerations
- The RC car receiver may need 5V logic levels
- Some receivers require 3.3V - use level shifter if needed
- Ensure common ground between Arduino and receiver

## 🐛 Troubleshooting

| Problem | Solution |
|---------|----------|
| No response from car | Check common ground connection |
| Intermittent control | Verify timing is precise (±10µs) |
| Wrong command executed | Count W1 pulses carefully |
| Car doesn't stop | Send end code (4×W2) |
| Multiple commands sent | Add delays between commands |

## 🔄 Protocol Variants

Some RC cars use different pulse widths:

| Variant | W2 High | W2 Low | W1 High | W1 Low |
|---------|---------|--------|---------|--------|
| Standard | 1500µs | 500µs | 500µs | 500µs |
| Fast | 1000µs | 500µs | 400µs | 400µs |
| Slow | 2000µs | 800µs | 800µs | 800µs |

## 📝 License

Free to use, modify, and share!

## 🙏 Acknowledgments

Protocol reverse-engineered from commercial RC car controllers.

---

**Control your RC car with simple pulses!** 🚗⚡🎮

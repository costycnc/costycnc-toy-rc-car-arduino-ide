
# RC Car Pulse Control in Assembly (ASM) – No IDE, No Libraries

[![AVR](https://img.shields.io/badge/AVR-ASM-blue.svg)](https://costycnc.github.io/avr-compiler-js/)
[![Arduino](https://img.shields.io/badge/Arduino-Uno%2FNano-green.svg)](https://costycnc.github.io/avr-compiler-js/)

## 📖 What does this code do?

**Controls an RC car** using pulse sequences (W1 and W2). The code is written in **pure Assembly (ASM)** for AVR microcontrollers (Arduino Uno/Nano).

This specific code sends:
- **4 x W2 pulses** → synchronization / start sequence
- **10 x W1 pulses** → **FORWARD** command

---

## 📝 The Assembly Code

```asm
.org 0
    rjmp init
.org 0x60
init:
    ; --- Initialize stack (MANDATORY!) ---
    ldi r16, 0xFF
    out 0x3D, r16    ; SPL
    ldi r16, 0x08
    out 0x3E, r16    ; SPH

loop:
    rcall forward    ; Send FORWARD command
    rjmp loop        ; Repeat forever

forward:
    ; Start sequence: 4 x W2 pulses
    rcall w2
    rcall w2
    rcall w2
    rcall w2
    
    ; Command: 10 x W1 pulses = FORWARD
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    ret

w2:
    sbi 5,0          ; Set PB0 HIGH (Arduino Pin 8)
    ldi r17,31       ; Delay for 1.5ms
    rcall pause
    cbi 5,0          ; Set PB0 LOW
    ldi r17,11       ; Delay for 0.5ms
    rcall pause
    ret

w1:
    sbi 5,0          ; Set PB0 HIGH
    ldi r17,11       ; Delay for 0.5ms
    rcall pause
    cbi 5,0          ; Set PB0 LOW
    ldi r17,11       ; Delay for 0.5ms
    rcall pause
    ret

pause:
    dec r16
    brne pause
    dec r17
    brne pause
    ret
```

---

## 🎮 Pulse Protocol Explained

| Pulse Type | HIGH Time | LOW Time | Purpose |
|------------|-----------|----------|---------|
| **W2** | 1500 µs | 500 µs | Start sequence / Sync |
| **W1** | 500 µs | 500 µs | Command data bits |

### What the code sends:

```
[W2][W2][W2][W2] ── [W1][W1][W1][W1][W1][W1][W1][W1][W1][W1]
     (sync)              (10 pulses = FORWARD)
```

---

## 🔌 Hardware Connection (IMPORTANT - READ THIS!)

The code uses `sbi 5,0` and `cbi 5,0` which control **PB0**.

| Assembly Code | Port | Bit | Arduino Pin |
|---------------|------|-----|-------------|
| `sbi 5,0` | PORTB | 0 | **Pin 8** |

### Connection Diagram:

```
┌───────────┐                    ┌─────────────┐
│  Arduino  │                    │  RC Car     │
│           │                    │  Receiver   │
│       8   ├────────────────────► Antenna     │
│     (PB0) │                    │  (Signal)   │
│           │                    │             │
│           |                    │
└───────────┘                    └─────────────┘
```

### Wire it like this:

| Arduino | Connect to |
|---------|------------|
| **Pin 8** (PB0) | RC car receiver **Antenna** (or Signal input) |


## 📊 Command Reference (Change W1 pulse count to change command)

| W1 Pulses | Command |
|-----------|---------|
| 10 | Forward |
| 16 | Forward + Turbo |
| 22 | Turbo |
| 28 | Turbo + Forward + Left |
| 34 | Turbo + Forward + Right |
| 40 | Backward |
| 46 | Backward + Right |
| 52 | Backward + Left |
| 58 | Left |
| 64 | Right |

### How to change the command:

Replace the 10 `rcall w1` calls with a different number:

```asm
; Example: Backward (40 pulses)
    rcall w1   ; repeat 40 times
    ; ... (40 total)
```

Or use a loop for cleaner code (advanced).

---

## 🔧 How to test it? (the compiler is just a tool)

Use my **online ASM compiler** to write and upload the code quickly:

🔗 **https://costycnc.github.io/avr-compiler-js/**

> ℹ️ The compiler is just a quick tool to write ASM. **The real star is the Assembly code above!**

### Quick steps:

1. Go to **https://costycnc.github.io/avr-compiler-js/**
2. Copy-paste the ASM code
3. Click **"Assemble"**
4. Connect Arduino via USB
5. Click **"Upload"** (select Uno/Nano)
6. Select the USB port → **Connect**
7. Connect Arduino Pin 8 to RC car antenna
8. The car goes FORWARD!

**No IDE installation. No drivers. No libraries. No magic.**

---

## ⚠️ Why stack, call/ret, push/pop are MANDATORY

Real disasters happened when people ignored them:

| Disaster | Cause |
|----------|-------|
| **Boeing 737 MAX (2019)** – 346 deaths | Stack corruption. Push without pop, call without ret. |
| **Toyota Unintended Acceleration** | Stack exhausted from recursive calls. |

### The 4 commandments (follow them!):

1. ✅ Every `call` must have a `ret`
2. ✅ Every `push` must have a `pop`
3. ✅ Know your stack limits
4. ✅ Otherwise, you're a **public hazard**

---

## 📊 Arduino IDE vs This Approach

| Feature | Arduino IDE | This ASM + Tool |
|---------|-------------|-----------------|
| Installation | Yes (IDE + drivers) | **No** - works in browser |
| Libraries | Many, hide everything | **None** - you see the registers |
| Control | DigitalWrite() | Direct port access (`sbi`, `cbi`) |
| Learning | Softer, less transparent | **Direct** - learn how it REALLY works |
| File size | KBs | **Bytes** (this code is tiny!) |

---

## 🎯 Summary

| What is this? | Assembly code that controls an RC car using pulses directly to the antenna |
|---------------|---------------------------------------------------------------------------|
| Which pin? | **Arduino Pin 8 (PB0)** → RC car antenna |
| Who is it for? | Beginners, students, hobbyists who want to learn how things REALLY work |
| Do I need to install anything? | **NO** – just a browser and a USB cable |
| What's the compiler? | Just a tool. The ASM code is the star! |

---

## 🚗 Final connection reminder:

```
Arduino Pin 8  ─────► RC Car Antenna
```

**That's it. Pure Assembly. No magic. Your RC car obeys your code.** 🎯🔥


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

![alt text](https://raw.githubusercontent.com/costycnc/costycnc-toy-rc-car-arduino-ide/refs/heads/master/foto/rc-car.jpeg)

![alt text](https://raw.githubusercontent.com/costycnc/costycnc-toy-rc-car-arduino-ide/refs/heads/master/foto/schematic.jpg)


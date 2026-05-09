
# 🚀 AVR ASM Online Compiler & Uploader

Website: **[costycnc.github.io/avr-compiler-js/](https://costycnc.github.io/avr-compiler-js/)**

## ✨ What is it?

This is an **online AVR ASM bare-metal compiler and uploader** based on WebSerial, made by myself.

It works entirely in your browser:
- Write your Assembly code
- Compile with one click
- Upload directly to Arduino Nano, Uno, etc.

**All you need:** a USB cable and an Arduino board.

**No IDE, no libraries, no installations, no magic.** Just pure code and your browser!

## 🎯 Perfect for beginners

Even though it says "Assembly", this platform is designed for **people with no programming knowledge at all**.

| What you need | Traditional (Arduino IDE) | This platform |
|---------------|---------------------------|---------------|
| Installation | Yes (IDE + drivers) | **No** - works in the browser |
| Configuration | Select board, port, chip | **Nothing** - plug and go |
| First LED code | `setup()`, `loop()`, `digitalWrite()` | `sbi 0x4,5` → LED turns on |
| Libraries | Many, but hide everything | **None** - you see the actual registers |
| Learning curve | Softer, but less transparent | **Direct** - you learn how it really works |

## 💻 How to use

### Step 1: Write your ASM code

Example code (makes the car go FORWARD):

```asm
.org 0
    rjmp init
.org 0x60
init:
    ; --- Initialize stack ---
    ldi r16, 0xFF
    out 0x3D, r16    ; SPL
    ldi r16, 0x08
    out 0x3E, r16    ; SPH
    
loop:
    rcall forward    ; Call the forward command
    rjmp loop        ; Repeat forever

forward:
    ; Start sequence: 4 x W2 pulses (1.5ms high, 0.5ms low)
    rcall w2
    rcall w2
    rcall w2
    rcall w2
    
    ; Command: 10 x W1 pulses (0.5ms high, 0.5ms low) = FORWARD
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
    sbi 5,0          ; Set pin HIGH (Pin 13 / PB5)
    ldi r17,31       ; Delay for 1.5ms
    rcall pause
    cbi 5,0          ; Set pin LOW
    ldi r17,11       ; Delay for 0.5ms
    rcall pause
    ret

w1:
    sbi 5,0          ; Set pin HIGH
    ldi r17,11       ; Delay for 0.5ms
    rcall pause
    cbi 5,0          ; Set pin LOW
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

### Step 2: Assemble

Click the **"Assemble"** button on the website.

The site automatically turns your Assembly code into a **HEX file** - no compilers needed on your computer!

### Step 3: Upload

1. Connect your board (Arduino UNO, Nano, etc.) to your computer with a **USB cable**
2. Click the button for your microcontroller (UNO, Nano, etc.)
3. A window (Web Serial API) will open
4. Select the USB port connected to your Arduino
5. Click **"Connect"**

That's it! The code uploads directly to your board.

### Step 4: See it work!

Right after uploading, the code starts running:
- The onboard LED on pin 13 (PB5) will blink according to your pulse pattern
- In this example, it sends the "FORWARD" command sequence

## 🎮 What this example does

This ASM code implements the **RC Car Pulse Control Protocol**:

| Pulse Type | Timing | Purpose |
|------------|--------|---------|
| **W2** | 1.5ms HIGH, 0.5ms LOW | Start sequence / Sync |
| **W1** | 0.5ms HIGH, 0.5ms LOW | Command data bits |

The example sends:
- **4 × W2 pulses** (start sequence)
- **10 × W1 pulses** (FORWARD command)

Connect Pin 13 (PB5) to an RC car receiver, and the car will go FORWARD!

## ⚠️ Why stack, call/ret, push/pop are MANDATORY

This platform enforces proper stack usage because real-world disasters happened without it:

| Disaster | Cause |
|----------|-------|
| **Boeing 737 MAX (2019)** – 346 deaths | Stack corruption in MCAS system. Push without pop, call without ret → crash. |
| **Toyota Unintended Acceleration (2010-2023)** | Recursive calls with no stack control. Stack exhausted → data corruption. |

### The 4 commandments of embedded systems:

1. **Every `call` must have a `ret`** (or you're a public hazard)
2. **`push` must be balanced by `pop`** (or the system crashes)
3. **The stack isn't magic** – it's limited (Boeing learned the hard way)
4. **If you don't know these, you're not an engineer** – you're a copy-paster

👉 **You are not authorized to code if you don't know these 4 instructions.**

## 📊 Arduino IDE vs This Platform

| Feature | Arduino IDE | costycnc.github.io/avr-compiler-js |
|---------|-------------|-------------------------------------|
| Installation | Yes (IDE + drivers) | **No** - works directly in browser |
| Configuration | Select board, port, chip | **Nothing to configure** - plug and go |
| First LED code | `setup()`, `loop()`, `digitalWrite()` | `sbi 0x4,5` → LED turns on (PB5) |
| Libraries | Many, but often hide everything | **None** - you see the actual registers |
| Complex projects | Ideal, with many libraries | Limited to basic learning |
| Learning curve | Softer, but less transparent | **More direct** - learn how it really works |

## 🔧 Requirements

- **Hardware:** Arduino UNO, Nano, or compatible board
- **Cable:** USB cable (for data, not just power)
- **Browser:** Chrome, Edge, or any browser that supports **WebSerial API**
- **No software installation needed!**

## 🎯 Who is this for?

| User type | Is this for you? |
|-----------|------------------|
| Absolute beginner with no programming knowledge | ✅ **YES** - start here to learn how things REALLY work |
| Student learning embedded systems | ✅ **YES** - see the actual registers, no magic |
| Hobbyist who wants to understand microcontrollers | ✅ **YES** - no libraries hiding what happens |
| Professional making complex products | ⚠️ Maybe - great for learning, but limited for large projects |
| Someone who just wants things to work fast | ❌ No - use Arduino IDE with libraries |

## 📝 License

Free to use, modify, and share!

## 🙏 Acknowledgments

Created to show that it's possible to program microcontrollers **without libraries, without an IDE, without magic.**

---

**Write ASM. Click Assemble. Click Upload. See it run. No IDE. No libraries. Just code.** 🎯🔥


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


# 🔹 STM32 GPIO Sequence Checker

A simple **Embedded C** project using the **STM32F4** microcontroller to verify a specific button sequence and control LEDs based on whether the sequence is correct or incorrect.

---

## 🧠 Project Idea

The program reads four buttons connected to **PA0 – PA3**  
and checks if the order in which the buttons are pressed matches the correct sequence **(1, 3, 2, 4)**.

- If the entered sequence is **correct** ✅ → the **green LED** (PA4) turns ON.  
- If the entered sequence is **incorrect** ❌ → the **red LEDs** (PA5 and PA6) turn ON.

---

## ⚙️ How It Works

1. The clock for **GPIOA** is enabled using the `RCC_AHB1ENR` register.  
2. GPIO configuration:
   - **PA0 – PA3** → Input (buttons)  
   - **PA4 – PA6** → Output (LEDs)
3. The program waits for 4 button presses.  
4. Once all 4 presses are registered:
   - It compares the pressed sequence with the correct sequence.
   - Turns ON the corresponding LED(s).
   - Resets variables for the next attempt.

---

## 🧩 Required Hardware

- **STM32F401** or **STM32F407** development board  
- 4 × Push Buttons connected to:
  - PA0 → Button 1  
  - PA1 → Button 2  
  - PA2 → Button 3  
  - PA3 → Button 4  
- 3 × LEDs connected to:
  - PA4 → Green LED (Correct)  
  - PA5 → Red LED (Incorrect)  
  - PA6 → Red LED (Incorrect)

---

## 🛠️ Project Files

| File | Description |
|------|--------------|
| `main.c` | Main program logic |
| `delay-lib.h` | Delay functions |
| `stm32f40xx.h` | STM32 register and peripheral definitions |
| `stm32f401-gpio.h` | GPIO control functions |

---

## ⚙️ How to Run

1. Open the project in **STM32CubeIDE**, **Keil uVision**, or **PlatformIO**.  
2. Select the correct **microcontroller target** (e.g., STM32F401 or STM32F407).  
3. Connect the components as described above.  
4. Compile and flash the program to the board.  
5. Test by pressing the buttons in correct and incorrect orders — observe LED behavior.

---

## 📘 Notes

- Use appropriate **resistors** for LEDs and buttons to prevent damage.  
- You can modify the correct button sequence by editing the `correct_seq[]` array in the code.  
- The program uses **register-level programming**, not the STM32 HAL library, for direct low-level control.

---

## 👨‍💻 Developer

**Mostafa Medhat**  
📧 mostafamedhatmostafa577@gmail.com  
📍 Giza, Egypt  


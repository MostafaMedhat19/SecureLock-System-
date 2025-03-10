#include "delay-lib.h"
#include "stm32f40xx.h"
#include "stm32f401-gpio.h"

int main(void) {

    // Enable the GPIOA clock
    RCC->RCC_AHB1ENR |= (1 << 0);

    // Configure PA0, PA1, PA2, PA3 as input
    GPIOA->MODER &= ~((3 << (0 * 2)) | (3 << (1 * 2)) | (3 << (2 * 2)) | (3 << (3 * 2)));
    GPIOA->MODER |= (0 << (0 * 2)) | (0 << (1 * 2)) | (0 << (2 * 2)) | (0 << (3 * 2));

    // Configure PA4, PA5, PA6 as output
    GPIOA->MODER &= ~((3 << (4 * 2)) | (3 << (5 * 2)) | (3 << (6 * 2)));
    GPIOA->MODER |= (1 << (4 * 2)) | (1 << (5 * 2)) | (1 << (6 * 2));

    int correct_seq[4] = {1, 3, 2, 4}; // Correct sequence
    int index = 0; // Index for button sequence
    int btn_seq[4] = {0}; // Array to store button sequence
    GPIOA->ODR &= ~((1 << 5) | (1 << 4) | (1 << 6)); // Turn off all LEDs initially

    while (1) {
        int checker = 1; // Flag to check if sequence is correct

        // Check if any button is pressed and update button sequence
        if (!((GPIOA->IDR >> 0) & 0x01)) {
            btn_seq[index++] = 1;
            while (!((GPIOA->IDR >> 0) & 0x01)); // Wait for button release
        } else if (!((GPIOA->IDR >> 1) & 0x01)) {
            btn_seq[index++] = 2;
            while (!((GPIOA->IDR >> 1) & 0x01)); // Wait for button release
        } else if (!((GPIOA->IDR >> 2) & 0x01)) {
            btn_seq[index++] = 3;
            while (!((GPIOA->IDR >> 2) & 0x01)); // Wait for button release
        } else if (!((GPIOA->IDR >> 3) & 0x01)) {
            btn_seq[index++] = 4;
            while (!((GPIOA->IDR >> 3) & 0x01)); // Wait for button release
        }

        // If 4 buttons have been pressed, check the sequence
        if (index == 4) {
            for (int i = 0; i < 4; i++) {
                if (btn_seq[i] != correct_seq[i]) {
                    checker = 0;
                    break;
                }
            }

            if (checker) {
                GPIOA->ODR |= (1 << 4); // Turn on LED at PA4
                GPIOA->ODR &= ~((1 << 5) | (1 << 6)); // Turn off LEDs at PA5 and PA6
            } else {
                GPIOA->ODR &= ~(1 << 4); // Turn off LED at PA4
                GPIOA->ODR |= ((1 << 5) | (1 << 6)); // Turn on LEDs at PA5 and PA6
            }

            // Reset index and button sequence
            index = 0;
            for (int i = 0; i < 4; i++) {
                btn_seq[i] = 0;
            }
        }
    }
}

#include "delay-lib.h"
#include "stm32f40xx.h"
#include "stm32f401-gpio.h"

int main(void) {

   
    RCC->RCC_AHB1ENR |= (1 << 0);

   
    GPIOA->MODER &= ~((3 << (0 * 2)) | (3 << (1 * 2)) | (3 << (2 * 2)) | (3 << (3 * 2)));
    GPIOA->MODER |= (0 << (0 * 2)) | (0 << (1 * 2)) | (0 << (2 * 2)) | (0 << (3 * 2));

    
    GPIOA->MODER &= ~((3 << (4 * 2)) | (3 << (5 * 2)) | (3 << (6 * 2)));
    GPIOA->MODER |= (1 << (4 * 2)) | (1 << (5 * 2)) | (1 << (6 * 2));

    int correct_seq[4] = {1, 3, 2, 4}; 
    int index = 0;
    int btn_seq[4] = {0}; 
    GPIOA->ODR &= ~((1 << 5) | (1 << 4) | (1 << 6)); 

    while (1) {
        int checker = 1; 

      
        if (!((GPIOA->IDR >> 0) & 0x01)) {
            btn_seq[index++] = 1;
            while (!((GPIOA->IDR >> 0) & 0x01));
        } else if (!((GPIOA->IDR >> 1) & 0x01)) {
            btn_seq[index++] = 2;
            while (!((GPIOA->IDR >> 1) & 0x01)); 
        } else if (!((GPIOA->IDR >> 2) & 0x01)) {
            btn_seq[index++] = 3;
            while (!((GPIOA->IDR >> 2) & 0x01)); 
        } else if (!((GPIOA->IDR >> 3) & 0x01)) {
            btn_seq[index++] = 4;
            while (!((GPIOA->IDR >> 3) & 0x01));
        }

   
        if (index == 4) {
            for (int i = 0; i < 4; i++) {
                if (btn_seq[i] != correct_seq[i]) {
                    checker = 0;
                    break;
                }
            }

            if (checker) {
                GPIOA->ODR |= (1 << 4);
                GPIOA->ODR &= ~((1 << 5) | (1 << 6)); 
            } else {
                GPIOA->ODR &= ~(1 << 4);
                GPIOA->ODR |= ((1 << 5) | (1 << 6));
            }

          
            index = 0;
            for (int i = 0; i < 4; i++) {
                btn_seq[i] = 0;
            }
        }
    }
}

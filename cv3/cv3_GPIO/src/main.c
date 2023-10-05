/***********************************************************************
 * 
 * Blink a LED in Arduino-style and use function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2022 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#define LED_GREEN PB5   // PB5 is AVR pin where green on-board LED 
#define LED_EXTER PB0
#define BUTTON PD2 //tlačítko na pinu 2 na arduino desce
                        // is connected
#define SHORT_DELAY_1 250 // Delay in milliseconds
//#define SHORT_DELAY_2 5000 // Delay in milliseconds
#ifndef F_CPU
# define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif

#include <gpio.h> //nutno includovat abychom mohli použít vytvořený gpio modul

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // Functions for busy-wait delay loops


// -----
// This part is needed to use Arduino functions but also physical pin
// names. We are using Arduino-style just to simplify the first lab.
//#include "Arduino.h"
//#define PB5 13          // In Arduino world, PB5 is called "13"
//#define PB0 8 
// -----

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    //uint8_t led_value = 0;  // Local variable to keep LED status

    // Set pin where on-board LED is connected as output
    //pinMode(LED_GREEN, OUTPUT);
    //pinMode(LED_EXTER, OUTPUT);
    
    //DDRB = DDRB | (1<<LED_GREEN);
    //DDRB = DDRB | (1<<LED_EXTER);

    GPIO_mode_output(&DDRB, LED_GREEN); //ddr registr slouží k nastavování I/O; port registr slouží k zápisu přinastavení jako výstupy, pin regist slouží ke čtení stavu při nastavení jako vstup
    GPIO_mode_output(&DDRB, LED_EXTER);
    GPIO_mode_input_pullup(&DDRD, BUTTON);

    while (1)
    {
        // Pause several milliseconds
        _delay_ms(SHORT_DELAY_1);

        // Change LED value
        if (GPIO_read(&PIND, 2) == 0) {
            // Set pin to HIGH
            //digitalWrite(LED_GREEN, HIGH);
            //digitalWrite(LED_EXTER, HIGH);
            
            //PORTB |= (1<<LED_GREEN);
            //PORTB |= (1<<LED_EXTER);
            GPIO_write_high(&PORTB, LED_GREEN);
            GPIO_write_high(&PORTB, LED_EXTER);

        }
        else {
            // Clear pin to LOW
            //digitalWrite(LED_GREEN, LOW);
            //digitalWrite(LED_EXTER, LOW);
            
            //PORTB &= ~(1<<LED_EXTER);
            //PORTB &= ~(1<<LED_GREEN);

            GPIO_write_low(&PORTB, LED_GREEN);
            GPIO_write_low(&PORTB, LED_EXTER);
            
        }
    }

    // Will never reach this
    return 0;
}
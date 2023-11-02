// https://github.com/Sylaina/oled-display
//* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <twi.h>            // I2C/TWI library for AVR-GCC
#include <stdlib.h>         // C library. Needed for number conversions
#include <oled.h>

/* Global variables --------------------------------------------------*/
// Declaration of "dht12" variable with structure "DHT_values_structure"
struct DHT_values_structure {
   uint8_t hum_int;
   uint8_t hum_dec;
   uint8_t temp_int;
   uint8_t temp_dec;
   uint8_t checksum;
} dht12;

// Flag for printing new data from sensor
volatile uint8_t new_sensor_data = 0;


// Slave and internal addresses of temperature/humidity sensor DHT12
#define SENSOR_ADR 0x5c
#define SENSOR_HUM_MEM 0
#define SENSOR_TEMP_MEM 2
#define SENSOR_CHECKSUM 4

int main(void)
{
char string[2];  // String for converting numbers by itoa()
char str_temp[2];

    // TWI
    twi_init();

    oled_init(OLED_DISP_ON);
    oled_clrscr();

    sei();  // Needed for UART

    


    // Timer1
    TIM1_OVF_1SEC
    TIM1_OVF_ENABLE

    sei();

    // Infinite loop
    while (1) {
        if (new_sensor_data == 1) {
            
            // Do not print it again and wait for the new data
            new_sensor_data = 0;
            //oled_clrscr();
            oled_charMode(NORMALSIZE);
            itoa(dht12.temp_int, string, 10);
            str_temp = strcat(string,'.');
            itoa(dht12.temp_int, string, 10);
            str_temp = strcat(str_temp,string);
            oled_puts(str_temp);
            oled_display();
            //new_sensor_data = 0;
        
        }
    }

    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
* Function: Timer/Counter1 overflow interrupt
* Purpose:  Read temperature and humidity from DHT12, SLA = 0x5c.
**********************************************************************/
ISR(TIMER1_OVF_vect)
{
    // Test ACK from sensor
    twi_start();
    if (twi_write((SENSOR_ADR<<1) | TWI_WRITE) == 0) {
        // Set internal memory location
        twi_write(SENSOR_TEMP_MEM);
        twi_stop();
        // Read data from internal memory
        twi_start();
        twi_write((SENSOR_ADR<<1) | TWI_READ);
        dht12.temp_int = twi_read(TWI_ACK);
        dht12.temp_dec = twi_read(TWI_NACK);

        new_sensor_data = 1;
    }
    twi_stop();
}

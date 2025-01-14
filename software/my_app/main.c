/******************************************************************************
 *  Version 3 (lightweight): 8-LED Chaser + Button + Switch-based Speed
 *  - Use alt_printf instead of printf
 *  - Potentially smaller footprint with small C library
 ******************************************************************************/
#include <unistd.h>                // usleep
#include <stdint.h>                // uint32_t
#include <sys/alt_stdio.h>         // alt_printf, alt_putstr
#include "system.h"
#include "altera_avalon_pio_regs.h"


static unsigned int calc_delay_us(uint32_t switch_val)
{
    unsigned int base_delay = 50000;  // 50ms
    unsigned int step       = 30000;  // 30ms
    if (switch_val > 15) {
        switch_val = 15;
    }
    return base_delay + switch_val * step;
}

int main(void)
{
    
    alt_printf("=== Light-Weight Version 3: LED Chaser + Button + Switch ===\n");

    unsigned int led_pattern = 0x01;
    unsigned int running     = 1;  
    unsigned int old_button  = 1;

    while (1) {
        
        unsigned int btn_now = IORD_ALTERA_AVALON_PIO_DATA(PIO_BUTTON_BASE) & 0x1;
        if ((old_button == 1) && (btn_now == 0)) {
            running = !running;
            alt_printf("BTN pressed => running=%x\n", running);
        }
        old_button = btn_now;

        
        unsigned int sw_val = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_BASE) & 0xF;
        unsigned int delay_us = calc_delay_us(sw_val);

        
        if (running) {
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_LEDS_BASE, led_pattern);

            led_pattern <<= 1;
            if (led_pattern == 0x100) {
                led_pattern = 0x01;
            }
        }

        
        usleep(delay_us);
    }
    return 0;
}
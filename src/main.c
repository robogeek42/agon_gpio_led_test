/*
  vim:ts=4
  vim:sw=4
*/
#include "agon/vdp.h"
#include "agon/mos.h"
#include "agon/keyboard.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define PB_DAT 0x009A
#define PB_DIR 0x009B
#define PC_DAT 0x009E
#define PC_DIR 0x009F
#define PD_DAT 0x00A2
#define PD_DIR 0x00A3

// BUSY WAIT: Delay a number of clock ticks
void delay(int timeout)
{
	clock_t timeout_ticks = clock()+timeout;
	do {
	} while( timeout_ticks > clock() );
}

// Thanks to tomm8086 and calc84maniac on the Agon Discord
// for the magic functions below

// Read from a IO port
static inline uint8_t io_in(int addr)
{
    return *((volatile uint8_t __attribute__((address_space(3))) *)addr);
}

// Read from a IO port
static inline void io_out(int addr, uint8_t value)
{
    *((volatile uint8_t __attribute__((address_space(3))) *)addr) = value;
}


// MAIN
int main(/*int argc, char *argv[]*/)
{
	kbuf_init(16);
    // Connect a LED to Port C Pin 7 with a current-limiting resistor

    printf("Press any key to exit\n");

    bool bquit = false;
	struct keyboard_event_t e;

    // Set Bit 7 of PortD to be an output
    io_out(PD_DIR, 0x7F);
    
    uint8_t state = 0;

    while (!bquit)
    {
        if (kbuf_poll_event(&e))
        {
            bquit = true;
        }
        io_out(PD_DAT, state << 7);
        state = 1 - state;
        delay(20);
    }

    // turn off the LED before exiting
    io_out(PD_DAT, 0);

    printf("\nBye.\n");

	kbuf_deinit();
    return 0;
}


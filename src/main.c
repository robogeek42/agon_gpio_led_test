/*
  vim:ts=4
  vim:sw=4
*/
#include "agon/vdp.h"
#include "agon/mos.h"
#include "agon/keyboard.h"
#include "agon/timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include <ez80f92.h>  // defines IO(addr) macro

#define PB_DAT 0x009A
#define PB_DIR 0x009B
#define PC_DAT 0x009E
#define PC_DIR 0x009F
#define PD_DAT 0x00A2
#define PD_DIR 0x00A3

// MAIN
int main(/*int argc, char *argv[]*/)
{
	kbuf_init(16);
    // Connect a LED to Port C Pin 7 with a current-limiting resistor

    printf("Press any key to exit\n");

    bool bquit = false;
	struct keyboard_event_t e;

    // Set Bit 7 of PortD to be an output
    IO(PD_DIR) = 0x7F;
    
    uint8_t state = 0;

    while (!bquit)
    {
        IO(PD_DAT) = state << 7;
        state = 1 - state;
        delay(200);
        if (kbuf_poll_event(&e))
        {
            bquit = true;
        }
    }

    // turn off the LED before exiting
    IO(PD_DAT) = 0;

    printf("\nBye.\n");

	kbuf_deinit();
    return 0;
}


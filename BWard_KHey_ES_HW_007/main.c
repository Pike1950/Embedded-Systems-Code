// Name: Kole Hey/Brad Ward
// Embedded Systems - ECE 4380
// TSK and SEM (HW6)
// Date: 10/29/19

// Adapted from 540 bios semaphore
// Written by Dr. Brian Nutter


#include "DspBiosConfigurationcfg.h"
#include "dsk6713_dip.h"
#include "dsk6713_led.h"
#include "dsk6713.h"
#include <sem.h>

void init(void);

int main(void) {
	
	init();
}


void init(void) {
	DSK6713_init();
	CSL_init();
	DSK6713_LED_init();
	DSK6713_DIP_init();

	DSK6713_LED_off(0);
	DSK6713_LED_off(1);
	DSK6713_LED_off(2);
	DSK6713_LED_off(3);
}


void TSK0_ftn() {
	for(;;) {
		SEM_pendBinary(&SEM0, SYS_FOREVER);
			if (DSK6713_DIP_get(0) == 0) {
				DSK6713_LED_on(0);
				while(DSK6713_DIP_get(1) == 1) { }
				DSK6713_LED_off(0);
			}
			SEM_postBinary(&SEM0);
	}
}


void TSK1_ftn() {
	for(;;) {
			SEM_pendBinary(&SEM0, SYS_FOREVER);
				if (DSK6713_DIP_get(3) == 0) {
					DSK6713_LED_on(2);
					while(DSK6713_DIP_get(2) == 1) { }
					DSK6713_LED_off(2);
				}
				SEM_postBinary(&SEM0);
	}
}


void TSK2_ftn() {
	SEM_postBinary(&SEM0);
}

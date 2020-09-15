// Name: Brad Ward
// Embedded Systems - ECE 4380
// Direct Memory Access (HW1)
// Date: 09/01/19

void main(void) {
	// Switches address
	// 0x90080000

	// continuous loop
	while(1) {
        // set character pointer to switches address
		char* LED_ARRAY = (char *) 0x90080000;
        // bit shift the value of the switches to the LEDs
		// and invert the bits
		*LED_ARRAY = ~*(LED_ARRAY) >> 4;
	}
}

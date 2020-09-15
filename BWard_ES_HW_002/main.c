// Name: Brad Ward
// Embedded Systems - ECE 4380
// Audio Passthrough (HW2)
// Date: 09/11/19

// Adapted from 070 AUDIO sample code
// Written by Dr. Brian Nutter

//-------------------------------------------------------------------
#include "dsk6713.h"
#include "dsk6713_dip.h"
#include "dsk6713_led.h"
#include "dsk6713_aic23.h"  	  						//codec-dsk support file

//-------------------------------------------------------------------
//-------------------------------------------------------------------

//-------------------------------------------------------------------
DSK6713_AIC23_Config config1 = {
	0x0017 , /* 0 Left line input channel volume */
	0x0017 , /* 1 Right line input channel volume */
	0x00F9 , /* 2 Left channel headphone volume */
	0x00F9 , /* 3 Right channel headphone volume */
	0x0011 , /* 4 Analog audio path control */
	0x0000 , /* 5 Digital audio path control */
	0x0000 , /* 6 Power down control */
	0x0043 , /* 7 Digital audio interface format */
	0x0081 , /* 8 Sample rate control (48 kHz) */
	0x0001 /* 9 Digital interface activation */
};

DSK6713_AIC23_CodecHandle hCodec;

union {
	Uint32 uint;
	short channel[2];
	} AIC_data;

//---------------------------------------------------------------------------------------------

#define LEFT  1                  //data structure for union of 32-bit data
#define RIGHT 0                  //into two 16-bit data

//-------------------------------------------------------------------


//-------------------------------------------------------------------
void main(void);
void output_sample(int out_data);
Uint32 input_sample(void);

int buff[16];
int j=0;								// universal counter of samples
volatile Uint8 *VOLUME_SEL = (Uint8 *) 0x90080000; // Pointer address to 4 LEDs next to 4 DIP switches

//-------------------------------------------------------------------

//-------------------------------------------------------------------
void main(void)
{
	int i=0;							// local counter for buffer

	CSL_init();

	DSK6713_init();
	hCodec = DSK6713_AIC23_openCodec(0, &config1);			// defaults to 16-bit frame.

//	* (volatile int *) 0x0190000C = 0x000000A0;						// prefer a double 16-bit frame
//	* (volatile int *) 0x01900010 = 0x000000A0;

	for(;;) // ever
	{
		buff[i]= input_sample();
		output_sample(buff[i]);
		i++;
		j++;
		i &= 0xF;
	} // for(ever)
} // void main(void)
//-------------------------------------------------------------------

//-------------------------------------------------------------------
void output_sample(int out_data)    //for out to Left and Right channels
{

	//AIC_data.uint=out_data;          //32-bit data -->data structure

	int multiplier = (int)(*VOLUME_SEL >> 4); // 4 DIP switches set volume multiplier

	int tempAudio = (int)AIC_data.channel[0] * multiplier; // Multiply the current data sample and store in a signed 32-bit
													  // variable to prevent overflow and distortion of sample

	if (tempAudio > 32767)
		tempAudio = 32767; // If temp value exceeds limit of signed 16-bit variable, then set value to limit
	else if (tempAudio < -32768)
		tempAudio = -32768; // Do the same for the negative range of the signed 16-bit variable

	AIC_data.channel[0] = (short)tempAudio; // Put the data back into the signed 16-bit variable to output to line out

    while(!MCBSP_xrdy(DSK6713_AIC23_DATAHANDLE));//if ready to transmit

    MCBSP_write(DSK6713_AIC23_DATAHANDLE, AIC_data.uint);//write/output data

} // void output_sample(int out_data)
//-------------------------------------------------------------------


//-------------------------------------------------------------------
Uint32 input_sample(void)                      	  	//for 32-bit input
{
	while(!MCBSP_rrdy(DSK6713_AIC23_DATAHANDLE));//if ready to receive

	AIC_data.uint=MCBSP_read(DSK6713_AIC23_DATAHANDLE);//read data

	return(AIC_data.uint);
} // Uint32 input_sample(void)
//-------------------------------------------------------------------

// Name: Kole Hey/Brad Ward
// Embedded Systems - ECE 4380
// DSP BIOS and Audio (HW8)
// Date: 11/21/19

// Adapted from 130 BSL AUDIO EDMA triple, 170 & 180 fixed point math, and 580 bios EDMA
// Written by Dr. Brian Nutter

#include "dsk6713.h"
#include "dsk6713_dip.h"
#include "dsk6713_led.h"
#include "dsk6713_aic23.h"  	  						//codec-dsk support file
#include "csl_edma.h"
#include "app_codec.h"

#include <c67fastMath.h>

#include "coefficients.h"

#include <std.h>
#include <log.h>
#include <prd.h>
#include <hwi.h>
#include <swi.h>

#include "HW8_KoleHey_BradWardcfg.h"


//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------

#define BUFLEN 0x80				// if you change this number, you have to go to the EDMA parameters
								// and change the number of reloads, the skip forward, and the skip backward
#define BUFWIDTH 2
#define FILSIZE 0x51
#define LEFT  1                  //data structure for union of 32-bit data
#define RIGHT 0                  //into two 16-bit data

#pragma DATA_SECTION (rx_ping, ".sysdata");
#pragma DATA_ALIGN   (rx_ping, 0x80);
shortDP15 rx_ping[BUFWIDTH][BUFLEN];

#pragma DATA_SECTION (rx_pong, ".sysdata");
#pragma DATA_ALIGN   (rx_pong, 0x80);
shortDP15 rx_pong[BUFWIDTH][BUFLEN];

#pragma DATA_SECTION (rx_pang, ".sysdata");
#pragma DATA_ALIGN   (rx_pang, 0x80);
shortDP15 rx_pang[BUFWIDTH][BUFLEN];

#pragma DATA_SECTION (tx_ping, ".sysdata");
#pragma DATA_ALIGN   (tx_ping, 0x80);
short tx_ping[BUFWIDTH][BUFLEN];

#pragma DATA_SECTION (tx_pong, ".sysdata");
#pragma DATA_ALIGN   (tx_pong, 0x80);
short tx_pong[BUFWIDTH][BUFLEN];

#pragma DATA_SECTION (tx_pang, ".sysdata");
#pragma DATA_ALIGN   (tx_pang, 0x80);
short tx_pang[BUFWIDTH][BUFLEN];
#include "app_edma.h"

//-------------------------------------------------------------------
// declare the CSL objects
EDMA_Handle hEdma_rx;     // Handle for the EDMA channel
EDMA_Handle hEdmaPing_rx; // Handle for the ping EDMA reload parameters
EDMA_Handle hEdmaPong_rx; // Handle for the pong EDMA reload parameters
EDMA_Handle hEdmaPang_rx; // Handle for the pong EDMA reload parameters
EDMA_Config cfgEdma_rx;   //EDMA configuration structure

EDMA_Handle hEdma_tx;
EDMA_Handle hEdmaPing_tx;
EDMA_Handle hEdmaPong_tx;
EDMA_Handle hEdmaPang_tx;
EDMA_Config cfgEdma_tx;


//-------------------------------------------------------------------
typedef struct _Globals {
	volatile Uint8 filter;

} Globals;

Globals Glo;
//-------------------------------------------------------------------

void main(void);
void output_sample(int out_data);
Uint32 input_sample(void);
void init(void);
long roundDP15(long);
void passAudio(int, int, int, long, long, shortDP15 [FILSIZE], shortDP15 [BUFWIDTH][BUFLEN], shortDP15 [BUFWIDTH][BUFLEN], short [BUFWIDTH][BUFLEN]);
//-------------------------------------------------------------------

void main(void)
{
	init();

    /* fall into DSP/BIOS idle loop */
    return;
} // void main(void)


//-------------------------------------------------------------------
void init(void)	     	 	//for communication/init using interrupt
{
	int i;
	for(i=0; i<BUFLEN; i++)
	  {
	  	rx_ping[RIGHT][i] = 0;
	  	rx_ping[LEFT][i] = 0xffff;
	  	rx_pong[RIGHT][i] = 0;
	  	rx_pong[LEFT][i] = 0xffff;
	  	rx_pang[RIGHT][i] = 0;
	  	rx_pang[LEFT][i] = 0xffff;
	  	tx_ping[RIGHT][i] = 0;
	  	tx_ping[LEFT][i] = 0xffff;
	  	tx_pong[RIGHT][i] = 0;
	  	tx_pong[LEFT][i] = 0xffff;
	  	tx_pang[RIGHT][i] = 0;
	  	tx_pang[LEFT][i] = 0xffff;
	  }
	DSK6713_init();                   	//call BSL to init DSK-EMIF,PLL)
	CSL_init();

   	hCodec = DSK6713_AIC23_openCodec(0, &config1);
                                        // codec has to be open before handle is referenced
   	EDMA_clearPram(0x00000000);

    hEdma_rx = EDMA_open(EDMA_CHA_REVT1, EDMA_OPEN_RESET);
    hEdmaPing_rx = EDMA_allocTable(-1);
    hEdmaPong_rx = EDMA_allocTable(-1);
    hEdmaPang_rx = EDMA_allocTable(-1);

    cfgEdmaPing_rx.rld = EDMA_RLD_RMK(2,hEdmaPong_rx);
    cfgEdmaPong_rx.rld = EDMA_RLD_RMK(2,hEdmaPang_rx);
    cfgEdmaPang_rx.rld = EDMA_RLD_RMK(2,hEdmaPing_rx);

    cfgEdma_rx = cfgEdmaPing_rx;        // start with ping

    EDMA_config(hEdma_rx, &cfgEdma_rx);
    EDMA_config(hEdmaPing_rx, &cfgEdmaPing_rx);
    EDMA_config(hEdmaPong_rx, &cfgEdmaPong_rx);
    EDMA_config(hEdmaPang_rx, &cfgEdmaPang_rx);

    hEdma_tx = EDMA_open(EDMA_CHA_XEVT1, EDMA_OPEN_RESET);
    hEdmaPing_tx = EDMA_allocTable(-1);
    hEdmaPong_tx = EDMA_allocTable(-1);
    hEdmaPang_tx = EDMA_allocTable(-1);

    cfgEdmaPing_tx.rld = EDMA_RLD_RMK(2,hEdmaPong_tx);
    cfgEdmaPong_tx.rld = EDMA_RLD_RMK(2,hEdmaPang_tx);
    cfgEdmaPang_tx.rld = EDMA_RLD_RMK(2,hEdmaPing_tx);

    cfgEdma_tx = cfgEdmaPing_tx;        // start with ping

    EDMA_config(hEdma_tx, &cfgEdma_tx);
    EDMA_config(hEdmaPing_tx, &cfgEdmaPing_tx);
    EDMA_config(hEdmaPong_tx, &cfgEdmaPong_tx);
    EDMA_config(hEdmaPang_tx, &cfgEdmaPang_tx);

    EDMA_intDisable(0xF);               // use 4 EDMA events
    EDMA_intClear(0xF);                 // on one EDMA interrupt
    EDMA_intEnable(0xF);

    EDMA_intDisable(0xE);
    EDMA_intClear(0xE);
    EDMA_intEnable(0xE);

    EDMA_intDisable(0xD);
    EDMA_intClear(0xD);
    EDMA_intEnable(0xD);

    EDMA_intDisable(0xC);
    EDMA_intClear(0xC);
    EDMA_intEnable(0xC);

    EDMA_intDisable(0xB);
    EDMA_intClear(0xB);
    EDMA_intEnable(0xB);

    EDMA_intDisable(0xA);
    EDMA_intClear(0xA);
    EDMA_intEnable(0xA);

    EDMA_enableChannel(hEdma_rx);       // start on the copy of ping

    EDMA_enableChannel(hEdma_tx);       // start on the copy of ping

    IRQ_reset(IRQ_EVT_EDMAINT);
    IRQ_enable(IRQ_EVT_EDMAINT);        // c_int8

  	output_sample(0);                   // start TX to launch EDMA
} // init

//-------------------------------------------------------------------
void output_sample(int out_data)    //for out to Left and Right channels
{
	AIC_data.uint=out_data;          //32-bit data -->data structure

    MCBSP_write(DSK6713_AIC23_DATAHANDLE, AIC_data.uint);//write/output data

} // void output_sample(int out_data)
//-------------------------------------------------------------------


//-------------------------------------------------------------------
Uint32 input_sample(void)                      	  	//for 32-bit input
{

	AIC_data.uint=MCBSP_read(DSK6713_AIC23_DATAHANDLE);//read data

	return(AIC_data.uint);
} // Uint32 input_sample(void)
//-------------------------------------------------------------------

int c_int8(int arg0)            // interrupt service routine
{
	if(EDMA_intTest(0xF))          // rx_ping is full
	{
		EDMA_intClear(0xF);
		SWI_post(&SWI_ping);
	}

	if(EDMA_intTest(0xE))          // tx_ping has been emptied
	{
		EDMA_intClear(0xE);
	}

	if(EDMA_intTest(0xD))          // rx_pong is full
	{
		EDMA_intClear(0xD);
		SWI_post(&SWI_pong);
	}

	if(EDMA_intTest(0xC))          // tx_pong has been emptied
	{
		EDMA_intClear(0xC);
	}

	if(EDMA_intTest(0xB))          // rx_pang is full
	{
		EDMA_intClear(0xB);
		SWI_post(&SWI_pang);
	}

	if(EDMA_intTest(0xA))          // tx_pang has been emptied
	{
		EDMA_intClear(0xA);
	}

	return arg0;

} // c_int8
//------------------------------------------------------------------

long tempR;
long tempL;

int SWI_ping_ftn(int arg0, int arg1) {

	int index;
	int j;
	int i;

	for(i=0;i<BUFLEN;i++)
	{
		tempR = 0;
		tempL = 0;

		if (Glo.filter == 0)
		{
			tx_ping[RIGHT][i] = 0;
			tx_ping[LEFT][i] = 0;
		}

		else if (Glo.filter == 1)
		{
			tx_ping[RIGHT][i] = rx_ping[RIGHT][i];
			tx_ping[LEFT][i]  = rx_ping[LEFT][i];
		}

		else if (Glo.filter == 2)
		{
			passAudio(i, j, index, tempR, tempL, lowPass, rx_ping, rx_pang, tx_ping);
		}

		else if (Glo.filter == 4)
		{
			passAudio(i, j, index, tempR, tempL, bandPass, rx_ping, rx_pang, tx_ping);
		}

		else if (Glo.filter == 8)
		{
			passAudio(i, j, index, tempR, tempL, highPass, rx_ping, rx_pang, tx_ping);
		}

		else
		{
			tx_ping[RIGHT][i] = 0;
			tx_ping[LEFT][i] = 0;
		}
	}

	return arg0;
}

int SWI_pong_ftn(int arg0, int arg1) {

	int index;
	int j;
	int i;

	for(i=0;i<BUFLEN;i++)
	{
		tempR = 0;
		tempL = 0;

		if (Glo.filter == 0)
		{
			tx_pong[RIGHT][i] = 0;
			tx_pong[LEFT][i] = 0;
		}

		else if (Glo.filter == 1)
		{
			tx_pong[RIGHT][i] = rx_pong[RIGHT][i];
			tx_pong[LEFT][i]  = rx_pong[LEFT][i];
		}

		else if (Glo.filter == 2)
		{
			passAudio(i, j, index, tempR, tempL, lowPass, rx_pong, rx_ping, tx_pong);
		}

		else if (Glo.filter == 4)
		{
			passAudio(i, j, index, tempR, tempL, bandPass, rx_pong, rx_ping, tx_pong);
		}

		else if (Glo.filter == 8)
		{
			passAudio(i, j, index, tempR, tempL, highPass, rx_pong, rx_ping, tx_pong);
		}

		else
		{
			tx_pong[RIGHT][i] = 0;
			tx_pong[LEFT][i] = 0;
		}
	}
	return arg0;
}

int SWI_pang_ftn(int arg0, int arg1) {

	int index;
	int j;
	int i;

	for(i=0;i<BUFLEN;i++)
	  {
		tempR = 0;
		tempL = 0;

		if (Glo.filter == 0)
		{
			tx_pang[RIGHT][i] = 0;
			tx_pang[LEFT][i] = 0;
		}


		else if (Glo.filter == 1)
		{
			tx_pang[RIGHT][i] = rx_pang[RIGHT][i];
			tx_pang[LEFT][i]  = rx_pang[LEFT][i];
		}

		else if (Glo.filter == 2)
		{
			passAudio(i, j, index, tempR, tempL, lowPass, rx_pang, rx_pong, tx_pang);
		}

		else if (Glo.filter == 4)
		{
			passAudio(i, j, index, tempR, tempL, bandPass, rx_pang, rx_pong, tx_pang);
		}

		else if (Glo.filter == 8)
		{
			passAudio(i, j, index, tempR, tempL, highPass, rx_pang, rx_pong, tx_pang);
		}

		else
		{
			tx_pang[RIGHT][i] = 0;
			tx_pang[LEFT][i] = 0;
		}
	  } //for
	return arg0;
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

void getSwitches(int arg0, int arg1) {
	volatile Uint8 *USER_REG = (Uint8 *) 0x90080000;

	Glo.filter = (*USER_REG >> 4);

	return;
}

void passAudio(int x, int y, int indexNum, long rightChannel, long leftChannel, shortDP15 filter[], shortDP15 inAudBuf1[BUFWIDTH][BUFLEN], shortDP15 inAudBuf2[BUFWIDTH][BUFLEN], short outAudBuf[BUFWIDTH][BUFLEN])
{
	for(y=0;y<81;y++) {
		indexNum = x - y;

		if (indexNum >= 0) {
			rightChannel = _lsadd(inAudBuf1[RIGHT][indexNum] * filter[y], rightChannel);
			leftChannel = _lsadd(inAudBuf1[LEFT][indexNum] * filter[y], leftChannel);
		}
		else {
			rightChannel = _lsadd(inAudBuf2[RIGHT][BUFLEN+indexNum] * filter[y], rightChannel);
			leftChannel = _lsadd(inAudBuf2[LEFT][BUFLEN+indexNum] * filter[y], leftChannel);
		}
	}

	rightChannel = roundDP15(rightChannel);
	leftChannel = roundDP15(leftChannel);

	outAudBuf[RIGHT][x] = _sat(rightChannel >> 15);
	outAudBuf[LEFT][x] = _sat(leftChannel >> 15);

	return;
}

long roundDP15(long audioChannel)
{
	if(audioChannel >= 0)
		audioChannel = _lsadd(1<<14, audioChannel);
	else
		audioChannel = _lsadd(-(1<<14), audioChannel);

	return audioChannel;
}
//-------------------------------------------------------------------


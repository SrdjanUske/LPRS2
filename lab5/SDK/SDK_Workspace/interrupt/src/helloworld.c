/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include <xparameters.h>
#include "xio.h"
#include "xintc.h"
#include "vga_periph_mem.h"
#include "xil_exception.h"


void print(char *str);

XIntc Intc;

void my_timer_interrupt_handler(void * baseaddr_p) {
	xil_printf("\n\rtimer timeout.");
}


int main()
{
	init_platform();

	 	XStatus Status;
	    Xuint32 value1, value2, value3;

	    xil_printf("Interrupt example\n\r");

	    //Set Terminal count for my_timer
	    XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 4*7, 480);

	    // Run my_timer
	    XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 4*8, 1);



	    unsigned char string_s[] = "LPRS 2 sestro\n";

	    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x00, 0x0);// direct mode   0
	    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0x3);// display_mode  1
	    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x08, 0x1);// show frame      2
	    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x0C, 0x1);// font size       3
	    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0xFFFFFF);// foreground 4
	    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14, 0x00FFFF);// background color 5
	    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0xFF0000);// frame color      6

	    print("Hello World\n\r");

	    clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
	    clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
	    draw_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
	    set_cursor(350);
	    int i = -6; //-6 17+8
	    int j = 0;
	    int sw = 0;
	    set_foreground_color(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, 0x000000);
	    draw_rectangle(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
	    set_font_size(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, 0x1);

	   /*while(1){
	    	for ( j = 0; j < 1000000; j++ )
	    	{

	    	}
	    	if (i == ( 33 - 4 )) {
	    		sw = 1;
	    	}
	    	else if (i == -6) {
	    		sw = 0;
	    	}
	    	if(sw == 1){
	    		i--;
	    		clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
	    		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR+4*i, "lprs", 4);
	    	}
	    	else if ( sw == 0)
	    	{
	    		i++;
	    		clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
	    		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR+4*i, "lprs", 4);
	    	}*/

	   	}
	    //clear_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);

	   // Read my_timer register to verify that TC value is written
		 value1 = XIo_In32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x0);
		 xil_printf("\n\rvalue1 = %x.", value1);
		 //initialize interrupt controller
		 Status = XIntc_Initialize (&Intc, XPAR_INTC_0_DEVICE_ID);
		 if (Status != XST_SUCCESS) xil_printf ("\r\nInterrupt controller initialization failure");
		 else xil_printf("\r\nInterrupt controller initialized");

		 // Connect my_timer_interrupt_handler
		 Status = XIntc_Connect (&Intc, XPAR_INTC_0_MY_TIMER_0_VEC_ID, (XInterruptHandler) my_timer_interrupt_handler, (void *)0);
		 if (Status != XST_SUCCESS) xil_printf ("\r\nRegistering MY_TIMER Interrupt Failed");
		 else xil_printf("\r\nMY_TIMER Interrupt registered");
		 //start the interrupt controller in real mode
		 Status = XIntc_Start(&Intc, XIN_REAL_MODE);
		 //enable interrupt controller
		 XIntc_Enable (&Intc, XPAR_INTC_0_MY_TIMER_0_VEC_ID);
		 microblaze_enable_interrupts();



    return 0;
}

/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F57Q43
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <time.h>
/*
                         Main application
 */
void send_AT(char *t);


void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    srand(time(NULL));
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    char texto2[]="Hala mundo2! \r\n";
    int r ;
    char msg[50];
    
    while (1)
    {
        
        
        //printf("hello world! \r\n"); //uart5
        
        //send_AT("Hola mundo2! \r\n");//uart1
        send_AT("AT \r\n");
         __delay_ms(2000);
        send_AT("AT$RC \r\n");
         __delay_ms(2000);
        
        r = rand()%20;
        snprintf(msg,50,"AT$SF=%d \r\n",r); 
        
        //send_AT("AT$SF=09 \r\n");
        send_AT(msg);
        printf(msg);
         __delay_ms(20000);
        
        /*
        for(int i=0;i<(sizeof(texto2));i++){
            if(UART1_is_tx_ready())
            {
                UART1_Write(texto2[i]); //uart1
            }
        }
         * */
        //UART1_Write('\n');
        
        __delay_ms(1000);
    }
}

void send_AT(char *t)
   {
   while(*t)
      {
       if(UART1_is_tx_ready())
        {
            UART1_Write(*t);
            ++t;
        }
      }
   }
/**
void main(void)
    {
        volatile uint8_t rxData;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        while(1)
        {
            // Logic to echo received data
            if(UART1_is_rx_ready())
            {
                rxData = UART1_Read();
                if(UART1_is_tx_ready())
                {
                    UART1_Write(rxData);
                }
            }
        }
    }
*/
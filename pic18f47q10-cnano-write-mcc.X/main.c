/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/i2c_host/i2c_host_types.h"
#include "mcc_generated_files/i2c_host/mssp1.h"

#define I2C_CLIENT_ADDR             0x20
#define MCP23008_REG_ADDR_IODIR     0x00
#define MCP23008_REG_ADDR_GPIO      0x09
#define PINS_DIGITAL_OUTPUT         0x00
#define PINS_DIGITAL_HIGH           0xFF
#define DATALENGTH                  2

const i2c_host_interface_t *I2C = &i2c1_host_interface;

int main(void)
{
    /* Initialize the device */
    SYSTEM_Initialize();
    __delay_ms(20);
    uint8_t data[DATALENGTH];
    
    /* Configure GPIO as output */
    data[0] = MCP23008_REG_ADDR_IODIR;
    data[1] = PINS_DIGITAL_OUTPUT;
    if (I2C->Write(I2C_CLIENT_ADDR, data, DATALENGTH))
    {
        while(I2C->IsBusy())
        {
            I2C->Tasks();
        }
        if (I2C->ErrorGet() == I2C_ERROR_NONE)
        {
            /* Write operation is successful */
        }
        else
        {
            /* Error handling */
        }
    }
    /* Write data to GPIO pins */
    data[0] = MCP23008_REG_ADDR_GPIO;
    data[1] = PINS_DIGITAL_HIGH;
    
    while(1)
    {
        if (I2C->Write(I2C_CLIENT_ADDR, data, DATALENGTH))
        {
            while(I2C->IsBusy())
            {
                I2C->Tasks();
            }
            if (I2C->ErrorGet() == I2C_ERROR_NONE)
            {
                /* Write operation is successful */
            }
            else
            {
                /* Error handling */
            }
            
            /* Toggle the output data */
            data[1] = ~data[1];
        } 
        /* Delay 1 second */
         __delay_ms(1000);
    }
}
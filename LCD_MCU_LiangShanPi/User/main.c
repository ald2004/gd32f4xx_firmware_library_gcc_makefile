/*!
	\file    main.c
	\brief   led spark with systick

	\version 2016-08-15, V1.0.0, firmware for GD32F4xx
	\version 2018-12-12, V2.0.0, firmware for GD32F4xx
	\version 2020-09-30, V2.1.0, firmware for GD32F4xx
	\version 2022-03-09, V3.0.0, firmware for GD32F4xx
*/

/*
	Copyright (c) 2022, GigaDevice Semiconductor Inc.

	Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.
	3. Neither the name of the copyright holder nor the names of its contributors
	   may be used to endorse or promote products derived from this software without
	   specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"

#include "usart0.h"
#include "led.h"
#include "key.h"
#include "lcd.h"


uint16_t POINT[5]={WHITE,BLUE,RED,YELLOW,GREEN};
uint16_t BACK[5]={LIGHTGREEN,LIGHTGRAY,LGRAY,LGRAYBLUE,LBBLUE};

/*!
	\brief    main function
	\param[in]  none
	\param[out] none
	\retval     none
*/
int main(void)
{
    uint16_t i;
    
    systick_config();
    usart0_init();
    led_init();
    key_init();
    
    printf("start!\r\n");
    
    /* 8080 mcu�� */
    LCD_Init(); //��ʾ����ʼ������

    while(1)
    {
        for(i=0;i<5;i++)
        {
            POINT_COLOR=POINT[i];
            BACK_COLOR=BACK[i];
            
            LCD_Clear(BACK[i]);
            LCD_ShowString(30,50,480,80,24,1,"https://lckfb.com");
            LCD_ShowString(30,80,480,110,24,1,lcd_id);
            delay_1ms(800);
        }
        
    }

}

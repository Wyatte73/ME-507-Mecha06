
#include "stm32f4xx_hal.h"

typedef struct{

	GPIO_TypeDef* RS;
	uint16_t 	 RS_n;

	GPIO_TypeDef* RW;
	uint16_t 	 RW_n;

	GPIO_TypeDef* EN;
	uint16_t 	 EN_n;

	GPIO_TypeDef* D0;
	uint16_t 	 D0_n;

	GPIO_TypeDef* D1;
	uint16_t 	 D1_n;

	GPIO_TypeDef* D2;
	uint16_t 	 D2_n;

	GPIO_TypeDef* D3;
	uint16_t 	 D3_n;

	GPIO_TypeDef* D4;
	uint16_t 	 D4_n;

	GPIO_TypeDef* D5;
	uint16_t 	 D5_n;

	GPIO_TypeDef* D6;
	uint16_t 	 D6_n;

	GPIO_TypeDef* D7;
	uint16_t 	 D7_n;
}LCD_param_t;

void Init(LCD_param_t inp);
//makes sure all pins are in the correct state

void ClearDis(LCD_param_t inp);

void ShiftCursor(LCD_param_t inp, char dir);
//shifts cursor left or right based on the digit value L or R

void PutChar(LCD_param_t inp, char dig);
//puts character at the cursor location




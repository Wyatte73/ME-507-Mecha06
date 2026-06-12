/*
 * LCD.c
 *
 *  Created on: Jun 10, 2026
 *      Author: maxwe
 */
#include <LCD.h>

void clearData(LCD_param_t inp){
	HAL_GPIO_WritePin(inp.RS,inp.RS_n,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inp.RW,inp.RW_n,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inp.D0,inp.D0_n,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inp.D1,inp.D1_n,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inp.D2,inp.D2_n,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inp.D3,inp.D3_n,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inp.D4,inp.D4_n,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inp.D5,inp.D5_n,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inp.D6,inp.D6_n,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inp.D7,inp.D7_n,GPIO_PIN_RESET);
	return;
}

void sendData(LCD_param_t inp){
	HAL_GPIO_WritePin(inp.EN, inp.EN_n, GPIO_PIN_SET);
	    HAL_Delay(1);   // EN high pulse — >450ns required
	    HAL_GPIO_WritePin(inp.EN, inp.EN_n, GPIO_PIN_RESET);
	    HAL_Delay(1);   // Hold time before next operation
}
static void sendCmd(LCD_param_t inp, uint8_t cmd) {
    HAL_GPIO_WritePin(inp.RS, inp.RS_n, GPIO_PIN_RESET); // RS=0 → command
    HAL_GPIO_WritePin(inp.RW, inp.RW_n, GPIO_PIN_RESET); // RW=0 → write

    if (cmd & 0x01) HAL_GPIO_WritePin(inp.D0, inp.D0_n, GPIO_PIN_SET);
    if (cmd & 0x02) HAL_GPIO_WritePin(inp.D1, inp.D1_n, GPIO_PIN_SET);
    if (cmd & 0x04) HAL_GPIO_WritePin(inp.D2, inp.D2_n, GPIO_PIN_SET);
    if (cmd & 0x08) HAL_GPIO_WritePin(inp.D3, inp.D3_n, GPIO_PIN_SET);
    if (cmd & 0x10) HAL_GPIO_WritePin(inp.D4, inp.D4_n, GPIO_PIN_SET);
    if (cmd & 0x20) HAL_GPIO_WritePin(inp.D5, inp.D5_n, GPIO_PIN_SET);
    if (cmd & 0x40) HAL_GPIO_WritePin(inp.D6, inp.D6_n, GPIO_PIN_SET);
    if (cmd & 0x80) HAL_GPIO_WritePin(inp.D7, inp.D7_n, GPIO_PIN_SET);

    sendData(inp);
    clearData(inp);
    return;
}


void Init(LCD_param_t inp) {
    // All pins low to start
    clearData(inp);
    HAL_GPIO_WritePin(inp.EN, inp.EN_n, GPIO_PIN_RESET);

    // Wait >40ms after VCC rises to 2.7V (datasheet requirement)
    HAL_Delay(50);

    // --- Hitachi HD44780 initialization by instruction ---

    // Step 1: Function Set — send 0x30 three times with required delays
    sendCmd(inp, 0x30);
    HAL_Delay(5);   // Wait >4.1ms

    sendCmd(inp, 0x30);
    HAL_Delay(1);   // Wait >100µs

    sendCmd(inp, 0x30);
    HAL_Delay(1);

    // Step 2: Function Set — configure 8-bit, 2-line, 5x8 font (0x38)
    sendCmd(inp, 0x38);
    HAL_Delay(1);

    // Step 3: Display OFF
    sendCmd(inp, 0x08);
    HAL_Delay(1);

    // Step 4: Clear Display — requires 1.52ms execution time
    sendCmd(inp, 0x01);
    HAL_Delay(2);

    // Step 5: Entry Mode Set — increment cursor, no display shift
    sendCmd(inp, 0x06);
    HAL_Delay(1);

    // Step 6: Display ON, cursor off, blink off
    sendCmd(inp, 0x0C);
    HAL_Delay(1);
    return;
}

void ClearDis(LCD_param_t inp){
	HAL_GPIO_WritePin(inp.D0,inp.D0_n,GPIO_PIN_SET);
	sendData(inp);
	HAL_Delay(2);
	clearData(inp);
	return;
}

void PutChar(LCD_param_t inp, char dig){
	HAL_GPIO_WritePin(inp.RS,inp.RS_n,GPIO_PIN_SET);

	if(dig & 0b1) HAL_GPIO_WritePin(inp.D0,inp.D0_n,GPIO_PIN_SET);
	if(dig >> 1 & 0b1) HAL_GPIO_WritePin(inp.D1,inp.D1_n,GPIO_PIN_SET);
	if(dig >> 2 & 0b1) HAL_GPIO_WritePin(inp.D2,inp.D2_n,GPIO_PIN_SET);
	if(dig >> 3 & 0b1) HAL_GPIO_WritePin(inp.D3,inp.D3_n,GPIO_PIN_SET);
	if(dig >> 4 & 0b1) HAL_GPIO_WritePin(inp.D4,inp.D4_n,GPIO_PIN_SET);
	if(dig >> 5 & 0b1) HAL_GPIO_WritePin(inp.D5,inp.D5_n,GPIO_PIN_SET);
	if(dig >> 6 & 0b1) HAL_GPIO_WritePin(inp.D6,inp.D6_n,GPIO_PIN_SET);
	if(dig >> 7 & 0b1) HAL_GPIO_WritePin(inp.D7,inp.D7_n,GPIO_PIN_SET);

	sendData(inp);
	clearData(inp);
	return;
}

void ShiftCursor(LCD_param_t inp, char dir){
	HAL_GPIO_WritePin(inp.D4,inp.D4_n,GPIO_PIN_SET);
	HAL_GPIO_WritePin(inp.D3,inp.D3_n,GPIO_PIN_RESET);
	if(dir=='R')HAL_GPIO_WritePin(inp.D2,inp.D2_n,GPIO_PIN_SET);
	else HAL_GPIO_WritePin(inp.D2,inp.D2_n,GPIO_PIN_RESET);

	sendData(inp);
	clearData(inp);
	return;
}











/*
 * input_reading.h
 *
 *  Created on: Oct 18, 2021
 *      Author: Dell
 */
#include "main.h"
#ifndef INC_BUTTON_INPUT_READING_H_
#define INC_BUTTON_INPUT_READING_H_

#define BUTTON_1_PORT	GPIOB
#define BUTTON_1_PIN	GPIO_PIN_0
#define BUTTON_2_PORT	GPIOB
#define BUTTON_2_PIN	GPIO_PIN_1
#define BUTTON_3_PORT	GPIOB
#define BUTTON_3_PIN	GPIO_PIN_2
#define BUTTON_4_PORT	GPIOB
#define BUTTON_4_PIN	GPIO_PIN_3

void reading_button(void);
unsigned char is_button_pressed(uint8_t index);
unsigned char is_button_pressed_1s(uint8_t index);

#endif /* INC_BUTTON_INPUT_READING_H_ */

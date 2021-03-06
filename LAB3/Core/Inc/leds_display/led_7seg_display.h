/*
 * led_7seg_display.h
 *
 *  Created on: Oct 18, 2021
 *      Author: Dell
 */

#include "main.h"
#ifndef INC_LEDS_DISPLAY_LED_7SEG_DISPLAY_H_
#define INC_LEDS_DISPLAY_LED_7SEG_DISPLAY_H_

#define ENABLE_7SEG_1				GPIO_PIN_4
#define ENABLE_7SEG_1_PORT			GPIOB
#define ENABLE_7SEG_2				GPIO_PIN_5
#define ENABLE_7SEG_2_PORT			GPIOB

#define ENABLE_7SEG_01				GPIO_PIN_6
#define ENABLE_7SEG_01_PORT			GPIOB
#define ENABLE_7SEG_02				GPIO_PIN_7
#define ENABLE_7SEG_02_PORT			GPIOB
//#define ENABLE_7SEG_3				GPIO_PIN_6
//#define ENABLE_7SEG_3_PORT			GPIOA
//#define ENABLE_7SEG_4				GPIO_PIN_7
//#define ENABLE_7SEG_4_PORT			GPIOA


#define SEVEN_SEGMENT_1_A 			GPIO_PIN_0
#define SEVEN_SEGMENT_1_A_PORT 		GPIOA
#define SEVEN_SEGMENT_1_B 			GPIO_PIN_1
#define SEVEN_SEGMENT_1_B_PORT 		GPIOA
#define SEVEN_SEGMENT_1_C 			GPIO_PIN_2
#define SEVEN_SEGMENT_1_C_PORT 		GPIOA
#define SEVEN_SEGMENT_1_D 			GPIO_PIN_3
#define SEVEN_SEGMENT_1_D_PORT 		GPIOA
#define SEVEN_SEGMENT_1_E 			GPIO_PIN_4
#define SEVEN_SEGMENT_1_E_PORT 		GPIOA
#define SEVEN_SEGMENT_1_F 			GPIO_PIN_5
#define SEVEN_SEGMENT_1_F_PORT 		GPIOA
#define SEVEN_SEGMENT_1_G 			GPIO_PIN_6
#define SEVEN_SEGMENT_1_G_PORT 		GPIOA
#define SEVEN_SEGMENT_1_H
#define SEVEN_SEGMENT_1_H_PORT

// extra led for mode display
#define EDGE_A	 			GPIO_PIN_9
#define EDGE_A_PORT 		GPIOB
#define EDGE_B	 			GPIO_PIN_10
#define EDGE_B_PORT 		GPIOB
#define EDGE_C	 			GPIO_PIN_11
#define EDGE_C_PORT 		GPIOB
#define EDGE_D	 			GPIO_PIN_12
#define EDGE_D_PORT 		GPIOB
#define EDGE_E	 			GPIO_PIN_13
#define EDGE_E_PORT 		GPIOB
#define EDGE_F	 			GPIO_PIN_14
#define EDGE_F_PORT 		GPIOB
#define EDGE_G	 			GPIO_PIN_15
#define EDGE_G_PORT 		GPIOB

void update_seven_segment_led_buffer(uint8_t index, uint8_t value);
void seven_segment_led_driver(void);

void update_mode_seven_segment_led_buffer(uint8_t value1, uint8_t value2);
void mode_seven_segment_led_driver(void);
void update_mode_led(uint8_t number);

#endif /* INC_LEDS_DISPLAY_LED_7SEG_DISPLAY_H_ */

/*
 * Traffic_Light.h
 *
 *  Created on: Oct 19, 2021
 *      Author: Dell
 */

#ifndef INC_LEDS_DISPLAY_TRAFFIC_LIGHT_H_
#define INC_LEDS_DISPLAY_TRAFFIC_LIGHT_H_

typedef enum {RED,GREEN,AMBER} eLightState;
#define TIME_CYCLE			10	//remember to precheck timer

#define RED1_PIN			GPIO_PIN_7
#define RED1_PORT			GPIOA
#define AMBER1_PIN			GPIO_PIN_8
#define AMBER1_PORT			GPIOA
#define GREEN1_PIN			GPIO_PIN_9
#define GREEN1_PORT			GPIOA

#define RED2_PIN			GPIO_PIN_10
#define RED2_PORT			GPIOA
#define AMBER2_PIN			GPIO_PIN_11
#define AMBER2_PORT			GPIOA
#define GREEN2_PIN			GPIO_PIN_12
#define GREEN2_PORT			GPIOA

#define RED_DURATION		50 	//500ms
#define	GREEN_DURATION		30	//300ms
#define AMBER_DURATION 		20 	//200ms

void Traffic_Light_Init(eLightState State);
void Traffic_Light_Update(void);

void Traffic_set_mode(uint16_t red, uint16_t amber, uint16_t green);

#endif /* INC_LEDS_DISPLAY_TRAFFIC_LIGHT_H_ */

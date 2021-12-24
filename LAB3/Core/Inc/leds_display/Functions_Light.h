/*
 * Traffic_Light.h
 *
 *  Created on: Oct 19, 2021
 *      Author: Dell
 */

#ifndef INC_LEDS_DISPLAY_FUNCTIONS_LIGHT_H_
#define INC_LEDS_DISPLAY_FUNCTIONS_LIGHT_H_

//typedef enum {RED,GREEN,AMBER} eLightState;

typedef enum {READY, FILL_WATER, HEAT_WATER, WASH, RINSE, SPIN} wState;
#define TIME_CYCLE			10	//remember to precheck timer
#define ON					SET
#define	OFF					RESET

#define SOAK_PIN			GPIO_PIN_7
#define SOAK_PORT			GPIOA
#define NORMAL_PIN			GPIO_PIN_8
#define NORMAL_PORT			GPIOA
#define QUICK_PIN			GPIO_PIN_9
#define QUICK_PORT			GPIOA

#define L90_PIN				GPIO_PIN_10
#define L90_PORT			GPIOA
#define L60_PIN				GPIO_PIN_11
#define L60_PORT			GPIOA
#define L30_PIN				GPIO_PIN_12
#define L30_PORT			GPIOA

#define HOT_PIN				GPIO_PIN_13
#define HOT_PORT			GPIOA
#define WARM_PIN			GPIO_PIN_14
#define WARM_PORT			GPIOA
#define COOL_PIN			GPIO_PIN_15
#define COOL_PORT			GPIOA

//Washing mode
#define SOAK_DURATION		50 	//500ms
#define	NORMAL_DURATION		30	//300ms
#define QUICK_DURATION 		20 	//200ms
//Water level
#define L90_DURATION		90 	//900ms
#define	L60_DURATION		60	//600ms
#define L30_DURATION 		30 	//300ms
//Temperature level
#define HOT_DURATION		50 	//500ms
#define	WARM_DURATION		30	//300ms
#define COOL_DURATION 		20 	//200ms
//Rinse
#define RINSE_DURATION 		40 	//300ms
//Spin
#define	SPIN_DURATION		40  //300ms
//


//void Traffic_Light_Init(eLightState State);
//void Traffic_Light_Update(void);
//
void  Washing_Light_Init(wState State);
void  Washing_Update(void);
void  Washing_Light_Update(void);

void Traffic_set_mode(uint16_t red, uint16_t amber, uint16_t green);
//STATE LED
void update_buffer_traffic_7seg_leds(uint8_t value1, uint8_t value2);

void Run(uint16_t washing_mode, uint16_t water_level, uint16_t temperature_level);
void Reset(void);
#endif /* INC_LEDS_DISPLAY_FUNCTIONS_LIGHT_H_ */

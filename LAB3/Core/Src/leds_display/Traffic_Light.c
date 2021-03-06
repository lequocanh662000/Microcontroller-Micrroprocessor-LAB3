#include <button/input_processing.h>
#include <button/input_reading.h>
#include <leds_display/led_7seg_display.h>
#include <leds_display/Traffic_Light.h>
#include "main.h"

#define NUMBER_OF_TRAFFIC_LIGHT			2
#define NUMBER_OF_DECIMAL_DIGIT			10

static eLightState Light_state_G;
static uint8_t lane1,lane2;

static uint16_t Time_in_State;
static uint16_t redDuration = RED_DURATION, amberDuration = AMBER_DURATION, greenDuration = GREEN_DURATION;

/////////////////////    MAIN   /////////////////////////////////
void update_buffer_traffic_7seg_leds(uint8_t lane1, uint8_t lane2){
	update_seven_segment_led_buffer(0, lane1);
	update_seven_segment_led_buffer(1, lane2);
}

void Traffic_Light_Init(eLightState State){
	Light_state_G = State;
}

void Traffic_Light_Update(){
	switch(Light_state_G){
		case RED: // default = 50
			// Set Traffic Light 1
			HAL_GPIO_WritePin(RED1_PORT, RED1_PIN, SET);
			HAL_GPIO_WritePin(AMBER1_PORT, AMBER1_PIN, RESET);
			HAL_GPIO_WritePin(GREEN1_PORT, GREEN1_PIN, RESET);
			// Set Traffic Light 2
			if(Time_in_State <= greenDuration){
				lane1 = redDuration/10 - Time_in_State/10;
				lane2 = greenDuration/10 - Time_in_State/10;

				HAL_GPIO_WritePin(RED2_PORT, RED2_PIN, RESET);
				HAL_GPIO_WritePin(AMBER2_PORT, AMBER2_PIN, RESET);
				HAL_GPIO_WritePin(GREEN2_PORT, GREEN2_PIN, SET);
			}else{
				lane1 = lane2 = redDuration/10 - Time_in_State/10;

				HAL_GPIO_WritePin(RED2_PORT, RED2_PIN, RESET);
				HAL_GPIO_WritePin(AMBER2_PORT, AMBER2_PIN, SET);
				HAL_GPIO_WritePin(GREEN2_PORT, GREEN2_PIN, RESET);
			}
			//////////////////////////////////////////////////////////
				if(++Time_in_State == redDuration){
					Light_state_G = GREEN;
					Time_in_State = 0;
				}
			break;

		case GREEN: // default = 30
			lane1 = greenDuration/10 - Time_in_State/10;
			lane2 = redDuration/10 - Time_in_State/10;

			// Set Traffic Light 1
			HAL_GPIO_WritePin(RED1_PORT, RED1_PIN, RESET);
			HAL_GPIO_WritePin(AMBER1_PORT, AMBER1_PIN, RESET);
			HAL_GPIO_WritePin(GREEN1_PORT, GREEN1_PIN, SET);
			// Set Traffic Light 2
			HAL_GPIO_WritePin(RED2_PORT, RED2_PIN, SET);
			HAL_GPIO_WritePin(AMBER2_PORT, AMBER2_PIN, RESET);
			HAL_GPIO_WritePin(GREEN2_PORT, GREEN2_PIN, RESET);
			//////////////////////////////////////////////////////////
			if(++Time_in_State == greenDuration){
				Light_state_G = AMBER;
				Time_in_State = 0;
			}
			break;

		case AMBER: // default = 20
			lane1 = lane2 = amberDuration/10 - Time_in_State/10;

			// Set Traffic Light 1
			HAL_GPIO_WritePin(RED1_PORT, RED1_PIN, RESET);
			HAL_GPIO_WritePin(AMBER1_PORT, AMBER1_PIN, SET);
			HAL_GPIO_WritePin(GREEN1_PORT, GREEN1_PIN, RESET);
			// Set Traffic Light 2
			HAL_GPIO_WritePin(RED2_PORT, RED2_PIN, SET);
			HAL_GPIO_WritePin(AMBER2_PORT, AMBER2_PIN, RESET);
			HAL_GPIO_WritePin(GREEN2_PORT, GREEN2_PIN, RESET);
			//////////////////////////////////////////////////////////
			if(++Time_in_State == amberDuration){
				Light_state_G = RED;
				Time_in_State = 0;
			}
			break;
	}
	update_buffer_traffic_7seg_leds(lane1, lane2);
}

void Traffic_set_mode(uint16_t red,  uint16_t amber , uint16_t green){
	if(red == amber + green){
		redDuration = red;
		amberDuration = amber;
		greenDuration = green;
		Time_in_State = 0;
		Traffic_Light_Init(RED);
	}
	else{
		redDuration = RED_DURATION;
		amberDuration = AMBER_DURATION;
		greenDuration = GREEN_DURATION;
		Time_in_State = 0;
		Traffic_Light_Init(RED);
	}
}

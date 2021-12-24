#include <button/input_processing.h>
#include <button/input_reading.h>
#include <leds_display/Functions_Light.h>
#include <leds_display/led_7seg_display.h>
#include <fault_control/fault_control.h>
#include "main.h"

#define NUMBER_OF_TRAFFIC_LIGHT			2
#define NUMBER_OF_DECIMAL_DIGIT			10

//static eLightState Light_state_G;

static uint8_t value1, value2;
static uint8_t reset = 1;
//
static wState Washing_state;

static uint16_t Time_in_State;
//static uint16_t redDuration = RED_DURATION, amberDuration = AMBER_DURATION, greenDuration = GREEN_DURATION;
static uint16_t washDuration = NORMAL_DURATION, waterLevel = L90_DURATION, tempLevel = WARM_DURATION; // default

//define function's PIN, PORT
static uint16_t functionDataPin[9] = {
		QUICK_PIN, NORMAL_PIN, SOAK_PIN,
		L30_PIN, L60_PIN, L90_PIN,
		COOL_PIN, WARM_PIN, HOT_PIN
};

static GPIO_TypeDef * functionDataPort[9] = {
		QUICK_PORT, NORMAL_PORT, SOAK_PORT,
		L30_PORT, L60_PORT, L90_PORT,
		COOL_PORT, WARM_PORT, HOT_PORT
};

/////////////////////    MAIN   /////////////////////////////////
void update_buffer_traffic_7seg_leds(uint8_t value1, uint8_t value2){
	update_seven_segment_led_buffer(0, value1);
	update_seven_segment_led_buffer(1, value2);
}

void Washing_Light_Init(wState State){
	Washing_state = State;
}

void Traffic_Light_Update(){
//	switch(Light_state_G){
//		case RED: // default = 50
//			// Set Traffic Light 1
//			HAL_GPIO_WritePin(RED1_PORT, RED1_PIN, SET);
//			HAL_GPIO_WritePin(AMBER1_PORT, AMBER1_PIN, RESET);
//			HAL_GPIO_WritePin(GREEN1_PORT, GREEN1_PIN, RESET);
//			// Set Traffic Light 2
//			if(Time_in_State <= greenDuration){
//				lane1 = redDuration/10 - Time_in_State/10;
//				lane2 = greenDuration/10 - Time_in_State/10;
//
//				HAL_GPIO_WritePin(RED2_PORT, RED2_PIN, RESET);
//				HAL_GPIO_WritePin(AMBER2_PORT, AMBER2_PIN, RESET);
//				HAL_GPIO_WritePin(GREEN2_PORT, GREEN2_PIN, SET);
//			}else{
//				lane1 = lane2 = redDuration/10 - Time_in_State/10;
//
//				HAL_GPIO_WritePin(RED2_PORT, RED2_PIN, RESET);
//				HAL_GPIO_WritePin(AMBER2_PORT, AMBER2_PIN, SET);
//				HAL_GPIO_WritePin(GREEN2_PORT, GREEN2_PIN, RESET);
//			}
//			//////////////////////////////////////////////////////////
//				if(++Time_in_State == redDuration){
//					Light_state_G = GREEN;
//					Time_in_State = 0;
//				}
//			break;
//
//		case GREEN: // default = 30
//			lane1 = greenDuration/10 - Time_in_State/10;
//			lane2 = redDuration/10 - Time_in_State/10;
//
//			// Set Traffic Light 1
//			HAL_GPIO_WritePin(RED1_PORT, RED1_PIN, RESET);
//			HAL_GPIO_WritePin(AMBER1_PORT, AMBER1_PIN, RESET);
//			HAL_GPIO_WritePin(GREEN1_PORT, GREEN1_PIN, SET);
//			// Set Traffic Light 2
//			HAL_GPIO_WritePin(RED2_PORT, RED2_PIN, SET);
//			HAL_GPIO_WritePin(AMBER2_PORT, AMBER2_PIN, RESET);
//			HAL_GPIO_WritePin(GREEN2_PORT, GREEN2_PIN, RESET);
//			//////////////////////////////////////////////////////////
//			if(++Time_in_State == greenDuration){
//				Light_state_G = AMBER;
//				Time_in_State = 0;
//			}
//			break;
//
//		case AMBER: // default = 20
//			lane1 = lane2 = amberDuration/10 - Time_in_State/10;
//
//			// Set Traffic Light 1
//			HAL_GPIO_WritePin(RED1_PORT, RED1_PIN, RESET);
//			HAL_GPIO_WritePin(AMBER1_PORT, AMBER1_PIN, SET);
//			HAL_GPIO_WritePin(GREEN1_PORT, GREEN1_PIN, RESET);
//			// Set Traffic Light 2
//			HAL_GPIO_WritePin(RED2_PORT, RED2_PIN, SET);
//			HAL_GPIO_WritePin(AMBER2_PORT, AMBER2_PIN, RESET);
//			HAL_GPIO_WritePin(GREEN2_PORT, GREEN2_PIN, RESET);
//			//////////////////////////////////////////////////////////
//			if(++Time_in_State == amberDuration){
//				Light_state_G = RED;
//				Time_in_State = 0;
//			}
//			break;
//	}
//	update_buffer_traffic_7seg_leds(lane1, lane2);
	return;
}
//
void Washing_Update(){
	if(reset == 1){
		return;
	}else{
		switch(Washing_state){
			case READY:
				HAL_GPIO_TogglePin(QUICK_PORT, QUICK_PIN);
				if((++Time_in_State)/10 == 10){
					Washing_state = FILL_WATER;
					washDuration = NORMAL_DURATION;
					waterLevel = L90_DURATION;
					tempLevel = WARM_DURATION;
					Time_in_State = 0;
				}
				//ERROR HANDLE
				break;
			case FILL_WATER:
				if(++Time_in_State/10 == waterLevel/10){
					Washing_Light_Update();
					Washing_state = HEAT_WATER;
					Time_in_State = 0;
				}
				//ERROR HANDLE
				break;
			case HEAT_WATER:
				if(++Time_in_State/10 == tempLevel/10){
					Washing_Light_Update();
					Washing_state = WASH;
					Time_in_State = 0;
				}
				//ERROR HANDLE
				break;
			case WASH:
				if(++Time_in_State/10 == washDuration/10){
					Washing_Light_Update();
					Washing_state = RINSE;
					Time_in_State = 0;
				}
				//ERROR HANDLE
				break;
			case RINSE:
				if(++Time_in_State/10 == RINSE_DURATION/10){
					Washing_Light_Update();
					Washing_state = SPIN;
					Time_in_State = 0;
				}
				//ERROR HANDLE
				break;
			case SPIN:
				if(++Time_in_State/10 == SPIN_DURATION/10){
					Washing_Light_Update();
					Washing_state = READY;
					Time_in_State = 0;
				}
				//ERROR HANDLE
				break;
			default:
				break;
		}
	}
	value1 = Time_in_State/100;
	value2 = (Time_in_State/10)%10;
	update_buffer_traffic_7seg_leds(value1, value2);
}
void Washing_Light_Update(){
	if(Washing_state == FILL_WATER){
		if(Time_in_State < L30_DURATION){
			HAL_GPIO_TogglePin(functionDataPort[3], functionDataPin[3]);
		}
		else if(Time_in_State == L30_DURATION){
			HAL_GPIO_WritePin(functionDataPort[3], functionDataPin[3], ON);
		}
		else if(Time_in_State == L60_DURATION){
			HAL_GPIO_WritePin(functionDataPort[3], functionDataPin[3], OFF);
			HAL_GPIO_WritePin(functionDataPort[4], functionDataPin[4], ON);
		}
		else if(Time_in_State == L90_DURATION){
			HAL_GPIO_WritePin(functionDataPort[4], functionDataPin[4], OFF);
			HAL_GPIO_WritePin(functionDataPort[5], functionDataPin[5], ON);
		}
	}
	else if(Washing_state == HEAT_WATER){
		if(Time_in_State < COOL_DURATION){
			HAL_GPIO_TogglePin(functionDataPort[6], functionDataPin[6]);
		}
		else if(Time_in_State == COOL_DURATION){
			HAL_GPIO_WritePin(functionDataPort[6], functionDataPin[6], ON);
		}
		else if(Time_in_State == WARM_DURATION){
			HAL_GPIO_WritePin(functionDataPort[6], functionDataPin[6], OFF);
			HAL_GPIO_WritePin(functionDataPort[7], functionDataPin[7], ON);
		}
		else if(Time_in_State == HOT_DURATION){
			HAL_GPIO_WritePin(functionDataPort[7], functionDataPin[7], OFF);
			HAL_GPIO_WritePin(functionDataPort[8], functionDataPin[8], ON);
		}
	}
	else if(Washing_state == WASH){
		if(washDuration == QUICK_DURATION){
			HAL_GPIO_WritePin(functionDataPort[0], functionDataPin[0], ON);
			HAL_GPIO_WritePin(functionDataPort[1], functionDataPin[1], OFF);
			HAL_GPIO_WritePin(functionDataPort[2], functionDataPin[2], OFF);
		}
		else if(washDuration == NORMAL_DURATION){
			HAL_GPIO_WritePin(functionDataPort[0], functionDataPin[0], OFF);
			HAL_GPIO_WritePin(functionDataPort[1], functionDataPin[1], ON);
		}
		else if(washDuration == SOAK_DURATION){
			HAL_GPIO_WritePin(functionDataPort[1], functionDataPin[1], OFF);
			HAL_GPIO_WritePin(functionDataPort[2], functionDataPin[2], ON);
		}
	}
	return;
}
//void Traffic_set_mode(uint16_t red,  uint16_t amber , uint16_t green){
//	if(red == amber + green){
//		redDuration = red;
//		amberDuration = amber;
//		greenDuration = green;
//		Time_in_State = 0;
//		Traffic_Light_Init(RED);
//	}
//	else{
//		redDuration = RED_DURATION;
//		amberDuration = AMBER_DURATION;
//		greenDuration = GREEN_DURATION;
//		Time_in_State = 0;
//		Traffic_Light_Init(RED);
//	}
//}

void Run(uint16_t washing_mode, uint16_t water_level, uint16_t temperature_level){
	if((washing_mode != 0)&&(water_level != 0)&&(temperature_level !=0)){
		reset = 1 - reset;
		washDuration = washing_mode;
		waterLevel = water_level;
		tempLevel = temperature_level;
		Time_in_State = 0;
		Washing_Light_Init(FILL_WATER);
	}else{
		reset = 1 - reset;
		washDuration = NORMAL_DURATION;
		waterLevel = L90_DURATION;
		tempLevel = WARM_DURATION;
		Time_in_State = 0;
		Washing_Light_Init(FILL_WATER);
	}
	return;
}
void Reset(){ // extra button
	return;
}
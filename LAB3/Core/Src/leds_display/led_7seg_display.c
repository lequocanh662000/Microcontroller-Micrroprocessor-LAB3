#include <button/input_processing.h>
#include <button/input_reading.h>
#include <leds_display/Functions_Light.h>
#include <leds_display/led_7seg_display.h>
#include <fault_control/fault_control.h>
#include "main.h"

#define NUMBER_OF_SEVEN_SEGMENT_LED  	2
#define NUMBER_OF_DECIMAL_DIGIT			10

//common Anode 0:off  1:one
static uint8_t sevenSegmentLEDConversion[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

//common Cathode 0:one  1:off
//uint8_t sevenSegmentLEDConversion[10] = {};

static uint8_t sevenSegmentLEDBuffer[NUMBER_OF_SEVEN_SEGMENT_LED]; // buffer to store value of each led
static uint8_t modeSevenSegmentLEDBuffer[2];

// STATE LED
static uint16_t sevenSegmentDataPin[8] = {
		SEVEN_SEGMENT_1_A, SEVEN_SEGMENT_1_B,
		SEVEN_SEGMENT_1_C, SEVEN_SEGMENT_1_D,
		SEVEN_SEGMENT_1_E, SEVEN_SEGMENT_1_F,
		SEVEN_SEGMENT_1_G, SEVEN_SEGMENT_1_H
};

static GPIO_TypeDef * sevenSegmentDataPort[8] = {
		SEVEN_SEGMENT_1_A_PORT, SEVEN_SEGMENT_1_B_PORT,
		SEVEN_SEGMENT_1_C_PORT, SEVEN_SEGMENT_1_D_PORT,
		SEVEN_SEGMENT_1_E_PORT, SEVEN_SEGMENT_1_F_PORT,
		SEVEN_SEGMENT_1_G_PORT, SEVEN_SEGMENT_1_H_PORT
};

static uint16_t sevenSegmentControlPin[NUMBER_OF_SEVEN_SEGMENT_LED] = {
		ENABLE_7SEG_1, ENABLE_7SEG_2
//		,
//		ENABLE_7SEG_3, ENABLE_7SEG_4
};

static GPIO_TypeDef * sevenSegmentControlPort[NUMBER_OF_SEVEN_SEGMENT_LED] = {
		ENABLE_7SEG_1_PORT, ENABLE_7SEG_2_PORT
//		,
//		ENABLE_7SEG_3_PORT, ENABLE_7SEG_4_PORT
};

// SET_FUNCTION LED
static uint16_t modeLedDataPin[7] = {
		EDGE_A, EDGE_B,
		EDGE_C, EDGE_D,
		EDGE_E, EDGE_F,
		EDGE_G
};

static GPIO_TypeDef * modeLedDataPort[7] = {
		EDGE_A_PORT, EDGE_B_PORT,
		EDGE_C_PORT, EDGE_D_PORT,
		EDGE_E_PORT, EDGE_F_PORT,
		EDGE_G_PORT
};

static uint16_t modeSevenSegmentControlPin[2] = {
		ENABLE_7SEG_01, ENABLE_7SEG_02
};

static GPIO_TypeDef * modeSevenSegmentControlPort[2] = {
		ENABLE_7SEG_01_PORT, ENABLE_7SEG_02_PORT
};
////////////////////////// FUNCTION CONFIGURATION ///////////////////////////////
// STATE LED CONFIGURATION
void update_seven_segment_led_buffer(uint8_t index, uint8_t value){
	if(index >= NUMBER_OF_SEVEN_SEGMENT_LED) return;
	if(value > 9) return ;
	sevenSegmentLEDBuffer[index] = value;
	return;
}

void seven_segment_data_output(uint8_t value){
	uint8_t index;
	for(index = 0; index < 7; index ++){
			if((value>>index) & 0x01){
				HAL_GPIO_WritePin(sevenSegmentDataPort[index], sevenSegmentDataPin[index], RESET);
			} else {
				HAL_GPIO_WritePin(sevenSegmentDataPort[index], sevenSegmentDataPin[index],	SET);
			}
		}
}

void clear_previous_seven_segment_led(uint8_t index){
	if(index >= NUMBER_OF_SEVEN_SEGMENT_LED) return;
	HAL_GPIO_WritePin(sevenSegmentControlPort[index], sevenSegmentControlPin[index], SET);
}

void set_current_seven_segment_led(uint8_t index){
	if(index >= NUMBER_OF_SEVEN_SEGMENT_LED) return;
	HAL_GPIO_WritePin(sevenSegmentControlPort[index], sevenSegmentControlPin[index], RESET);
}

void seven_segment_led_driver(void){
	static uint8_t led_index = 0;
	uint8_t tempData;
	// clear previous led data
	clear_previous_seven_segment_led(led_index);
	// current led data setting
	led_index = (led_index + 1) % NUMBER_OF_SEVEN_SEGMENT_LED;
	tempData = sevenSegmentLEDConversion[sevenSegmentLEDBuffer[led_index]];
	seven_segment_data_output(tempData);
	set_current_seven_segment_led(led_index);
}
//////////////////// MODE SEVEN SEGMENT LED CONFIGURATION  //////////////////////////

//void update_mode_led(uint8_t number){ // number is the order of button
//	static uint8_t mode = 0;
//	static uint16_t red, amber, green = 0;
//
//
//	if(number == 0)mode = (mode + 1) % 4; 	// SET MODE
//	else if(number == 1){   					// INCREASE MODe
//		if(mode == 0)mode = (mode + 1) % 4;
//		if(mode == 1)red = (red+1) % 100;
//		if(mode == 2)amber = (amber+1) % 100;
//		if(mode == 3)green = (green+1) % 100;
//	}
//
//	else if(number == 2){ 					// DECREASE MODE
//		if(mode == 1){
//			if(red == 0)red = 99;
//			else red = red - 1;
//		}
//		if(mode == 2){
//			if(amber == 0)amber = 99;
//			else amber = amber - 1;
//		}
//		if(mode == 3){
//			if(green  == 0)green = 99;
//			else green = green - 1;
//		}
//	}
//	else if(number == 3){ 					// SET VALUE
//			Traffic_set_mode(red, amber, green);
//	}
//
//	if(mode == 0 || number == 0){
//		update_mode_seven_segment_led_buffer(0, mode);
//	}
//	else if(number == 1){
//		if(mode == 0)update_mode_seven_segment_led_buffer(0, mode);
//		else if(mode == 1)update_mode_seven_segment_led_buffer(red/10, red%10);
//		else if(mode == 2)update_mode_seven_segment_led_buffer(amber/10, amber%10);
//		else if(mode == 3)update_mode_seven_segment_led_buffer(green/10, green%10);
//	}
//	else if(number == 2){
//		if(mode == 0)update_mode_seven_segment_led_buffer(0, mode);
//		else if(mode == 1)update_mode_seven_segment_led_buffer(red/10, red%10);
//		else if(mode == 2)update_mode_seven_segment_led_buffer(amber/10, amber%10);
//		else if(mode == 3)update_mode_seven_segment_led_buffer(green/10, green%10);
//	}
//	else if(number == 3){
//		return;
//	}
//}
// ver washing machine

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
//Initialize variables for update_mode_led()
static uint8_t setting = 0;
static uint16_t washing_mode, water_level, temperature_level = 0;
static uint16_t wTimeArray[4]={0,20,30,50};
static uint16_t tLevelArray[4]={0,20,30,50};

void update_mode_led(uint8_t number){ // number is the order of button
	switch(number){
		case 0:        		//CHOOSE_SETTING
			setting = (setting+1) % 4;
			break;
		case 1:  			// INCREASE MODE
			if(setting == 0)setting = (setting+1) % 4;
			if(setting == 1)washing_mode = 1 + (washing_mode % 3); // 1.QUICK  2.NORMAL(MIXED)  3.RINSE
			if(setting == 2)water_level = 30 + (water_level % 90); // 30% 60% 90%
			if(setting == 3)temperature_level = 1+ (temperature_level % 3); // NORMAL  WARM  HOT
			break;
		case 2:             // DECREASE MODE
			if(setting == 0)break;
			if(setting == 1){
				if(washing_mode == 1)washing_mode = 3;
				else washing_mode--;
			}
			if(setting == 2){
				if(water_level == 30)water_level = 90;
				else water_level-=30;
			}
			if(setting == 3){
				if(temperature_level == 1)temperature_level = 3;
				else temperature_level--;
			}
			break;
		case 3:            	//  RUN
			for(int i = 0; i<9; i++){
				HAL_GPIO_WritePin(functionDataPort[i], functionDataPin[i], OFF);
			}
			Run(wTimeArray[washing_mode], water_level, tLevelArray[temperature_level]);
			break;
	}
	// update buffer
	if(number == 3){
		Reset_Set_Funtion();
		return;
	}
	if(setting == 0 || number == 0){
		update_mode_seven_segment_led_buffer(0, setting);
	}
	else if(number == 1 || number == 2){
		if(setting == 0)update_mode_seven_segment_led_buffer(0, setting);
		else if(setting == 1){
			if(washing_mode == 1){
				HAL_GPIO_WritePin(functionDataPort[0], functionDataPin[0], ON);
				HAL_GPIO_WritePin(functionDataPort[1], functionDataPin[1], OFF);
				HAL_GPIO_WritePin(functionDataPort[2], functionDataPin[2], OFF);
			}
			else if(washing_mode == 2){
				HAL_GPIO_WritePin(functionDataPort[0], functionDataPin[0], OFF);
				HAL_GPIO_WritePin(functionDataPort[1], functionDataPin[1], ON);
				HAL_GPIO_WritePin(functionDataPort[2], functionDataPin[2], OFF);
			}
			else if(washing_mode == 3){
				HAL_GPIO_WritePin(functionDataPort[0], functionDataPin[0], OFF);
				HAL_GPIO_WritePin(functionDataPort[1], functionDataPin[1], OFF);
				HAL_GPIO_WritePin(functionDataPort[2], functionDataPin[2], ON);
			}
			update_mode_seven_segment_led_buffer(washing_mode/10, washing_mode%10);
		}
		else if(setting == 2){
			if(water_level == 30){
				HAL_GPIO_WritePin(functionDataPort[3], functionDataPin[3], ON);
				HAL_GPIO_WritePin(functionDataPort[4], functionDataPin[4], OFF);
				HAL_GPIO_WritePin(functionDataPort[5], functionDataPin[5], OFF);
			}
			else if(water_level == 60){
				HAL_GPIO_WritePin(functionDataPort[3], functionDataPin[3], OFF);
				HAL_GPIO_WritePin(functionDataPort[4], functionDataPin[4], ON);
				HAL_GPIO_WritePin(functionDataPort[5], functionDataPin[5], OFF);
			}
			else if(water_level == 90){
				HAL_GPIO_WritePin(functionDataPort[3], functionDataPin[3], OFF);
				HAL_GPIO_WritePin(functionDataPort[4], functionDataPin[4], OFF);
				HAL_GPIO_WritePin(functionDataPort[5], functionDataPin[5], ON);
			}
			update_mode_seven_segment_led_buffer(water_level/10, water_level%10);
		}
		else if(setting == 3){
			if(temperature_level == 1){
				HAL_GPIO_WritePin(functionDataPort[6], functionDataPin[6], ON);
				HAL_GPIO_WritePin(functionDataPort[7], functionDataPin[7], OFF);
				HAL_GPIO_WritePin(functionDataPort[8], functionDataPin[8], OFF);
			}
			else if(temperature_level == 2){
				HAL_GPIO_WritePin(functionDataPort[6], functionDataPin[6], OFF);
				HAL_GPIO_WritePin(functionDataPort[7], functionDataPin[7], ON);
				HAL_GPIO_WritePin(functionDataPort[8], functionDataPin[8], OFF);
			}
			else if(temperature_level == 3){
				HAL_GPIO_WritePin(functionDataPort[6], functionDataPin[6], OFF);
				HAL_GPIO_WritePin(functionDataPort[7], functionDataPin[7], OFF);
				HAL_GPIO_WritePin(functionDataPort[8], functionDataPin[8], ON);
			}
			update_mode_seven_segment_led_buffer(temperature_level/10, temperature_level%10);
		}
	}
}
//
void Reset_Set_Funtion(){
	setting = washing_mode = water_level = temperature_level = 0;
	// update buffer
	update_mode_seven_segment_led_buffer(0, 0);
}

// SET FUNCTIONS 7 SEG LED

void update_mode_seven_segment_led_buffer(uint8_t value1, uint8_t value2){
	if(value1 > 9 || value2 > 9) return;
	modeSevenSegmentLEDBuffer[0] = value1;
	modeSevenSegmentLEDBuffer[1] = value2;
	return;
}

void mode_seven_segment_data_output(uint8_t value){
	uint8_t index;
	for(index = 0; index < 7; index ++){
			if((value>>index) & 0x01){
				HAL_GPIO_WritePin(modeLedDataPort[index], modeLedDataPin[index], RESET);
			} else {
				HAL_GPIO_WritePin(modeLedDataPort[index], modeLedDataPin[index], SET);
			}
		}
}

void clear_previous_mode_seven_segment_led(uint8_t index){
	if(index >= NUMBER_OF_SEVEN_SEGMENT_LED) return;
	HAL_GPIO_WritePin(modeSevenSegmentControlPort[index], modeSevenSegmentControlPin[index], SET);
}

void set_current_mode_seven_segment_led(uint8_t index){
	if(index >= NUMBER_OF_SEVEN_SEGMENT_LED) return;
	HAL_GPIO_WritePin(modeSevenSegmentControlPort[index], modeSevenSegmentControlPin[index], RESET);
}

void mode_seven_segment_led_driver(void){
	static uint8_t mode_led_index = 0;
	uint8_t tempModeData;
	// clear previous led data
	clear_previous_mode_seven_segment_led(mode_led_index);
	// current led data setting
	mode_led_index = (mode_led_index + 1) % 2;
	tempModeData = sevenSegmentLEDConversion[modeSevenSegmentLEDBuffer[mode_led_index]];
	mode_seven_segment_data_output(tempModeData);
	set_current_mode_seven_segment_led(mode_led_index);
}
// STATES 7 SEG LED

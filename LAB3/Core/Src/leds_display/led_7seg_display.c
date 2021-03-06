#include <button/input_processing.h>
#include <button/input_reading.h>
#include <leds_display/Traffic_Light.h>
#include <leds_display/led_7seg_display.h>
#include "main.h"

#define NUMBER_OF_SEVEN_SEGMENT_LED  	2
#define NUMBER_OF_DECIMAL_DIGIT			10

//common Anode 0:off  1:one
static uint8_t sevenSegmentLEDConversion[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

//common Cathode 0:one  1:off
//uint8_t sevenSegmentLEDConversion[10] = {};

static uint8_t sevenSegmentLEDBuffer[NUMBER_OF_SEVEN_SEGMENT_LED]; // buffer to store value of each led
static uint8_t modeSevenSegmentLEDBuffer[2];

// FORMAT PIN, PORT
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

// extra led for mode display
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

void update_mode_led(uint8_t number){ // number is the order of button
	static uint8_t mode = 0;
	static uint16_t red, amber, green = 0;


	if(number == 0)mode = (mode + 1) % 4; 	// SET MODE
	else if(number == 1){   					// INCREASE MODe
		if(mode == 0)mode = (mode + 1) % 4;
		if(mode == 1)red = (red+1) % 100;
		if(mode == 2)amber = (amber+1) % 100;
		if(mode == 3)green = (green+1) % 100;
	}

	else if(number == 2){ 					// DECREASE MODE
		if(mode == 1){
			if(red == 0)red = 99;
			else red = red - 1;
		}
		if(mode == 2){
			if(amber == 0)amber = 99;
			else amber = amber - 1;
		}
		if(mode == 3){
			if(green  == 0)green = 99;
			else green = green - 1;
		}
	}
	else if(number == 3){ 					// SET VALUE
			Traffic_set_mode(red, amber, green);
	}

	if(mode == 0 || number == 0){
		update_mode_seven_segment_led_buffer(0, mode);
	}
	else if(number == 1){
		if(mode == 0)update_mode_seven_segment_led_buffer(0, mode);
		else if(mode == 1)update_mode_seven_segment_led_buffer(red/10, red%10);
		else if(mode == 2)update_mode_seven_segment_led_buffer(amber/10, amber%10);
		else if(mode == 3)update_mode_seven_segment_led_buffer(green/10, green%10);
	}
	else if(number == 2){
		if(mode == 0)update_mode_seven_segment_led_buffer(0, mode);
		else if(mode == 1)update_mode_seven_segment_led_buffer(red/10, red%10);
		else if(mode == 2)update_mode_seven_segment_led_buffer(amber/10, amber%10);
		else if(mode == 3)update_mode_seven_segment_led_buffer(green/10, green%10);
	}
	else if(number == 3){
		return;
	}
}
//
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
				HAL_GPIO_WritePin(modeLedDataPort[index], modeLedDataPin[index],	SET);
			}
		}
}

void clear_previous_mode_seven_segment_led(uint8_t index){
	if(index >= 2) return;
	HAL_GPIO_WritePin(modeSevenSegmentControlPort[index], modeSevenSegmentControlPin[index], SET);
}

void set_current_mode_seven_segment_led(uint8_t index){
	if(index >= 2) return;
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

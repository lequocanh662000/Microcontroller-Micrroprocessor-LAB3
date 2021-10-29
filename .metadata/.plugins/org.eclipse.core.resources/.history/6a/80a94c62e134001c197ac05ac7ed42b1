#include <button/input_processing.h>
#include <button/input_reading.h>
#include <leds_display/led_7seg_display.h>
#include "main.h"

enum ButtonState {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSES_MORE_THAN_1_SEC};
enum ButtonState buttonState1 = BUTTON_RELEASED;
enum ButtonState buttonState2 = BUTTON_RELEASED;
enum ButtonState buttonState3 = BUTTON_RELEASED;
enum ButtonState buttonState4 = BUTTON_RELEASED;


void fsm_for_input1_processing(void){
	switch(buttonState1){
//////////////////// RELEASED ////////////////////////////
		case BUTTON_RELEASED:
			if(is_button_pressed(0)){
				buttonState1 = BUTTON_PRESSED;
			}
			break;
/////////////////   PRESSED  /////////////////////////////
		case BUTTON_PRESSED:
			if(!is_button_pressed(0)){
				buttonState1 = BUTTON_RELEASED;
			}else{
				if(is_button_pressed_1s(0)){
					buttonState1 = BUTTON_PRESSES_MORE_THAN_1_SEC;
				}
			}
			break;
/////////////////////   MORE THAN 1 SEC //////////////////
		case BUTTON_PRESSES_MORE_THAN_1_SEC:
			if(!is_button_pressed(0)){
				buttonState1 = BUTTON_RELEASED;
			}else{
				// to do
			}
			break;
	}
}

void fsm_for_input2_processing(void){
	switch(buttonState2){
//////////////////// RELEASED ////////////////////////////
		case BUTTON_RELEASED:
			if(is_button_pressed(1)){
				buttonState2 = BUTTON_PRESSED;
			}
			break;
/////////////////   PRESSED  /////////////////////////////
		case BUTTON_PRESSED:
			if(!is_button_pressed(1)){
				buttonState2 = BUTTON_RELEASED;
			}else{
				if(is_button_pressed_1s(1)){
					buttonState2 = BUTTON_PRESSES_MORE_THAN_1_SEC;
				}
			}
			break;
/////////////////////   MORE THAN 1 SEC //////////////////
		case BUTTON_PRESSES_MORE_THAN_1_SEC:
			if(!is_button_pressed(1)){
				buttonState2 = BUTTON_RELEASED;
			}else{
				// to do
			}
			break;
	}
}

void fsm_for_input3_processing(void){
	switch(buttonState3){
//////////////////// RELEASED ////////////////////////////
		case BUTTON_RELEASED:
			if(is_button_pressed(2)){
				buttonState3 = BUTTON_PRESSED;
			}
			break;
/////////////////   PRESSED  /////////////////////////////
		case BUTTON_PRESSED:
			if(!is_button_pressed(2)){
				buttonState3 = BUTTON_RELEASED;
			}else{
				if(is_button_pressed_1s(2)){
					buttonState3 = BUTTON_PRESSES_MORE_THAN_1_SEC;
				}
			}
			break;
/////////////////////   MORE THAN 1 SEC //////////////////
		case BUTTON_PRESSES_MORE_THAN_1_SEC:
			if(!is_button_pressed(2)){
				buttonState3 = BUTTON_RELEASED;
			}else{
				// to do
			}
			break;
	}
}

void fsm_for_input4_processing(void){
	switch(buttonState4){
//////////////////// RELEASED ////////////////////////////
		case BUTTON_RELEASED:
			if(is_button_pressed(3)){
				buttonState4 = BUTTON_PRESSED;
			}
			break;
/////////////////   PRESSED  /////////////////////////////
		case BUTTON_PRESSED:
			if(!is_button_pressed(3)){
				buttonState4 = BUTTON_RELEASED;
			}else{
				if(is_button_pressed_1s(0)){
					buttonState4 = BUTTON_PRESSES_MORE_THAN_1_SEC;
				}
			}
			break;
/////////////////////   MORE THAN 1 SEC //////////////////
		case BUTTON_PRESSES_MORE_THAN_1_SEC:
			if(!is_button_pressed(3)){
				buttonState4 = BUTTON_RELEASED;
			}else{
				// to do
			}
			break;
	}
}

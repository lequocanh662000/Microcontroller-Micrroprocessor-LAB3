#include <button/input_reading.h>
#include <leds_display/led_7seg_display.h>
#include "main.h"

#define NUMBER_OF_BUTTONS				4
#define DURATION_OF_AUTO_INCREASING 	100

#define BUTTON_IS_PRESSED				GPIO_PIN_RESET
#define BUTTON_IS_RELEASED				GPIO_PIN_SET

// define PIN, PORT
static uint16_t buttonDataPin[4] = {
		BUTTON_1_PIN, BUTTON_2_PIN,
		BUTTON_3_PIN, BUTTON_4_PIN
};

static GPIO_TypeDef * buttonDataPort[4] = {
		BUTTON_1_PORT, BUTTON_2_PORT,
		BUTTON_3_PORT, BUTTON_4_PORT
};

//the buffer that the final result is stored after deboucing
static 	GPIO_PinState buttonBuffer[NUMBER_OF_BUTTONS];

//we define 2 buffers for deboucing
static GPIO_PinState debounceButtonBuffer1[NUMBER_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NUMBER_OF_BUTTONS];

static uint16_t counterForButtonPress1s[NUMBER_OF_BUTTONS];
static uint8_t flagForButtonPress1s[NUMBER_OF_BUTTONS];

//////////////////////  MAIN ////////////////////////////

void reading_button(void){
	for(uint8_t i = 0; i<NUMBER_OF_BUTTONS; i++){
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(buttonDataPort[i], buttonDataPin[i]);

		if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i]){
			buttonBuffer[i] = debounceButtonBuffer1[i];

			if(buttonBuffer[i] == BUTTON_IS_PRESSED){
				if(counterForButtonPress1s[i] == 0)update_mode_led(i);

				if(counterForButtonPress1s[i] < DURATION_OF_AUTO_INCREASING){
					counterForButtonPress1s[i]++;
				}else{
					flagForButtonPress1s[i] = 1;
					//to do
				}
			}else{
				counterForButtonPress1s[i] = 0;
				flagForButtonPress1s[i] = 0;
			}
		}

	}
}

unsigned char is_button_pressed(uint8_t index){
	if(index >= NUMBER_OF_BUTTONS)return 0;
	else{
		return buttonBuffer[index] == BUTTON_IS_PRESSED;
	}
}

unsigned char is_button_pressed_1s(uint8_t index){
	if(index >= NUMBER_OF_BUTTONS)return 0xff;
	return flagForButtonPress1s[index] == 1;
}

#include <button/input_processing.h>
#include <button/input_reading.h>
#include <timer/timer.h>
#include <leds_display/led_7seg_display.h>
#include <leds_display/Traffic_Light.h>

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		timer0_run();
		seven_segment_led_driver();
		mode_seven_segment_led_driver();
		reading_button();
	}

}


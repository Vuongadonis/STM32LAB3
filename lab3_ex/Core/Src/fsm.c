/*
 * fsm.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Acer
 */


#include "fsm.h"
#include "main.h"
#include "softwareTimer.h"
#include "global.h"

void mode1() {
	switch( led_status ) {
	case 0:
		led_status = 1;
		led7buffer[1] = 6;
		led7buffer[0] = 4;
		break;
	case 1:
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, RESET);
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		if( flag1 == 1 ) {
			led_status = 2;
			led7buffer[1] = 3;
			led7buffer[0] = 3;
			setTimer1(3000);
		}
		break;
	case 2:
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, RESET);
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, RESET);
		if( flag1 == 1 ) {
			led_status = 3;
			led7buffer[1] = 4;
			led7buffer[0] = 6;
			setTimer1(2000);
		}
		break;
	case 3:
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, RESET);
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		if( flag1 == 1 ) {
			led_status = 4;
			led7buffer[1] = 3;
			led7buffer[0] = 3;
			setTimer1(3000);
		}
		break;
	case 4:
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, RESET);
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, RESET);
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		if( flag1 == 1 ) {
			led_status = 1;
			led7buffer[1] = 6;
			led7buffer[0] = 4;
			setTimer1(2000);
		}
		break;
	default:
		break;
	}
	if( flag_7seg == 1 && led_status != OUT) {
		led7buffer[0]--;
		led7buffer[1]--;
		if(led7buffer[0] < 0) {
			led7buffer[0] = 5;
		}
		if(led7buffer[1] < 0) {
			led7buffer[1] = 6;
		}
		setTime_counter_7seg(1000);
	}

}

void mode2() {
	if( flagBlinkMode == 1 ) {
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, blink_state);
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, blink_state);
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		blink_state = 1 - blink_state;
		setTimerBlinkMode(250);
	}
	if( isButton2Pressed() == 1) {
		red_timer_mode++;
		if( red_timer_mode > 99 ) {
			red_timer_mode = 0;
		}
	}
	if( isButton3Pressed() == 1 ) {
		red_timer = red_timer_mode;
	}
}

void mode3() {
	if( flagBlinkMode == 1 ) {
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, blink_state);
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, blink_state);
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
		blink_state = 1 - blink_state;
		setTimerBlinkMode(250);
	}
	if( isButton2Pressed() == 1) {
		green_timer_mode++;
		if( green_timer_mode > 99 ) {
			green_timer_mode = 0;
		}
	}
	if( isButton3Pressed() == 1 ) {
		green_timer = green_timer_mode;
	}
}

void mode4() {
	if( flagBlinkMode == 1 ) {
		HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, blink_state);
		HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, blink_state);
		HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
		blink_state = 1 - blink_state;
		setTimerBlinkMode(250);
	}
	if( isButton2Pressed() == 1) {
		yellow_timer_mode++;
		if( yellow_timer_mode > 99 ) {
			yellow_timer_mode = 0;
		}
	}
	if( isButton3Pressed() == 1 ) {
		yellow_timer = yellow_timer_mode;
	}
}

void fsmButton() {
	switch( traffic_status ) {
	case 0:
		traffic_status = 1;
		led_status = 0;
		break;
	case 1:
		mode1();
		led7buffer[2] = 0;
		led7buffer[3] = 1;
		if( isButton1Pressed() == 1 ) {
			traffic_status = 2;
			led_status = OUT;
		}
		break;
	case 2:
		mode2();
		led7buffer[0] = red_timer_mode/10;
		led7buffer[1] = red_timer_mode%10;
		led7buffer[2] = 0;
		led7buffer[3] = 2;
		if( isButton1Pressed() == 1 ) {
			red_timer_mode = red_timer;
			traffic_status = 3;
			led_status = OUT;
		}
		break;
	case 3:
		mode3();
		led7buffer[0] = green_timer_mode/10;
		led7buffer[1] = green_timer_mode%10;
		led7buffer[2] = 0;
		led7buffer[3] = 3;
		if( isButton1Pressed() == 1 ) {
			green_timer_mode = green_timer;
			traffic_status = 4;
			led_status = OUT;
		}
		break;
	case 4:
		mode4();
		led7buffer[0] = yellow_timer_mode/10;
		led7buffer[1] = yellow_timer_mode%10;
		led7buffer[2] = 0;
		led7buffer[3] = 4;
		if( isButton1Pressed() == 1 ) {
			yellow_timer_mode = yellow_timer;
			traffic_status = 1;
			led_status = 0;
		}
		break;
	default:
		break;
	}
}
/*
 * button.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Acer
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#define PRESSED_STATE 	0
#define NORMAL_STATE 	1


int isButton1Pressed();
int isButton2Pressed();
int isButton3Pressed();

int isButton1LongPressed();
int isButton2LongPressed();
int isButton3LongPressed();

void getKeyInput1();
void getKeyInput2();
void getKeyInput3();

#endif /* INC_BUTTON_H_ */

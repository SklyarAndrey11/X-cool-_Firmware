/*
 * buzzer.h
 *
 *  Created on: Sep 26, 2023
 *      Author: Loc
 */

#ifndef SRC_BUZZER_H_
#define SRC_BUZZER_H_
#include <stdint.h>
#include "led.h"
extern led_t buzzer;
void buzzer_init(void);
void buzzer_togle(led_t* buzzer, uint16_t on_ms, uint16_t off_ms, uint16_t count);
#endif /* SRC_BUZZER_H_ */

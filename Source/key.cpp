#include "key.hpp"


#include "gpio.h"
uint8_t mode = 0x00;
Key :: Key(uint8_t (*Key_State)()) : key_state(Key_State),trg(0),cont(0) {
        ReadData = key_state() ^ 0xff;
		trg = ReadData & (ReadData^cont);
		cont = ReadData;
        }

uint8_t Key1_State() { 
   return HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);
}
uint8_t Key2_State() { 
   return HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin);
}


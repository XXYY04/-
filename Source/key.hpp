#ifndef KEY_HPP
#define KEY_HPP


#include <stdint.h>


#define KEY1_FALLING 0x01
#define KEY2_FALLING 0x01




	
class Key { 
public:
      Key(uint8_t (*Key_State)());
    uint8_t (*key_state)();
    uint8_t ReadData;
    uint8_t trg;
    uint8_t cont;
};

  uint8_t Key1_State();
  uint8_t Key2_State();   







#endif

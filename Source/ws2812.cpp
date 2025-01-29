#include "ws2812.hpp"
#include "tim.h"
#include <stdint.h>
#include <vector>
#include "key.hpp"

WS2812 red(11,RED);
WS2812 blue(11,BLUE);
WS2812 black(11,BLACK);
Key key1(Key1_State);

const RGB_Color_TypeDef WHITE = {255,255,255}; //白色
const RGB_Color_TypeDef HALF_WHITE = {127,127,127}; //淡白色
const RGB_Color_TypeDef BLACK = {0,0,0}; //黑色
const RGB_Color_TypeDef RED = {0,255,0}; //红色
const RGB_Color_TypeDef GREEN = {255,0,0}; //绿色
const RGB_Color_TypeDef BLUE = {0,0,255}; //蓝色



WS2812 :: WS2812(uint8_t nums,RGB_Color_TypeDef color) : NUM(nums){
      Color_deta_buf.resize(NUM + 1);
      for( auto& row : Color_deta_buf)
         row.resize(24,0);
            Set_All(color); 
            Final_Set();
   }

    void WS2812 ::Final_Set(){    //置位信号
        Color_deta_buf[NUM].assign(24,0);
    }

    void WS2812 ::Set_One(RGB_Color_TypeDef color,int id){   //设置一个灯的颜色和ID
        uint8_t i;

    // 存储绿色通道的二进制值
    for (i = 0; i < 8; i++) 
    
        Color_deta_buf[id][i] = ((color.G & (1 << (7 - i))) ? HIGH : LOW);
    
    // 存储红色通道的二进制值
    for (i = 8; i < 16; i++) 
        Color_deta_buf[id][i] = ((color.R & (1 << (15 - i))) ? HIGH : LOW);
    
    // 存储蓝色通道的二进制值
    for (i = 16; i < 24; i++) 
        Color_deta_buf[id][i] = ((color.B & (1 << (23 - i))) ? HIGH : LOW);
    }

    void WS2812 :: Set_All(RGB_Color_TypeDef color){   //设置全部灯的颜色
        for(int i=0;i<NUM;i++){
            Set_One(color,i);
        }
    }
void WS2812 ::Send_Data() {
    std::vector<uint32_t> flat_buffer((NUM + 1) * 24); // 创建一个一维缓冲区
    for (uint8_t i = 0; i < NUM + 1; i++) {
        for (uint8_t j = 0; j < 24; j++) {
            flat_buffer[i * 24 + j] = Color_deta_buf[i][j];
        }
    }
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, flat_buffer.data(), (NUM + 1) * 24);
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_2, flat_buffer.data(), (NUM + 1) * 24);
}
    
uint8_t SOUND :: Sound_State(){
    return HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if(htim->Instance==TIM14){

        if (key1.trg & KEY1_FALLING)
        {
            mode++;  //mode = 1;
            if (mode == 1)
            {
            red.Send_Data();  
            }
            else if (mode == 2) 
            {
            blue.Send_Data();  
            mode = 0;
            }
            else if (mode == 0)
            {
            black.Send_Data();  
            }
        }
        
    }
}
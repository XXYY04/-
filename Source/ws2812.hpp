#ifndef WS2812_HPP
#define WS2812_HPP
#include <stdint.h>
#include <vector>

#define HIGH 53
#define LOW 26

// 定义RGB颜色结构体
typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} RGB_Color_TypeDef;

// 定义全局常量：白色
extern const RGB_Color_TypeDef WHITE;
extern const RGB_Color_TypeDef RED;
extern const RGB_Color_TypeDef GREEN;
extern const RGB_Color_TypeDef BLUE;
extern const RGB_Color_TypeDef BLACK;




extern uint8_t mode;
// 定义WS2812类
class WS2812 {
private:
    std::vector<std::vector<uint32_t>> Color_deta_buf; // 二维数组存储每个LED的24位数据
    uint8_t NUM; // LED数量

public:
    // 构造函数
    WS2812(uint8_t nums, RGB_Color_TypeDef color);

    // 设置终止信号
    void Final_Set();

    // 设置单个LED的颜色
    void Set_One(RGB_Color_TypeDef color, int id);

    // 设置所有LED的颜色
    void Set_All(RGB_Color_TypeDef color);

    // 发送数据到LED灯带
    void Send_Data();
};



class SOUND{
public:
    uint8_t Sound_State();
};

extern WS2812 red;
extern WS2812 blue;
extern WS2812 black;

#endif // WS2812_H


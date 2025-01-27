#ifndef WS2812_HPP
#define WS2812_HPP
#include <stdint.h>
#include <vector>

#define HIGH 53
#define LOW 26

// ����RGB��ɫ�ṹ��
typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} RGB_Color_TypeDef;

// ����ȫ�ֳ�������ɫ
extern const RGB_Color_TypeDef WHITE;
extern const RGB_Color_TypeDef RED;
extern const RGB_Color_TypeDef GREEN;
extern const RGB_Color_TypeDef BLUE;
extern const RGB_Color_TypeDef BLACK;




extern uint8_t mode;
// ����WS2812��
class WS2812 {
private:
    std::vector<std::vector<uint32_t>> Color_deta_buf; // ��ά����洢ÿ��LED��24λ����
    uint8_t NUM; // LED����

public:
    // ���캯��
    WS2812(uint8_t nums, RGB_Color_TypeDef color);

    // ������ֹ�ź�
    void Final_Set();

    // ���õ���LED����ɫ
    void Set_One(RGB_Color_TypeDef color, int id);

    // ��������LED����ɫ
    void Set_All(RGB_Color_TypeDef color);

    // �������ݵ�LED�ƴ�
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


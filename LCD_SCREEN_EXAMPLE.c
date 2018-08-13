#include "Energia.h"

#include "SPI.h"

#include "Screen_HX8353E.h"
Screen_HX8353E myScreen;

#include "LCD_SCREEN_EXAMPLE.h"

void setup() {
    myScreen.begin();
    myScreen.setOrientation(0);
}

void loop() {
    myScreen.clear(grayColour);
            
    uint16_t* image1_ptr = (uint16_t*)image1_arr;
    for (uint8_t y = 0; y < IMAGE1_H; y++)
        for (uint8_t x = 0; x < IMAGE1_W; x++)
                myScreen.point(x, y, *(image1_ptr++));

    uint16_t* image2_ptr = (uint16_t*)image2_arr;
    for (uint8_t y = 0; y < IMAGE2_H; y++)
        for (uint8_t x = 0; x < IMAGE2_W; x++)
                myScreen.point(x, y, *(image2_ptr++));


    uint16_t* image3_ptr = (uint16_t*)image3_arr;
    for (uint8_t y = 0; y < IMAGE3_H; y++)
        for (uint8_t x = 0; x < IMAGE3_W; x++)
                myScreen.point(x, y, *(image3_ptr++));

    
    uint16_t* image4_ptr = (uint16_t*)image4_arr;
    for (uint8_t y = 0; y < IMAGE4_H; y++)
        for (uint8_t x = 0; x < IMAGE4_W; x++)
                myScreen.point(x, y, *(image4_ptr++));


    uint16_t* image5_ptr = (uint16_t*)image5_arr;
    for (uint8_t y = 0; y < IMAGE5_H; y++)
        for (uint8_t x = 0; x < IMAGE5_W; x++)
                myScreen.point(x, y, *(image5_ptr++));            


     uint16_t* image6_ptr = (uint16_t*)image6_arr;
    for (uint8_t y = 0; y < IMAGE6_H; y++)
        for (uint8_t x = 0; x < IMAGE6_W; x++)
                myScreen.point(x, y, *(image6_ptr++));   
                
}


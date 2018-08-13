## **_HARDWARE COMPONENTS_**
- Educational BoosterPack MKII -> http://www.ti.com/tool/BOOSTXL-EDUMKII
- MSP-EXP432P401R LaunchPad -> http://www.ti.com/tool/msp-exp432p401r?jktype=recommendedresults#1

## **_SOFTWARE_**
- Energia -> http://energia.nu/download/

### **LCD DISPLAY**
- Startup Energia. This will open a new sketch. Copy "LCD_SCREEN_EXAMPLE.c" and "LCD_SCREEN_EXAMPLE.h" to the sketch.
- Select the appropriate board and port from the tools tab. Click on upload.

[![IMAGE DISPLAY ON A 128x128 TFT LCD](http://img.youtube.com/vi/xQYOcPorGW0/0.jpg)](https://www.youtube.com/watch?v=xQYOcPorGW0 "IMAGE DISPLAY ON A 128x128 TFT LCD")

- This example is a slight modification of the already available built-in LCD examples. To learn more, check out: http://energia.nu/guide/edumkii/edumkii_lcd_screen_logos/  OR
- Startup Energia -> File -> Examples -> EducationalBP_MKII -> LCD_screen_Logos

- #### **IMAGE FILE -> C-ARRAY**
- To play around with different images, **convert the image file (example: .png) into a C-array**.
- If the image is in an another file format -> Open MS Paint -> Resize the image (example: 128x128) to the desired display -> File -> Save as type: PNG   
- The [png2c](https://github.com/vaskevich/png2c) program can convert a .PNG file into a C-array.
- For this example the [png2c](https://github.com/vaskevich/png2c) program is compiled on Ubuntu. 
- Before running this program, check if the PNG library (libpng) is installed. Else, open the terminal -> sudo apt-get install libpng-dev

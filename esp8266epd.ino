#include <SPI.h>
#include "epd2in13_V2.h"
#include "imagedata.h"
#include "epdpaint.h"
#include "GUI_Paint.h"
#include "DEV_Config.h"
Epd epd;

void setup()
{
  const int Width = 104;
  const int Height = 212;
  
  // put your setup code here, to run once:
  printf("EPD_2IN13_test Demo\r\n");
  DEV_Module_Init();
  
  epd.Init(FULL);
  epd.Clear();

    //Create a new image cache
  UBYTE *BlackImage;
  /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
  UWORD Imagesize = ((104 % 8 == 0) ? (104 / 8 ) : (104 / 8 + 1)) * 212;
  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    while (1);
  }
  Paint_NewImage(BlackImage, 104, 212, 270, WHITE);

  printf("Drawing\r\n");
  //1.Select Image
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  // 2.Drawing on the image
  Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
  Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
  Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
  Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

  Paint_DrawLine(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawLine(70, 10, 20, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawRectangle(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(85, 10, 135, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

  Paint_DrawLine(45, 15, 45, 55, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawLine(25, 35, 70, 35, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawCircle(45, 35, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawCircle(110, 35, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);

  Paint_DrawString_EN(140, 15, "waveshare", &Font16, BLACK, WHITE);
  Paint_DrawNum(140, 40, 123456789, &Font16, BLACK, WHITE);

  Paint_DrawString_CN(140, 60, "你好abc", &Font12CN, BLACK, WHITE);
  Paint_DrawString_CN(5, 65, "微雪电子", &Font24CN, WHITE, BLACK);

     char s,e;
    for (int x = 0; x < Width / 8; x++) {
    for (int y = 0; y < Height/2; y++) {
        s=BlackImage[x+y* Width / 8];
        e=BlackImage[x+(Height-1-y)* Width / 8];
        BlackImage[x+y* Width / 8]=e;
        BlackImage[x+(Height-1-y)* Width / 8]=s;
    }
    }
 
  epd.Display(BlackImage);

  epd.show();
  
  epd.Sleep();

}

void loop()
{

}

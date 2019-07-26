
/*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Display_EPD_W21.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

ErrorStatus HSEStartUpStatus;


/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);

#define DELAYTIME 50
#define xDot 200
#define yDot 200

const unsigned char logo[] = {
 /* 0X00,0X01,0XC8,0X00,0XC8,0X00, */

0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X1E,0X1F,0XFF,0XFF,0XCF,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X3C,0X8F,0XFF,0XFF,0X07,0XF0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X3D,0XCF,0XFF,0XFF,0X73,0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7D,0XEF,0XFF,0XFE,0X73,
0XF8,0X00,0X0F,0XC0,0X7C,0X38,0X0E,0X00,0X0F,0XF9,0XFF,0XE0,0X0E,0X03,0XF7,0X00,
0XE7,0XFC,0X00,0X00,0X7C,0XCF,0XFF,0XFE,0X73,0XF8,0X00,0X0F,0XC0,0X7C,0X38,0X0E,
0X00,0X0F,0XF9,0XFF,0XE0,0X0E,0X03,0XF7,0X81,0XE7,0XFC,0X00,0X00,0X7E,0X1F,0XFC,
0XFF,0X07,0XF8,0X00,0X0F,0XC0,0XFC,0X38,0X0E,0X00,0X0F,0XF9,0XFF,0XE0,0X0E,0X01,
0XE3,0X81,0XC7,0XFC,0X00,0X00,0X7E,0X1F,0XF8,0X7F,0X8F,0XF8,0X00,0X0E,0XE0,0XFC,
0X38,0X0E,0X00,0X0F,0X00,0X1E,0X00,0X0E,0X01,0XE3,0X81,0XC7,0X80,0X00,0X00,0X7E,
0X1F,0XF8,0X7F,0XDF,0XF8,0X00,0X0E,0XE0,0XDC,0X38,0X0E,0X00,0X0F,0X00,0X1E,0X00,
0X0E,0X01,0XE3,0XC3,0XC7,0X80,0X00,0X00,0X7E,0X4F,0XFA,0X7F,0XDF,0XF8,0X00,0X0E,
0XE1,0XDC,0X38,0X0E,0X00,0X0F,0X00,0X1E,0X00,0X0E,0X01,0XE1,0XC3,0X87,0X80,0X00,
0X00,0X7E,0X6F,0XF2,0X7F,0XDF,0XC0,0X00,0X0E,0X71,0XDC,0X3F,0XFE,0X00,0X0F,0XF8,
0X1E,0X00,0X0E,0X01,0XE1,0XC3,0X87,0XFC,0X00,0X00,0X7E,0X67,0XF2,0X7F,0XDF,0XC0,
0X00,0X0E,0X71,0X9C,0X3F,0XFE,0X00,0X0F,0XF8,0X1E,0X00,0X0E,0X01,0XE1,0XE7,0X87,
0XFC,0X00,0X00,0X7E,0X73,0XE6,0X7F,0XDF,0XF8,0X00,0X0E,0X73,0X9C,0X3F,0XFE,0X1F,
0X8F,0XF8,0X1E,0X00,0X0E,0X01,0XE0,0XE7,0X07,0XFC,0X00,0X00,0X7E,0X73,0XE6,0X7F,
0XDF,0XF8,0X00,0X0E,0X3B,0X9C,0X38,0X0E,0X1F,0X8F,0X00,0X1E,0X00,0X0E,0X01,0XE0,
0XE7,0X07,0X80,0X00,0X00,0X7E,0X79,0XEE,0X7F,0XDF,0XC0,0X00,0X0E,0X3B,0X1C,0X38,
0X0E,0X00,0X0F,0X00,0X1E,0X00,0X0E,0X01,0XE0,0XFF,0X07,0X80,0X00,0X00,0X7E,0X7D,
0XCE,0X7F,0XDF,0XC0,0X00,0X0E,0X3F,0X1C,0X38,0X0E,0X00,0X0F,0X00,0X1E,0X00,0X0E,
0X01,0XE0,0X7E,0X07,0X80,0X00,0X00,0X7E,0X7C,0XCE,0X7F,0XDF,0XF8,0X00,0X0E,0X1F,
0X1C,0X38,0X0E,0X00,0X0F,0X00,0X1E,0X00,0X0E,0X01,0XE0,0X7E,0X07,0X80,0X00,0X00,
0X7E,0X7E,0X5E,0X7F,0XDF,0XF8,0X00,0X0E,0X1E,0X1C,0X38,0X0E,0X00,0X0F,0XFC,0X1E,
0X00,0X0F,0XFB,0XF0,0X7E,0X07,0XFE,0X00,0X00,0X7E,0X7E,0X1E,0X7F,0XDF,0XF8,0X00,
0X0E,0X0E,0X1C,0X38,0X0E,0X00,0X0F,0XFC,0X1E,0X00,0X0F,0XFB,0XF0,0X3C,0X07,0XFE,
0X00,0X00,0X7E,0X7F,0X3E,0X7F,0XDF,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7E,0X7F,0XFE,0X7F,0XDC,
0X38,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X7C,0X3F,0XFE,0X7F,0XD9,0X98,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X79,0X9F,0XFE,
0X00,0X03,0XD8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X7B,0XC0,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7B,
0X9F,0XFE,0X7F,0XD9,0X98,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X79,0X1F,0XFE,0X7F,0XDC,0X38,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X7C,0X3F,0XFE,0X7F,0XDF,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0XFF,0XFE,0X7F,0XDF,0XF8,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X7F,0XFF,0XFE,0X7F,0XDC,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0XFF,0XFE,0X7F,
0XDF,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X7F,0XFF,0XFE,0X7F,0XDC,0X00,0X00,0X00,0X00,0X00,0X00,
0X39,0X80,0X00,0X00,0X00,0X00,0X00,0X0C,0X03,0X00,0X00,0X00,0X00,0X00,0X7F,0XFF,
0XFE,0X7F,0XDC,0X00,0X00,0X00,0X06,0X0E,0X00,0X39,0X80,0X00,0X70,0XE1,0X80,0X00,
0X0C,0X03,0X18,0XE3,0X00,0X00,0X00,0X7F,0XFF,0XFE,0X7F,0XDF,0XF8,0X00,0X00,0X06,
0X0E,0X00,0X39,0X80,0X00,0X30,0XE1,0X80,0X00,0X0C,0X03,0X18,0XE3,0X00,0X00,0X00,
0X7F,0XFF,0XFE,0X7F,0XDC,0X00,0X00,0X00,0X06,0X0E,0X00,0X39,0X80,0X00,0X30,0XF3,
0X80,0X00,0X0C,0X03,0X18,0XE3,0X00,0X00,0X00,0X7F,0XFF,0XFE,0X7F,0XDF,0XF8,0X00,
0X00,0X06,0X0E,0X1E,0X39,0X87,0X80,0X39,0XB3,0X87,0X86,0XCC,0X3B,0X18,0XE3,0X00,
0X00,0X00,0X7F,0XFF,0XFE,0X7F,0XDF,0XF8,0X00,0X00,0X06,0X0E,0X3F,0X39,0X8F,0XE0,
0X39,0XB3,0X1F,0XC6,0XCC,0X7F,0X18,0XE3,0X00,0X00,0X00,0X7F,0XFF,0XFE,0X7F,0XDF,
0XF8,0X00,0X00,0X07,0XFE,0X63,0X39,0X9C,0X60,0X19,0XB3,0X18,0XE7,0X0C,0XE7,0X18,
0XE3,0X00,0X00,0X00,0X7F,0XFF,0XFE,0X7F,0XDF,0XF8,0X00,0X00,0X07,0XFE,0X63,0XB9,
0X98,0X70,0X1B,0XBB,0X38,0X67,0X0C,0XC3,0X18,0XE3,0X00,0X00,0X00,0X7F,0XFF,0XFC,
0X1F,0X07,0XF8,0X00,0X00,0X06,0X0E,0X7F,0XB9,0X98,0X70,0X1F,0X1F,0X38,0X66,0X0C,
0XC3,0X18,0XE3,0X00,0X00,0X00,0X7F,0XFF,0XF9,0X9F,0X73,0XF8,0X00,0X00,0X06,0X0E,
0X60,0X39,0X98,0X70,0X1F,0X1E,0X38,0X66,0X0C,0XC3,0X00,0X00,0X00,0X00,0X00,0X3F,
0XFF,0XF9,0XDE,0X73,0XF0,0X00,0X00,0X06,0X0E,0X71,0X39,0X9C,0XE0,0X0F,0X1E,0X1C,
0XE6,0X0C,0XE7,0X18,0XE3,0X00,0X00,0X00,0X3F,0XFF,0XF9,0XDE,0X73,0XF0,0X00,0X00,
0X06,0X0E,0X3F,0X39,0X8F,0XC0,0X0E,0X1E,0X0F,0XC6,0X0C,0X7F,0X18,0XE7,0X00,0X00,
0X00,0X1F,0XFF,0XF8,0X1F,0X07,0XE0,0X00,0X00,0X00,0X00,0X0C,0X00,0X03,0X00,0X00,
0X00,0X03,0X00,0X00,0X30,0X08,0X42,0X00,0X00,0X00,0X0F,0XFF,0XFC,0X3F,0X8F,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X3F,0XDF,0XDF,0XDF,0XDF,0XFF,0XEF,0XEF,0XEF,0XEF,0XFF,0XF7,0XF7,0XF7,0XF7,
0XFB,0XFB,0XFB,0XFB,0XFB,0XFD,0XFD,0XFD,0XFD,0XFE,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF0,
0X00,0X00,0X01,0X80,0X00,0XC0,0X00,0X00,0X06,0X06,0X0E,0X31,0XCE,0X0E,0X0C,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFE,0X00,0X00,0X01,0X80,0X18,0XC0,0X00,
0X00,0X1F,0X9F,0X1F,0X31,0X9F,0X1F,0X1F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0XC6,0X00,0X00,0X01,0X80,0X18,0X00,0X00,0X00,0X11,0X99,0XB3,0X1B,0X01,0X93,
0XB3,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC6,0X3C,0X79,0XF1,0XB1,0XBC,
0XCF,0X8B,0X81,0X81,0XB1,0XB1,0X9B,0X01,0XB1,0XB3,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0XCE,0X66,0XC9,0XB9,0XB1,0XBC,0XDD,0XCD,0XC1,0X83,0XB1,0XB1,0X8E,
0X03,0X31,0XB1,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF8,0X66,0XE3,0X19,
0XB1,0X98,0XD8,0XCC,0XC0,0X03,0X31,0XB1,0X8E,0X07,0X31,0XB1,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0XCC,0X7E,0X7B,0X19,0XB1,0X98,0XD8,0XC8,0XC0,0X0E,0X31,
0XB1,0X9B,0X0E,0X31,0XB3,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC6,0X60,
0X1B,0X19,0XB1,0X98,0XD8,0XC8,0XC0,0X1C,0X19,0XB3,0X1B,0X18,0X33,0X33,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC7,0X7C,0XF9,0XF9,0X9F,0X9C,0XCF,0X88,0XC1,
0X9F,0X9F,0X1F,0X31,0X9F,0X9F,0X1F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XC3,0X3C,0XF0,0XE1,0X9D,0X8C,0XC7,0X08,0XC1,0X9F,0X8E,0X0E,0X71,0XDF,0X8E,0X0C,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1C,
0X00,0X00,0X00,0X00,0X0C,0X00,0X00,0X18,0X60,0X06,0X00,0X00,0X00,0X00,0X70,0X06,
0X30,0X61,0XBE,0X01,0X8C,0X18,0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0X8C,0X00,0X00,
0X18,0X60,0X06,0X60,0X00,0X00,0X00,0XF8,0X0F,0X98,0X61,0XBE,0X03,0XEC,0X30,0X00,
0X00,0X63,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X1C,0X60,0X06,0X60,0X00,0X00,0X00,
0X0C,0X01,0X98,0XC3,0X30,0X06,0X66,0X30,0X00,0X00,0XC1,0XB7,0X0F,0X34,0XF3,0XED,
0XB8,0XFC,0X0C,0X43,0XC6,0XF3,0XC3,0XE3,0XCC,0X0C,0X01,0X98,0XC3,0X30,0X06,0X66,
0X30,0X00,0X00,0XC1,0XBB,0X99,0X3C,0X9B,0XCD,0XDC,0XDC,0X0C,0XC6,0XE6,0XF2,0X66,
0XE6,0X6C,0X78,0X0F,0X0C,0X82,0X3E,0X06,0X66,0X60,0X00,0X00,0XC1,0XB9,0X91,0XB0,
0X39,0X8D,0X8D,0X8C,0X06,0XCC,0X66,0X60,0XE6,0X66,0X60,0X78,0X0F,0X8D,0X86,0X07,
0X06,0X63,0X60,0X00,0X00,0XC1,0XB1,0XBF,0XB1,0XF9,0X8D,0X8D,0X8C,0X06,0X8C,0X66,
0X63,0XEC,0X67,0XE0,0X0C,0X01,0X8D,0X84,0X03,0X06,0X63,0X60,0X00,0X00,0XE3,0XB9,
0X98,0X31,0X99,0X8D,0X8D,0X8C,0X07,0X8C,0X66,0X66,0X66,0X66,0X00,0X0C,0X01,0X87,
0X0C,0X03,0X06,0X63,0XC0,0X00,0X00,0X7F,0X3F,0X9F,0X31,0XF9,0XED,0X8C,0XFC,0X03,
0X87,0XE6,0X77,0XE7,0XE7,0XEC,0XFD,0XDF,0X87,0X0C,0X3E,0X67,0XE1,0XC0,0X00,0X00,
0X1C,0X37,0X0F,0X30,0XD8,0XED,0X8C,0X6C,0X03,0X03,0X86,0X33,0X63,0X61,0XCC,0XF0,
0X8E,0X07,0X18,0X3C,0X21,0X81,0XC0,0X00,0X00,0X00,0X30,0X00,0X00,0X00,0X00,0X00,
0X0C,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X18,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X30,0X00,0X00,0X00,0X00,0X00,0XF8,0X00,0X00,0X00,0X00,0X07,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X30,0X00,0X00,0X00,
0X00,0X00,0XF0,0X00,0X00,0X00,0X00,0X07,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X70,
0X00,0X38,0X00,0X00,0XC0,0X0E,0X0E,0X00,0X06,0X00,0X01,0XE3,0X00,0X30,0X00,0X60,
0XD8,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0XFE,0X00,0X60,0X00,0X00,0XC0,0X0E,0X1E,
0X00,0X06,0X00,0X07,0XF3,0X00,0X30,0X00,0X60,0X98,0X00,0X00,0X01,0X80,0X00,0X00,
0X00,0XC6,0X00,0X60,0X00,0X00,0XC0,0X0F,0X1E,0X00,0X06,0X00,0X0E,0X13,0X00,0X30,
0X00,0X61,0X98,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0XC6,0X3C,0XF6,0XCE,0X1C,0XDC,
0X0F,0X16,0X3C,0X3E,0X3C,0XCC,0X03,0X3E,0X3E,0X3E,0X61,0X98,0X1E,0X1E,0XF9,0X80,
0X00,0X00,0X00,0XCE,0X66,0XF7,0XDB,0X30,0XEC,0X0D,0X36,0X6E,0X76,0X66,0XCC,0XF3,
0X77,0X3F,0X26,0X63,0X18,0X37,0X3A,0X9D,0X80,0X00,0X00,0X00,0XF8,0X66,0X66,0X31,
0XB0,0XCC,0X0D,0XB6,0XC6,0X66,0X66,0X0C,0XF3,0X63,0X33,0X06,0X63,0X18,0X63,0X60,
0X1D,0X80,0X00,0X00,0X00,0XCC,0X7E,0X66,0X3F,0XBC,0XCC,0X0D,0XA6,0XC3,0X66,0X7E,
0X0C,0X33,0X63,0X23,0X3E,0X62,0X18,0X63,0X60,0XFD,0X80,0X00,0X00,0X00,0XC6,0X60,
0X66,0X30,0X06,0XCC,0X0C,0XE6,0XE6,0X66,0X60,0X0E,0X33,0X63,0X33,0X66,0X66,0X18,
0X63,0X70,0XCD,0X80,0X00,0X00,0X00,0XC6,0X7C,0X66,0X1F,0X3E,0XCC,0X0C,0XE6,0X7E,
0X7E,0X7E,0XE7,0XF3,0X3E,0X3F,0X7E,0X66,0X1F,0X3F,0X3E,0XFD,0X80,0X00,0X00,0X00,
0XC3,0X3C,0X66,0X0F,0X38,0XCC,0X0C,0XC6,0X3C,0X3E,0X1C,0X41,0XE3,0X1C,0X3E,0X3A,
0X6C,0X1F,0X1C,0X1E,0X6D,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0C,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0C,
0X00,0X00,0X00,0X00,0X00,0X00,0X30,0X00,0X00,0XC0,0X00,0X00,0X00,0X00,0X00,0X60,
0X00,0X38,0X00,0X00,0X00,0X00,0X00,0X00,0X3E,0X00,0X00,0X00,0X00,0X00,0X00,0X30,
0X00,0X08,0XC0,0X00,0X00,0XE0,0XE0,0X00,0X60,0X00,0XFC,0XFD,0XE0,0X00,0X00,0X00,
0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X18,0X00,0X00,0X00,0XF1,0XE0,
0X00,0X60,0X00,0XC0,0XCE,0XC0,0X00,0X00,0X00,0X00,0XC0,0X3C,0X7E,0XE6,0XEE,0X63,
0X2E,0X31,0XCF,0X3E,0XC7,0X8D,0XC0,0XF1,0X63,0XC3,0XE3,0XCC,0XC0,0XCE,0XC0,0X00,
0X00,0X00,0X00,0XC0,0X6E,0X7F,0X67,0X77,0X63,0X37,0X37,0X49,0XBE,0XCE,0XCE,0XC0,
0XDB,0X67,0XE7,0X67,0X6C,0XF0,0XCC,0XC0,0X00,0X00,0X00,0X00,0XC0,0XC6,0X66,0X66,
0X63,0X63,0X33,0X36,0X01,0X98,0XCC,0X6C,0XC0,0XDB,0X6C,0X66,0X66,0X60,0X3C,0XFC,
0XC0,0X00,0X00,0X00,0X00,0XC0,0XC6,0X66,0X66,0X63,0X63,0X23,0X36,0X0F,0X98,0XD8,
0X6C,0X40,0XDA,0X6C,0X36,0X27,0XE0,0X0C,0XC0,0XC0,0X00,0X00,0X00,0X00,0XE0,0XC6,
0X66,0X66,0X63,0X63,0X23,0X36,0X19,0X98,0XCC,0XEC,0X40,0XCE,0X66,0X66,0X66,0X00,
0X0C,0XC0,0XC0,0X00,0X00,0X00,0X00,0X7E,0X7E,0X66,0X66,0X63,0X3F,0X23,0X33,0XDF,
0X8E,0XCF,0XCC,0X40,0XCE,0X67,0XE7,0XE7,0XEE,0XFC,0XC1,0XE0,0X00,0X00,0X00,0X00,
0X1E,0X3C,0X66,0X66,0X63,0X3B,0X23,0X31,0XCF,0X8E,0XC7,0X8C,0X40,0XCC,0X63,0XC3,
0XE1,0XC4,0XF8,0XC1,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC6,
0X31,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC6,0X31,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0XC6,0X31,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC6,0X31,0X80,0X00,0X00,0X00,
0X00,0X0F,0XFF,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0XC6,0X31,0X80,0X00,0X00,0X00,0X00,0X3F,0XFF,0XFF,0XE0,0X00,0X00,
0X00,0X00,0X00,0X01,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC6,0X31,0X80,0X00,
0X00,0X00,0X00,0X3F,0XFF,0XFF,0XF0,0X00,0X00,0X00,0X00,0X00,0X07,0XFF,0XC0,0X00,
0X00,0X00,0X00,0X00,0X00,0XC6,0X31,0X80,0X00,0X00,0X00,0X00,0X70,0X00,0X01,0XF8,
0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X70,0X00,0X01,0XBC,0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,
0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X70,0X00,
0X01,0X9E,0X00,0X00,0X00,0X00,0X00,0X1F,0XEF,0XF0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X70,0X00,0X01,0X8E,0X00,0X00,0X00,0X00,0X00,
0X3F,0XE7,0XF9,0X00,0X00,0X00,0X00,0X00,0X03,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,
0X70,0X00,0X01,0XC7,0X00,0X00,0X00,0X00,0X00,0X3F,0XC7,0XFF,0X00,0X00,0X00,0X00,
0X00,0X03,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0X70,0XFF,0XF1,0XFF,0X00,0X00,0X00,
0X00,0X00,0X7F,0XC3,0XFF,0X00,0X00,0X00,0X00,0X1F,0XE3,0XFF,0XFF,0XE7,0XF8,0X00,
0X00,0X00,0X70,0XFF,0XF0,0XFF,0X00,0X00,0X00,0X00,0X00,0X7F,0X83,0XFE,0X00,0X00,
0X00,0X00,0X1F,0XE3,0XFF,0XFF,0XE7,0XF8,0X00,0X00,0X00,0X70,0X00,0X00,0X07,0X00,
0X00,0X00,0X00,0X00,0XFF,0X01,0XFE,0X00,0X00,0X00,0X00,0X00,0X03,0XFF,0XFF,0XE0,
0X00,0X00,0X00,0X00,0X70,0X00,0X00,0X07,0X00,0X00,0X00,0X00,0X00,0XFF,0X01,0XFE,
0X00,0X00,0X00,0X00,0X00,0X03,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0X70,0X00,0X00,
0X07,0X00,0X00,0X00,0X00,0X00,0X3E,0X07,0XFE,0X00,0X00,0X00,0X00,0X00,0X03,0XFF,
0XFF,0XE0,0X00,0X00,0X00,0X00,0X70,0X00,0X00,0X07,0X00,0X00,0X00,0X00,0X00,0X1E,
0X01,0XFC,0X00,0X00,0X00,0X00,0X1F,0XE3,0XFF,0XFF,0XE7,0XF8,0X00,0X00,0X00,0X70,
0XFF,0XFF,0X87,0X00,0X00,0X00,0X00,0X01,0XC4,0X00,0X3C,0X40,0X00,0X00,0X00,0X1F,
0XE3,0XFF,0XFF,0XE7,0XF8,0X00,0X00,0X00,0X70,0XFF,0XFF,0X87,0X00,0X00,0X00,0X00,
0X1F,0XC0,0X3C,0X01,0XC0,0X00,0X00,0X00,0X00,0X03,0XFF,0XFF,0XE0,0X00,0X00,0X00,
0X00,0X70,0X7F,0XFF,0X87,0X00,0X00,0X00,0X00,0XFF,0XC0,0X3C,0X07,0XE0,0X00,0X00,
0X00,0X00,0X03,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0X70,0X00,0X00,0X07,0X00,0X00,
0X00,0X00,0X3F,0XE0,0X38,0X1F,0XE0,0X00,0X00,0X00,0X00,0X03,0XFF,0XFF,0XE0,0X00,
0X00,0X00,0X00,0X70,0X00,0X00,0X07,0X00,0X00,0X00,0X00,0X1F,0XE0,0X78,0X0F,0XF0,
0X00,0X00,0X00,0X1F,0XE3,0XFF,0XFF,0XE7,0XF8,0X00,0X00,0X00,0X70,0X00,0X00,0X07,
0X00,0X00,0X00,0X00,0X3F,0XE0,0X7E,0X0F,0XF8,0X00,0X00,0X00,0X1F,0XE3,0XFF,0XFF,
0XE7,0XF8,0X00,0X00,0X00,0X70,0XFF,0XFF,0X87,0X00,0X00,0X00,0X00,0X7F,0XF0,0X7C,
0X07,0XF8,0X00,0X00,0X00,0X00,0X03,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0X70,0XFF,
0XFF,0X87,0X00,0X00,0X00,0X00,0X7F,0XF0,0X18,0X07,0XFC,0X00,0X00,0X00,0X00,0X03,
0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0X70,0XFF,0XFF,0X87,0X00,0X00,0X00,0X00,0XFF,
0X90,0X30,0X03,0XFC,0X00,0X00,0X00,0X0F,0XE3,0XFF,0XFF,0XE3,0XF8,0X00,0X00,0X00,
0X70,0X00,0X00,0X07,0X00,0X00,0X00,0X00,0XFF,0X00,0X20,0X01,0XFC,0X00,0X00,0X00,
0X1F,0XE3,0XFF,0XFF,0XE7,0XF8,0X00,0X00,0X00,0X70,0X00,0X00,0X07,0X00,0X00,0X00,
0X00,0XFF,0X00,0X40,0X01,0XFC,0X00,0X00,0X00,0X0F,0XE3,0XFF,0XFF,0XE7,0XF8,0X00,
0X00,0X00,0X70,0X00,0X00,0X07,0X00,0X00,0X00,0X00,0XFE,0X00,0X00,0X40,0XFC,0X00,
0X00,0X00,0X00,0X03,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0X70,0X00,0X00,0X07,0X00,
0X00,0X00,0X00,0X7C,0X00,0X00,0XC0,0XFC,0X00,0X00,0X00,0X00,0X03,0XFF,0XFF,0XE0,
0X00,0X00,0X00,0X00,0X70,0XFF,0XFF,0X87,0X00,0X00,0X00,0X00,0X3C,0X00,0X01,0XC0,
0X78,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X70,0XFF,0XFF,
0X87,0X00,0X00,0X00,0X00,0X3F,0XFF,0X83,0XFF,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X70,0X00,0X00,0X07,0X00,0X00,0X00,0X00,0X1F,0XFF,
0X87,0XFF,0XF0,0X00,0X00,0X00,0X00,0X00,0XC6,0X31,0X80,0X00,0X00,0X00,0X00,0X70,
0X00,0X00,0X07,0X00,0X00,0X00,0X00,0X1F,0XFF,0X8F,0XFF,0XF0,0X00,0X00,0X00,0X00,
0X00,0XC6,0X31,0X80,0X00,0X00,0X00,0X00,0X70,0X00,0X00,0X07,0X00,0X00,0X00,0X00,
0X0F,0XFF,0X9F,0XFF,0XE0,0X00,0X00,0X00,0X00,0X00,0XC6,0X31,0X80,0X00,0X00,0X00,
0X00,0X70,0X00,0X00,0X07,0X00,0X00,0X00,0X00,0X07,0XFF,0X8F,0XFF,0XE0,0X00,0X00,
0X00,0X00,0X00,0XC6,0X31,0X80,0X00,0X00,0X00,0X00,0X70,0X00,0X00,0X07,0X00,0X00,
0X00,0X00,0X03,0XFF,0X87,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0XC6,0X31,0X80,0X00,
0X00,0X00,0X00,0X3F,0XFF,0XFF,0XFE,0X00,0X00,0X00,0X00,0X00,0XFF,0X83,0XFF,0X80,
0X00,0X00,0X00,0X00,0X00,0XC6,0X31,0X80,0X00,0X00,0X00,0X00,0X3F,0XFF,0XFF,0XFE,
0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0XC6,0X31,
0X80,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0XC6,0X31,0X80,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X40,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X86,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
0X80,0X00,0X00,0X01,0XB6,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0C,0XC0,0X00,0X00,0X01,0X86,0X00,0X00,
0X78,0X00,0X00,0X00,0X0F,0X00,0X04,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X0C,0XDE,0X7C,0X73,0XC1,0XB6,0XCE,0X00,0X40,0X00,0X00,0X00,0X0C,0X00,0X00,
0X00,0X00,0XC2,0X01,0X04,0X02,0X00,0X30,0X00,0X00,0X0D,0XC2,0X66,0XDB,0X41,0XB6,
0X99,0X00,0X43,0XCF,0X3B,0XD9,0X0C,0X3D,0X34,0XF3,0XE0,0XC6,0X01,0X24,0X02,0X02,
0X20,0X00,0X00,0X0F,0X9F,0X66,0XFB,0X39,0XB7,0X9F,0X00,0X72,0X69,0X26,0X49,0X07,
0X05,0XA4,0X96,0X60,0XE6,0X49,0X74,0XB2,0X67,0X73,0X17,0XD8,0X0C,0X13,0X66,0X83,
0X01,0XB7,0X98,0X00,0X42,0X6F,0XA6,0X4F,0X01,0XBC,0XA4,0X96,0X60,0XAE,0X49,0X24,
0XD2,0X92,0X64,0X9F,0X6C,0X0C,0X1F,0X7C,0XD3,0X01,0XB6,0XDD,0X00,0X42,0X68,0X26,
0X46,0X09,0XEC,0XE4,0X92,0X60,0XAA,0X49,0X24,0X9A,0X72,0X6C,0XD3,0X64,0X0C,0X1B,
0X78,0X73,0X01,0XB6,0X66,0X00,0X7A,0X67,0X23,0XC6,0X0F,0X34,0XC4,0X93,0XE0,0XBA,
0X49,0X24,0X9A,0X92,0X64,0X93,0X64,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X44,0X00,0X00,0X00,0X00,0X40,0X92,0X79,0X34,0XF2,0XF3,0X67,0X93,0X64,
0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XDC,0X00,0X00,0X00,0X03,
0XC0,0X00,0X00,0X00,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00
};	

int main(void)
{
  unsigned int m;
	#ifdef DEBUG
	  debug();
	#endif
	// 系统时钟设置
	RCC_Configuration();
	//GPIO参数设置
	GPIO_Configuration();
	
	EPD_init_Full();
	driver_delay_xms(300);
	
	m=0xff;
	
	EPD_Dis_Full((unsigned char *)&m,0);
//	driver_delay_xms(DELAYTIME*3);
	
	EPD_Dis_Full((unsigned char *)&m,0);
//	driver_delay_xms(DELAYTIME*3);
  driver_delay_xms(300);	
	EPD_Dis_Full((unsigned char *)logo,1);
//	driver_delay_xms(DELAYTIME*3);
	
	EPD_Dis_Full((unsigned char *)logo,1);
//	driver_delay_xms(DELAYTIME*3);
	
	
  while(1)
  {		

   	}
}


/***********************************************************
						end file
***********************************************************/

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
 
  // 复位RCC时钟配置(用于调试模式) 
  RCC_DeInit();
 
  // 使能外部晶振 
  RCC_HSEConfig(RCC_HSE_ON);
  
  // 等待外部晶振稳定 
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  if(HSEStartUpStatus == SUCCESS)
  {
    // 设置锁相环频率PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
  }
  else {
    // 使能内部晶振 
    RCC_HSICmd(ENABLE);
    // 等待内置振荡器稳定 
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

    // 设置锁相环频率PLLCLK = 8MHz/2 * 16 = 64 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_16);
  }

    // 使能FLASH的预取缓冲 
  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

  //设置代码延时值,FLASH_Latency_2为两个延时周期
  FLASH_SetLatency(FLASH_Latency_2);
	
  //设置系统总线时钟
  RCC_HCLKConfig(RCC_SYSCLK_Div1); 

  //设置高速设备总线时钟，RCC_HCLK_Div1为系统时钟除以1
  RCC_PCLK2Config(RCC_HCLK_Div1); 

  //设置低速设备总线时钟，RCC_HCLK_Div2为系统时钟除以2
  RCC_PCLK1Config(RCC_HCLK_Div2);
  
  //使能锁相环倍频
  RCC_PLLCmd(ENABLE);
  
  // 等待锁相环倍频后的频率稳定 
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
  
  // 选择锁相环时钟为系统时钟源 
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
  // 等待设置完成 
  while(RCC_GetSYSCLKSource() != 0x08);
    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |
            RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO,
            ENABLE);

}

/*******************************************************************************
* 函数名   : GPIO_Configuration
* 描述         : 设置设置串口所用GPIO引脚的参数
* 输入         : None
* 输出         : None
* 返回         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;    //abcd OE ST LT0输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;    //abcd OE ST LT0输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{ 
  //NVIC_InitTypeDef NVIC_InitStructure;
  ;
}


#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif







#include <stdio.h>

#include "pico/stdlib.h"
#include "lib/fonts.h"
#include "lib/st7735.h"
#include "lib/ICM20948.h"

int main() {
  // Screen and other boilerplate initialisation
  stdio_init_all();  // Initialise serial in/output
  setvbuf ( stdout , NULL , _IONBF , 0 );  // Disable line and block buffering on stdout (for talking through serial)
  sleep_ms(1000);  // Give the Pico some time to think...
  ST7735_Init();  // Initialise the screen
  ST7735_DrawImage(0, 0, 80, 160, arducam_logo);  // Draw me :-)
  sleep_ms(1000);  // Sleep for 20 seconds

  // Accelerometer (Critically important, but I do not know what it does.)
  i2c_init(i2c0, 400 * 1000);
  gpio_set_function(4, GPIO_FUNC_I2C);
  gpio_set_function(5, GPIO_FUNC_I2C);
  gpio_pull_up(4);
  gpio_pull_up(5);
  sleep_ms(1000);
  
  IMU_EN_SENSOR_TYPE enMotionSensorType;

  imuInit(&enMotionSensorType);
  if (IMU_EN_SENSOR_TYPE_ICM20948 != enMotionSensorType) {
    printf("Failed to initialise IMU...");
  }

  printf("IMU initialised!");
  ST7735_FillScreen(ST7735_BLACK);

  float x;
  float y;
  float z;

  while (true) {
    icm20948AccelRead(&x, &y, &z);  // Use the addresses of our variables. This function sets data at a pointer, so we give it three pointers.

    // Use code adapted from "strings" in the ST7735 examples to print xyz
    char arrayX[10];
    if (x > 0) {
      sprintf(arrayX, "%.2f", x);
    } else {
      sprintf(arrayX, "%.1f", x);
    }

    char arrayY[10];
    if (y > 0) {
    sprintf(arrayY, "%.2f", y);
    } else {
      sprintf(arrayY, "%.1f", y);
    }

    char arrayZ[10];
    if (z > 0) {
      sprintf(arrayZ, "%.2f", z);
    } else {
      sprintf(arrayZ, "%.1f", z);
    }

    ST7735_WriteString(5, 5, arrayX, Font_16x26, ST7735_RED, ST7735_BLACK);
    ST7735_WriteString(5, 31, arrayY, Font_16x26, ST7735_GREEN, ST7735_BLACK);
    ST7735_WriteString(5, 57, arrayZ, Font_16x26, ST7735_BLUE, ST7735_BLACK);

    ST7735_WriteString(7, 120, "x", Font_16x26, ST7735_RED, ST7735_BLACK);
    ST7735_WriteString(27, 120, "y", Font_16x26, ST7735_GREEN, ST7735_BLACK);
    ST7735_WriteString(47, 120, "z", Font_16x26, ST7735_BLUE, ST7735_BLACK);
  }
}

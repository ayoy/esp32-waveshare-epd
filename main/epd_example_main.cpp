/**
 *  @filename   :   epd1in54-demo.ino
 *  @brief      :   1.54inch e-paper display demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     September 5 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "epd1in54b.h"
#include "epdpaint.h"
#include "imagedata.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/timer.h"

static const char * kEPDTAG = "EPD";

#define COLORED     0
#define UNCOLORED   1

extern "C" void app_main() {
  Epd epd;

  if (epd.Init() != 0) {
      ESP_LOGE(kEPDTAG, "e-Paper init failed");
      vTaskDelay(2000 / portTICK_RATE_MS);
      return;
  }
  ESP_LOGE(kEPDTAG, "e-Paper initialized");

  unsigned char* frame_black = (unsigned char*)malloc(epd.width * epd.height / 8);
  unsigned char* frame_red = (unsigned char*)malloc(epd.width * epd.height / 8);

  Paint paint_black(frame_black, epd.width, epd.height);
  Paint paint_red(frame_red, epd.width, epd.height);
  paint_black.Clear(UNCOLORED);
  paint_red.Clear(UNCOLORED);

  /* Draw something to the frame buffer */
  /* For simplicity, the arguments are explicit numerical coordinates */
  paint_black.DrawRectangle(10, 60, 50, 110, COLORED);
  paint_black.DrawLine(10, 60, 50, 110, COLORED);
  paint_black.DrawLine(50, 60, 10, 110, COLORED);
  paint_black.DrawCircle(120, 80, 30, COLORED);
  paint_red.DrawFilledRectangle(10, 130, 50, 180, COLORED);
  paint_red.DrawFilledRectangle(0, 6, 200, 26, COLORED);
  paint_red.DrawFilledCircle(120, 150, 30, COLORED);

  /*Write strings to the buffer */
  paint_black.DrawStringAt(30, 30, "e-Paper Demo", &Font12, COLORED);
  paint_red.DrawStringAt(28, 10, "Hello world!", &Font12, UNCOLORED);
 
  /* Display the frame buffer */
  epd.DisplayFrame(frame_black, frame_red);

  /* Display the image buffer */
  epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);
}

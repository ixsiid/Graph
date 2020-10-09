#include <esp_err.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <graph.hpp>
#include <ili9341.hpp>

#define TAG "Graph sample"
#include "log.h"

extern "C" {
void app_main();
}

uint8_t buffer1[320], buffer2[320];

void app_main() {
	LCD::ILI9341 *lcd = new LCD::ILI9341();

	for (int i = 0; i < 320; i++) {
		int v = i * 4;
		while (v >= 240) v -= 240;
		buffer1[i] = v;
		buffer2[i] = 239 - v;
	}

	xTaskCreatePinnedToCore([](void *lcd_p) {
		LCD::ILI9341 *lcd = (LCD::ILI9341 *)lcd_p;
		Graph *graph	   = new Graph(lcd->getBuffer(), 320, 240, 0, 0, 320, 240, 0x0000);
		graph->add(buffer1, 0xffff);
		graph->add(buffer2, LCD::GREEN);

		while (true) {
			vTaskDelay(100);

			lcd->clear(LCD::BLACK);

			graph->update(120);

			lcd->update();
		}
	}, "Graph", 4096, lcd, 1, NULL, 1);
}

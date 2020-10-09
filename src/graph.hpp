#pragma once

#include <sys/types.h>

#define MAX_DATA_BUFFER 16

class Graph {
    public:
	Graph(uint16_t* buffer, size_t screenWidth, size_t screenHeight, size_t x, size_t y, size_t canvasWidth, size_t canvasHeight, uint16_t backgroundColor);
	int add(uint8_t* data, uint16_t color);
	void clear();
	void update(size_t dataIndex);
	void update(size_t dataNum, size_t dataIndex);

    private:
	uint16_t* frameBuffer;
	size_t screenWidth, screenHeight, offsetX, offsetY, canvasWidth, canvasHeight;
	uint16_t backgroundColor;

	uint8_t* dataBuffer[MAX_DATA_BUFFER];
	uint16_t dataColor[MAX_DATA_BUFFER];
	size_t dataCount;
};

#include "graph.hpp"

#define TAG "Graph"
#define LOG_LOCAL_LEVEL 3
#include "log.h"

Graph::Graph(uint16_t* buffer, size_t screenWidth, size_t screenHeight, size_t x, size_t y, size_t canvasWidth, size_t canvasHeight, uint16_t backgroundColor) {
	this->frameBuffer  = buffer;
	this->screenWidth  = screenWidth;
	this->screenHeight = screenHeight;
	this->offsetX	    = x;
	this->offsetY	    = y;
	this->canvasWidth  = canvasWidth;
	this->canvasHeight = canvasHeight;

	this->backgroundColor = backgroundColor;
}

void Graph::clear() {
	for(int x=0; x<canvasWidth; x++) {
		for(int y=0; y<canvasHeight; y++) {
			frameBuffer[screenHeight * (y + offsetY) + offsetX + x] = backgroundColor;
		}
	}
}

int Graph::add(uint8_t* data, uint16_t color) {
	if (dataCount >= MAX_DATA_BUFFER) return -1;

	dataBuffer[dataCount] = data;
	dataColor[dataCount]  = color;

	dataCount += 1;
	return dataCount - 1;
}

void Graph::update(size_t dataIndex) {
	for (int i = 0; i < dataCount; i++) update(i, dataIndex);
}

void Graph::update(size_t dataNum, size_t dataIndex) {
	int x = 0;
	for (int i = dataIndex; i < canvasWidth; i++) {
		frameBuffer[screenWidth * (offsetY + (canvasHeight - 1 - dataBuffer[dataNum][i])) + offsetX + x] = dataColor[dataNum];
		x += 1;
	}
	for (int i = 0; i < dataIndex; i++) {
		frameBuffer[screenWidth * (offsetY + (canvasHeight - 1 - dataBuffer[dataNum][i])) + offsetX + x] = dataColor[dataNum];
		x += 1;
	}
}

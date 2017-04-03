#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "graphics.h"
#include "../gps/gps.h"
#include "../touchscreen/touchscreen.h"

void WriteAPixel(int x, int y, int Colour) {
    WAIT_FOR_GRAPHICS; // is graphics ready for new command
    GraphicsX1Reg = x; // write coords to x1, y1
    GraphicsY1Reg = y;
    GraphicsColourReg = Colour; // set pixel colour
    GraphicsCommandReg = PutAPixel; // give graphics "write pixel" command
}
/*********************************************************************************************
 * This function read a single pixel from the x,y coords specified and returns its colour
 * Note returned colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
 *********************************************************************************************/
int ReadAPixel(int x, int y) {
    WAIT_FOR_GRAPHICS; // is graphics ready for new command
    GraphicsX1Reg = x; // write coords to x1, y1
    GraphicsY1Reg = y;
    GraphicsCommandReg = GetAPixel; // give graphics a "get pixel" command
    WAIT_FOR_GRAPHICS
    ; // is graphics done reading pixel
    return (int) (GraphicsColourReg); // return the palette number (colour)
}

void ProgramPalette(int PaletteNumber, int RGB) {
    WAIT_FOR_GRAPHICS;
    GraphicsColourReg = PaletteNumber;
    GraphicsX1Reg = RGB >> 16; // program red value in ls.8 bit of X1 reg
    GraphicsY1Reg = RGB; // program green and blue into ls 16 bit of Y1 reg
    GraphicsCommandReg = ProgramPaletteColour; // issue command
}

void HLine(int x1, int y1, int length, int Colour) {
    WAIT_FOR_GRAPHICS;
    GraphicsX1Reg = x1; // write coords to x1, y1
    GraphicsY1Reg = y1;
    GraphicsX2Reg = x1 + length;
    GraphicsColourReg = Colour; // set pixel colour
    GraphicsCommandReg = DrawHLine; // give graphics "write pixel" command
}

void VLine(int x1, int y1, int length, int Colour) {
    WAIT_FOR_GRAPHICS;
    GraphicsX1Reg = x1; // write coords to x1, y1
    GraphicsY1Reg = y1;
    GraphicsY2Reg = y1 + length;
    GraphicsColourReg = Colour; // set pixel colour
    GraphicsCommandReg = DrawVLine; // give graphics "write pixel" command
}

void Line(int x1, int y1, int x2, int y2, int Colour) {
    WAIT_FOR_GRAPHICS;
    GraphicsX1Reg = x1;
    GraphicsY1Reg = y1;
    GraphicsX2Reg = x2;
    GraphicsY2Reg = y2;
    GraphicsColourReg = Colour;
    GraphicsCommandReg = DrawLine;
}

//x1, y1 are coordinates of top left corner, x2, y2 are corrdinates of bottom right corner
void Rectangle(int x1, int y1, int x2, int y2, int Colour) {
    WAIT_FOR_GRAPHICS;
    GraphicsX1Reg = x1;
    GraphicsY1Reg = y1;
    GraphicsX2Reg = x2;
    GraphicsY2Reg = y2;
    GraphicsColourReg = Colour;
    GraphicsCommandReg = DrawARectangle;
}

void Circle(int x1, int y1, int radius, int Colour) {
    WAIT_FOR_GRAPHICS;
    GraphicsX1Reg = x1;
    GraphicsY1Reg = y1;
    GraphicsY2Reg = radius;
    GraphicsColourReg = Colour;
    GraphicsCommandReg = DrawACircle;
}

void DLine(int x1, int y1, int x2, int y2, int Colour) {

    int x = x1;
    int y = y1;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int s1, s2;

    int subX = x2 - x1;
    int subY = y2 - y1;

    if (subX < 0)
        s1 = -1;
    else if (subX == 0)
        s1 = 0;
    else
        s1 = 1;

    if (subY < 0)
        s2 = -1;
    else if (subX == 0)
        s2 = 0;
    else
        s2 = 1;

    int i, temp, interchange = 0, error;

    if (dx == 0 && dy == 0)
        return;
    else {
        if (dy > dx) {
            temp = dx;
            dx = dy;
            dy = temp;
            interchange = 1;
        }
        error = (dy << 1) - dx; // error = (2 * dy) - dx
        for (i = 1; i <= dx; i++) {
            WriteAPixel(x, y, Colour);
            while (error >= 0) {
                if (interchange == 1)
                    x += s1;
                else
                    y += s2;

                error -= (dx << 1); // error = error � (dx * 2)
            }

            if (interchange == 1)
                y += s2;
            else
                x += s1;
            error += (dy << 1); // error = error + (dy * 2)
        }
    }
}

void DRectangle(int x1, int y1, int x2, int y2, int Colour) {
    HLine(x1, y1, x2 - x1, Colour);
    HLine(x1, y2, x2 - x1, Colour);
    VLine(x1, y1, y2 - y1, Colour);
    VLine(x2, y1, y2 - y1, Colour);
}

void DRectangleFill(int x1, int y1, int x2, int y2, int Colour) {
    for (; y1 <= y2; y1++) {
        HLine(x1, y1, x2 - x1, Colour);
    }
}

void ClearScreen(int Colour) {
    int j;
    for (j = 0; j <= YRES; j++) {
        HLine(0, j, XRES, Colour);
    }
}

void DCircle(int x1, int y1, int radius, int Colour) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        WriteAPixel(x1 + x, y1 + y, Colour);
        WriteAPixel(x1 + y, y1 + x, Colour);
        WriteAPixel(x1 - y, y1 + x, Colour);
        WriteAPixel(x1 - x, y1 + y, Colour);
        WriteAPixel(x1 - x, y1 - y, Colour);
        WriteAPixel(x1 - y, y1 - x, Colour);
        WriteAPixel(x1 + y, y1 - x, Colour);
        WriteAPixel(x1 + x, y1 - y, Colour);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }

}

void DFillCircle(int xo, int yo, int radius, int Colour) {
    int y, x;
    for (y = -radius; y <= radius; y++)
        for (x = -radius; x <= radius; x++)
            if (x * x + y * y <= radius * radius)
                WriteAPixel(xo + x, yo + y, Colour);
}

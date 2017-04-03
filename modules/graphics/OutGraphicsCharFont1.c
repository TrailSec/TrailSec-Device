#include "graphics.h"
#include "OutGraphicsCharFont.h"
#include "../touchscreen/touchscreen.h"

// Constants ideally put this in a header file and #include it
#define XRES 800
#define YRES 480

// declaration of the external Array, ideally put this in a header file and #include it
extern const unsigned char Font5x7[][7];

/*************************************************************************************************
** This function draws a single ASCII character at the coord and colour specified
** it optionally ERASES the background colour pixels to the background colour
** This means you can use this to erase characters
**
** e.g. writing a space character with Erase set to true will set all pixels in the
** character to the background colour
**
*************************************************************************************************/
void
OutGraphicsCharFont1 (int x, int y, int fontcolour, int backgroundcolour, int c, int Erase)
{
  // using register variables (as opposed to stack based ones) may make execution faster
  // depends on compiler and CPU
	register int row, column, theX = x, theY = y;
	register int pixels;
	register char theColour = fontcolour;
	register int BitMask, theC = c;

  // if x,y coord off edge of screen don't bother
  if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))
    return;

  // if printable character subtract hex 20
	if(((short)(theC) >= (short)(' ')) && ((short)(theC) <= (short)('~'))) {
		theC = theC - 0x20;

		for(row = 0; (char)(row) < (char)(7); row ++)	{
			// get the bit pattern for row 0 of the character from the software font
			pixels = Font5x7[theC][row];
			BitMask = 16;

			for(column = 0; (char)(column) < (char)(5); column ++)	{
        // if a pixel in the character display it
        if((pixels & BitMask)) {
          WriteAPixel(theX+column, theY+row, theColour);
        }
        else if(Erase == 1) {
					// if pixel is part of background (not part of character)
					// erase the background to value of variable BackGroundColour
					WriteAPixel(theX+column, theY+row, backgroundcolour);
        }
				BitMask = BitMask >> 1;
      }
    }
	}
}

void
PrintStringFont1 (char * string, int size, int x, int y, int fontcolour, int backgroundcolour, int Erase)
{
	int index;
	for(index = 0; index < size; index++){
		OutGraphicsCharFont1(x, y + index * 7, fontcolour, backgroundcolour, string[index], Erase);
	}
}

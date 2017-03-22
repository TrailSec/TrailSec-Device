#include "OutGraphicsCharFont.h"
#include "touchscreen.h"

// Constants ideally put this in a header file and #include it
#define XRES 800
#define YRES 480
#define FONT2_XPIXELS	10				// width of Font2 characters in pixels (no spacing)
#define FONT2_YPIXELS	14				// height of Font2 characters in pixels (no spacing)

// declaration of the external Array, ideally put this in a header file and #include it
extern const unsigned short int Font10x14[][14];

/******************************************************************************************************************************
** This function draws a single ASCII character at the coord specified using the colour specified
** OutGraphicsCharFont2(100,100, RED, 'A', TRUE, FALSE, 1, 1);	// display upper case 'A' in RED at coords 100,100, erase background
** no scroll, scale x,y= 1,1
**
******************************************************************************************************************************/
void
OutGraphicsCharFont2 (int x, int y, int colour, int backgroundcolour, int c, int Erase)
{
  register int row, column, theX = x, theY = y;
  register int pixels;
	register char theColour = colour;
	register int BitMask, theCharacter = c;
  register int theRow, theColumn;

  // if start off edge of screen don't bother
  if (((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))
    return;

  // if printable character
	if (((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {

    // subtract hex 20 to get index of first printable character (the space character)
		theCharacter -= 0x20;
		theRow = FONT2_YPIXELS;
		theColumn = FONT2_XPIXELS;

		for(row = 0; row < theRow; row ++)	{
      // get the pixels for row 0 of the character to be displayed
      pixels = Font10x14[theCharacter][row];
      // set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			BitMask = 512;

      for(column = 0; column < theColumn;) {
        // if valid pixel, then write it
				if((pixels & BitMask)) {
					WriteAPixel(theX+column, theY+row, theColour);
        }
        // if not a valid pixel, do we erase or leave it along (no erase)
				else if(Erase == 1) {
					WriteAPixel(theX+column, theY+row, backgroundcolour);
				}

				column++;
				BitMask = BitMask >> 1;
			}
		}
	}
}

void
PrintStringFont2 (char * string, int size, int x, int y, int fontcolour, int backgroundcolour, int Erase)
{
	int index;
	for (index = 0; index < size; index++) {
		OutGraphicsCharFont2(x + index * 11, y, fontcolour, backgroundcolour, string[index], Erase);
	}
}

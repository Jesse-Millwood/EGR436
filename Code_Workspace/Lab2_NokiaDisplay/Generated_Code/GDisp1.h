/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : GDisp1.h
**     Project     : Lab2_NokiaDisplay
**     Processor   : MK64FN1M0VLL12
**     Component   : GDisplay
**     Version     : Component 01.190, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-01-12, 20:49, # CodeGen: 6
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         PutPixel              - void GDisp1_PutPixel(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelColor...
**         SetPixel              - void GDisp1_SetPixel(GDisp1_PixelDim x, GDisp1_PixelDim y);
**         ClrPixel              - void GDisp1_ClrPixel(GDisp1_PixelDim x, GDisp1_PixelDim y);
**         Clear                 - void GDisp1_Clear(void);
**         DrawBox               - void GDisp1_DrawBox(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim...
**         DrawFilledBox         - void GDisp1_DrawFilledBox(GDisp1_PixelDim x, GDisp1_PixelDim y,...
**         DrawHLine             - void GDisp1_DrawHLine(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim...
**         DrawVLine             - void GDisp1_DrawVLine(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim...
**         DrawLine              - void GDisp1_DrawLine(GDisp1_PixelDim xstart, GDisp1_PixelDim ystart,...
**         DrawCircle            - void GDisp1_DrawCircle(GDisp1_PixelDim x0, GDisp1_PixelDim y0,...
**         DrawFilledCircle      - void GDisp1_DrawFilledCircle(GDisp1_PixelDim x0, GDisp1_PixelDim y0,...
**         DrawBarChart          - void GDisp1_DrawBarChart(GDisp1_PixelDim x, GDisp1_PixelDim y,...
**         DrawMonoBitmap        - void GDisp1_DrawMonoBitmap(GDisp1_PixelDim x, GDisp1_PixelDim y, PIMAGE...
**         DrawColorBitmap       - void GDisp1_DrawColorBitmap(GDisp1_PixelDim x, GDisp1_PixelDim y, PIMAGE image);
**         Draw65kBitmap         - void GDisp1_Draw65kBitmap(GDisp1_PixelDim x1, GDisp1_PixelDim y1,...
**         Draw256BitmapLow      - void GDisp1_Draw256BitmapLow(GDisp1_PixelDim x1, GDisp1_PixelDim y1,...
**         Draw256BitmapHigh     - void GDisp1_Draw256BitmapHigh(GDisp1_PixelDim x1, GDisp1_PixelDim y1,...
**         UpdateFull            - void GDisp1_UpdateFull(void);
**         UpdateRegion          - void GDisp1_UpdateRegion(GDisp1_PixelDim x, GDisp1_PixelDim y,...
**         GetDisplayOrientation - GDisp1_DisplayOrientation GDisp1_GetDisplayOrientation(void);
**         SetDisplayOrientation - void GDisp1_SetDisplayOrientation(GDisp1_DisplayOrientation newOrientation);
**         GetWidth              - GDisp1_PixelDim GDisp1_GetWidth(void);
**         GetHeight             - GDisp1_PixelDim GDisp1_GetHeight(void);
**         GetLongerSide         - GDisp1_PixelDim GDisp1_GetLongerSide(void);
**         GetShorterSide        - GDisp1_PixelDim GDisp1_GetShorterSide(void);
**         GetDisplay            - void GDisp1_GetDisplay(void);
**         GiveDisplay           - void GDisp1_GiveDisplay(void);
**         Init                  - void GDisp1_Init(void);
**
**     License : Open Source (LGPL)
**     Copyright : (c) Copyright Erich Styger, 2013, all rights reserved.
**     http://www.mcuoneclipse.com
**     This an open source software in the form of a Processor Expert Embedded Component.
**     This is a free software and is opened for education, research and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file GDisp1.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup GDisp1_module GDisp1 module documentation
**  @{
*/         


#ifndef __GDisp1_H
#define __GDisp1_H

/* MODULE GDisp1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "PDC1.h"

#include "Cpu.h"


/* this type is declared in PE_Types.h for non-LDD processors, need to declare it locally otherwise */
typedef struct {                       /* Image */
  word width;                          /* Image width  */
  word height;                         /* Image height */
  const byte * pixmap;                 /* Image pixel bitmap */
  word size;                           /* Image size   */
  const char_t * name;                 /* Image name   */
} TIMAGE;
typedef TIMAGE* PIMAGE ;               /* Pointer to image */

#define GDisp1_RGB565(R,G,B)     ((GDisp1_PixelColor)((((R)&0x1f)<<11)+(((G)&0x3f)<<5)+((B)&0x1f))) /* convert RGB into 565 color format */

#define GDisp1_COLOR_PIXEL_SET          PDC1_COLOR_PIXEL_SET       /* value for a pixel set */
#define GDisp1_COLOR_PIXEL_CLR          PDC1_COLOR_PIXEL_CLR       /* value for a pixel cleared */
#define GDisp1_COLOR_BLACK              PDC1_COLOR_BLACK           /* black color */
#define GDisp1_COLOR_WHITE              PDC1_COLOR_WHITE           /* white color */
#define GDisp1_COLOR_RED                PDC1_COLOR_RED             /* red color */
#define GDisp1_COLOR_BRIGHT_RED         PDC1_COLOR_BRIGHT_RED      /* bright red color */
#define GDisp1_COLOR_DARK_RED           PDC1_COLOR_DARK_RED        /* dark red color */
#define GDisp1_COLOR_GREEN              PDC1_COLOR_GREEN           /* green color */
#define GDisp1_COLOR_DARK_GREEN         PDC1_COLOR_DARK_GREEN      /* dark green color */
#define GDisp1_COLOR_BRIGHT_GREEN       PDC1_COLOR_BRIGHT_GREEN    /* bright green color */
#define GDisp1_COLOR_BLUE               PDC1_COLOR_BLUE            /* blue color */
#define GDisp1_COLOR_BRIGHT_BLUE        PDC1_COLOR_BRIGHT_BLUE     /* bright blue color */
#define GDisp1_COLOR_DARK_BLUE          PDC1_COLOR_DARK_BLUE       /* dark blue color */
#define GDisp1_COLOR_YELLOW             PDC1_COLOR_YELLOW          /* yellow color */
#define GDisp1_COLOR_BRIGHT_YELLOW      PDC1_COLOR_BRIGHT_YELLOW   /* bright yellow color */
#define GDisp1_COLOR_ORANGE             PDC1_COLOR_ORANGE          /* orange color */
#define GDisp1_COLOR_GREY               PDC1_COLOR_GREY            /* grey color */
#define GDisp1_COLOR_BRIGHT_GREY        PDC1_COLOR_BRIGHT_GREY     /* bright grey color */

typedef PDC1_PixelDim   GDisp1_PixelDim; /* Display specific type for a pixel coordinate. */
typedef PDC1_PixelColor GDisp1_PixelColor; /* Display specific color type. */
typedef PDC1_PixelCount GDisp1_PixelCount; /* Type able to hold the number of pixels for the display. */

/* wrappers for the low level display orientation enumeration and type */
typedef PDC1_DisplayOrientation GDisp1_DisplayOrientation;
#define GDisp1_ORIENTATION_PORTRAIT     PDC1_ORIENTATION_PORTRAIT
#define GDisp1_ORIENTATION_PORTRAIT180  PDC1_ORIENTATION_PORTRAIT180
#define GDisp1_ORIENTATION_LANDSCAPE    PDC1_ORIENTATION_LANDSCAPE
#define GDisp1_ORIENTATION_LANDSCAPE180 PDC1_ORIENTATION_LANDSCAPE180


/* Landscape */

#define GDisp1_BUF_BYTE(x,y)  /* how to access a byte in the display buf[][] */ \
      PDC1_DisplayBuf[(y)/8][x]

#define GDisp1_BUF_BYTE_PIXEL_BIT_NO(x,y) /* pixel bit number inside display buffer byte (0 is LSB, 7 MSB) */ \
      ((byte)((y)%8))

#define GDisp1_BUF_BYTE_PIXEL_MASK(x,y)  /* pixel mask for an individual bit inside a display buffer byte */ \
  (1<<GDisp1_BUF_BYTE_PIXEL_BIT_NO(x,y))

#define GDisp1_BUF_BYTE_GET_PIXEL(x,y)  /* extract a pixel */ \
  ((GDisp1_BUF_BYTE(x,y)&GDisp1_BUF_BYTE_PIXEL_MASK(x,y))>>GDisp1_BUF_BYTE_PIXEL_BIT_NO(x,y))

void GDisp1_Clear(void);
/*
** ===================================================================
**     Method      :  GDisp1_Clear (component GDisplay)
**     Description :
**         Clears the display buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_SetPixel(GDisp1_PixelDim x, GDisp1_PixelDim y);
/*
** ===================================================================
**     Method      :  GDisp1_SetPixel (component GDisplay)
**     Description :
**         Sets a pixel in the display buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - Pixel x position
**         y               - Pixel y position
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_ClrPixel(GDisp1_PixelDim x, GDisp1_PixelDim y);
/*
** ===================================================================
**     Method      :  GDisp1_ClrPixel (component GDisplay)
**     Description :
**         Clears a single pixel in the display.
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - Pixel x position.
**         y               - Pixel y position.
**     Returns     : Nothing
** ===================================================================
*/

#define GDisp1_UpdateFull()   PDC1_UpdateFull()
/*
** ===================================================================
**     Method      :  GDisp1_UpdateFull (component GDisplay)
**     Description :
**         Updates the image on the display. This is needed in case the
**         display requires a periodic refresh. For display using
**         windowing, this function may be implemented as dummy stub,
**         as the display content already is written.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_DrawFilledBox(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim width, GDisp1_PixelDim height, GDisp1_PixelColor color);
/*
** ===================================================================
**     Method      :  GDisp1_DrawFilledBox (component GDisplay)
**     Description :
**         Draws a rectangle box (filled)
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x left upper coordinate
**         y               - y left upper coordinate
**         width           - Width in pixels
**         height          - Height in pixels
**         color           - color to be used to fill the box.
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_PutPixel(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelColor color);
/*
** ===================================================================
**     Method      :  GDisp1_PutPixel (component GDisplay)
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x coordinate
**         y               - y coordinate
**         color           - color to be used for the pixel
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_DrawBox(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim width, GDisp1_PixelDim height, GDisp1_PixelDim lineWidth, GDisp1_PixelColor color);
/*
** ===================================================================
**     Method      :  GDisp1_DrawBox (component GDisplay)
**     Description :
**         Draws a rectangle line box
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x left upper coordinate
**         y               - y left upper coordinate
**         width           - width in pixels
**         height          - height in pixels
**         lineWidth       - width of the line
**         color           - color for the box
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_DrawMonoBitmap(GDisp1_PixelDim x, GDisp1_PixelDim y, PIMAGE image, GDisp1_PixelColor pixelColor, GDisp1_PixelColor backgroundColor);
/*
** ===================================================================
**     Method      :  GDisp1_DrawMonoBitmap (component GDisplay)
**     Description :
**         Draws a B/W bitmap.
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x position of left upper corner
**         y               - y position of left upper corner
**         image           - Pointer to image structure and
**                           information.
**         pixelColor      - Color to be used for pixels
**                           (pixel set)
**         backgroundColor - Color to be used
**                           for background (pixel not set)
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_DrawHLine(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim length, GDisp1_PixelColor color);
/*
** ===================================================================
**     Method      :  GDisp1_DrawHLine (component GDisplay)
**     Description :
**         Draws a horizontal line
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x left upper coordinate
**         y               - y left upper coordinate
**         length          - Length of line in pixels
**         color           - color to be used to fill the box.
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_DrawVLine(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim length, GDisp1_PixelColor color);
/*
** ===================================================================
**     Method      :  GDisp1_DrawVLine (component GDisplay)
**     Description :
**         Draws a vertical line
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x left upper coordinate
**         y               - y left upper coordinate
**         length          - Length of line in pixels
**         color           - color to be used to fill the box.
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_DrawBarChart(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim width, GDisp1_PixelDim height, byte *data, byte nofData, GDisp1_PixelColor barColor, byte borderWidth, GDisp1_PixelColor borderColor, byte borderSpace);
/*
** ===================================================================
**     Method      :  GDisp1_DrawBarChart (component GDisplay)
**     Description :
**         Draws a series of bars for a chart
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - upper left corner x coordinate
**         y               - upper left corner y coordinate
**         width           - Chart box width
**         height          - Chart box height
**       * data            - Pointer to data (series of % values
**                           from 0...100%)
**         nofData         - number of data bytes
**         barColor        - Color to be used for the bars.
**         borderWidth     - width of a border to be
**                           draw. Pass zero if there shall be no border.
**         borderColor     - Color to be used for the
**                           border (if borderWidth is not zero)
**         borderSpace     - Space to be used in pixels
**                           between border and bars.
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_DrawColorBitmap(GDisp1_PixelDim x, GDisp1_PixelDim y, PIMAGE image);
/*
** ===================================================================
**     Method      :  GDisp1_DrawColorBitmap (component GDisplay)
**     Description :
**         Draws a color bitmap. Pixel data is in 3-3-2 RGB format.
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x position of left upper corner
**         y               - y position of left upper corner
**         image           - Pointer to image structure and
**                           information.
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_DrawLine(GDisp1_PixelDim xstart, GDisp1_PixelDim ystart, GDisp1_PixelDim xend, GDisp1_PixelDim yend, GDisp1_PixelColor color);
/*
** ===================================================================
**     Method      :  GDisp1_DrawLine (component GDisplay)
**     Description :
**         Draws a line using the Bresenham method
**     Parameters  :
**         NAME            - DESCRIPTION
**         xstart          - x start coordinate
**         ystart          - y start coordinate
**         xend            - x end coordinate
**         yend            - y end coordinate
**         color           - color to be used for the line
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_DrawCircle(GDisp1_PixelDim x0, GDisp1_PixelDim y0, GDisp1_PixelDim radius, GDisp1_PixelColor color);
/*
** ===================================================================
**     Method      :  GDisp1_DrawCircle (component GDisplay)
**     Description :
**         Draws a circle using the Bresenham method
**     Parameters  :
**         NAME            - DESCRIPTION
**         x0              - x start coordinate
**         y0              - y start coordinate
**         radius          - Radius of the circle
**         color           - color to be used for the line
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_Draw65kBitmap(GDisp1_PixelDim x1, GDisp1_PixelDim y1, GDisp1_PixelDim x2, GDisp1_PixelDim y2, word *bmp, bool compressed);
/*
** ===================================================================
**     Method      :  GDisp1_Draw65kBitmap (component GDisplay)
**     Description :
**         Draws a 65k color bitmap (compressed or uncompressed)
**     Parameters  :
**         NAME            - DESCRIPTION
**         x1              - left upper starting corner
**         y1              - left upper starting corner
**         x2              - right lower corner
**         y2              - right lower corner
**       * bmp             - Pointer to bitmap
**         compressed      - 
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_Draw256BitmapLow(GDisp1_PixelDim x1, GDisp1_PixelDim y1, GDisp1_PixelDim x2, GDisp1_PixelDim y2, byte *bmp, bool compressed);
/*
** ===================================================================
**     Method      :  GDisp1_Draw256BitmapLow (component GDisplay)
**     Description :
**         Draws a 256 color bitmap (compressed or uncompressed)
**     Parameters  :
**         NAME            - DESCRIPTION
**         x1              - left upper starting corner
**         y1              - left upper starting corner
**         x2              - right lower corner
**         y2              - right lower corner
**       * bmp             - Pointer to bitmap
**         compressed      - 
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_Draw256BitmapHigh(GDisp1_PixelDim x1, GDisp1_PixelDim y1, GDisp1_PixelDim x2, GDisp1_PixelDim y2, byte *bmp, GDisp1_PixelColor *ColorTable, bool compressed);
/*
** ===================================================================
**     Method      :  GDisp1_Draw256BitmapHigh (component GDisplay)
**     Description :
**         Draws a 256 color bitmap (compressed or uncompressed) with a
**         color table.
**     Parameters  :
**         NAME            - DESCRIPTION
**         x1              - left upper starting corner
**         y1              - left upper starting corner
**         x2              - right lower corner
**         y2              - right lower corner
**       * bmp             - Pointer to bitmap
**       * ColorTable      - Pointer to array of colors
**                           (color table)
**         compressed      - 
**     Returns     : Nothing
** ===================================================================
*/

#define GDisp1_UpdateRegion(x,y,w,h)   PDC1_UpdateRegion(x,y,w,h)

/*
** ===================================================================
**     Method      :  GDisp1_UpdateRegion (component GDisplay)
**     Description :
**         Update a region of the display.
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x coordinate
**         y               - y coordinate
**         w               - Width of the update region
**         h               - height of the update region
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_DrawFilledCircle(GDisp1_PixelDim x0, GDisp1_PixelDim y0, GDisp1_PixelDim radius, GDisp1_PixelColor color);
/*
** ===================================================================
**     Method      :  GDisp1_DrawFilledCircle (component GDisplay)
**     Description :
**         Draws a circle using the Bresenham method
**     Parameters  :
**         NAME            - DESCRIPTION
**         x0              - x start coordinate
**         y0              - y start coordinate
**         radius          - Radius of the circle
**         color           - fill color to be used
**     Returns     : Nothing
** ===================================================================
*/

#define GDisp1_GetDisplayOrientation() GDisp1_ORIENTATION_LANDSCAPE
/*
** ===================================================================
**     Method      :  GDisp1_GetDisplayOrientation (component GDisplay)
**     Description :
**         Returns the current display orientation
**     Parameters  : None
**     Returns     :
**         ---             - current display orientation
** ===================================================================
*/

#define GDisp1_SetDisplayOrientation PDC1_SetDisplayOrientation
/*
** ===================================================================
**     Method      :  GDisp1_SetDisplayOrientation (component GDisplay)
**     Description :
**         Sets the display orientation. If you enable this method,
**         then the orientation of the display can be changed at
**         runtime. However, this requires additional resources.
**     Parameters  :
**         NAME            - DESCRIPTION
**         newOrientation  - new orientation to
**                           be used
**     Returns     : Nothing
** ===================================================================
*/

#define GDisp1_GetWidth PDC1_GetLongerSide
/*
** ===================================================================
**     Method      :  GDisp1_GetWidth (component GDisplay)
**     Description :
**         Returns the width of the display in pixels (in x direction)
**     Parameters  : None
**     Returns     :
**         ---             - pixel count
** ===================================================================
*/

#define GDisp1_GetHeight PDC1_GetShorterSide
/*
** ===================================================================
**     Method      :  GDisp1_GetHeight (component GDisplay)
**     Description :
**         Returns the height of the display in pixels (in y direction)
**     Parameters  : None
**     Returns     :
**         ---             - pixel count
** ===================================================================
*/

#define GDisp1_GetLongerSide PDC1_GetLongerSide
/*
** ===================================================================
**     Method      :  GDisp1_GetLongerSide (component GDisplay)
**     Description :
**         Returns the size of the longer side of the display
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

#define GDisp1_GetShorterSide PDC1_GetShorterSide
/*
** ===================================================================
**     Method      :  GDisp1_GetShorterSide (component GDisplay)
**     Description :
**         Returns the size of the shorter side of the display
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

void GDisp1_GetDisplay(void);
/*
** ===================================================================
**     Method      :  GDisp1_GetDisplay (component GDisplay)
**     Description :
**         Method used to reserve the display (for mutual exclusive
**         access)
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_GiveDisplay(void);
/*
** ===================================================================
**     Method      :  GDisp1_GiveDisplay (component GDisplay)
**     Description :
**         Returns the display after having it reserved with
**         GetDisplay()
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_Init(void);
/*
** ===================================================================
**     Method      :  GDisp1_Init (component GDisplay)
**     Description :
**         
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END GDisp1. */

#endif
/* ifndef __GDisp1_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.11]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

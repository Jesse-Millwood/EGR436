/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : GDisp1.c
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
** @file GDisp1.c
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup GDisp1_module GDisp1 module documentation
**  @{
*/         

/* MODULE GDisp1. */

#include "GDisp1.h"

static const word c332to565[256] = { /* converts a 3-3-2 RBG value into a 5-6-5 RGB value */
 0x0000, 0x000A, 0x0014, 0xF81E, 0x0120, 0x012A, 0x0134, 0xF93E,
 0x0240, 0x024A, 0x0254, 0xFA5E, 0x0360, 0x036A, 0x0374, 0xFB7E,
 0x0480, 0x048A, 0x0494, 0xFC9E, 0x05A0, 0x05AA, 0x05B4, 0xFDBE,
 0x06C0, 0x06CA, 0x06D4, 0xFEDE, 0x07E0, 0x07EA, 0x07F4, 0xFFFE,
 0x2000, 0x200A, 0x2014, 0xF81E, 0x2120, 0x212A, 0x2134, 0xF93E,
 0x2240, 0x224A, 0x2254, 0xFA5E, 0x2360, 0x236A, 0x2374, 0xFB7E,
 0x2480, 0x248A, 0x2494, 0xFC9E, 0x25A0, 0x25AA, 0x25B4, 0xFDBE,
 0x26C0, 0x26CA, 0x26D4, 0xFEDE, 0x27E0, 0x27EA, 0x27F4, 0xFFFE,
 0x4000, 0x400A, 0x4014, 0xF81E, 0x4120, 0x412A, 0x4134, 0xF93E,
 0x4240, 0x424A, 0x4254, 0xFA5E, 0x4360, 0x436A, 0x4374, 0xFB7E,
 0x4480, 0x448A, 0x4494, 0xFC9E, 0x45A0, 0x45AA, 0x45B4, 0xFDBE,
 0x46C0, 0x46CA, 0x46D4, 0xFEDE, 0x47E0, 0x47EA, 0x47F4, 0xFFFE,
 0x6000, 0x600A, 0x6014, 0xF81E, 0x6120, 0x612A, 0x6134, 0xF93E,
 0x6240, 0x624A, 0x6254, 0xFA5E, 0x6360, 0x636A, 0x6374, 0xFB7E,
 0x6480, 0x648A, 0x6494, 0xFC9E, 0x65A0, 0x65AA, 0x65B4, 0xFDBE,
 0x66C0, 0x66CA, 0x66D4, 0xFEDE, 0x67E0, 0x67EA, 0x67F4, 0xFFFE,
 0x8000, 0x800A, 0x8014, 0xF81E, 0x8120, 0x812A, 0x8134, 0xF93E,
 0x8240, 0x824A, 0x8254, 0xFA5E, 0x8360, 0x836A, 0x8374, 0xFB7E,
 0x8480, 0x848A, 0x8494, 0xFC9E, 0x85A0, 0x85AA, 0x85B4, 0xFDBE,
 0x86C0, 0x86CA, 0x86D4, 0xFEDE, 0x87E0, 0x87EA, 0x87F4, 0xFFFE,
 0xA000, 0xA00A, 0xA014, 0xF81E, 0xA120, 0xA12A, 0xA134, 0xF93E,
 0xA240, 0xA24A, 0xA254, 0xFA5E, 0xA360, 0xA36A, 0xA374, 0xFB7E,
 0xA480, 0xA48A, 0xA494, 0xFC9E, 0xA5A0, 0xA5AA, 0xA5B4, 0xFDBE,
 0xA6C0, 0xA6CA, 0xA6D4, 0xFEDE, 0xA7E0, 0xA7EA, 0xA7F4, 0xFFFE,
 0xC000, 0xC00A, 0xC014, 0xF81E, 0xC120, 0xC12A, 0xC134, 0xF93E,
 0xC240, 0xC24A, 0xC254, 0xFA5E, 0xC360, 0xC36A, 0xC374, 0xFB7E,
 0xC480, 0xC48A, 0xC494, 0xFC9E, 0xC5A0, 0xC5AA, 0xC5B4, 0xFDBE,
 0xC6C0, 0xC6CA, 0xC6D4, 0xFEDE, 0xC7E0, 0xC7EA, 0xC7F4, 0xFFFE,
 0xF800, 0xF80A, 0xF814, 0xF81E, 0xF920, 0xF92A, 0xF934, 0xF93E,
 0xFA40, 0xFA4A, 0xFA54, 0xFA5E, 0xFB60, 0xFB6A, 0xFB74, 0xFB7E,
 0xFC80, 0xFC8A, 0xFC94, 0xFC9E, 0xFDA0, 0xFDAA, 0xFDB4, 0xFDBE,
 0xFEC0, 0xFECA, 0xFED4, 0xFEDE, 0xFFE0, 0xFFEA, 0xFFF4, 0xFFFE,
};
/*
** ===================================================================
**     Method      :  GDisp1_Clear (component GDisplay)
**     Description :
**         Clears the display buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void GDisp1_Clear(void)
{
  byte *p = &PDC1_DisplayBuf[0][0]; /* first element in display buffer */

  while (p<((byte*)PDC1_DisplayBuf)+sizeof(PDC1_DisplayBuf)) {
    *p++ = (byte)(  (GDisp1_COLOR_WHITE<<7)
                  | (GDisp1_COLOR_WHITE<<6)
                  | (GDisp1_COLOR_WHITE<<5)
                  | (GDisp1_COLOR_WHITE<<4)
                  | (GDisp1_COLOR_WHITE<<3)
                  | (GDisp1_COLOR_WHITE<<2)
                  | (GDisp1_COLOR_WHITE<<1)
                  |  GDisp1_COLOR_WHITE
                 );
  }
}

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
void GDisp1_SetPixel(GDisp1_PixelDim x, GDisp1_PixelDim y)
{
  if (x>=GDisp1_GetWidth() || y>=GDisp1_GetHeight()) { /* values out of range */
    return;
  }
  GDisp1_BUF_BYTE(x,y) |= GDisp1_BUF_BYTE_PIXEL_MASK(x,y);
}

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
void GDisp1_ClrPixel(GDisp1_PixelDim x, GDisp1_PixelDim y)
{
  if (x>=GDisp1_GetWidth() || y>=GDisp1_GetHeight()) { /* values out of range */
    return;
  }
  GDisp1_BUF_BYTE(x,y) &= ~GDisp1_BUF_BYTE_PIXEL_MASK(x,y);
}

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
/* method is implemented as macro in header file
void GDisp1_UpdateFull(void)
{
}
*/

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
void GDisp1_DrawFilledBox(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim width, GDisp1_PixelDim height, GDisp1_PixelColor color)
{
  GDisp1_PixelDim x0, xe, y0, ye;
  GDisp1_PixelDim d_width = GDisp1_GetWidth();
  GDisp1_PixelDim d_height = GDisp1_GetHeight();

  if (   width==0 || height==0
      || x>=d_width || y>=d_height
     ) {
    return; /* nothing to do */
  }
  if (x+width>d_width) { /* value out of range */
    if (x>=d_width) {
      return;                          /* completely outside of display */
    } else {
      width = (GDisp1_PixelDim)(d_width-x);
    }
  }
  if (y+height>d_height) { /* value out of range */
    if (y>=d_height) {
      return;                          /* completely outside of display */
    } else {
      height = (GDisp1_PixelDim)(d_height-y);
    }
  }
  y0 = y; ye = (GDisp1_PixelDim)(y0+height-1);
  for(;;) { /* breaks */
    x0 = x; xe = (GDisp1_PixelDim)(x0+width-1);
    for(;;) { /* process line, breaks */
      GDisp1_PutPixel(x0, y0, color);
      if (x0==xe) {
        break; /* reached end of line */
      }
      x0++;
    } /* for */
    if (y0==ye) break; /* reached end */
    y0++;
  } /* for */
}

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
#ifdef __HC08__
  #pragma MESSAGE DISABLE C4001 /* condition always FALSE */
#endif
void GDisp1_PutPixel(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelColor color)
{
  if (x>=GDisp1_GetWidth() || y>=GDisp1_GetHeight()) { /* values out of range */
    return;
  }
  if (   (color==GDisp1_COLOR_BLACK && GDisp1_COLOR_BLACK==GDisp1_COLOR_PIXEL_SET)
      || (color==GDisp1_COLOR_WHITE && GDisp1_COLOR_WHITE==GDisp1_COLOR_PIXEL_SET)
     )
  {
    GDisp1_SetPixel(x,y);
  } else {
    GDisp1_ClrPixel(x,y);
  }
}
#ifdef __HC08__
  #pragma MESSAGE DEFAULT C4001 /* condition always FALSE */
#endif

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
void GDisp1_DrawBox(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim width, GDisp1_PixelDim height, GDisp1_PixelDim lineWidth, GDisp1_PixelColor color)
{
  /* top line: */
  GDisp1_DrawFilledBox(x, y, width, lineWidth, color);
  /* left line: */
  GDisp1_DrawFilledBox(x, (GDisp1_PixelDim)(y+lineWidth), lineWidth, (GDisp1_PixelDim)(height-(2*lineWidth)), color);
  /* right line: */
  GDisp1_DrawFilledBox((GDisp1_PixelDim)(x+width-lineWidth), (GDisp1_PixelDim)(y+lineWidth), lineWidth, (GDisp1_PixelDim)(height-(2*lineWidth)), color);
  /* bottom line: */
  GDisp1_DrawFilledBox(x, (GDisp1_PixelDim)(y+height-lineWidth), width, lineWidth, color);
}

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
void GDisp1_DrawMonoBitmap(GDisp1_PixelDim x, GDisp1_PixelDim y, PIMAGE image, GDisp1_PixelColor pixelColor, GDisp1_PixelColor backgroundColor)
{
  GDisp1_PixelDim x0, y0, xe, ye;
  GDisp1_PixelColor pixel;
  byte i;
  const byte *data;

  data = image->pixmap;
  y0 = y;
  ye = (GDisp1_PixelDim)(y+image->height-1);
  xe = (GDisp1_PixelDim)(x+image->width-1);
  for(;;) {
    i=7;
    x0 = x;
    for(;;) {
      pixel = (GDisp1_PixelColor)(((*data)&(1<<i))>>i); /* extract pixel out of bitstream */
      GDisp1_PutPixel(x0, y0, (GDisp1_PixelColor)(pixel==1?pixelColor:backgroundColor));
      if (i==0 && x0!=xe) { /* next byte inside the row */
        data++;
        i = 7;
      } else {
        i--;
      }
      if (x0==xe) { /* reached end of line, next row */
        data++; /* next data byte */
        break;
      }
      x0++;
    } /* for */
    if (y0==ye) break; /* reached end */
    y0++;
  } /* for */
}

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
void GDisp1_DrawColorBitmap(GDisp1_PixelDim x, GDisp1_PixelDim y, PIMAGE image)
{
  GDisp1_PixelDim x0, y0, xe, ye;
  GDisp1_PixelColor pixel;
  const byte *data;

  data = image->pixmap;
  y0 = y;
  ye = (GDisp1_PixelDim)(y+image->height-1);
  xe = (GDisp1_PixelDim)(x+image->width-1);
  for(;;) {
    x0 = x;
    for(;;) {
      pixel = (GDisp1_PixelColor)c332to565[*data]; /* extract pixel out of bitstream and convert it to our color mode*/
      GDisp1_PutPixel(x0, y0, pixel);
      data++;
      if (x0==xe) { /* reached end of line, next row */
        break;
      }
      x0++;
    } /* for */
    if (y0==ye) break; /* reached end */
    y0++;
  } /* for */
}

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
void GDisp1_DrawHLine(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim length, GDisp1_PixelColor color)
{
  GDisp1_DrawFilledBox(x, y, length, 1, color);
}

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
void GDisp1_DrawVLine(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim length, GDisp1_PixelColor color)
{
  GDisp1_DrawFilledBox(x, y, 1, length, color);
}

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
void GDisp1_DrawBarChart(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim width, GDisp1_PixelDim height, byte *data, byte nofData, GDisp1_PixelColor barColor, byte borderWidth, GDisp1_PixelColor borderColor, byte borderSpace)
{
  byte i;
  GDisp1_PixelDim barHeight; /* for calculation of each bar height */
  GDisp1_PixelDim barWidth; /* bar width, based on even distribution of the bars */

  if (borderWidth > 0) { /* border */
    GDisp1_DrawBox(x, y, width, height, borderWidth, borderColor);
  }
  /* reduce drawing area because of border */
  x += borderWidth+borderSpace;
  y += borderWidth+borderSpace;
  width -= 2*(borderWidth+borderSpace);
  height -= 2*(borderWidth+borderSpace);

  /* calculat bar width based on number of bars so we fill out our drawing area */
  barWidth = (GDisp1_PixelDim)((width-(nofData+1)*borderSpace)/nofData);

  /* draw some bars */
  for(i=0; i<nofData; i++) {
    barHeight = (GDisp1_PixelDim)((height*data[i])/100); /* scale with % value */
    if (barHeight > 0) {
      GDisp1_DrawFilledBox(x, (GDisp1_PixelDim)(y+height-barHeight), barWidth, barHeight, barColor);
    }
    x += barWidth+borderSpace;
  }
}

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
void GDisp1_DrawLine(GDisp1_PixelDim xstart, GDisp1_PixelDim ystart, GDisp1_PixelDim xend, GDisp1_PixelDim yend, GDisp1_PixelColor color)
{
  /* Based on Bresenham algorithm and http://de.wikipedia.org/wiki/Bresenham-Algorithmus */
  #define sgn(x) ((x) > 0) ? 1 : ((x) < 0) ? -1 : 0
  GDisp1_PixelDim x, y;
  int t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, es, el, err;

  /* Calculate distance in both dimensions */
  dx = xend - xstart;
  dy = yend - ystart;
  /* Determin sign of increment */
  incx = sgn(dx);
  incy = sgn(dy);
  if(dx<0) dx = -dx;
  if(dy<0) dy = -dy;
  /* Check which distance is larger */
  if (dx>dy) { /* we are faster in x direction */
    pdx=incx; pdy=0;    /* pd. is parallel step */
    ddx=incx; ddy=incy; /* dd. is diagonal step */
    es =dy;   el =dx;   /* error steps fast (es) and slow (el) */
  } else { /* faster in y direction */
    pdx=0;    pdy=incy; /* pd. is parallel step */
    ddx=incx; ddy=incy; /* dd. is diagonal step */
    es =dx;   el =dy;   /* error step fast (es) and slow (el) */
  }
  /* Do some initialization first... */
  x = xstart; y = ystart; err = el/2;
  GDisp1_PutPixel(x, y, color); /* put first pixel */
  /* calculate pixels */
  for(t=0; t<el; ++t) { /* t counts the pixels, el is the number of pixels */
    err -= es; /* adapt error */
    if(err<0) { /* make error positive again */
      err += el;
      /* step into the slow direction, diagonal step  */
      x += ddx;
      y += ddy;
    } else {
      /* step into the fast direction, parallel step*/
      x += pdx;
      y += pdy;
    }
    GDisp1_PutPixel(x, y, color);
  }
}

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
void GDisp1_DrawCircle(GDisp1_PixelDim x0, GDisp1_PixelDim y0, GDisp1_PixelDim radius, GDisp1_PixelColor color)
{
  /* draw a circle using the Bresenham method, see http://de.wikipedia.org/wiki/Bresenham-Algorithmus */
  int f = 1 - radius;
  int ddF_x = 0;
  int ddF_y = -2 * radius;
  GDisp1_PixelDim x = 0;
  GDisp1_PixelDim y = radius;

  GDisp1_PutPixel(x0, (GDisp1_PixelDim)(y0 + radius), color);
  GDisp1_PutPixel(x0, (GDisp1_PixelDim)(y0 - radius), color);
  GDisp1_PutPixel((GDisp1_PixelDim)(x0 + radius), y0, color);
  GDisp1_PutPixel((GDisp1_PixelDim)(x0 - radius), y0, color);
  while(x < y) {
    if(f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x + 1;
    GDisp1_PutPixel((GDisp1_PixelDim)(x0 + x), (GDisp1_PixelDim)(y0 + y), color);
    GDisp1_PutPixel((GDisp1_PixelDim)(x0 - x), (GDisp1_PixelDim)(y0 + y), color);
    GDisp1_PutPixel((GDisp1_PixelDim)(x0 + x), (GDisp1_PixelDim)(y0 - y), color);
    GDisp1_PutPixel((GDisp1_PixelDim)(x0 - x), (GDisp1_PixelDim)(y0 - y), color);
    GDisp1_PutPixel((GDisp1_PixelDim)(x0 + y), (GDisp1_PixelDim)(y0 + x), color);
    GDisp1_PutPixel((GDisp1_PixelDim)(x0 - y), (GDisp1_PixelDim)(y0 + x), color);
    GDisp1_PutPixel((GDisp1_PixelDim)(x0 + y), (GDisp1_PixelDim)(y0 - x), color);
    GDisp1_PutPixel((GDisp1_PixelDim)(x0 - y), (GDisp1_PixelDim)(y0 - x), color);
  }
}

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
void GDisp1_DrawFilledCircle(GDisp1_PixelDim x0, GDisp1_PixelDim y0, GDisp1_PixelDim radius, GDisp1_PixelColor color)
{
  /* draw a circle using the Bresenham method, see http://de.wikipedia.org/wiki/Bresenham-Algorithmus and
  http://forums.tigsource.com/index.php?topic=17068.0;wap2 */
  GDisp1_PixelDim xoff=0;
  GDisp1_PixelDim yoff=radius;
  int balance=-((int)radius);
  GDisp1_PixelDim p0, p1, w0, w1;

  while (xoff <= yoff) {
    p0 = (GDisp1_PixelDim)(x0-xoff);
    p1 = (GDisp1_PixelDim)(x0-yoff);
    w0 = (GDisp1_PixelDim)(2*xoff);
    w1 = (GDisp1_PixelDim)(2*yoff);
    GDisp1_DrawHLine(p0, (GDisp1_PixelDim)(y0+yoff), w0, color);
    GDisp1_DrawHLine(p0, (GDisp1_PixelDim)(y0-yoff), w0, color);
    GDisp1_DrawHLine(p1, (GDisp1_PixelDim)(y0+xoff), w1, color);
    GDisp1_DrawHLine(p1, (GDisp1_PixelDim)(y0-xoff), w1, color);
    balance += 2*xoff;
    xoff++;
    if (balance>=0) {
      yoff--;
      balance -= 2*yoff;
    }
  } /* while */
}

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
void GDisp1_Draw65kBitmap(GDisp1_PixelDim x1, GDisp1_PixelDim y1, GDisp1_PixelDim x2, GDisp1_PixelDim y2, word *bmp, bool compressed)
{
  /* NYI */
  (void)x1; (void)y1; (void)x2; (void)y2; (void)bmp; (void)compressed; /* avoid compiler warning */
}

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
void GDisp1_Draw256BitmapHigh(GDisp1_PixelDim x1, GDisp1_PixelDim y1, GDisp1_PixelDim x2, GDisp1_PixelDim y2, byte *bmp, GDisp1_PixelColor *ColorTable, bool compressed)
{
  /* NYI */
  (void)x1; (void)y1; (void)x2; (void)y2; (void)bmp;  (void)ColorTable; (void)compressed; /* avoid compiler warning */
}

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
void GDisp1_Draw256BitmapLow(GDisp1_PixelDim x1, GDisp1_PixelDim y1, GDisp1_PixelDim x2, GDisp1_PixelDim y2, byte *bmp, bool compressed)
{
/* For uncompressed bitmap data:
      The pixels are provided in an array of 8bit pixel information (bmp[]).
      Each byte describes a pixel in 3-3-2 RBG format
   For compressed bitmap data:
      If two bytes are the same, this means that the 3rd byte contains how many times the color has to be repeated.
      Example: 10 red dots are compressed as:
        RED RED 8
 */

  /* NYI */
  (void)x1; (void)y1; (void)x2; (void)y2; (void)bmp; (void)compressed; /* avoid compiler warning */
}

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
#if 0
void GDisp1_UpdateRegion(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim w, GDisp1_PixelDim h)
{
  /* method is implemented as macro in the header file */
}
#endif

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
/*
GDisp1_DisplayOrientation GDisp1_GetDisplayOrientation(void)
  ** This method is implemented as macro
*/

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
/*
void GDisp1_SetDisplayOrientation(GDisp1_DisplayOrientation newOrientation)
  ** This method is implemented as macro
*/

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
/*
GDisp1_PixelDim GDisp1_GetWidth(void)
  ** This method is implemented as macro
*/

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
/*
GDisp1_PixelDim GDisp1_GetHeight(void)
  ** This method is implemented as macro
*/

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
/*
GDisp1_PixelDim GDisp1_GetLongerSide(void)
  ** This method is implemented as macro
*/

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
/*
GDisp1_PixelDim GDisp1_GetShorterSide(void)
  ** This method is implemented as macro
*/

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
void GDisp1_GetDisplay(void)
{
  PDC1_GetLCD();
}

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
void GDisp1_GiveDisplay(void)
{
  PDC1_GiveLCD();
}

/*
** ===================================================================
**     Method      :  GDisp1_Init (component GDisplay)
**     Description :
**         
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void GDisp1_Init(void)
{
}

/* END GDisp1. */

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

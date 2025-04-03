/*****************************************************************************
 * LCD control functions.
 * lcd.c
 * 2004,2006 ASP Digital.  All rights reserved. * Andy Peters, ASP Digital
 * devel@latke.net
 * 
 * various functions to support the usual sort of LCD display.
 * Created: 19 Jul 2004
 * Modified:
 *  11 Dec 2006: Add LcdWriteCGRAM().
 *  03 Mar 2025: Modified for C8051F005.  
 ****************************************************************************/
 #include <c8051F000.h>
 #include "lcd.h"
 #include "lcdcmd.h"
 
 /*
  * Private prototypes:
  */
 void LcdWriteCmd(unsigned char cmd);
 bit isLcdBusy(void);
 void waitUntilDone(void);
 
 
 sbit LCD_E = P1^2;
 sbit LCD_RW = P1^1;
 sbit LCD_RS = P1^0;
 
 sbit LCD_BUSY = P0^7;
 
 /*
  * Fetch LCD's busy flag.
  * Put P0 into read mode before attempting to read!
  */
 bit isLcdBusy(void) {
     bit retbit;
 
     retbit = 0;
 
     PRT0CF = 0x00;
     LCD_RW = 1;
     LCD_RS = 0;
     LCD_E = 1;
     P0 = 0xFF;
     retbit = P0^7;
     LCD_E = 0;
     PRT0CF = 0xFF;
     LCD_RW = 0;
     return (retbit);
 } // isLcdBusy
 
 void waitUntilDone(void)
 {                       
     bit retbit = 1;
     PRT0CF = 0x00;
     P0 = 0xFF;
     LCD_RW = 1;
     LCD_RS = 0;
     while (retbit == 1)
     {
        LCD_E = 1;
        retbit = LCD_BUSY;
        LCD_E = 0;
     } //while retbit == 1
     PRT0CF = 0xFF;
     LCD_RW = 0;
 } // waitUntilDone()
 
 /*
  * Write a character to the display at the current cursor position.
  */
 void LcdWriteChar(unsigned char dval) 
 {
     LCD_RW = 0;
     LCD_RS = 1;
     LCD_E  = 1;	
     P0 = dval;
     LCD_E  = 0;
     waitUntilDone();
 } // LcdWriteChar()
 
 /*
  * Write a string to the display, starting at the current cursor position.
  */
 void LcdWriteString(unsigned char *str)
 {
     while (*str != '\0')
     {
         LcdWriteChar(*str);
         ++str;
     }
 } // LcdWriteString
 
 /*
  * Move the cursor to the specified row and column.
  */
 void LcdMoveCursor(unsigned char row, unsigned char col)
 {
     LcdWriteCmd(LCD_MOVEDISPLAY | (row << 6) | col);
 } // LcdMoveCursor
 
 /*
  * Write a command to the LCD.
  */
 void LcdWriteCmd(unsigned char cmd) 
 {
     LCD_RW = 0;
     LCD_RS = 0;
     LCD_E = 1;
     P0 = cmd;
     LCD_E = 0;
     waitUntilDone();
 } // LcdWriteCmd
 
 
 /*
  * Initialize the LCD.
  */
 
 void LcdInit(void)
 {
     P0 = 0xFF;	 // enable port 0 digital inputs, needed for LCD_BUSY.
     LCD_RW = 0;
     LCD_RS = 0;
     LCD_E  = 0;
 
     LcdWriteCmd(0x30);
     LcdWriteCmd(0x30);
     LcdWriteCmd(0x30);
     LcdWriteCmd(LCD_SETIFLEN | LCD_SETIFLEN_N | LCD_SETIFLEN_DL); 
 
     // should be initialized here.
 
     LcdWriteCmd(LCD_DISPEN); // display off, cursor off, no blink
     LcdWriteCmd(LCD_CLEAR);
     LcdWriteCmd(LCD_DISPEN | LCD_DISPEN_DISP); // | LCD_DISPEN_CURSOR);
     LcdWriteCmd(LCD_MOVEDIR | LCD_MOVEDIR_ID); 
 } // LcdInit
 
 /*
  * Clear the LCD.
  */
 void LcdClear(void)
 {
     LcdWriteCmd(LCD_CLEAR);
 } // LcdClear()
 
 /*
  * Write the given pattern to the CGRAM at the given address.
  */
 void LcdWriteCGRAM(unsigned char addr, unsigned char pattern)
 {
     // First, move the cursor into the CGRAM area:
     LcdWriteCmd(LCD_MOVERAM | addr);
     // Then write the pattern to that location:
     LcdWriteChar(pattern);
 } // LcdWriteCGRAM() 



/*
 * lcd.h: definitions and headers for LCD control.
 *
 * 2004, 2006 ASP Digital.  All rights reserved.
 * Andy Peters, devel@latke.net
 * 11 Dec 2006: add LcdWriteCGRAM()
 */
 #ifndef _LCD_H
 #define _LCD_H
 
 /*
  * LcdWriteChar()
  * Writes a character to the display at the current cursor location.
  * Parameters: 
  *     unsigned char dval: the character to write to the display (see
  *       the Hitachi data sheet)
  * Returns: nothing
  */
 void LcdWriteChar(unsigned char dval);
 
 /*
  * LcdWriteString()
  * Writes a string to the display, starting at the current cursor location.
  * Parameters: 
  *     unsigned char *str: pointer to the string to write to the display
  * Returns: nothing
  */
 void LcdWriteString(unsigned char *str);
 
 /*
  * LcdMoveCursor()
  * Moves the cursor to a specific row and column.
  * Parameters:
  *     unsigned char row: Put the cursor on this row.
  *     unsigned char col: Put the cursor in this column.
  * Returns: nothing
  * Note: No bounds checking is performed, so it's possible to set an illegal
  *       location.
  */
 void LcdMoveCursor(unsigned char row, unsigned char col);
 
 /*
  * LcdInit()
  * Prepare the LCD for use.  This function should be called before attempting
  * to actually use the LCD.
  * Parameters: none.
  * Returns: nothing.
  */
 void LcdInit(void);
 
 /*
  * LcdClear()
  * Clear the display and return the cursor to the home position.
  * Parameters: none.
  * Returns: nothing
  */
 void LcdClear(void);
 
 /*
  * LcdWriteCGRAM()
  * Store a pattern in the CGRAM at the given address.
  * Parameters: 
  *    unsigned char addr: where we store pattern
  *    unsigned char pattern: bit pattern to store at addr
  */
 void LcdWriteCGRAM(unsigned char addr, unsigned char pattern);
 
 #endif 
 
 
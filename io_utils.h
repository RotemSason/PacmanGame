#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_

#include "config.h"
#include "Color.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void gotoxy(int x, int y);
void hideCursor();
void clear_screen();

	#ifndef WINDOWS	
		int _getch(void);
		int _kbhit(void);
		void Sleep(unsigned long);		
	#else
		#include <stdlib.h>
		#include <conio.h>
		#include <windows.h>
	#endif

#endif
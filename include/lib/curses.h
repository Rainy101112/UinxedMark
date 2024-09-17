/* 
 * 
 * 		curses.h
 * 		专用于Uinxed-Kernel的Curses控制台库
 * 
 * 		2024/9/14 By Rainy101112
 * 		此代码的原始著作权归属于Rainy101112
 * 		Public with GPL-3.0 License
 * 
 */

#ifndef INCLUDE_UXCURSES_H_
#define INCLUDE_UXCURSES_H_

#include "types.h"
#include "vbe.h"
#include "fifo.h"

#define SCREEN_WIDTH	80		// 屏幕字符总宽
#define SCREEN_HEIGHT	25		// 屏幕字符总高
/* 字符模式下的屏幕分辨率为80x25个字符长宽 */
/* 当然这只是普通的字符模式分辨率，实际上分辨率可以更低，只不过Uinxed-Kernel还是选择80x25 VGA */

#define INPUTBOX_WIDTH	40		// 输入框的宽度

int curses_drawInput(int handle, char *title);				// 绘制一个输入界面，可连接特定函数至输入框内容中

#endif // INCLUDE_UXCURSES_H_
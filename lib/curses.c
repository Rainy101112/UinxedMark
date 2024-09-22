/* 
 * 
 * 		curses.c
 * 		专用于Uinxed-Kernel的Curses控制台库
 * 
 * 		2024/9/14 By Rainy101112
 * 		此代码的原始著作权归属于Rainy101112
 * 		Public with GPL-3.0 License
 * 
 */

#include "lib/curses.h"
#include "common.h"
#include "printk.h"
#include "keyboard.h"
#include "bmp.h"
#include "timer.h"

/* VGA 的显示缓冲的起点是0xB8000 */
static uint16_t *video_memory = (uint16_t *)0xB8000;

/* 屏幕"光标"的坐标 */
static uint8_t cursorX = 0;
static uint8_t cursorY = 0;

/* 移动光标 */
static void mvcursor(void)
{
	/* 屏幕是80字节宽 */
	uint16_t cursorLocation = cursorY * 80 + cursorX;

	outb(0x3D4, 14);					// 告诉 VGA 我们要设置光标的高字节
	outb(0x3D5, cursorLocation >> 8);	// 发送高8位
	outb(0x3D4, 15);					// 告诉 VGA 我们要设置光标的低字节
	outb(0x3D5, cursorLocation);		// 发送低8位
}

/* 屏幕滚动操作 */
static void scroll(void)
{
	/* attribute_byte 被构造出一个黑底白字的描述格式 */
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attribute_byte << 8); // space 是0x20

	/* cursor_y 到25的时候，就该换行了 */
	if (cursorY >= 25) {
		/* 将所有行的显示数据复制到上一行，第一行永远消失了 */
		int i;
		for (i = 0 * 80; i < 24 * 80; i++) {
			video_memory[i] = video_memory[i+80];
		}

		/* 最后的一行数据现在填充空格，不显示任何字符 */
		for (i = 24 * 80; i < 25 * 80; i++) {
			video_memory[i] = blank;
		}

		/* s向上移动了一行，所以 cursor_y 现在是24 */
		cursorY = 24;
	}
}

/* 绘制一个Curses输入框，标题不超过5个字符 */
int curses_drawInput(int handle, char *title){
	static uint8_t varModeChoose;

	vbe_clear();	// 背景色是自定的，前景色始终都为白色

	extern uint8_t UxMarkLogoBmp[];
	bmp_analysis((Bmp *)UxMarkLogoBmp, 250, 100, 1);

	printk_color(0xffffff,"\n\n\n\n\n\n\n\n\n\n\n                  +-%s-+----------------------------------------------------------------+\n", title);
	printk_color(0xffffff,			 			"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |           Choose a mode.                                               |\n");
	printk_color(0xffffff,						"                  |           1. Start Uinxed-Mark.                                        |\n");
	printk_color(0xffffff,						"                  |           2. About.                                                    |\n");
	printk_color(0xffffff,						"                  |           3. Reboot. (Not ACPI)                                        |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |           Look for the mode you want then enter the number.            |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  |                                                                        |\n");
	printk_color(0xffffff,						"                  +------------------------------------------------------------------------+\n");
	printk_color(0xffffff,						"                  STATUS: Listening keyboard event                                          \r");

	while (1){
		while (fifo_status(&decoded_key) == 0);
		varModeChoose = fifo_get(&decoded_key);

		if (varModeChoose == '1'){
			printk_color(0xffffff,				"                  STATUS: User typed in 1                                                   \r");
			return 1;
		} else
		if (varModeChoose == '2'){
			printk_color(0xffffff,				"                  STATUS: User typed in 2                                                   \r");
			return 2;
		} else
		if (varModeChoose == '3'){
			printk_color(0xffffff,				"                  STATUS: User typed in 3                                                   \r");
			return 3;
		} else{
			printk_color(0xffffff,				"                  STATUS: Invaild mode number                                               \r");
			continue;
		}
	}
}
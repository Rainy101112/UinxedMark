#include "UxMark/uxmark.h"
#include "timer.h"
#include "uinxed.h"
#include "fifo.h"
#include "keyboard.h"
#include "vbe.h"
#include "cpu.h"
#include "debug.h"
#include "memory.h"

static char *UxMarkLogo = 
			"###      *$$$$$$\n"
			"###     *$$$$$$$\n"
			"###    *$$$$$$$$\n"
			"###   *$$$$*$$$$\n"
			"###   *$$$$*$$$$\n"
			"###  *$$$$$*$$$$\n"
			"###  *$$$$ *$$$$\n"
			"###  *$$$$ *$$$$\n"
			"###  *$$$$ *$$$$\n"
			"### *$$$$*  *$$$\n"
			"### *$$$$*  *$$$\n"
			"###*$$$$$*  *$$$\n"
			"###$$$$$*   *$$$\n"
			"*$$$$$$*   *##$$\n"
			" *$$$#*   *###$$\n"
			"    *######* *$$\n";

static char *UxMarkLogoWithInfo = 
			" *#####*        *$$$$$$\n"
			"  *###*         $$$$$$\n"
			" $$$#$           $$$$$\n"
			"  $$$$$           $$$$           UU     UU XXX   XXX MMM   MMM     A     RRRRRRRR  KK    KK \n"
			" #$$$$$$          #$$$$          UU     UU   XX XX   MM M M MM    AAA    RR     RR KK   KK  \n"
			"   $$$$$          ##$$$          UU     UU    XXX    MM  M  MM   AA AA   RRRRRRR   KKKKKK  \n"
			"  $##$$           ###$           UU     UU   XX XX   MM     MM  AAAAAAA  RR    RR  KK   KK  \n"
			"  $###            ###$            UUUUUUU  XXX   XXX MM     MM AA     AA RR     RR KK    KKK\n"
			" $$$##           $###\n"
			" $$$$#           $###\n"
			" $$$$#          $$###                A CPU marking tool(Or system).\n"
			"  $$##         $$$###                Powered by Uinxed-Kernel (uinxed-kernel.asia).\n"
			"   ###*       $$$*###                ViudiraTechnologies & RainySoft-Team.\n"
			"   *###*$   $$$$*###*                Version: "UXMARK_VERSION"\n"
			"    *###*$$$$$$*###*\n"
			"       *########*    \n";

static void uxmarkPrintLogo(){
	printk_color( 0xff00ff, UxMarkLogoWithInfo);
}

static void doFor(){
	printk("Starting test: doFor(Do \"for\" 999999999 times)\n");
	int times = 0;
	for (times; times <= 999999999; times++){
		if (times == 10000){
			printk("Test: Passed 10000 times just now...\n");
		} else
		if (times == 100000){
			printk("Test: Passed 100000 times just now...\n");
		} else
		if (times == 1000000){
			printk("Test: Passed 1000000 times just now...\n");
		} else
		if (times == 10000000){
			printk("Test: Passed 10000000 times just now...\n");
		}
		if (times == 100000000){
			printk("Test: Passed 100000000 times just now...\n");
		} else
		if (times == 200000000){
			printk("Test: Passed 200000000 times just now...\n");
		} else
		if (times == 400000000){
			printk("Test: Passed 400000000 times just now...\n");
		} else
		if (times == 600000000){
			printk("Test: Passed 600000000 times just now...\n");
		} else
		if (times == 800000000){
			printk("Test: Passed 800000000 times just now...\n");
		} else
		if (times == 900000000){
			printk("Test: Passed 900000000 times just now...\n");
		} else
		if (times == 999999999){
			printk("Test: doFor done.\n");
			break;
		}
	}
}

static void waitTenSec(){
	printk("Waiting for 1000 CPU ticks...(About 10s).\n");
	for(int i = 0; i <= 10; i++){
		clock_sleep(100);
		printk_color(0x008400, "*");
	}
	printk("\rWaited up.   \n");
}

static void waitSec(int second, bool showInfo){
	if(showInfo == true) printk("\rWaiting...(%ds, %d CPU ticks)                                          \n", second, second * 1000);
	for(int i = 0; i <= second; i++){
		clock_sleep(100);
		printk_color(0x008400, "*");
	}
	printk("\rWaited up.   \n");
}


static void aboutUxMark(){
	vbe_clear();
	uxmarkPrintLogo();
	printk("\n");
	printk_color(0x848484, "Uinxed-Mark(Or UxMark) is a CPU marking testing tool(Or system).\n");
	printk_color(0x848484, "The project was began on 9/14/2024. Developing by Rainy101112 (RainySoft-Team).\n");
	printk_color(0x848484, "Uinxed-Kernel "PROJK_COPY"\n");
	printk_color(0x848484, "Kernel version: "KERNL_VERS"");
	printk_color(0x848484, " | Kernel build: ");
	printk_color(0x848484, "%d", KERNL_BUID);
	printk_color(0x848484, "\n");
	printk_color(0x848484, "Build time: "BUILD_DATE" "BUILD_TIME"\n");
	printk("\n");

	printk_color(0x0000ff, "Press any key to start Uinxed-Mark.");
	while (fifo_status(&decoded_key) == 0);
	return;
}

static void marking(){
	vbe_clear();
	printk_color(0x840084, "Welcome to Uinxed-Mark!\n");
	uxmarkPrintLogo();
	printk("\n");
	print_cpu_info();

	waitSec(3, true);

	extern void do_qsort(void);
	extern void pi();
	//do_qsort();
	//panic("TESTING");
	pi();
	doFor();

	uint32_t *keybuf = (uint32_t *) kmalloc(128);
	uint32_t *dkey_buf = (uint32_t *) kmalloc(128);
	fifo_init(&keyfifo, 32, keybuf);
	fifo_init(&decoded_key, 32, dkey_buf);

	printk_color(0x0000ff, "Press any key to reboot your computer.");
	while (fifo_status(&decoded_key) == 0);

	printk_color(0xffff00, "\n[ ** ] The system is going to \"Reboot\" NOW!");
	waitSec(3, false);
	outb(0x64, 0xfe);
}

void start_uxmark(int modeNumber){
	if (modeNumber == 1){
		marking();
	} else
	if (modeNumber == 2){
		aboutUxMark();
		waitSec(5, true);
		marking();
	}
	if (modeNumber == 3){
		printk_color(0xffff00, "                  [ ** ] The system is going to \"Reboot\" NOW!");
		waitSec(3, false);
		outb(0x64, 0xfe);
	}
}
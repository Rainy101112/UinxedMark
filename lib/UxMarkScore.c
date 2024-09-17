#include "timer.h"
#include "types.h"
#include "task.h"
#include "debug.h"
#include "printk.h"

void pi(){
	int m, i = 1;
	float s = 0;

	for(m = 1; m < 10000; m += 2){
		s += i * (1.0 / m);
		i =- i;
	}
	printk("Pi: Done\n");
}

void Qsort(int a[], int low, int high){//快排算法
	if (low >= high) return;

	int first = low;
	int last = high;
	int key = a[first];

	while(first < last){
		while (first < last && a[last] >= key) --last;
		a[first] = a[last];

		while (first < last && a[first] <= key) ++first;
		a[last] = a[first];
	}

	a[first] = key;

	Qsort(a, low, first - 1);
	Qsort(a, first + 1, high);
}

void do_qsort(void){//调用快排算法的函数
	int a[10000], i;
	for (i=10000; i > 0; i--) a[10000 - 1] = i;
	Qsort(a, 0, 10000 - 1);
	printk("QSort: Done\n");
}

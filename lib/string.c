/*
 *
 *		string.s
 *		基础内存操作和字符串处理的内联函数库
 *
 *		2024/6/27 By Rainy101112
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留所有权利。
 *
 */

#include "string.h"
#include "types.h"

/* 比较两个内存区域的前count个字节 */
int memcmp(const void* buffer1,const void* buffer2,size_t count)
{
	if(!count) {
		return 0;
	}

	/* 当比较位数不为0时，且每位数据相等时，移动指针 */
	while(count-- && *(char*)buffer1 == *(char*)buffer2) {
		buffer1 = (char*)buffer1 + 1; // 转换类型，移动指针
		buffer2 = (char*)buffer2 + 1;
	}

	/* 返回超过比较位数之后 比较的大小 */
	return( *((uint8_t *)buffer1) - *((uint8_t *)buffer2) );    
}

/* 将len个字节从源地址复制到目标地址 */
inline void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len)
{
	uint8_t *sr = (uint8_t *)src;
	uint8_t *dst = dest;

	while (len != 0) {
		*dst++ = *sr++;
		len--;
	}
}

/* 将目标内存区域的前len个字节设置为值val */
inline void memset(void *dest, uint8_t val, uint32_t len)
{
	for (uint8_t *dst = (uint8_t *)dest; len != 0; len--) {
		*dst++ = val;
	}
}

/* 将目标内存区域的前len个字节设置为0 */
inline void bzero(void *dest, uint32_t len)
{
	memset(dest, 0, len);
}

/* 清除一个字符数组s的内存 */
void memclean(char *s, int len)
{
	int i;
	for (i = 0; i != len; i++) {
		s[i] = 0;
	}
	return;
}

/* 比较两个字符串 */
inline int strcmp(const char *dest, const char *src)
{
	int ret = 0 ;

	while(!(ret = *(unsigned char *)src - *(unsigned char *)dest) && *dest) {
		++src;
		++dest;
	}
	if (ret < 0) {
		ret = -1;
	}
	else if (ret > 0) {
		ret = 1;
	}
	return ret;
}

/* 将字符串src复制到dest */
inline char *strcpy(char *dest, const char *src)
{
	char *tmp = dest;

	while (*src) {
		*dest++ = *src++;
	}
	*dest = '\0';	
	return tmp;
}

/* 将字符串的前len个字符复制到dest */
char *strncpy(char *dest, const char *src, uint32_t len)
{
	char *dst = dest;

	while (len > 0) {
		while (*src) {
			*dest++ = *src++;
		}
		len--;
	}
	*dest = '\0';
	return dst;
}

/* 将字符串src连接到dest的末尾 */
inline char *strcat(char *dest, const char *src)
{
	char *cp = dest;

	while (*cp) {
		cp++;
	}
	while ((*cp++ = *src++));
	return dest;
}

/* 查找字符串中的一个字符并返回该字符在字符串中第一次出现的位置 */
char *strchr(char *str, int c)
{
	for (; *str != 0; ++str) {
		if (*str == c) {
			return str;
		}
	}
	return NULL;
}

/* 返回字符串src的长度 */
inline int strlen(const char *src)
{
	const char *eos = src;

	while (*eos++);
	return (eos - src - 1);
}

/* 删除字符串中指定位置的字符 */
void delete_char(char *str, int pos)
{
	int i;
	for (i = pos; i < strlen(str); i++) {
		str[i] = str[i + 1];
	}
}

/* 在字符串的指定位置插入一个字符 */
void insert_char(char *str, int pos, char ch)
{
	int i;
	for (i = strlen(str); i >= pos; i--) {
		str[i + 1] = str[i];
	}
	str[pos] = ch;
}

/* 在字符串的指定位置插入另一个字符串 */
void insert_str(char *str, char *insert_str, int pos)
{
	for (int i = 0; i < strlen(insert_str); i++) {
		insert_char(str, pos + i, insert_str[i]);
	}
}

/* 将字符串中的所有小写字母转换为大写字母 */
void strtoupper(char *str)
{
	while (*str != '\0') {
		if (*str >= 'a' && *str <= 'z') {
			*str -= 32;
		}
		str++;
	}
}

/* 从文件件路径中获取文件名 */
char *get_filename(char *path)
{
	char ch = '/';
	char *filename = strchr(path, ch) + 1;
	return filename;
}

/* 将字符串数字转换为整数数字 */
int atoi(char* pstr)
{
	int ret_integer = 0;
	int integer_sign = 1;

	if (*pstr == '-') integer_sign = -1;
	if (*pstr == '-' || *pstr == '+') pstr++;

	while (*pstr >= '0' && *pstr <= '9') {
		ret_integer = ret_integer * 10 + *pstr - '0';
		pstr++;
	}
	ret_integer = integer_sign * ret_integer;
	return ret_integer;
}

/* 把浮点数转换成字符数组 */
char *ftoa(double f, char *buf, int precision)
{
	char * ptr = buf;
	char * p = ptr;
	char * p1;
	char c;
	long intPart;

	if (precision > MAX_PRECISION)
		precision = MAX_PRECISION;
	if (f < 0)
	{
		f = -f;
		*ptr++ = '-';
	}
	if (precision < 0)
	{
		if (f < 1.0) precision = 6;
		else if (f < 10.0) precision = 5;
		else if (f < 100.0) precision = 4;
		else if (f < 1000.0) precision = 3;
		else if (f < 10000.0) precision = 2;
		else if (f < 100000.0) precision = 1;
		else precision = 0;
	}
	if (precision)
		f += rounders[precision];
	intPart = f;
	f -= intPart;
	if (!intPart)
		*ptr++ = '0';
	else
	{
		p = ptr;
		while (intPart)
		{
			*p++ = '0' + intPart % 10;
			intPart /= 10;
		}
		p1 = p;
		while (p > ptr)
		{
			c = *--p;
			*p = *ptr;
			*ptr++ = c;
		}
		ptr = p1;
	}
	if (precision)
	{
		*ptr++ = '.';
		while (precision--)
		{
			f *= 10.0;
			c = f;
			*ptr++ = '0' + c;
			f -= c;
		}
	}
	*ptr = 0;
	return ptr;
}

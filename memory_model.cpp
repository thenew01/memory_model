// memory_model.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int g_a = 1;
int g_aa = 2;
const int g_b = 3;
const int g_bb = 4;

class CA
{
public:
	void func1() 
	{
		int a;
	}
	void func2()
	{
		int a;
	}
	static void func3(){
		static int a;
	}
	static void func4(){
		static int a;
	}
	int a;
	int b;
};


int test1()
{
	char szA[1024*1000];
	return 0;
}

int test2()
{
	char szA[10] = {0,};
	szA[1000] = 0;
	return 1;
}
template<typename dst_type,typename src_type>
dst_type union_cast(src_type src)
{
	union{
		src_type s;
		dst_type d;
	}u;
	u.s = src;
	return u.d;
}
int _tmain(int argc, _TCHAR* argv[])
{

	//test2();
	//char szA[2];
	//strcpy(szA, "11111111111111111111111111111111111111111111111111111111111111111111111111111111111");

	const int c = 1;
	const int cc = 2;
	int d = 3;
	int dd = 4;

	CA* pA = new CA;
	pA->a = 1;
	pA->b = 2;

	typedef void (CA::*func_ptr)();
	func_ptr f1 = &CA::func1;

	void* p1 = (void*)union_cast<void*>(&CA::func1);
	void* p2 = (void*)union_cast<void*>(&CA::func2);
	printf("0x%08x\n", &CA::func1 );
	printf("0x%08x\n", &CA::func2 );
	printf("0x%08x\n" ,(int)&CA::func3 );
	printf("0x%08x\n" ,(int)&CA::func4 );

	char* p3 = new char[5];
	//delete[] p1;	
	strcpy(p3, "1234567");
	void* p4 = malloc(100);
	free(p4);


	return 0;
}*/

/*
#include <stdio.h> 
int g1=0, g2=0, g3=0; 
int main() 
{ 
	static int s1=0, s2=0, s3=0; 
	int v1=0, v2=0, v3=0; 
	//打印出各个变量的内存地址 
	printf("0x%08x\n",&v1); //打印各本地变量的内存地址 
	printf("0x%08x\n",&v2); 
	printf("0x%08x\n\n",&v3); 
	printf("0x%08x\n",&g1); //打印各全局变量的内存地址 
	printf("0x%08x\n",&g2); 
	printf("0x%08x\n\n",&g3); 
	printf("0x%08x\n",&s1); //打印各静态变量的内存地址 
	printf("0x%08x\n",&s2); 
	printf("0x%08x\n\n",&s3); 

	int a; 
	char b; 
	int c; 
	printf("0x%08x\n",&a); 
	printf("0x%08x\n",&b); 
	printf("0x%08x\n",&c); 

	return 0; 
} */

#include <windows.h>
#include <tchar.h>
#include <locale.h>

//在MSVC中，一般使用#progma pack来指定内存对齐：
#pragma pack(show)  //以警告信息的形式显示当前字节对齐的值(在编译输出框显示)
//默认的8字节对齐
struct BYTE1{
    char ch1;
    int i1;
};

#pragma pack(push)
#pragma pack(1)
#pragma pack(show)
struct BYTE2{
    char ch2;
    int i2;
};
#pragma pack(pop)

//微软的__declspec(align(#))，其#的内容可以是预编译宏，但不能是编译期数值
#pragma pack(show)
struct __declspec(align(1)) BYTE3{
    char ch3;
    int i3;
};

VOID AlignTest(PVOID pvDataBuffer){

    char *pc = (PCHAR)pvDataBuffer;
    pc++; //指向第2个字节

    //未对齐方式访问：将第2-5个字节当成DWORD来看待,此时内存没对齐，
    //因为DWORD的起始地址而是4的倍数
    DWORD dwUnAligned = *(DWORD*)(pc);
    _tprintf(_T("dwUnAligned=0x%08X\n"), dwUnAligned);
    
    //用对齐方式访问，效率更高
    DWORD dwAligned = *(UNALIGNED DWORD*)pc;//*(DWORD*)pc;
    _tprintf(_T("dwAligned  =0x%08X\n"), dwAligned);
}

int _tmain(){

    char c[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    AlignTest((PVOID)c);

    //内存对齐
    size_t  sz1 = sizeof(BYTE1); 
    size_t  sz2 = sizeof(BYTE2);
    size_t  sz3 = sizeof(BYTE2);
    _tprintf(_T("sizeof(BYTE1)==%d\n"), sz1);
    _tprintf(_T("sizeof(BYTE2)==%d\n"), sz2);
    _tprintf(_T("sizeof(BYTE3)==%d\n"), sz3);

    //MSVC使用__alignof获得结构体中最大成员变量的对齐大小，即结构体的对齐大小
    sz1 = __alignof(BYTE1); //最大成员为i1，对齐大小应为4
    sz2 = __alignof(BYTE2); //最大成员为ch2，对齐大小应为1
    sz3 = __alignof(BYTE3); //最大成员为i3，对齐大小应为4
    _tprintf(_T("__alignof(BYTE1)==%d\n"), sz1);
    _tprintf(_T("__alignof(BYTE2)==%d\n"), sz2);
    _tprintf(_T("__alignof(BYTE3)==%d\n"), sz3);

    return 0;
}
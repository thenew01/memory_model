// memory_model.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//��ӡ�������������ڴ��ַ 
	printf("0x%08x\n",&v1); //��ӡ�����ر������ڴ��ַ 
	printf("0x%08x\n",&v2); 
	printf("0x%08x\n\n",&v3); 
	printf("0x%08x\n",&g1); //��ӡ��ȫ�ֱ������ڴ��ַ 
	printf("0x%08x\n",&g2); 
	printf("0x%08x\n\n",&g3); 
	printf("0x%08x\n",&s1); //��ӡ����̬�������ڴ��ַ 
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

//��MSVC�У�һ��ʹ��#progma pack��ָ���ڴ���룺
#pragma pack(show)  //�Ծ�����Ϣ����ʽ��ʾ��ǰ�ֽڶ����ֵ(�ڱ����������ʾ)
//Ĭ�ϵ�8�ֽڶ���
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

//΢���__declspec(align(#))����#�����ݿ�����Ԥ����꣬�������Ǳ�������ֵ
#pragma pack(show)
struct __declspec(align(1)) BYTE3{
    char ch3;
    int i3;
};

VOID AlignTest(PVOID pvDataBuffer){

    char *pc = (PCHAR)pvDataBuffer;
    pc++; //ָ���2���ֽ�

    //δ���뷽ʽ���ʣ�����2-5���ֽڵ���DWORD������,��ʱ�ڴ�û���룬
    //��ΪDWORD����ʼ��ַ����4�ı���
    DWORD dwUnAligned = *(DWORD*)(pc);
    _tprintf(_T("dwUnAligned=0x%08X\n"), dwUnAligned);
    
    //�ö��뷽ʽ���ʣ�Ч�ʸ���
    DWORD dwAligned = *(UNALIGNED DWORD*)pc;//*(DWORD*)pc;
    _tprintf(_T("dwAligned  =0x%08X\n"), dwAligned);
}

int _tmain(){

    char c[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    AlignTest((PVOID)c);

    //�ڴ����
    size_t  sz1 = sizeof(BYTE1); 
    size_t  sz2 = sizeof(BYTE2);
    size_t  sz3 = sizeof(BYTE2);
    _tprintf(_T("sizeof(BYTE1)==%d\n"), sz1);
    _tprintf(_T("sizeof(BYTE2)==%d\n"), sz2);
    _tprintf(_T("sizeof(BYTE3)==%d\n"), sz3);

    //MSVCʹ��__alignof��ýṹ��������Ա�����Ķ����С�����ṹ��Ķ����С
    sz1 = __alignof(BYTE1); //����ԱΪi1�������СӦΪ4
    sz2 = __alignof(BYTE2); //����ԱΪch2�������СӦΪ1
    sz3 = __alignof(BYTE3); //����ԱΪi3�������СӦΪ4
    _tprintf(_T("__alignof(BYTE1)==%d\n"), sz1);
    _tprintf(_T("__alignof(BYTE2)==%d\n"), sz2);
    _tprintf(_T("__alignof(BYTE3)==%d\n"), sz3);

    return 0;
}
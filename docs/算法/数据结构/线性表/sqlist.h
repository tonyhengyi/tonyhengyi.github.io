#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//typedef int SLDataType;
//#define N 100000
//
//// 静态顺序表 -- 开少了不够用 开多了浪费
//struct SeqList
//{
//	SLDataType a[N];
//	int size;
//};

typedef int SLDataType;
#define INIT_CAPACITY 4

// 动态顺序表 -- 按需申请
typedef struct SeqList
{
    SLDataType* a;
    int size;     // 有效数据个数
    int capacity; // 空间容量
}SL;

// 增删查改
void SLInit(SL* ps);
void SLDestroy(SL* ps);
void SLPrint(SL* ps);
void SLCheckCapacity(SL* ps);

void SLPushBack(SL* ps, SLDataType x);
void SLPopBack(SL* ps);
void SLPushFront(SL* ps, SLDataType x);
void SLPopFront(SL* ps);
void SLInsert(SL* ps, int pos, SLDataType x);
void SLErase(SL* ps, int pos);
int SLFind(SL* ps, SLDataType x);







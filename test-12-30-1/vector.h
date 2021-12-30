#pragma once
#include <stdio.h>
#include <stdlib.h>
//1.定义顺序表
//结构体 Vector:表的类型
typedef struct
{
  //1.指针 存储申请的内存的首地址
  int* pV;
  //2.总容量 记录当前的表的最大元素个数
  size_t capacity;
  //3.长度 当前拥有的元素长度
  int size;
}Vector;
//创建顺序表
//初始化
//参数: 长度(用作计算开辟内存的大小)
extern Vector InitVector(int n);
//扩容顺序表
//扩容
//参数: 表指针 容量
extern Vector* CheckCapacityVector(Vector* pVector,size_t n);
//尾部插入元素
//增
//参数: 表指针 数值
extern Vector* PushBankVector(Vector* pVector,int num);
//任意位置插入元素
//插入
//参数: 表指针 数值 位置
extern Vector* InsertVector(Vector* pVector,int num,int pos);

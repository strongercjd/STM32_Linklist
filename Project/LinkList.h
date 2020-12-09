/**
* @file LinkList.h
* 
* @author strongercjd (strongercjd@163.com)
* @brief 
* @version 0.1
* @date 2020-12-08
* 
* @copyright Copyright (c) 2020
* 
*/
#ifndef LINKLIST_H_
#define LINKLIST_H_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "stm32f2xx.h"

#define false                   0
#define true                    1


typedef struct Area_Inf
{
  uint8_t ID;
  uint8_t X;
  uint8_t Y;
  uint8_t Width;
  uint8_t Height;
  uint8_t data_len;
  uint8_t* Area_Data;
}Area_Inf_Typedef; 

typedef struct Area_List_Inf
{
  Area_Inf_Typedef *Area_Inf;
  struct Area_List_Inf *next_Area_Inf;  //用于指向下一个
}Area_List_Inf_Typedef;


int Area_List_Init(void);
int Add_Area_ToList(Area_Inf_Typedef *Area_Inf);
int Delete_Area_Accordingn_ID(int num);
int Find_Area_According_ID(Area_Inf_Typedef **data_p,int num);
int Delete_All_Area(void);


#endif

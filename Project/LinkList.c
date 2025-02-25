
/**
* @file LinkList.c
* 
* @author strongercjd (strongercjd@163.com)
* @brief 链表管理
* @version 0.1
* @date 2020-12-08
* 
* @copyright Copyright (c) 2020
* 
*/


#include "LinkList.h"

Area_List_Inf_Typedef *Head_Area_List; //链表的头指针

/**
* @brief 动态区链表初始化
* 
* 
* @return int 
*/
int Area_List_Init(void)
{
  // 初始化头指针为空
  Head_Area_List = NULL;
  return true;
}

/**
* @brief 在链表末尾增加一个区域参数
* 
* @param Area_Inf 增加的区域区参数指针
* @return int 
*/
int Add_Area_ToList(Area_Inf_Typedef *Area_Inf)
{
  if (Head_Area_List == NULL) {  // 处理空链表的情况
    Head_Area_List = (Area_List_Inf_Typedef*)malloc(sizeof(Area_List_Inf_Typedef));
    if (Head_Area_List == NULL)
      return false;
    
    Head_Area_List->Area_Inf = (Area_Inf_Typedef*)malloc(sizeof(Area_Inf_Typedef));
    if (Head_Area_List->Area_Inf == NULL) {
      free(Head_Area_List);
      Head_Area_List = NULL;
      return false;
    }
    
    memcpy(Head_Area_List->Area_Inf, Area_Inf, sizeof(Area_Inf_Typedef));
    Head_Area_List->Area_Inf->Area_Data = (uint8_t*)malloc(Area_Inf->data_len);
    if (Head_Area_List->Area_Inf->Area_Data == NULL) {
      free(Head_Area_List->Area_Inf);
      free(Head_Area_List);
      Head_Area_List = NULL;
      return false;
    }
    memcpy(Head_Area_List->Area_Inf->Area_Data, Area_Inf->Area_Data, Area_Inf->data_len);
    Head_Area_List->next_Area_Inf = NULL;
    return true;
  }

  Area_List_Inf_Typedef *p = Head_Area_List;
  while(p->next_Area_Inf != NULL)
  {
    p = p->next_Area_Inf;
  }
  
  //先申请链表结构体的空间，因为后续还要继续增加
  p->next_Area_Inf =  (Area_List_Inf_Typedef*)malloc(sizeof(Area_List_Inf_Typedef));
  if(p->next_Area_Inf == NULL) 
    return false;//申请不到内存，返回失败
  
  //指向刚刚申请的空间，并为需要存放的动态区信息申请对应的内存
  p = p->next_Area_Inf;
  
  p->Area_Inf = (Area_Inf_Typedef*)malloc(sizeof(Area_Inf_Typedef));
  if(p->Area_Inf == NULL) 
  {
    free(p);//由于申请失败，先前申请的链表空间也要释放
    return false;
  }    
  memcpy(p->Area_Inf,Area_Inf,sizeof(Area_Inf_Typedef));
  
  /*拷贝数据*/
  p->Area_Inf->Area_Data = (uint8_t*)malloc(Area_Inf->data_len);
  if(p->Area_Inf->Area_Data == NULL) 
  {
    free(p->Area_Inf);
    free(p);
    return false;
  }
  memcpy(p->Area_Inf->Area_Data,Area_Inf->Area_Data,Area_Inf->data_len);
  
  //标记这个链表的尾部
  p->next_Area_Inf=NULL;
  
  //添加成功
  return true;
}

/**
* @brief 根据区域ID删除动态区
* 
* @param num 区域ID
* @return int 
*/
int Delete_Area_Accordingn_ID(int num)
{
  if (Head_Area_List == NULL) return false;

  int res = false;
  Area_List_Inf_Typedef *current = Head_Area_List;
  Area_List_Inf_Typedef *prev = NULL;

  while (current != NULL) {
    if (current->Area_Inf->ID == num) {
      if (prev == NULL) {
        // 删除头节点
        Head_Area_List = current->next_Area_Inf;
      } else {
        prev->next_Area_Inf = current->next_Area_Inf;
      }

      free(current->Area_Inf->Area_Data);
      free(current->Area_Inf);
      free(current);
      res = true;
      break;
    }
    prev = current;
    current = current->next_Area_Inf;
  }
  return res;
}

/**
* @brief 根据区域ID找到链表
* 
* @param data_p 链表指针
* @param num    区域ID编号
* @return int 
*/
int Find_Area_According_ID(Area_Inf_Typedef **data_p,int num)
{
  Area_List_Inf_Typedef *p = Head_Area_List;
  while(p != NULL)
  {
    if(p->Area_Inf->ID == num) {
      *data_p = p->Area_Inf;
      return true;
    }
    p = p->next_Area_Inf;
  }
  return false;
}


/**
* @brief 删除所有区域
* 
*/
int Delete_All_Area(void)
{
  if (Head_Area_List == NULL) return false;

  int res = false;
  Area_List_Inf_Typedef *current = Head_Area_List;
  
  while (current != NULL) {
    Area_List_Inf_Typedef *next = current->next_Area_Inf;
    
    // 释放节点内存
    if (current->Area_Inf != NULL) {
      free(current->Area_Inf->Area_Data);
      free(current->Area_Inf);
    }
    free(current);
    
    current = next;
    res = true;
  }
  
  Head_Area_List = NULL; // 重置头指针
  return res;
}

/**
* @brief 打印链表信息
* 
*/
void Printf_Area_Inf(void)
{
  if (Head_Area_List == NULL) {
    printf("List is empty\r\n");
    return;
  }

  int i=0;
  Area_List_Inf_Typedef *p = Head_Area_List;
  printf("list   ID   X   Y   Width   Height   Area_Data\r\n");
  
  while(p != NULL)
  {
    printf(" %d     %d    %d   %d    %d      %d      %s\r\n",i,p->Area_Inf->ID,p->Area_Inf->X,p->Area_Inf->Y,p->Area_Inf->Width,p->Area_Inf->Height,p->Area_Inf->Area_Data);
    p = p->next_Area_Inf;
    i++;
  }
  printf("----------------------end-----------------------\r\n");
}

/**
* @brief 链表测试函数
* 
*/
void list_main()
{
  int i,j;
  Area_Inf_Typedef temp;
  Area_Inf_Typedef *found_area = NULL;
  Area_Inf_Typedef **data_p = &found_area;
  
  printf("------------------List test---------------------\r\n"); 
  if(!Area_List_Init())
  {
    printf("Memory fail..\r\n");
    return;
  }

  // 创建测试数据
  for(i=0;i<5;i++)
  {
    temp.ID = i;
    temp.X = 5+i;
    temp.Y = i;
    temp.Width = 10+i;
    temp.Height = 10+i;
    temp.data_len = i+1;
    temp.Area_Data = (uint8_t*)malloc(temp.data_len+1);
    for(j=0;j<temp.data_len;j++)
    {
      temp.Area_Data[j] = j+0x30;
    }
    temp.Area_Data[j] = 0;
    
    if(!Add_Area_ToList(&temp))
    {
      printf("Add Area %d Area_Info fail\r\n",i);
    }
    free(temp.Area_Data); // 释放临时分配的内存
  }
  
  Printf_Area_Inf();
  
  printf("\r\n-------------Delete ID of Area is 3-------------\r\n");
  Delete_Area_Accordingn_ID(3);
  Printf_Area_Inf();
  
  // 添加新区域
  temp.ID = 9;
  temp.data_len = 10;
  temp.Area_Data = (uint8_t*)malloc(temp.data_len+1);
  for(j=0;j<temp.data_len;j++)
  {
    temp.Area_Data[j] = j+0x30;
  }
  temp.Area_Data[j] = 0;
  
  if(!Add_Area_ToList(&temp))
  {
    printf("Add Area %d info fail\r\n",temp.ID);
  }
  free(temp.Area_Data); // 释放临时分配的内存
  
  printf("\r\n--------------Add ID of Area is 9---------------\r\n");
  Printf_Area_Inf();
  
  // 查找区域测试
  if(Find_Area_According_ID(data_p,2))
  {
    printf("Found area ID: %d\r\n", (*data_p)->ID);
  }
  else
  {
    printf("Area ID 2 not found\r\n");
  }
  
  // 清理测试环境
  Delete_All_Area();
  printf("\r\n--------------Delete All Area-------------------\r\n");
  Printf_Area_Inf();
}

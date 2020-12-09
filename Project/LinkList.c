
/**
* @file LinkList.c
* 
* @author strongercjd (strongercjd@163.com)
* @brief �������
* @version 0.1
* @date 2020-12-08
* 
* @copyright Copyright (c) 2020
* 
*/


#include "LinkList.h"

Area_List_Inf_Typedef *Head_Area_List; //�����ͷָ��

/**
* @brief ��̬�������ʼ��
* 
* 
* @return int 
*/
int Area_List_Init(void)
{
  //�����������ʹ�С�Ŀռ䣬����ͷָ��ָ����
  Head_Area_List = (Area_List_Inf_Typedef*)malloc(sizeof(Area_List_Inf_Typedef));
  if(Head_Area_List == NULL) 
    return false;
  
  //ͬʱҪ�����һ����ϢΪ��
  Head_Area_List->next_Area_Inf = NULL;
  return true;
}

/**
* @brief ������ĩβ����һ���������
* 
* @param Area_Inf ���ӵ�����������ָ��
* @return int 
*/
int Add_Area_ToList(Area_Inf_Typedef *Area_Inf)
{
  Area_List_Inf_Typedef *p = Head_Area_List;
  while(p->next_Area_Inf!=NULL)
  {
    p = p->next_Area_Inf;
  }
  
  //����������ṹ��Ŀռ䣬��Ϊ������Ҫ��������
  p->next_Area_Inf =  (Area_List_Inf_Typedef*)malloc(sizeof(Area_List_Inf_Typedef));
  if(p->next_Area_Inf == NULL) 
    return false;//���벻���ڴ棬����ʧ��
  
  //ָ��ո�����Ŀռ䣬��Ϊ��Ҫ��ŵĶ�̬����Ϣ�����Ӧ���ڴ�
  p = p->next_Area_Inf;
  
  p->Area_Inf = (Area_Inf_Typedef*)malloc(sizeof(Area_Inf_Typedef));
  if(p->Area_Inf == NULL) 
  {
    free(p);//��������ʧ�ܣ���ǰ���������ռ�ҲҪ�ͷ�
    return false;
  }    
  memcpy(p->Area_Inf,Area_Inf,sizeof(Area_Inf_Typedef));
  
  /*��������*/
  p->Area_Inf->Area_Data = (uint8_t*)malloc(Area_Inf->data_len);
  if(p->Area_Inf->Area_Data == NULL) 
  {
    free(p->Area_Inf);
    free(p);
    return false;
  }
  memcpy(p->Area_Inf->Area_Data,Area_Inf->Area_Data,Area_Inf->data_len);
  
  //�����������β��
  p->next_Area_Inf=NULL;
  
  //��ӳɹ�
  return true;
}

/**
* @brief ��������IDɾ����̬��
* 
* @param num ����ID
* @return int 
*/
int Delete_Area_Accordingn_ID(int num)
{
  int res = false;
  Area_List_Inf_Typedef *p = Head_Area_List;
  
  while(p->next_Area_Inf!=NULL)
  {
    Area_List_Inf_Typedef *temp = p;
    p = p->next_Area_Inf;
    if(p->Area_Inf->ID == num)//ƥ�䵽��Ӧ��ֵ
    {
      temp->next_Area_Inf = p->next_Area_Inf;
      //�ͷ��ڴ�ռ� 
      free(p->Area_Inf->Area_Data);
      free(p->Area_Inf);
      
      free(p);
      
      p=temp;
      res = true;
    }
  }
  return res;
}

/**
* @brief ��������ID�ҵ�����
* 
* @param data_p ����ָ��
* @param num    ����ID���
* @return int 
*/
int Find_Area_According_ID(Area_Inf_Typedef **data_p,int num)
{
  Area_List_Inf_Typedef *p =  Head_Area_List;
  while(p->next_Area_Inf!=NULL)
  {
    p = p->next_Area_Inf;
    if(p->Area_Inf->ID == num)//ƥ�䵽��Ӧ��ֵ
    {
      *data_p = p->Area_Inf;
      
      return true;
    }
  }
  return false;
}


/**
* @brief ɾ����������
* 
*/
int Delete_All_Area(void)
{
  int res = false;
  Area_List_Inf_Typedef *p =  Head_Area_List;
  while(p->next_Area_Inf!=NULL)
  {
    Area_List_Inf_Typedef *temp = p;
    p = p->next_Area_Inf;
    
    temp->next_Area_Inf = p->next_Area_Inf;
    
    //�ͷ��ڴ�ռ� 
    free(p->Area_Inf->Area_Data);
    free(p->Area_Inf);
    free(p);
    
    p=temp;
    
    res = true;
    
  }
  return res;
} 

/**
* @brief ��ӡ������Ϣ
* 
*/
void Printf_Area_Inf(void)
{
  int i=0;
  Area_List_Inf_Typedef *p =  Head_Area_List;
  printf("list   ID   X   Y   Width   Height   Area_Data\r\n");
  
  while(p->next_Area_Inf!=NULL)
  {
    p = p->next_Area_Inf;
    printf(" %d     %d    %d   %d    %d      %d      %s\r\n",i,p->Area_Inf->ID,p->Area_Inf->X,p->Area_Inf->Y,p->Area_Inf->Width,p->Area_Inf->Height,p->Area_Inf->Area_Data);
    i++;
  }	
  printf("----------------------end-----------------------\r\n");
} 

/**
* @brief ������Ժ���
* 
*/
void list_main()
{
  int i,j;
  Area_Inf_Typedef temp;
  Area_Inf_Typedef **data_p;
  
  data_p = NULL;
  
  
  printf("------------------List test---------------------\r\n"); 
  if(!Area_List_Init( ))
  {
    printf("Memory fail..\r\n");
  }
  
  
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
  }
  
  Printf_Area_Inf();
  
  printf("\r\n-------------Delete ID of Area is 3-------------\r\n");
  Delete_Area_Accordingn_ID(3);
  
  Printf_Area_Inf();
  
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
  printf("\r\n--------------Add ID of Area is 9---------------\r\n");
  Printf_Area_Inf();
  
  Find_Area_According_ID(data_p,2);
  temp.ID = (*data_p)->ID;
  
  Delete_All_Area();
  printf("\r\n--------------Delete All Area-------------------\r\n");
  
  Printf_Area_Inf();
  
  while(1);
}



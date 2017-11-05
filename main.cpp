#include<iostream>
#include<thread>
#include <fstream>  
#include <ctime>  
#include <windows.h>  
#include <tchar.h>  
#include <sys/timeb.h>  
#include <time.h>  
#include <cmath>  
#include <stdio.h>  
#include "func.h"
using namespace std;

string s="";
void PrintArray(int *array,int size,int*index)  //�ֵ���
{
	for(int i=0;i<size;i++)
	{
		cout<<array[index[i]-1];
	}
	cout<<endl;
}
bool find(int*index,int size)  //�ֵ���
{
	bool match=false;
	int find=-1;
	for(int i=size-1;i>=1;i--)//Ѱ�ҽ�����
	{
		if(index[i]>index[i-1])
		{
			match=true;
			find=i-1;
			break;
		}

	}
	if(!match)
	{
		return false;
	}
	for(int i=size-1;i>find;i--)
	{
		if(index[i]>index[find])//����
		{
			int temp=index[i];
			index[i]=index[find];
			index[find]=temp;
			break;
		}
	}
	int index2[1000];
	for(int i=0;i<1000;i++)//��ʼ��Ϊ0
		index2[i]=0;

	for(int i=find+1;i<=size-1;i++)
	{
		index2[i]=index[i];
	}
	for(int i=find+1;i<=size-1;i++)
	{
		index[i]=index2[find+size-i];
	}
	return  true;

}
void dic(int* array,int size)   //�ֵ���
{
	int index[1000];
	for(int i=0;i<size;i++)//�õ�һ���ֵ�����С������
	{
		index[i]=i+1;
	}
	PrintArray(array,size,index);//�����һ������
	
	while(find(index,size))
	{
		PrintArray(array,size,index);
	}
}

//������
bool End(int *index,int size)//�ж��Ƿ��սᣬ������λ�������,�Ƿ����
{
	for(int i=size-2;i>=0;i--)
	{
		if(index[i]!=i+1)
		{
			return false;
		}
	}
	return true;

}
void plusIndex(int *index,int size)  //������λ����+1
{
	for(int i=0;i<=size-2;i++)
	{
		if(index[i]+1>=i+2)
		{
			index[i]=0;

		}else
		{
			index[i]=index[i]+1;
			break;
		}
	}

}
void PrintArray2(int*array,int*index,int size) //�ɵ�����λ������ӡ��Ӧ����
{
	int Kong[1000];
	for(int i=0;i<1000;i++)
	{
		Kong[i]=-1;
	}
	for(int i=size-2;i>=0;i--)
	{
		int num=0;
		for(int j=0;j<size;j++)
		{
			if(num==index[i])
			{
				while(Kong[j]!=-1)
				{
					j++;
				}
				Kong[j]=array[i+1];
				break; //�ҵ���λ֮������ѭ��
			}
			if(Kong[j]==-1)
			{
				num++;
			}
			
		}
	}
	for(int i=0;i<size;i++)
	{
		if(Kong[i]==-1)
		{
			Kong[i]=array[0];
			break;
		}
	}
	for(int i=size-1;i>=0;i--)
	{
		cout<<Kong[i];
	}
	cout<<endl;
}

void incre(int*array,int size)//������λ����
{
	int index[1000];
	for(int i=size-2;i>=0;i--)
	{
		index[i]=0;
	}
	int num=0;
	
	PrintArray2(array,index,size);
	while(!End(index,size))
	{
		plusIndex(index,size); //��λ����+1
		PrintArray2(array,index,size);

	}
}



//���̷߳� ����n���̵߳ĵ�����λ�Ʒ�
void PrintArray3(int*array,int*index,int size) //�ɵ�����λ������ӡ��Ӧ����
{
	int Kong[1000];
	for(int i=0;i<1000;i++)
	{
		Kong[i]=-1;
	}
	for(int i=size-2;i>=0;i--)
	{
		int num=0;
		for(int j=0;j<size;j++)
		{
			if(num==index[i])
			{
				while(Kong[j]!=-1)
				{
					j++;
				}
				Kong[j]=array[i+1];
				break; //�ҵ���λ֮������ѭ��
			}
			if(Kong[j]==-1)
			{
				num++;
			}
			
		}
	}
	for(int i=0;i<size;i++)
	{
		if(Kong[i]==-1)
		{
			Kong[i]=array[0];
			break;
		}
	}
	for(int i=size-1;i>=0;i--)
	{
		char a[8];
		_itoa_s(Kong[i],a,10);
		s+=a[0];
		if(a[1]!='\0')
		{
			s+=a[1];
		}
	}
	s+='\n';
}
bool End_Thread(int *index,int size,int *end)//�ж��Ƿ��սᣬ������λ�������,�Ƿ����
{
	for(int i=size-2;i>=0;i--)
	{
		if(index[i]!=end[i])
		{
			return false;
		}
	}
	return true;

}
void incre_Thread(int*array,int size,int *BeginIndex,int*EndIndex)//������λ����
{
	do{

		PrintArray3(array,BeginIndex,size);
		plusIndex(BeginIndex,size); //��λ����+1
		

	}while(!End_Thread(BeginIndex,size,EndIndex));
}

void thread_incre(int*array,int size)
{
	int index=1000;
	int n=2; //�������̵߳���Ŀ ���Ϊ size-1
	int thread_num=n+1;  
	int End[10][100];
	for(int i=size-2;i>=0;i--) //������ʼ����ֹ��index
	{
		End[0][i]=0;
		End[thread_num-1][i]=i+1;
	}

	int begin=int((size-2)/(thread_num-2));
	for(int i=1;i<thread_num-1;i++)
	{
		End[i][size-2]=begin;
		begin=begin+int((size-2)/(thread_num-2));

	}
	for(int i=1;i<thread_num-1;i++)
	{
		for(int j=size-3;j>=0;j--)
		{
			End[i][j]=0;
		}
	}
	for(int i=0;i<thread_num-1;i++) //�������߳�
	{
		thread t1(incre_Thread,array,size,End[i],End[i+1]);
		t1.join();
	}
	PrintArray3(array,End[thread_num-1],size);
	cout<<s.c_str();
	s="";

}

int main()
{
	//����Ҫ��������
	int A[100];
	int n;
	int end=1;
	while(end)
	{
		cout<<"������Ҫ���е�����n��"<<endl;
		cin>>n;
		N=n;
		for (int i = 1 ; i <= N ; i ++)
		{ 
			num[i] = N+1-i;
			mid_num[i] = 0;
			mid_next[i] = 0;
		}
		if(n>=100)
		{

			cout<<"�������ݹ���"<<endl;
			system("pause");
			return 0;
		}
		for(int i=1;i<=n;i++)
		{
			A[i-1]=i;

		}
		cout<<"�����뷽�� 1���ֵ���  2��������  3�� �ݼ���  4��������   5�����̷߳�"<<endl;
		int choice;
		cin>>choice;
		 DWORD start, end;  
		start = GetTickCount(); 
		switch(choice)
		{
			case 1:		
				dic(A,n);
				break;
			case 2:
				incre(A,n);
				break;
			case 3:
				jian();
				break;
			case 4:
				change();
				break;
			case 5:
				thread_incre(A,n);
				break;
			default:
				cout<<"û�����ַ�����";
		}
		 end = GetTickCount();
		cout<<"����ʱ�䣺"<<end-start<<" ms"<<endl;
		cout<<"����1����������0����"<<endl;
		cin>>end;
	}
	system("pause");
	return 0;

}

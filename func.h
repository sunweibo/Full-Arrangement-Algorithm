#include <iostream>
using namespace std;
int N , num[15];	//ȫ���о��� 1�Ǹ�λ
int mid_num[15] , mid_next[15];	//�н�������һ���н��� 

void calu_mid_num_jian()	//����ݼ���λ���н��� 
{
	//for (int i = n ; i >= 2 ; i--)
	//{
	//	int temp_small = 0;	//i���ұ߱�iС�����ָ���
	//	for (int j = i - 1 ; j >= 1 ; j --)
	//	{
	//		if (num[j] < num[i])
	//			temp_small ++;
	//	}
	//	mid_num[num[i]] = temp_small;	//index=2���Ǹ�λ��������2��index=n���ǵ�λ��������n 
	//}
	for (int i = 2; i <= N; i++)
	{
		int indexnum = 0;
		for (int j = 1; j <= N; j++)
		{
			if (num[j] == i)
			{
				indexnum = j;
				break;
			}
		}
		int temp_small = 0;	
		for (int j = indexnum ; j >= 1 ; j --)
		{
			if (num[j] < num[indexnum])
				temp_small ++;
		}
		mid_num[i] = temp_small;	//index=2���Ǹ�λ��������2��index=n���ǵ�λ��������n 
	}
	
}

void calu_mid_num_next()	//������һ���н��� 
{
	//for (int i = 1; i <= n; i++)
	//{
	////	mid_num[i] = 0;
	//	mid_next[i] = 0;
	//}
	if (mid_num[N] + 1 < N)	//���λ����Ҫ��λ 
	{
		mid_next[N] =  mid_num[N] + 1;
		for(int i = N - 1 ; i >= 2 ; i--)
			mid_next[i] = mid_num[i];
	}
	else
	{
		mid_next[N] = 1;	//��λ��� 
		for(int i = N ; i >= 2 ; i--)
		{
			if(mid_num[i] + mid_next[i] >= i)
			{
				mid_next[i] = 0;	//��λ֮����һλ��0��
				mid_next[i-1] = 1; 	//��һλ�и���λ��� 
			}
			else
			mid_next[i] =  mid_num[i] + mid_next[i];	//	û��λ�Ļ���һλ����ԭ���� 
		}
	}

}

void calu_next_num_jian()	//���н�������ݼ���λ�Ƶ���һ������ 
{
	for (int i = 1 ; i <= N ; i++)
		num[i] = 0;
	for(int i = N ; i >= 2 ; i--)
	{
		int num_zero = 0;	//��λ�������ҵ���ʼѰ�ҿ�λ 
		for (int j = N ; j >= 1 ; j --)
		{
			if(num[j] == 0)
				num_zero ++;
			if(num_zero == mid_next[i] + 1)
			{
				num[j] = i;
				break;
			} 
		}
	}
	for(int i = N ; i >= 1 ; i--)	//����ٰ�1���ȥ 
	{
		if (num[i] == 0)
		{
			num[i] = 1;
			break;
		}
	}
	
	for (int i = 1; i <= N/2; i++)	//��תһ��
	{
		int temp = num[i];
		num[i] = num[N + 1 - i];
		num[N + 1 - i] = temp;
	}
}

void calu_mid_num_exchange()	//��λ�Ի��н��� 
{
	for(int i = 2 ; i <= N ; i ++)
	{
		int index_i = 0;	//���ҵ�i��λ�� 
		for(int j = 1 ; j <= N ; j ++)
		{
			if(num[j] == i)
			{
				index_i = j;
				break;
			} 
		}
		
		int num_small = 0;	//С�ĸ��� 
		if (i == 2)	//2�ķ���������������������index��С�ķ��� 
		{
			for(int j = index_i ; j >= 1 ; j --)
			{
				if (num[j] < i)
					num_small ++;
			}
		}
		else if (i % 2 == 1)	//i���� 
		{
			if(mid_num[i-1] % 2 == 1)	//i-1 ���������ң�����������index���� 
			{
				for(int j = index_i ; j <= N ; j ++)
				{
					if (num[j] < i)
						num_small ++;
				} 
			} 
			else	//i-1 ż������������������index��С 
			{
				for(int j = index_i ; j >= 1 ; j --)
				{
					if (num[j] < i)
						num_small ++;
				}
			}
		} 
		else	//iż�� 
		{
			if((mid_num[i-1]+mid_num[i-2]) % 2 == 1)	//���������ң�����������index����
			{
				for(int j = index_i ; j <= N ; j ++)
				{
					if (num[j] < i)
						num_small ++;
				} 
			} 
			else	//ż������������������index��С
			{
				for(int j = index_i ; j >= 1 ; j --)
				{
					if (num[j] < i)
						num_small ++;
				}
			}
		} 
		mid_num[i] = num_small;
	} 
} 

void calu_next_num_exchange()	//���н���������λ�Ի�����һ������
{
	for (int i = 1 ; i <= N ; i++)
		num[i] = 0;
	for (int i = N ; i >= 3 ; i --)
	{
		int num_zero = 0;	//��λ��
		if (i % 2 == 1)	//i���� 
		{
			if(mid_next[i-1] % 2 == 1)	//i-1 ���������ң�index���� 
			{
				for(int j = 1 ; j <= N ; j ++)
				{
					if (num[j] == 0)
						num_zero ++;
					if(num_zero == mid_next[i] + 1)
					{
						num[j] = i;
						break;
					} 
				} 
			} 
			else	//i-1 ż��������index��С 
			{
				for(int j = N ; j >= 1 ; j --)
				{
					if (num[j] == 0)
						num_zero ++;
					if(num_zero == mid_next[i] + 1)
					{
						num[j] = i;
						break;
					} 
				} 
			}
		} 
		else	//iż��
		{
			if((mid_next[i-1]+mid_next[i-2]) % 2 == 1) //���������ң�index���� 
			{
				for(int j = 1 ; j <= N ; j ++)
				{
					if (num[j] == 0)
						num_zero ++;
					if(num_zero == mid_next[i] + 1)
					{
						num[j] = i;
						break;
					} 
				}
			}
			else	//ż��������index��С 
			{
				for(int j = N ; j >= 1 ; j --)
				{
					if (num[j] == 0)
						num_zero ++;
					if(num_zero == mid_next[i] + 1)
					{
						num[j] = i;
						break;
					} 
				} 
			}
		}
	} 
	int num_zero = 0;	//��λ��
	for(int j = N ; j >= 1 ; j --)	//��2�Ž�ȥ 
	{
		if (num[j] == 0)
			num_zero ++;
		if(num_zero == mid_next[2] + 1)
		{
			num[j] = 2;
			break;
		} 
	} 
	for(int i = N ; i >= 1 ; i--)	//����ٰ�1���ȥ 
	{
		if (num[i] == 0)
		{
			num[i] = 1;
			break;
		}
	}
	for (int i = 1; i <= N / 2; i++)	//��תһ��
	{
		int temp = num[i];
		num[i] = num[N + 1 - i];
		num[N + 1 - i] = temp;
	}
}

void print_array()
{
	for (int i = N ; i >= 1 ; i --)
		cout << num[i] << ' ';
	cout << endl;
}

int pailie[10] = {0,1,2,6,24,120,720,5040,40320,362880};
void jian()
{
	print_array();
	for (int i = 1 ; i < pailie[N] ; i ++)
	{
		calu_mid_num_jian();
		calu_mid_num_next();
		calu_next_num_jian();
		print_array();
	}
}

void change()
{
	print_array();
	for (int i = 1; i < pailie[N]; i++)
	{
		calu_mid_num_exchange();
		calu_mid_num_next();
		calu_next_num_exchange();
		print_array();
	}
}
/*

int main()
{
	cin >> N;
	for (int i = 1 ; i <= N ; i ++)
	{ 
		num[i] = N+1-i;
		mid_num[i] = 0;
		mid_next[i] = 0;
	}

//	jian();
	change();
	system("pause"); 
	return 0;
}
*/
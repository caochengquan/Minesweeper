#include <iostream>
#include <time.h>
using namespace std;

#define Bomb 9

int Star = 1;

//��ͼ
void Draw(int **pMap,int **pState,int line,int row,int bombnum)
{
	for (int k = 0; k < row; k++)
		cout << " " << k;
	cout << "\t�׵�����:" << bombnum << endl;
	//cout << endl;
	for (int i = 0; i < line; i++)
	{
		cout << i;
		for (int j = 0; j < row; j++)
		{
			switch (pState[i][j])
			{
			case 0:
				cout << "��";
				break;
			case 1:
				if (0 == pMap[i][j])
					cout << "  ";
				else
					cout << " " << pMap[i][j];
				break;
			}
		}
		cout << endl;
	}
}

//����
void Planted(int **pMap,int line,int row)
{
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < row; j++)
		{
			int x = rand() % line, y = rand() % row, t;
			t = pMap[x][y], pMap[x][y] = pMap[i][j], pMap[i][j] = t;
		}
	}
}

//��
void Click(int **pMap, int **pState, int line,int row,int x, int y)
{
	//����㿪�Ĳ�����
	if (pMap[x][y] != Bomb && !pState[x][y])
	{	
			//��
			pState[x][y] = 1;
			for (int i = x - 1, Number = 0; i <= x + 1; i++)
			{
				for (int j = y - 1; j <= y + 1; j++)
				{
					//�߽��ж�
					if (i >= 0 && i < line&&j >= 0 && j < row)
					{
						if (1 == pState[i][j])
							continue;
						//ը������
						if (pMap[i][j] == Bomb)
						{
							Number += 1;
							pMap[x][y] = Number;
						}
					}
				}
			}

			if (0 == pMap[x][y] && x >= 0 && x < line && y >= 0 && y < row)
			{
				//�ݹ�
				for (int i = x - 1; i <= x + 1; i++)
				{
					for (int j = y - 1; j <= y + 1; j++)
					{
						if (i >= 0 && i < line && j >= 0 && j < row)
							Click(pMap, pState,line,row,i, j);
					}
				}
			}

			
	}
	else if (pMap[x][y] == Bomb)
	{
		cout << "��ȵ�����,��Ϸ����" << endl;
		Star = 0;
		system("pause");
	}


}




int main()
{
	srand(time(NULL));

	int line, row,bombnum;
	cout << "����������Ĵ�С" << endl;
	cin >> line >> row;
	cout << "������ը������" << endl;
	cin >> bombnum;

	//�����ͼ����
	int **pMap = new int*[line];
	//����״̬����
	int **pState = new int*[line];
	for (int i = 0; i < line; i++)
	{
		pMap[i] = new int[row];
		pState[i] = new int[row];
	}

	//��ʼ������
	for (int i = 0 ,num=bombnum; i < line; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if (num>0)
			{
				pMap[i][j] = Bomb;
				num--;
			}
			else
			{
				pMap[i][j] = 0;
			}
			pState[i][j] = 0;
		}
	}

	Planted(pMap, line, row);


	while (Star)
	{
		Draw(pMap,pState,line,row,bombnum);
		cout << "������Ҫ����������:" << endl << "�� ��" << endl;
		int x, y;
		cin >> x >> y;
		if (x >= 0 && x < line&&y >= 0 && y < row)
		Click(pMap, pState,line,row,x, y);

		system("CLS");
	}


	//�ͷ�:
	for (int i = 0; i < line; i++)
	{
		delete[] pState[i];
		delete[] pMap[i];
	}
	delete[]pState;
	delete[]pMap;


	return 0;
}
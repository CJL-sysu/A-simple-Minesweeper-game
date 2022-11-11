#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<ctime>
#include<fstream>
#define Jin '#'
#define Jia '+'
using namespace std;
char** gra = NULL;
int** arr = NULL;
int** ar = NULL;//初始化二维数组的指针为全局变量
void file(int m, unsigned int time)
{
	ofstream ofs;
	ofs.open("BoomData.txt", ios::app);
	if (m == 0)
		ofs << "游戏失败,用时" << time << "秒" << endl;
	else
		ofs << "游戏成功,用时" << time << "秒" << endl;
	ofs.close();
}
int kopen(int x,int y)//快捷标记打开函数
{
	void open(int x, int y);
	void open1(int x, int y);
	if (gra[x][y] == Jia)
		return 0;
	else
	{
		if (arr[x][y] == 9)
			return 1;//发现有雷
		else if (ar[x][y] == 0)
			open(x, y);
		else
			open1(x, y);
		return 0;
	}
}
void open1(int x, int y)//遇到非0的函数实现
{
	gra[x][y] = ar[x][y] + 48;
}
void open(int x, int y)
{
	gra[x][y] = ar[x][y] + 48;//生成数字，展示在屏幕上
	if (ar[x - 1][y] == 0 && gra[x - 1][y] == Jin)
		open(x - 1, y);
	if (ar[x][y - 1] == 0 && gra[x][y - 1] == Jin)
		open(x, y - 1);
	if (ar[x][y + 1] == 0 && gra[x][y + 1] == Jin)
		open(x, y + 1);
	if (ar[x + 1][y] == 0 && gra[x + 1][y] == Jin)
		open(x + 1, y);
	if (ar[x - 1][y - 1] == 0 && gra[x - 1][y - 1] == Jin)
		open(x - 1, y - 1);
	if (ar[x - 1][y + 1] == 0 && gra[x - 1][y + 1] == Jin)
		open(x - 1, y + 1);
	if (ar[x + 1][y - 1] == 0 && gra[x + 1][y - 1] == Jin)
		open(x + 1, y - 1);
	if (ar[x + 1][y + 1] == 0 && gra[x + 1][y + 1] == Jin)
		open(x + 1, y + 1);
	//遇到0时自动开启周围八格，并且开启的部分继续开启周围八格
	if (ar[x - 1][y] > 0 && ar[x - 1][y] < 9 && gra[x - 1][y] == Jin)
		open1(x - 1, y);
	if (ar[x][y - 1] > 0 && ar[x][y - 1] < 9 && gra[x][y - 1] == Jin)
		open1(x, y - 1);
	if (ar[x][y + 1] > 0 && ar[x][y + 1] < 9 && gra[x][y + 1] == Jin)
		open1(x, y + 1);
	if (ar[x + 1][y] > 0 && ar[x + 1][y] < 9 && gra[x + 1][y] == Jin)
		open1(x + 1, y);
	if (ar[x - 1][y - 1] > 0 && ar[x - 1][y - 1] < 9 && gra[x - 1][y - 1] == Jin)
		open1(x - 1, y - 1);
	if (ar[x - 1][y + 1] > 0 && ar[x - 1][y + 1] < 9 && gra[x - 1][y + 1] == Jin)
		open1(x - 1, y + 1);
	if (ar[x + 1][y - 1] > 0 && ar[x + 1][y - 1] < 9 && gra[x + 1][y - 1] == Jin)
		open1(x + 1, y - 1);
	if (ar[x + 1][y + 1] > 0 && ar[x + 1][y + 1] < 9 && gra[x + 1][y + 1] == Jin)
		open1(x + 1, y + 1);
	//遇到非0时自动开启周围八格，不允许开启的部分继续开启周围八格
}
void printgraph(int n)//用于打印游戏界面
{
	system("cls");
	for (int i = 0; i <= n; i++)
		cout << setw(2) << setfill('0') << i << " ";
	cout << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << setw(2) << setfill('0') << i << "  ";
		for (int j = 1; j <= n; j++)
		{
			cout << gra[i][j] << "  ";
		}
		if (i == 1)
			cout << "   操作'1'代表标记安全";
		if (i == 2)
			cout << "   操作'2'代表标记有雷";
		if (i == 3)
			cout << "   操作'3'取消标记有雷";
		if (i == 4)
			cout << "   操作'4'快捷标记安全（自动标记周围八格）";
		cout << endl;
	}
	cout << "请输入:(用空格隔开)" << endl;
	cout << "行 列 操作" << endl;
}
void game(int n, int boom)
{
	srand((unsigned int)time(NULL));
	unsigned int gametimestart = (unsigned int)time(NULL);//记录游戏开始的时间
	cout << "游戏正在加载中，请等待" << endl;
	arr = new int*[n+2];
	for (int i = 0; i < n+2; i++)
		arr[i] = new int[n+2];//定义二维数组arr
	ar = new int* [n + 2];
	for (int i = 0; i < n + 2; i++)
		ar[i] = new int[n + 2];//定义二维数组ar
	for (int i = 0; i < n + 2; i++)
	{
		arr[0][i] = 10;
		arr[n + 1][i] = 10;
		arr[i][0] = 10;
		arr[i][n + 1] = 10;//初始化边缘无雷
		ar[0][i] = 10;
		ar[n + 1][i] = 10;//10表示无雷
		ar[i][0] = 10;
		ar[i][n + 1] = 10;
	}
	vector<int>v;
	v.resize(n * n, 10);
	for (vector<int>::iterator it = v.begin(); it < v.begin() + boom; it++)
		*it = 9;//9表示有雷
	random_shuffle(v.begin(),v.end());//随机生成n个位置夹杂boom个雷的排列
	for (int i = 0; i < n * n; i++)
		arr[i / n + 1][i % n + 1] = v[i];//将雷填充入二维数组arr
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)//遍历二维数组arr每个位置
		{
			if (arr[i][j] == 9)//如果是雷，遍历下一个位置
				ar[i][j] = 9;
			else
			{
				ar[i][j] = arr[i][j] + arr[i - 1][j - 1] + arr[i - 1][j] + arr[i - 1][j + 1]
					+ arr[i][j - 1] + arr[i][j + 1] + arr[i + 1][j - 1] + arr[i + 1][j]
					+ arr[i + 1][j + 1];
				ar[i][j] = 90 - ar[i][j];//如果不是雷，计算其周边八格雷的个数，并赋值给ar
			}
		}
	}
	gra = new char* [n + 2];
	for (int i = 0; i < n + 2; i++)
		gra[i] = new char[n + 2];//定义用于显示游戏页面的二维数组gra
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			gra[i][j] = Jin;//初始化用Jin填充
		}
	}
	int x, y, z, m1 = 0,right=0;
	another:
	printgraph(n);
	cin >> x >> y >> z;//输入三数以操作
	if (!(x >= 1 && x <= n && y >= 1 && y <= n))
	{
		cout << "输入坐标错误" << endl;
		system("pause");
		goto another;
	}
	if (z == 1 && gra[x][y] == Jin)
	{
		if (ar[x][y] == 10)
			return;
		if (ar[x][y] == 9)
		{
			fail:
			system("cls");//此处游戏失败，显示所有的雷
			unsigned int gametimeend = (unsigned int)time(NULL);
			for (int i = 0; i <= n; i++)
				cout << setw(2) << setfill('0') << i << " ";
			cout << endl;
			for (int i = 1; i <= n; i++)
			{
				cout << setw(2) << setfill('0') << i << "  ";
				for (int j = 1; j <= n; j++)
				{
					if (ar[i][j] == 9)
						cout << '*' << "  ";
					else
						cout << ar[i][j] << "  ";
				}
				cout << endl;
			}
			unsigned int gametime = gametimeend - gametimestart;
			cout << "你没了" << endl;
			cout << "本次游戏用时" << gametime << "秒" << endl;//输出游戏时间
			file(0, gametime);//游戏记录写入文件
			return;
		}
		else
		{
			gra[x][y] = ar[x][y] + 48;
			if (ar[x][y] == 0)
			{
				open(x, y);
			}
		}
	}
	else if (z == 2 && gra[x][y] == Jin)
	{
		gra[x][y] = Jia;
		m1++;
		right = (ar[x][y] == 9) ? (right + 1) : right;
	}
	else if (z == 3 && gra[x][y] == Jia)
	{
		gra[x][y] = Jin;
		m1--;
		right = (ar[x][y] == 9) ? (right - 1) : right;
	}
	else if (z == 4 && gra[x][y] != Jin && gra[x][y] != Jia)//快捷标记安全实现
	{
		int jnum=0;
		jnum = (gra[x - 1][y - 1] == Jia ? jnum + 1 : jnum);
		jnum = (gra[x - 1][y] == Jia ? jnum + 1 : jnum);
		jnum = (gra[x - 1][y + 1] == Jia ? jnum + 1 : jnum);
		jnum = (gra[x][y - 1] == Jia ? jnum + 1 : jnum);
		jnum = (gra[x][y + 1] == Jia ? jnum + 1 : jnum);
		jnum = (gra[x + 1][y - 1] == Jia ? jnum + 1 : jnum);
		jnum = (gra[x + 1][y] == Jia ? jnum + 1 : jnum);
		jnum = (gra[x + 1][y + 1] == Jia ? jnum + 1 : jnum);//统计周围标记有雷点个数
		if (jnum != ar[x][y])
		{
			cout << "不符合快捷标记条件，周围标记雷数与实际雷数不等" << endl;
			system("pause");
		}
		else
		{
			int failnum=0;//检查是否踩雷
			failnum += kopen(x - 1, y - 1);
			failnum += kopen(x - 1, y);
			failnum += kopen(x - 1, y + 1);
			failnum += kopen(x, y - 1);
			failnum += kopen(x, y + 1);
			failnum += kopen(x + 1, y - 1);
			failnum += kopen(x + 1, y);
			failnum += kopen(x + 1, y + 1);
			if (failnum != 0)
				goto fail;
		}
	}
	if (m1 == boom&&right==boom)//采用m1(标记点个数)和right(正确点个数)判断是否赢了
	{
		printgraph(n);
		cout << "你赢了" << endl;
		unsigned int gametimeend = (unsigned int)time(NULL);
		unsigned int gametime = gametimeend - gametimestart;//输出游戏时间
		cout << "本次游戏用时" << gametime << "秒" << endl;
		file(1, gametime);//游戏记录写入文件
		return;
	}
	goto another;
}
int main()
{
	system("color 3F");
	system("title 扫雷3.0");
	int choose, n, boom;
home:
	system("cls");
	cout << "*******************" << endl;
	cout << "******扫雷游戏*****" << endl;
	cout << "版本号2022.1105.3.0" << endl;
	cout << "Copyright: CJL_sysu" << endl;
	cout << "****1、开始游戏****" << endl;
	cout << "****2、退出游戏****" << endl;
	cout << "****3、排位赛******" << endl;
	cout << "****4、排行榜******" << endl;
	cout << "****5、游戏记录****" << endl;
	cout << "****6、游戏会员****" << endl;
	cout << "*******************" << endl;
	cin >> choose;
	switch (choose)
	{
	case 1:
	{
		inp1:
		cout << "请输入雷区边长" << endl;
		cin >> n;
		if (n <= 3)
		{
			cout << "雷区边长不合法" << endl;
			goto inp1;
		}
		inp2:
		cout << "请输入地雷个数" << endl;
		cin >> boom;
		if (boom > n * n)
		{
			cout << "地雷数量过多" << endl;
			goto inp2;
		}
		game(n, boom);
		system("pause");
		goto home;
	}
	case 2:
	{
		break;
	}
	case 3:
	case 4:
	{
		cout << "开通游戏会员以使用该功能" << endl;
		cout << "开通会员请在疯狂星期四微CJL￥50" << endl;
		system("pause");
		goto home;
	}
	case 5:
	{
		ifstream ifs;
		ifs.open("BoomData.txt", ios::in);
		if (!ifs.is_open())
		{
			cout << "无历史记录" << endl;
			system("pause");
			goto home;
		}
		char buf[1024] = { 0 };
		while (ifs >> buf)
			cout << buf << endl;//按行读取
		ifs.close();
		system("pause");
		goto home;
	}
	case 6:
	{
		cout << "Please V CJL 50 during crazy Thursday!" << endl;
		system("mspaint 开通会员.jpg");
		system("pause");
		goto home;
	}
	default:
		goto home;
	}
	return 0;
}

#include <iostream>
#include <iomanip> 
#include <string>
using namespace std;

const int WARRIOR_NUM = 5;

class Warriors
{
public:
	Warriors(int strength, int kindNO);
	static int WarriorsLife[WARRIOR_NUM];  //武士生命值，按编号

private:
	int no;
	int kindNo;  //种类编号
};

int Warriors::WarriorsLife[WARRIOR_NUM] = { 0 };

Warriors::Warriors(int no, int kindNo)
{
	this->no = no;  // 当前武士编号
	this->kindNo = kindNo;  // 武士编号
}

class Headquarter
{
public:
	Headquarter(int color, int lifeVlaue);  // 根据颜色和生命值创建司令部
	~Headquarter();
	void Making(int time);  // 根据时间生产武士
	bool getStopState();    // 返回是否停止生产
	string getColorByNo(int color);  // 通过数值获取当前司令部颜色

private:
	int lifeValue;   // 司令部生命值
	static int bornSequence[2][WARRIOR_NUM];
	int color;
	int totalWarriors;  //生产的武士总数
	int warriorNum[WARRIOR_NUM];  // 当前种类武士数量
	Warriors *pWarriors[100];     // 假设最多生产100个武士
	bool isStoped;
	int sequence;  // 生产编号
	static string warriorName[WARRIOR_NUM];  // 武士名称

};

int Headquarter::bornSequence[2][WARRIOR_NUM] = { { 2, 3, 4, 1, 0 }, { 3, 0, 1, 2, 4 } };
string Headquarter::warriorName[WARRIOR_NUM] = { "dragon", "ninja", "iceman", "lion", "wolf" };

Headquarter::Headquarter(int color, int lifeValue)
{
	this->lifeValue = lifeValue;
	this->color = color;
	totalWarriors = 0;
	for (int i = 0; i < WARRIOR_NUM; i++)
	{
		warriorNum[i] = 0;
	}
	isStoped = false;
	sequence = 0;
}

Headquarter::~Headquarter()
{
	for (int i = 0; i < totalWarriors; i++)
	{
		delete pWarriors[i];
	}
}

string Headquarter::getColorByNo(int color)
{
	if (color == 0)
	{
		return "red";
	}
	else
	{
		return "blue";
	}
}

void Headquarter::Making(int time)
{
	if (isStoped)
	{
		return;
	}

	int times = 0;
	while (Warriors::WarriorsLife[bornSequence[color][sequence]] > lifeValue  && times < WARRIOR_NUM)
	{
		sequence = (sequence + 1) % WARRIOR_NUM;
		times++;
	}

	int kindNo = bornSequence[color][sequence];
	if (Warriors::WarriorsLife[kindNo] > lifeValue)  // 未找到生命元小于lifeValue的武士
	{
		isStoped = true;
		if (color == 0)
		{
			printf("%03d red headquarter stops making warriors\n", time);
		}
		else
			printf("%03d blue headquarter stops making warriors\n", time);
		return;
	}
	lifeValue -= Warriors::WarriorsLife[kindNo];
	sequence = (sequence + 1) % WARRIOR_NUM;
	pWarriors[totalWarriors] = new Warriors(totalWarriors + 1, kindNo);
	warriorNum[kindNo]++;
	printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
		time,
		getColorByNo(color).c_str(),
		warriorName[kindNo].c_str(),
		++totalWarriors,
		Warriors::WarriorsLife[kindNo],
		warriorNum[kindNo],
		warriorName[kindNo].c_str(),
		getColorByNo(color).c_str());
	return;
}

bool Headquarter::getStopState()
{
	return isStoped;
}

int main()
{
	int dataNum;
	cin >> dataNum;
	int cases = 1;
	while (dataNum--)
	{
		int lifeValue = 0;
		cin >> lifeValue;
		for (int i = 0; i < WARRIOR_NUM; i++)
		{
			cin >> Warriors::WarriorsLife[i];
		}
		Headquarter red(0, lifeValue), blue(1, lifeValue);
		cout << "Case:" << cases++ << endl;
		int times = 0;
		while (1)
		{
			red.Making(times);
			blue.Making(times);
			if (red.getStopState() && blue.getStopState())
			{
				break;
			}
			times++;
		}
	}
	return 0;
}

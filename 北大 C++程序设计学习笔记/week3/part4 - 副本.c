#include<iostream>  
#include<iomanip>  
#include<string>  
using namespace std;

class warCraft
{
private:
	int count;
	int time;
	int id;        //current created soilder  
	string color;
	string type[5];
	int life[5];
	int numberofeach[5];
	int totallife;
public:
	warCraft(int totallife_, string c, string t[], int l[]);
	bool generate();
	void printCurrent(bool);
};

warCraft::warCraft(int totallife_, string c, string t[], int l[]) :count(0), id(4), time(0)
{
	totallife = totallife_;
	color = c;
	for (int i = 0; i<5; i++)
	{
		type[i] = t[i];
		life[i] = l[i];
		numberofeach[i] = 0;
	}
}

bool warCraft::generate()
{
	time++;
	//next target  
	id = (id + 1) % 5;      //下一个要造的士兵  
	int t = 0;
	while (totallife - life[(id + t) % 5] < 0 && t < 5)  //一直寻找， 直到无法制造，或者找到可以制造的  
	{
		t++;
	}
	if (t == 5)
	{
		return false;
	}
	else
	{
		id = (id + t) % 5;
		totallife -= life[id];
		count++;
		numberofeach[id]++;
		return true;
	}

}

void warCraft::printCurrent(bool suss)
{
	cout << setw(3) << setfill('0') << time - 1 << " ";                  //输出时间  
	if (suss)

	{
		cout << color << " " << type[id] << " " << count << " born with strength " << life[id] << ",";
		cout << numberofeach[id] << " " << type[id] << " in " << color << " headquarter" << endl;
	}
	else
	{
		cout << color << " headquarter stops making warriors" << endl;
	}
}

int main()
{
	int n;
	cin >> n;
	string redtype[5] = { "iceman", "lion", "wolf", "ninja", "dragon" };
	string bluetype[5] = { "lion", "dragon", "ninja", "iceman", "wolf" };
	int redcycle[] = { 2, 3, 4, 1, 0 };
	int bluecycle[] = { 3, 0, 1, 2, 4 };
	string redcolor = "red";
	string bluecolor = "blue";
	int redlife[5];
	int bluelife[5];

	for (int i = 1; i <= n; i++)
	{
		int M;
		cin >> M;

		int a[5];
		for (int j = 0; j<5; j++)
		{
			cin >> a[j];

		}
		for (int k = 0; k<5; k++)
		{
			redlife[k] = a[redcycle[k]];
			bluelife[k] = a[bluecycle[k]];
		}
		cout << "Case:" << i << endl;
		warCraft red(M, redcolor, redtype, redlife);
		warCraft blue(M, bluecolor, bluetype, bluelife);
		bool r, b;
		int c1 = 0, c2 = 0;
		while (true)
		{
			r = red.generate();
			b = blue.generate();
			if (r){
				red.printCurrent(r);
			}
			else if (c1 == 0)
			{
				red.printCurrent(r);
				c1 = 1;
			}
			if (b){
				blue.printCurrent(b);
			}
			else if (c2 == 0)
			{
				blue.printCurrent(b);
				c2 = 1;
			}
			if (c1 == 1 && c2 == 1)
				break;

		}

	}


}

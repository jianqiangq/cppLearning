#include <iostream>
using namespace std;
class Sample{
public:
	int v;
	Sample(int n) :v(n) { }
	// 在此处补充你的代码
	Sample(const Sample& c)
	{
		cout << "拷贝构造函数" << endl;
		v = c.v * 2;
	}
	
};
int main() {
	Sample a(5);
	Sample b = a;
	cout << b.v << endl;;
	return 0;
}
	Sample(const Sample& c)
	{
		cout << "拷贝构造函数" << endl;
		v = c.v * 2;
	}
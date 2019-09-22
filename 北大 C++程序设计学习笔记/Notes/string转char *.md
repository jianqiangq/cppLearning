#### string转char *

---

```
string str("test");
const char *c1 = str.c_str(); // 第一种方法
const char *c2 = str.data();  // 第二种方法
// 从str的下标0的字符开始,
// 制作一个最长str.length()个字符长度的字符串副本并将其赋值给c3
// 返回值表明实际复制字符串的长度
char *c3 = new char[str.length()+1]; // 第三种方法
size_t length = str.copy(c3, str.length(), 0);
c3[length] = '\0';
cout << c1 << endl;
cout << c2 << endl;
cout << c3 << endl;
delete []c3;

```
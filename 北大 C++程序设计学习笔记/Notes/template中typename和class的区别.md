### template class（类模板）和template function(函数模板)中typename和class的区别
---

声明类模板两种方法  
```
template <class T>
template <typename T>
```
两种声明方式是相同的。但是C++中定义类模板，有种情况必须要使用typename：

A.h
```
class A {
public:
    int a;
};
```

B.h
```
#include "A.h"

class B {
public:
    typedef int Subtype;  //Subtype 为 class B 的内部型别(inner type)
    class A;  //class A 为 class B 中的抽象内部数据类别
};
```

C.h
```
template <class T> 
class MyClass {  // MyClass为类模板
    typename T::Subtype * ptr;
    //必须使用typename，声明Subtype为class T中的一个内部类。
    //T类中必须包含Subtype类别，ptr为指向Subtype(int型)的指针。如果没有关键字typename，Subtype会被当成class T中的一个static成员变量。
    typename T::A *ptr_; 
    //T类中必须包含A这个抽象数据类型(内部类)。ptr_为指向类T中内部类class A的指针。
};
```

main.h
```
#include "MyClass.h"
int main() {
    MyClass<B> myclass;
    return 0;
}
```

**注意，如果要把一个template中的某个标识符号指定为一种类别，就算是意图显而易见，关键字typename也是不能省略的，因此C++的一般规则是，除了使用typename修饰之外，template内的任何标识符号都被视为一个值而不是一个类别(对象)。**

---
再举一个函数模板的例子

```
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class A_ {
private:
    int n;
public:
    A_(int n_): n(n_) { }
    friend ostream & operator<<(ostream &o, const A_ &a);  //流提取运算符重载为友元函数（全局）
};

ostream & operator<<(ostream &o, const A_ &a) {
    o << a.n;
    return o;
}

template <class T>
void PrintVector(const vector<T> &vec){
    int tmp = vec.size();
    if (tmp > 0) {
    	// typename不能少，否则报错use of undeclared identifier 'it'
        typename vector<T>::const_iterator it;
        for(it = vec.begin(); it != vec.end(); it++){
            cout << *it << " ";
        }
        cout << endl;
    }
}

template <class T>
void PrintList(const list<T> &lst){
    int tmp = lst.size();
    if (tmp > 0) {
    	// typename不能少，否则报错use of undeclared identifier 'it'
        typename list<T>::const_iterator it;
        for(it = lst.begin(); it != lst.end(); it++){
            cout << *it << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<int> v;
    list<int> l;
    for(int i = 0; i < 5; i ++ ) {
        v.push_back(i);
        l.push_back(10*i);
    }

    PrintVector(v);
    PrintList(l);
}
```
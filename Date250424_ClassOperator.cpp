#include<iostream>
using namespace std;

/*
运算符重载
对已有的运算符重新进行定义，赋予其另一种功能，以适应不同的数据类型

内置的数据类型的表达式的运算符是不会改变的
不要滥用运算符重载
*/

/*
1.加号+
实现两个自定义数据类型相加的运算
*/
class Person {
public:
    Person() {};
    Person(int a, int b)
    {
        this->m_A = a;
        this->m_B = b;
    }
    //成员函数实现 + 号运算符重载
    Person operator+(const Person& p) {
        Person temp;
        temp.m_A = this->m_A + p.m_A;
        temp.m_B = this->m_B + p.m_B;
        return temp;
    }

    int m_A;
    int m_B;
};

//全局函数实现 - 号运算符重载
Person operator-(const Person& p1, const Person& p2) {
	Person temp(0,0);
	temp.m_A = p1.m_A - p2.m_A;
	temp.m_B = p1.m_B - p2.m_B;
	return temp;
}

//运算符重载 可以发生函数重载 
Person operator+(const Person& p2, int val)  
{
    Person temp;
    temp.m_A = p2.m_A + val;
    temp.m_B = p2.m_B + val;
    return temp;
}

void test() {

    Person p1(10, 10);
    Person p2(20, 20);

    //成员函数方式
    Person p3 = p2 + p1;  //相当于 p2.operaor+(p1)
    cout << "mA:" << p3.m_A << " mB:" << p3.m_B << endl;

    Person p4 = p3 + 10; //相当于 operator+(p3,10)
    cout << "mA:" << p4.m_A << " mB:" << p4.m_B << endl;

    Person p5 = p2-p1;
    cout << "mA:" << p5.m_A << " mB:" << p5.m_B << endl;

}

int main() {
    test();
    system("pause");
    return 0;
}


/*
2.左移<<
可以输出自定义数据类型
只能通过全局函数重载实现
重载座椅运算符配合友元可以实现输出自定义数据类型
*/
class Person {
	friend ostream& operator<<(ostream& out, Person& p);
    //友元 让<<重载可以访问到私有变量成员
public:
	Person(int a, int b)
	{
		this->m_A = a;
		this->m_B = b;
	}

	//成员函数 实现不了  p << cout 不是我们想要的效果
	//void operator<<(Person& p){
	//}

private:
	int m_A;
	int m_B;
};

//全局函数实现左移重载
//ostream对象只能有一个
//语法：返回值类型和参数类型都是ostream&
ostream& operator<<(ostream& cout, Person& p) {
	cout << "a:" << p.m_A << " b:" << p.m_B;
	return cout;
}

void test() {
	Person p1(10, 20);
	cout << p1 << endl << "hello world" << endl; //链式编程
}

int main() {
	test();
	system("pause");
	return 0;
}

/*
3.递增++
实现自定义数据类型的递增运算
*/
class MyInteger {
	friend ostream& operator<<(ostream& out, MyInteger myint);
public:
	MyInteger() {
		m_Num = 0;
	}

	//前置++
	MyInteger& operator++() {
		//先++
		m_Num++;
		//再返回
		return *this;
	}

	//后置++
    //需要在参数列表里添加int类型，来区分前置++和后置++
	MyInteger operator++(int) {
		//先返回
		MyInteger temp = *this; //记录当前本身的值，然后让本身的值加1，但是返回的是以前的值，达到先返回后++；
		m_Num++;
		return temp;//返回复制的对象
	}
private:
	int m_Num;
};

ostream& operator<<(ostream& out, MyInteger myint) {
	out << myint.m_Num;
	return out;
}

//前置++ 先++ 再返回
void test01() {
	MyInteger myInt;
	cout << ++myInt << endl;
	cout << myInt << endl;
}

//后置++ 先返回 再++
void test02() {
	MyInteger myInt;
	cout << myInt++ << endl;
	cout << myInt << endl;
}

int main() {
	test01();
	//test02();
	system("pause");
	return 0;
}


/*
4.赋值=
对自定义类型的属性进行值拷贝
注意：如果类中有属性指向堆区（new），做赋值操作时也会出现深浅拷贝问题

c++编译器至少给一个类添加4个函数：
    a.默认构造函数(无参，函数体为空)
    b.默认析构函数(无参，函数体为空)
    c.默认拷贝构造函数，对属性进行值拷贝
    d.赋值运算符 operator=, 对属性进行值拷贝
*/
class Person
{
public:
	Person(int age)
	{
		//将年龄数据开辟到堆区
		m_Age = new int(age);
	}

	//重载赋值运算符 
	Person& operator=(Person &p)
	{
    	//编译器提供的代码是浅拷贝
		//m_Age = p.m_Age;
        
		if (m_Age != NULL)//先释放
		{
			delete m_Age;
			m_Age = NULL;
		}
		//提供深拷贝 解决浅拷贝的问题
		m_Age = new int(*p.m_Age);//再分配
		return *this;
	}

	~Person()
	{
		if (m_Age != NULL)
		{
			delete m_Age;
			m_Age = NULL;
		}
	}

	//年龄的指针
	int *m_Age;

};


void test01()
{
	Person p1(18);
	Person p2(20);
	Person p3(30);
	p3 = p2 = p1; //连等 赋值操作
	cout << "p1的年龄为：" << *p1.m_Age << endl;
	cout << "p2的年龄为：" << *p2.m_Age << endl;
	cout << "p3的年龄为：" << *p3.m_Age << endl;
}

int main() {
	test01();
	system("pause");
	return 0;
}

/*
5.关系== !=
以让两个自定义类型对象进行对比操作
*/
class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	};

	bool operator==(Person & p)
	{
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator!=(Person & p)
	{
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	string m_Name;
	int m_Age;
};

void test01()
{
	//int a = 0;
	//int b = 0;

	Person a("孙悟空", 18);
	Person b("孙悟空", 18);

	if (a == b)
	{
		cout << "a和b相等" << endl;
	}
	else
	{
		cout << "a和b不相等" << endl;
	}

	if (a != b)
	{
		cout << "a和b不相等" << endl;
	}
	else
	{
		cout << "a和b相等" << endl;
	}
}

int main() {
	test01();
	system("pause");
	return 0;
}


/*
6.函数调用()
由于重载后使用的方式非常像函数的调用，因此称为仿函数
仿函数没有固定写法，非常灵活
*/

class MyPrint
{
public:
	void operator()(string text)//operator()(参数)
	{
		cout << text << endl;
	}
};
void test01()
{
	//重载的（）操作符 也称为仿函数
	MyPrint myFunc;
	myFunc("hello world");
}

class MyAdd
{
public:
	int operator()(int v1, int v2)
	{
		return v1 + v2;
	}
};

void test02()
{
	MyAdd add;
	int ret = add(10, 10);
	cout << "ret = " << ret << endl;
    MyAdd();//匿名对象
	//匿名对象调用  仿函数
	cout << "MyAdd()(100,100) = " << MyAdd()(100, 100) << endl;
}

int main() {
	test01();
	test02();
	system("pause");
	return 0;
}
#include<iostream>
using namespace std;

/*
对象的初始化和清理
*/
/*
1.构造函数和析构函数
默认提供的构造函数和析构函数是空实现
构造函数语法：类名(){}

构造函数，没有返回值也不写void
函数名称与类名相同
构造函数可以有参数，因此可以发生重载
程序在调用对象时候会自动调用构造，无须手动调用,而且只会调用一次
析构函数语法： ~类名(){}

析构函数，没有返回值也不写void
函数名称与类名相同,在名称前加上符号 ~
析构函数不可以有参数，因此不可以发生重载
程序在对象销毁前会自动调用析构，无须手动调用,而且只会调用一次
*/
class Person
{
public:
	Person()//构造函数
	{
		cout << "Person的构造函数调用" << endl;
	}
	~Person()//析构函数
	{
		cout << "Person的析构函数调用" << endl;
	}
};

void test01()
{
	Person p;
}

int main() {
	
	test01();
	system("pause");
	return 0;
}
/*
2.构造函数
两种分类方式：
    按参数分为： 有参构造和无参构造
    按类型分为： 普通构造和拷贝构造
三种调用方式：
?   括号法
?   显示法
?   隐式转换法
*/
class Person {
public:
    //无参（默认）构造函数
    Person() {
        cout << "无参构造函数!" << endl;
    }
    //有参构造函数
    Person(int a) {
        age = a;
        cout << "有参构造函数!" << endl;
    }
    //拷贝构造函数
    Person(const Person& p) {
        age = p.age;
        cout << "拷贝构造函数!" << endl;
    }
    //析构函数
    ~Person() {
        cout << "析构函数!" << endl;
    }
public:
    int age;
};
void test01() {
    Person p; //调用无参构造函数
}
//调用有参的构造函数
void test02() {

    //2.1  括号法，常用
    Person p1(10);
    //Person p2();//调用无参构造函数不能加括号，如果加了编译器认为这是一个函数声明
    //2.2 显式法
    Person p2 = Person(10); 
    Person p3 = Person(p2);
    //Person(10)单独写就是匿名对象  当前行结束之后，马上析构

    //2.3 隐式转换法
    Person p4 = 10; // Person p4 = Person(10); 
    Person p5 = p4; // Person p5 = Person(p4); 
}
int main() {
    test01();
    test02();
    system("pause");
    return 0;
}

/*
3.拷贝构造函数调用
a.使用一个已经创建完毕的对象来初始化一个新对象
b.值传递的方式给函数参数传值
c.以值方式返回局部对象
*/
class Person {
public:
    Person() {
        cout << "无参构造函数!" << endl;
        mAge = 0;
    }
    Person(int age) {
        cout << "有参构造函数!" << endl;
        mAge = age;
    }
    Person(const Person& p) {
        cout << "拷贝构造函数!" << endl;
        mAge = p.mAge;
    }
    //析构函数在释放内存之前调用
    ~Person() {
        cout << "析构函数!" << endl;
    }
public:
    int mAge;
};

void test01() {

    Person man(100); //p对象已经创建完毕
    Person newman(man); //1. 使用一个已经创建完毕的对象来初始化一个新对象
    Person newman2 = man; //等价
    //newman2 = man; //不是调用拷贝构造函数，赋值操作
}

//2. 值传递的方式给函数参数传值 等价Person p1 = p; 两个对象
void doWork(Person p1) {}
void test02() {
    Person p; //无参构造函数
    doWork(p);
}

Person doWork2()
{
    Person p1;
    cout << (int *)&p1 << endl;
    return p1;//3. 以值方式返回局部对象
}
void test03()
{
    Person p = doWork2();//p和p1是同一个对象
    cout << (int *)&p << endl;
}
int main() {
    //test01();
    //test02();
    test03();
    system("pause");
    return 0;
}

/*
4.构造函数调用规则
默认情况下，c++编译器至少给一个类添加3个函数
a．默认构造函数(无参，函数体为空)
b．默认析构函数(无参，函数体为空)
c．默认拷贝构造函数，对属性进行值拷贝

构造函数调用规则如下：
a.如果用户定义有参构造函数，c++不在提供默认无参构造，但是会提供默认拷贝构造
b.如果用户定义拷贝构造函数，c++不会再提供其他构造函数
c.按照无参、有参、拷贝的顺序，有其中一个前面的函数就不提供了
*/
// class Person {
// public:
//     //无参（默认）构造函数
//     Person() {
//         cout << "无参构造函数!" << endl;
//     }
//     //有参构造函数
//     Person(int a) {
//         age = a;
//         cout << "有参构造函数!" << endl;
//     }
//     //拷贝构造函数
//     Person(const Person& p) {
//         age = p.age;
//         cout << "拷贝构造函数!" << endl;
//     }
//     //析构函数
//     ~Person() {
//         cout << "析构函数!" << endl;
//     }
// public:
//     int age;
// };

// void test01()
// {
//     Person p1(18);
//     //如果不写拷贝构造，编译器会自动添加拷贝构造，并且做浅拷贝操作
//     Person p2(p1);

//     cout << "p2的年龄为： " << p2.age << endl;
// }

// void test02()
// {
//     //如果用户提供有参构造，编译器不会提供默认构造，会提供拷贝构造
//     Person p1; //此时如果用户自己没有提供默认构造，会出错
//     Person p2(10); //用户提供的有参
//     Person p3(p2); //此时如果用户没有提供拷贝构造，编译器会提供

//     //如果用户提供拷贝构造，编译器不会提供其他构造函数
//     Person p4; //此时如果用户自己没有提供默认构造，会出错
//     Person p5(10); //此时如果用户自己没有提供有参，会出错
//     Person p6(p5); //用户自己提供拷贝构造
// }

// int main() {

//     test01();

//     system("pause");
// }

/*
5.浅拷贝与深拷贝
a.浅拷贝：简单的赋值拷贝操作
b.深拷贝：在堆区重新申请空间，进行拷贝操作
在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的问题
*/
class Person {
public:
    //无参（默认）构造函数
    Person() {
        cout << "无参构造函数!" << endl;
    }
    //有参构造函数
    Person(int age ,int height) {
        cout << "有参构造函数!" << endl;
        m_age = age;
        m_height = new int(height);//在堆区开辟
        
    }
    //拷贝构造函数  
    Person(const Person& p) {
        cout << "拷贝构造函数!" << endl;
        //如果不利用深拷贝在堆区创建新内存，会导致浅拷贝带来的重复释放堆区问题
        m_age = p.m_age;//浅拷贝
        m_height = new int(*p.m_height);//深拷贝
        
    }

    //析构函数
    ~Person() {
        cout << "析构函数!" << endl;
        if (m_height != NULL)
        {
            delete m_height;//浅拷贝会二次释放内存
        }
    }
public:
    int m_age;
    int* m_height;
};

void test01()
{
    Person p1(18, 180);
    Person p2(p1);
    cout << "p1的年龄： " << p1.m_age << " 身高： " << *p1.m_height << endl;
    cout << "p2的年龄： " << p2.m_age << " 身高： " << *p2.m_height << endl;
}

int main() {
    test01();
    system("pause");
    return 0;
}

/*
6.初始化列表
语法：构造函数()：属性1(值1),属性2（值2）... {}
*/
class Person {
public:

    ////传统方式初始化
    //Person(int a, int b, int c) {
    //	m_A = a;
    //	m_B = b;
    //	m_C = c;
    //}

    //初始化列表方式初始化
    Person(int a, int b, int c) :m_A(a), m_B(b), m_C(c) {}
    void PrintPerson() {
        cout << "mA:" << m_A << endl;
        cout << "mB:" << m_B << endl;
        cout << "mC:" << m_C << endl;
    }
private:
    int m_A;
    int m_B;
    int m_C;
};

/*
7.类对象作为类成员
当类中成员是其他类对象时，我们称该成员为 对象成员
构造顺序：先调用对象成员构造，再调用本类构造
析构顺序：先调用本类析构，再调用对象成员析构
*/
class Phone
{
public:
	Phone(string name)
	{
		m_PhoneName = name;
		cout << "Phone构造" << endl;
	}

	~Phone()
	{
		cout << "Phone析构" << endl;
	}

	string m_PhoneName;

};

class Person
{
public:
	Person(string name, string pName) :m_Name(name), m_Phone(pName)
	{
		cout << "Person构造" << endl;
	}
	~Person()
	{
		cout << "Person析构" << endl;
	}
	void playGame()
	{
		cout << m_Name << " 使用" << m_Phone.m_PhoneName << " 牌手机! " << endl;
	}

	string m_Name;
	Phone m_Phone;
};
void test01()
{
	Person p("张三" , "苹果X");
	p.playGame();
}

int main() {
	test01();
	system("pause");
	return 0;
}

/*
8.静态成员
静态成员就是在成员变量和成员函数前加上关键字static，称为静态成员

静态成员分为：
a.静态成员变量
    所有对象共享同一份数据
    在编译阶段分配内存
    类内声明，类外初始化
b.静态成员函数
    所有对象共享同一个函数
    静态成员函数只能访问静态成员变量
*/
class Person
{
	
public:
	static int m_A; //静态成员变量 类内声明
    static void func()
	{
		cout << "func调用" << endl;
		m_A = 100;
		//m_C = 100; //只能访问静态成员变量 不可以访问非静态成员变量
	}
private:
	static int m_B; //静态成员变量也是有访问权限的
    int m_C; //非静态成员变量
};
int Person::m_A = 10;//静态成员变量 类外初始化
int Person::m_B = 10;

void test01()
{
	//静态成员变量两种访问方式
	//1、通过对象
	Person p1;
	p1.m_A = 100;
	cout << "p1.m_A = " << p1.m_A << endl;

	Person p2;
	p2.m_A = 200;
	cout << "p1.m_A = " << p1.m_A << endl; //共享同一份数据
	cout << "p2.m_A = " << p2.m_A << endl;

	//2、通过类名
	cout << "m_A = " << Person::m_A << endl;

    //静态成员变量两种访问方式
	//1、通过对象
	Person p1;
	p1.func();

	//2、通过类名
	Person::func();
}

int main() {
	test01();
	system("pause");
	return 0;
}
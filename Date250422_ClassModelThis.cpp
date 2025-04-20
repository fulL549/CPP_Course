#include<iostream>
using namespace std;

/*
对象模型和this指针
*/

/*
1.成员变量和成员函数分开存储
只有非静态成员变量才属于类的对象上
*/
class Person {
public:
    Person() {
        mA = 0;
    }
    int mA;//非静态成员变量占对象空间
    static int mB; //静态成员变量不占对象空间
    void func() {//函数也不占对象空间，所有函数共享一个函数实例
        cout << "mA:" << this->mA << endl;
    }
    static void sfunc() {//静态成员函数也不占对象空间
    }
};

/*
2.this指针
this指针指向被调用的成员函数所属的对象
this指针是隐含每一个非静态成员函数内的一种指针
this指针不需要定义，直接使用即可
this指针的用途：
    当形参和成员变量同名时，可用this指针来区分
    在类的非静态成员函数中返回对象本身，可使用return *this
*/
class Person
{
public:
	Person(int age)
	{
		this->age = age;//1、当形参和成员变量同名时，可用this指针来区分
	}
	Person& PersonAddPerson(Person p)
	{
		this->age += p.age;
		return *this;//返回对象本身
	}
	int age;
};

void test01()
{
	Person p1(10);
	cout << "p1.age = " << p1.age << endl;
	Person p2(10);
	p2.PersonAddPerson(p1).PersonAddPerson(p1).PersonAddPerson(p1);
	cout << "p2.age = " << p2.age << endl;
}

int main() {
	test01();
	system("pause");
	return 0;
}

/*
3.类的空指针访问成员函数
*/

class Person {
public:
    void ShowClassName() {
        cout << "我是Person类!" << endl;
    }
    void ShowPerson() {
        if (this == NULL) {
            return;
        }
        cout << mAge << endl;
    }
public:
    int mAge;
};

void test01()
{
    Person * p = NULL;
    p->ShowClassName(); //空指针，可以调用成员函数
    p->ShowPerson();  //但是如果成员函数中用到了this指针，就不可以了
}

int main() {
    test01();
    system("pause");
    return 0;
}

/*
4.const修饰成员函数
常函数：
    成员函数后加const后我们称为这个函数为常函数
    常函数内不可以修改成员属性
    成员属性声明时加关键字mutable后，在常函数中依然可以修改
常对象：
    声明对象前加const称该对象为常对象
    常对象只能调用常函数
*/
class Person {
public:
    Person() {
        m_A = 0;
        m_B = 0;
    }
    //this指针的本质是一个指针常量，指针的指向不可修改
    //如果想让指针指向的值也不可以修改，需要声明常函数
    void ShowPerson() const {
        //const Type* const pointer;
        //this = NULL; //不能修改指针的指向 Person* const this;

        //this->m_A = 100; //常函数中this指向的值不可以修改的
        this->m_B = 100; //mutable修饰的变量可以修改
        cout<<m_B<<endl;
    }
    void MyFunc() const {
        cout<<m_A<<endl;
    }
public:
    int m_A;
    mutable int m_B; //可修改 可变的
};

void test01() {
    const Person person; //在声明前加const修饰对象  常对象
    cout << person.m_A << endl;//常对象可以访问成员变量的值
    //person.mA = 100; //常对象不能修改成员变量的值
    person.m_B = 100; //但是常对象可以修改mutable修饰成员变量
    
    person.MyFunc(); //常对象只能调用const常函数
    person.ShowPerson();
}

int main() {
    test01();
    system("pause");
    return 0;
}
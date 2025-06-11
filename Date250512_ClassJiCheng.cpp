#include<iostream>
using namespace std;

/*
4.6 继承
*/

/*
4.6.1 继承的语法

class A : public B;
    A 类称为子类 或 派生类
    B 类称为父类 或 基类

派生类中的成员，包含两大部分：
    一类是从基类继承过来的，一类是自己增加的成员。
    从基类继承过过来的表现其共性，而新增的成员体现了其个性。
*/

/*
4.6.2 继承方式
子类不能访问父类的私有proovate成员
    1. public 继承：基类的public和protected成员在派生类中仍然是public和protected
    2. protected 继承：基类的public和protected成员在派生类中变为protected
    3. private 继承：基类的public和protected成员在派生类中变为private
*/
class Base1
{
public: 
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

//公共继承
class Son1 :public Base1
{
public:
	void func()
	{
		m_A; //可访问 public权限
		m_B; //可访问 protected权限
		//m_C; //不可访问
	}
};

void myClass()
{
	Son1 s1;
	s1.m_A; //其他类只能访问到公共权限
}

//保护继承
class Base2
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son2:protected Base2
{
public:
	void func()
	{
		m_A; //可访问 protected权限
		m_B; //可访问 protected权限
		//m_C; //不可访问
	}
};
void myClass2()
{
	Son2 s;
	//s.m_A; //不可访问
}

//私有继承
class Base3
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son3:private Base3
{
public:
	void func()
	{
		m_A; //可访问 private权限
		m_B; //可访问 private权限
		//m_C; //不可访问
	}
};
class GrandSon3 :public Son3
{
public:
	void func()
	{
		//Son3是私有继承，所以继承Son3的属性在GrandSon3中都无法访问到
		//m_A;
		//m_B;
		//m_C;
	}
};

/*
4.6.3 继承中的对象模型
从父类继承过来的成员，私有成员会被隐藏无法访问（在内存中还是继承下去了）
*/

/*
4.6.4 继承中的构造和析构顺序
构造顺序：父类，再子类
析构顺序：子类，再父类
*/

/*
4.6.5 继承同名成员处理方式
直接访问：会调用到子类的成员
添加作用域，才可以访问到父类的成员（即子类隐藏了父类的成员函数）
*/
class Base {
public:
	Base()
	{
		m_A = 100;
	}
	void func()
	{
		cout << "Base - func()调用" << endl;
	}
	void func(int a)
	{
		cout << "Base - func(int a)调用" << endl;
	}
public:
	int m_A;
};

class Son : public Base {
public:
	Son()
	{
		m_A = 200;
	}
	//当子类与父类拥有同名的成员函数，子类会隐藏父类中所有版本的同名成员函数
	//如果想访问父类中被隐藏的同名成员函数，需要加父类的作用域
	void func()
	{
		cout << "Son - func()调用" << endl;
	}
public:
	int m_A;
};

int main() {
	Son s;
	cout << "Son下的m_A = " << s.m_A << endl;
	cout << "Base下的m_A = " << s.Base::m_A << endl;
	s.func();
	s.Base::func();
	s.Base::func(10);

	system("pause");
	return EXIT_SUCCESS;
}

/*
4.6.6 子类中访问父类的同名成员
同上，需要添加作用域
*/

/*
4.6.7 多继承语法
继承多个父类
语法： class 子类 ：继承方式 父类1 ， 继承方式 父类2...
*/

/*
4.6.8 菱形继承
两个派生类（羊、驼）继承同一个父类（动物）
另一个类（羊驼）同时继承这两个派生类


问题：羊驼使用数据时会产生二义性，比如：通过羊还是驼使用父类动物的数据呢？
解决：虚继承
    1. 在父类前加上关键字 virtual
    2. 在子类中使用父类的成员时，添加作用域
    3. 只会在内存中存在一份父类的成员


菱形继承中的构造函数和析构函数：
    1.动物类的虚构函数需要使用virtual
    2.羊驼类的构造函数需要先调用父类（动物）的构造函数，再调用子类（羊、驼）的构造函数
*/
class Animal
{
public:
	int m_Age;
};

//继承前加virtual关键字后，变为虚继承
//此时公共的父类Animal称为虚基类
class Sheep : virtual public Animal {};//virtual
class Tuo   : virtual public Animal {};//virtual
class SheepTuo : public Sheep, public Tuo {};

int main() {

	SheepTuo st;
	st.Sheep::m_Age = 100;
	st.Tuo::m_Age = 200;//都是对同一个数据操作
	cout << "st.Sheep::m_Age = " << st.Sheep::m_Age << endl;
	cout << "st.Tuo::m_Age = " <<  st.Tuo::m_Age << endl;
	cout << "st.m_Age = " << st.m_Age << endl;
	system("pause");
	return 0;
}
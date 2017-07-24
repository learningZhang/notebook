#include <iostream>
using namespace std;
//内聚：模块应该做好一个件事情，描述的是模块内的功能联系
//耦合：不同模块之间的互联程度的度量。各模块之间接口的复杂成都、进入或者访问一个模块的点或者通过接口的数据
      //模块之间应该独立存在，独立完成某个特定的子功能，之间的接口少而简单，利于修改和组合
//其好处，代码重用性，维护性，扩展性


//抽象出一些类的公共接口以形成抽象基类或者接口，通过指向基类指针指向实际的子类实现多态。

//在父类中并不知道具体要实例化哪个具体的子类

//抽象工厂两个重要的功能
//1>定义创建对象的接口，封装对象的功能
//2>使得具体类的工作延迟到子类


class Product//基类，可以派生出很多实现具体功能的子类
{
public:
	virtual ~Product()=0;
protected:
	Product();
private:
};
Product::Product(){}
Product::~Product(){}

///////////////////////////////////////////////////////////////
//同是继承于父类，但是各有个的分化，每个类完成不同的特化版本

//实现具体功能的类之一
class ConcreteProduct:public Product//继承父类，这样父类可以通过指针来接收子类，实现所有的子类统一化处理
{
public:
	~ConcreteProduct();
	ConcreteProduct();
protected:
private:
};
ConcreteProduct::ConcreteProduct()
{
	cout<<"ConcreteProduct.."<<endl;
}
ConcreteProduct::~ConcreteProduct()
{
}

//实现具体功能的类之二
class ConcreteProduct2:public Product//继承
{
public:
	~ConcreteProduct2();
	ConcreteProduct2();
protected:
private:
};
ConcreteProduct2::ConcreteProduct2()
{
	cout<<"ConcreteProduct2.."<<endl;
}
ConcreteProduct2::~ConcreteProduct2()
{
}

//////////////////////////////////////////////////////////
//工厂模式用来生产对象
     //Factory派生出不同的类来实现创建不同的具体实现功能的Product类
class Factory
{
public:
	virtual ~Factory()=0;
	virtual Product* CreateProduct()=0;
protected:
	Factory();
private:
};
Factory::Factory(){}
Factory::~Factory(){}

//////////////////////////////////////////////////////
//用于创建不同的类的对象

class  ConcreteFactory:public Factory//创建对象ConcreteProduct
{
public:
	~ConcreteFactory();
	ConcreteFactory();
	Product*CreateProduct();//重写父类中的方法
protected:
private:
};
ConcreteFactory::ConcreteFactory()
{
	cout<<"ConcreteFactory.."<<endl;
}
ConcreteFactory::~ConcreteFactory()
{
}
Product *ConcreteFactory::CreateProduct()
{
	return new ConcreteProduct();//
}

//////

class  ConcreteFactory2:public Factory////创建对象ConcreteProduct2
{
public:
	~ConcreteFactory2();
	ConcreteFactory2();
	Product*CreateProduct();//重写父类中的方法
protected:
private:
};

ConcreteFactory2::ConcreteFactory2()
{
	cout<<"ConcreteFactory2.."<<endl;
}
ConcreteFactory2::~ConcreteFactory2()
{
}
Product *ConcreteFactory2::CreateProduct()
{
	return new ConcreteProduct2();
}

//////////////////////////////////////////////////////////

int main()
{
	Factory* fac = new ConcreteFactory();//返回的是ConcreteFactory对象，用其父类来接收基类指针
	Product *p = fac->CreateProduct();//多态，调用子类中的方法来创建ConcreteProduct2对象，用父类来接收
	return 0;
}
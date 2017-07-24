#include <iostream>
using namespace std;
//�ھۣ�ģ��Ӧ������һ�������飬��������ģ���ڵĹ�����ϵ
//��ϣ���ͬģ��֮��Ļ����̶ȵĶ�������ģ��֮��ӿڵĸ��ӳɶ���������߷���һ��ģ��ĵ����ͨ���ӿڵ�����
      //ģ��֮��Ӧ�ö������ڣ��������ĳ���ض����ӹ��ܣ�֮��Ľӿ��ٶ��򵥣������޸ĺ����
//��ô������������ԣ�ά���ԣ���չ��


//�����һЩ��Ĺ����ӿ����γɳ��������߽ӿڣ�ͨ��ָ�����ָ��ָ��ʵ�ʵ�����ʵ�ֶ�̬��

//�ڸ����в���֪������Ҫʵ�����ĸ����������

//���󹤳�������Ҫ�Ĺ���
//1>���崴������Ľӿڣ���װ����Ĺ���
//2>ʹ�þ�����Ĺ����ӳٵ�����


class Product//���࣬�����������ܶ�ʵ�־��幦�ܵ�����
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
//ͬ�Ǽ̳��ڸ��࣬���Ǹ��и��ķֻ���ÿ������ɲ�ͬ���ػ��汾

//ʵ�־��幦�ܵ���֮һ
class ConcreteProduct:public Product//�̳и��࣬�����������ͨ��ָ�����������࣬ʵ�����е�����ͳһ������
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

//ʵ�־��幦�ܵ���֮��
class ConcreteProduct2:public Product//�̳�
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
//����ģʽ������������
     //Factory��������ͬ������ʵ�ִ�����ͬ�ľ���ʵ�ֹ��ܵ�Product��
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
//���ڴ�����ͬ����Ķ���

class  ConcreteFactory:public Factory//��������ConcreteProduct
{
public:
	~ConcreteFactory();
	ConcreteFactory();
	Product*CreateProduct();//��д�����еķ���
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

class  ConcreteFactory2:public Factory////��������ConcreteProduct2
{
public:
	~ConcreteFactory2();
	ConcreteFactory2();
	Product*CreateProduct();//��д�����еķ���
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
	Factory* fac = new ConcreteFactory();//���ص���ConcreteFactory�������丸�������ջ���ָ��
	Product *p = fac->CreateProduct();//��̬�����������еķ���������ConcreteProduct2�����ø���������
	return 0;
}
#include <iostream>
using namespace std;
#include <vector>
#include <iterator>
#include <map>
#include <string>
#include <vector>

class Listener
{
public:
	Listener(string name):_name(name){}
	virtual void handMessage(int msg) = 0;
protected:
	string _name;
};

class Listener1 : public Listener
{
public:
	Listener1(string name):Listener(name){}

	void handMessage(int msg)
	{
		cout<<_name<<" ";
		switch(msg)
		{
		case 0:
			cout<<"handle 0 msg"<<endl;
			break;
		case 1:
			cout<<"handle 1 msg"<<endl;
			break;
		case 2:
			cout<<"handle 2 msg"<<endl;
			break;
		default:
			cout<<"invalid msg"<<endl;
			break;
		}
	}
};

class Listener2:public Listener
{
public:
	Listener2(string name):Listener(name){}

	void handMessage(int msg)
	{
		cout<<_name<<" ";
		switch(msg)
		{
		case 0:
			cout<<"handle 0 msg"<<endl;
			break;
		case 2:
			cout<<"handle 2 msg"<<endl;
			break;
		default:
			cout<<"invalid msg"<<endl;
			break;
		}
	}
};

class Listener3:public Listener
{
public:
	Listener3(string name):Listener(name){}

	void handMessage(int msg)
	{
		cout<<_name<<" ";
		switch(msg)
		{
		case 0:
			cout<<"handle 0 msg"<<endl;
			break;
		case 1:
			cout<<"handle 1 msg"<<endl;
			break;
		default:
			cout<<"invalid msg"<<endl;
			break;
		}
	}
};

class Observer
{
public:
	void Register(int msgid,Listener *listener)
	{
		map<int,vector<Listener*>>::iterator it =_observerMap.find(msgid);
			//指向map的迭代器
		if (it == _observerMap.end())
		{
			vector<Listener*> tmpvec;//开辟一个对象，这个对象的生命周期
			tmpvec.push_back(listener);
			_observerMap[msgid] = tmpvec;//将这个vector加入到map中
		}
		else
		{
			it->second.push_back(listener);
		}
	}
	
	void Dispath(int msgid)//分发事件
	{
		map<int,vector<Listener*>>::iterator it = _observerMap.find(msgid);
		if (it == _observerMap.end())
		{
			return;
		}
		
		vector<Listener*>::iterator vit = it->second.begin();
		for(;vit != it->second.end(); ++vit)
		{
			(*vit)->handMessage(msgid);
		}
	}
private:
	map<int,vector<Listener*>> _observerMap;//map中传递的是键值对
};

int main()
{
	Observer obser;

	Listener *p1 = new Listener1("Listener1");
	Listener *p2 = new Listener2("Listener2");
	Listener *p3 = new Listener3("Listener3");

	//注册事件，监听者p1监听012号事件
	obser.Register(0, p1);
	obser.Register(1, p1);
	obser.Register(2, p1);
	
	obser.Register(0, p2);
	obser.Register(2, p2);
	
	obser.Register(0, p3);
	obser.Register(1, p3);

	int msgid;
	while (true)
	{
		cout<<"input msg id :"<<endl;
		cin>>msgid;//发生了该事件

		if (msgid == -1)
		{
			break;
		}
		
		obser.Dispath(msgid);//将事件进行分发

	}

	return 0;
}

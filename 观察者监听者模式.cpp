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
			//ָ��map�ĵ�����
		if (it == _observerMap.end())
		{
			vector<Listener*> tmpvec;//����һ����������������������
			tmpvec.push_back(listener);
			_observerMap[msgid] = tmpvec;//�����vector���뵽map��
		}
		else
		{
			it->second.push_back(listener);
		}
	}
	
	void Dispath(int msgid)//�ַ��¼�
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
	map<int,vector<Listener*>> _observerMap;//map�д��ݵ��Ǽ�ֵ��
};

int main()
{
	Observer obser;

	Listener *p1 = new Listener1("Listener1");
	Listener *p2 = new Listener2("Listener2");
	Listener *p3 = new Listener3("Listener3");

	//ע���¼���������p1����012���¼�
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
		cin>>msgid;//�����˸��¼�

		if (msgid == -1)
		{
			break;
		}
		
		obser.Dispath(msgid);//���¼����зַ�

	}

	return 0;
}

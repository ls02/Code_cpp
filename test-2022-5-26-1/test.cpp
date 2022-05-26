#include <iostream>
#include <thread>
#include <mutex>


////饿汉模式
//class Singleton
//{
//private:
//	Singleton()
//		:_a(0)
//	{};
//
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//
//	size_t _a;
//	static Singleton* _inst;
//
//public:
//	static Singleton* GetInstance(void)
//	{
//		return _inst;
//	}
//};
//
//Singleton* Singleton::_inst = new Singleton;

//懒汉模式
class Singleton
{
private:
	Singleton()
		:_a(0)
	{};

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	size_t _a;
	static Singleton* _inst;
	static std::mutex _mut;

public:
	static Singleton* GetInstance(void)
	{
		if (nullptr == _inst)
		{
			_mut.lock();

			if (nullptr == _inst)
			{
				_inst = new Singleton;
			}

			_mut.unlock();
		}
		return _inst;
	}
};

std::mutex Singleton::_mut;

Singleton* Singleton::_inst = nullptr;

void Test1(void)
{
	int a = 5;
	int b = 2;
	auto f1 = [](int& a, int& b)->void
	{
		int temp = a;
		a = b;
		b = temp;
	};

	auto f2 = [&a, &b]
	{
		auto temp = a;
		a = b;
		b = temp;
	};

	f1(a, b);
	f2();

	auto f3 = [&]
	{
		auto temp = a;
		a = b;
		b = temp;
	};

	f3();

	std::cout << a << " " << b << std::endl;
}

void Test2(void)
{
	Singleton* a;
	Singleton* b;
	Singleton* c;

	std::cout << a->GetInstance() << std::endl;
	std::cout << b->GetInstance() << std::endl;
	std::cout << c->GetInstance() << std::endl;
}

int main(void)
{
	Test2();

	return 0;
}
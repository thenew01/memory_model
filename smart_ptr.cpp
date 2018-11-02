#include <iostream>
#include <memory>
#include <tchar.h>

using namespace std;

void foo(std::shared_ptr<int> i)
{
	(*i)++;
}

struct A;
struct B;

struct A {
	//std::shared_ptr<B> pointer;
	std::weak_ptr<B> pointer;
	~A() {
		std::cout << "A ������" << std::endl;
	}
};
struct B {
	std::shared_ptr<A> pointer;
	~B() {
		std::cout << "B ������" << std::endl;
	}
};

int main()
{
	// auto pointer = new int(10); // �Ƿ�, ������ֱ�Ӹ�ֵ
	// ������һ�� std::shared_ptr
	auto pointer = std::make_shared<int>(10);
	foo(pointer);
	std::cout << *pointer << std::endl; // 11

	auto pointer2 = pointer;    // ���ü���+1
	auto pointer3 = pointer;    // ���ü���+1
	int *p = pointer.get();             // ���������������ü���
				
	std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;      // 3
	std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;    // 3
	std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;    // 3

	pointer2.reset();
	std::cout << "reset pointer2:" << std::endl;
	std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;      // 2
	std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;    // 0, pointer2 �� reset
	std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;    // 2

	pointer3.reset();
	std::cout << "reset pointer3:" << std::endl;
	std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;      // 1
	std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;    // 0
	std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;    // 0, pointer3 �� reset
								
	std::unique_ptr<int> pointer0 = std::make_unique<int>(10);   // make_unique �� C++14 ����
	std::unique_ptr<int> pointer20 = std::move(pointer0);    // �Ƿ�


	
	{
		auto a = std::make_shared<A>();
		auto b = std::make_shared<B>();
		a->pointer = b;
		b->pointer = a;
	}

	// �뿪������ǰ��shared_ptr �ᱻ�������Ӷ��ͷ��ڴ�
	return 0;
}
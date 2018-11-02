
/*
--------lamda�﷨--------
[capture list](params list) mutable exception-> return type{ function body }
��Lambda���ʽ�У�����Դ�ֵ��ʽ�����ⲿ�������������в����޸ĸ��ⲿ����������������������

// �����﷨
[ capture-list ] ( params ) mutable(optional) constexpr(optional)(c++17) exception attribute -> ret { body }

// ��ѡ�ļ��﷨
[ capture-list ] ( params ) -> ret { body }
[ capture-list ] ( params ) { body }
[ capture-list ] { body }

*/
/*
----��Ϸ�ʽ----
������ʽ	˵��
[]	�������κ��ⲿ����
[������, ��]	Ĭ����ֵ����ʽ����ָ���Ķ���ⲿ�������ö��ŷָ�����������ò�����Ҫ��ʾ������ʹ��&˵������
[this]	��ֵ����ʽ����thisָ��
[*this]��ͨ����ֵ��ʽ����ǰ����
[=]	��ֵ����ʽ���������ⲿ����
[&]	��������ʽ���������ⲿ����
[=, &x]	����x��������ʽ������������Դ�ֵ��ʽ����
[&, x]	����x��ֵ����ʽ�������������������ʽ����

-----����-----
�����б��в�����Ĭ�ϲ���
��֧�ֿɱ����
���в��������в�����
**/

//�ֲ��������ں����������ж���ĺ�����Ҳ��Ϊ��Ƕ������
//ÿ���㶨��һ��lambda���ʽ�󣬱��������Զ�����һ�������ࣨ����൱Ȼ������()�������
/*
1.�����������״̬
2.ÿ�������������Լ������ͣ�������ͨ������˵��ֻҪǩ��һ�£������;�����ͬ�ġ�
�����Ⲣ�������ں���������Ϊ�����������������������͡�
�����������������Լ������ͣ�����ζ�ź��������������ģ���������Է��ͱ���кܴ�������
*/

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool cmp(int a, int b)
{
	return  a < b;
}

int main()
{

	vector<int> myvec{ 3, 2, 5, 7, 3, 2 };
	vector<int> lbvec(myvec);

	sort(myvec.begin(), myvec.end(), cmp); // ��ʽ����
	cout << "predicate function:" << endl;
	for (int it : myvec)
		cout << it << ' ';
	cout << endl;

	sort(lbvec.begin(), lbvec.end(), [](int a, int b) -> bool { return a < b; });   // Lambda���ʽ
	cout << "lambda expression:" << endl;
	for (int it : lbvec)
		cout << it << ' ';
	cout << endl;

	//////////////////////////////////////////////////////////////////////////
	int a0 = 123;
	auto f = [a0] { cout << "a0:" << a0 << endl; };
	f(); // �����123

		 //��ͨ���������塱����ġ�()���������
	[](int a) {cout << a << endl; }(123);
	[](int a) {cout << a << endl; }(a0);
	//////////////////////////////////////////////////////////////////////////

	//��ֵ����
	int a1 = 123;
	auto ff = [a1] { cout << "a1: " << a1 << endl; };
	a1 = 321;
	ff(); // �����123

		  // ���ò���
	int a = 123;
	auto f0 = [&a] { cout << "a: " << a << endl; };
	a = 321;
	f0(); //123

	a = 123;
	// ��ʽ���� [=],[&]
	auto f1 = [=]() { cout << "��ʽ����[=] " << a << endl;  };
	a = 321;
	f1();  //123

	a = 123;
	auto f2 = [&]() { cout << "��ʽ����[&] " << a << endl;  };
	a = 321;
	f2();	// �����321

	a = 123;
	auto f3 = [=]() mutable { a = 1;  cout << "��ʽ����[=]mutable " << a << endl; };
	a = 321;
	f3();

	a = 123;
	auto f4 = [&]() mutable { a = 2;  cout << "��ʽ����[&]mutable " << a << endl; };
	a = 321;
	f4();

	// �߼��÷� 
	{
		//�հ�
		int m = [](int x) { return [](int y) { return y * 2; }(x)+6; }(5);
		std::cout << "m:" << m << std::endl;	//���m:16
		std::cout << "n:" << [](int x, int y) { return x + y; }(5, 4) << std::endl;            //���n:9

		auto gFunc = [](int x) -> function<int(int)> { return [=](int y) { return x + y; }; };
		auto lFunc = gFunc(4);
		std::cout << lFunc(5) << std::endl;

		auto hFunc = [](const function<int(int)>& f, int z) { return f(z) + 1; };
		auto aa = hFunc(gFunc(7), 8);
		std::cout << aa << endl;

		//��ϲ���ʽ
		int a = 111, b = 222;
		auto func = [=, &b]()mutable { a = 22; b = 333; std::cout << "a:" << a << " b:" << b << std::endl; };
		func();
		std::cout << "a:" << a << " b:" << b << std::endl;

		a = 333;
		auto func2 = [=, &a] { a = 444; std::cout << "a:" << a << " b:" << b << std::endl; };
		func2();

		std::function<void(int x)> f_display_42 = [](int x) {
			//print_num(x); 
			std::cout << x << endl;
		};
		f_display_42(44);
	}

	//����lambda���ʽ	
	auto add = [](auto x, auto y) { return x + y; };
	int x0 = add(2, 3);   // 5
	double y0 = add(2.5, 3.5);  // 6.0

								//��׽���ʽ
								// ���ñ��ʽ���񣬿��Ը����ش����������ڵı���
	int x = 4;
	auto y = [&r = x, x = x + 1]{ r += 2; return x * x; }();
	// ��ʱ x ����Ϊ6��y Ϊ25

	// ֱ��������ֵ��ʼ������
	auto z = [str = "string"]{ return str; }();
	// ��ʱz��const char* ���ͣ��洢�ַ��� string

	//������binder��
	//����std::bind����õĺ����������������Խ���������Ĳ��������ض���ֵ��
	// ����û�а󶨵Ĳ�������ʹ��std::placeholers::_1, std::placeholers::_2�ȱ�ǡ�
	auto minus10 = std::bind(std::minus<int>{}, std::placeholders::_1, 10);
	cout << minus10(20) << endl;  // ���10

								  //�������в�����˳��
	auto vminus = std::bind(std::minus<int>{}, std::placeholders::_2, std::placeholders::_1);
	cout << vminus(20, 10) << endl;  // ���-10

									 //���������Ի���Ƕ�ף��Ӷ�ʵ�ֺ�����������
									 // ����һ������һ��������Ȼ�󽫲�����10�ٳ���2�ĺ�������
	auto plus10times2 = std::bind(std::multiplies<int>{},
		std::bind(std::plus<int>{}, std::placeholders::_1, 10), 2);
	cout << plus10times2(4) << endl; // ����� 28 

									 // ����3�η���������
	auto pow3 = std::bind(std::multiplies<int>{},
		std::bind(std::multiplies<int>{}, std::placeholders::_1, std::placeholders::_1),
		std::placeholders::_1);
	cout << pow3(3) << endl;  // �����27
}


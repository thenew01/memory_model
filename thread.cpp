#include <iostream>
#include <future>
#include <thread>
#include <string>
/*
int main()
{
	// ��һ������ֵΪ7�� lambda ���ʽ��װ�� task ��
	// std::packaged_task ��ģ�����ΪҪ��װ����������
	std::packaged_task<int()> task([]() {return 7; });
	// ��� task �� future
	std::future<int> result = task.get_future();    // ��һ���߳���ִ�� task
	std::thread(std::move(task)).detach();    
	std::cout << "Waiting...";
	result.wait();
	// ���ִ�н��
	std::cout << "Done!" << std::endl << "Result is " << result.get() << '\n';
}
*/

// �ַ����������Զ�������������µĲ����б�
std::string operator"" _wow1(const char *wow1, size_t len) {
	return std::string(wow1) + "woooooooooow, amazing";
}

std::string operator"" _wow2(unsigned long long i) {
	return std::to_string(i) + "woooooooooow, amazing";
}

int main() {
	auto str = "abc"_wow1;
	auto num = 1_wow2;
	std::cout << str << std::endl;
	std::cout << num << std::endl;
	return 0;
}
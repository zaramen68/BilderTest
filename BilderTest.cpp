// BilderTest.cpp: определяет точку входа для приложения.
//
#include <map>
#include "BilderTest.h"
#include "FooF.h"

using namespace std;

std::map<int, std::shared_ptr<Target>> target_list{ {1, std::shared_ptr<Target>{new Target{1, foo1, {2, 4}}}},
													{2, std::shared_ptr<Target>{new Target{2, foo2, {3,}}}}, 
													{3, std::shared_ptr<Target>{new Target{3, foo3, {}}}}, 
													{4, std::shared_ptr<Target>{new Target{4, foo4, {2, 5}}}}, 
													{5, std::shared_ptr<Target>{new Target{5, foo5, {}}}}};

int main()
{
	BuildGraph bg(target_list);
	Builder builder(1);
	builder.execute(bg, 1);
	
	return 0;
}

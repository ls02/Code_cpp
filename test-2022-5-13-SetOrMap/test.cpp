#include "RBTree.h"
#include "Map.h"
#include "Set.h"

int main(void)
{
	ls::map<int, int> m1;
	ls::set<int> s1;

	m1.Insert(std::make_pair(1, 1));
	m1.Insert(std::make_pair(2, 2));
	m1.Insert(std::make_pair(3, 3));
	m1.Insert(std::make_pair(4, 4));

	s1.Insert(1);
	s1.Insert(2);
	s1.Insert(3);
	s1.Insert(4);

	auto mit = m1.begin();

	while (mit != m1.end())
	{
		std::cout << mit->first << ":" << mit->second << std::endl;
		++mit;
	}

	auto sit = s1.begin();
	while (sit != s1.end())
	{
		std::cout << *sit << std::endl;
		++sit;
	}

	return 0;
}
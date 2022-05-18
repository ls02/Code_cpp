#include "HashTable.h"
#include "UnorderedMap.h"
#include "UnorderedSet.h"

void HashMapTest1(void)
{
	ls::unordered_map<int, int> m1;
	
	m1.Insert(std::make_pair(1, 1));
	m1.Insert(std::make_pair(2, 2));
	m1.Insert(std::make_pair(3, 3));
	m1.Insert(std::make_pair(4, 4));

	m1[2] = 10;

	ls::unordered_map<int, int>::iterator it = m1.begin();
	while (it != m1.end())
	{
		std::cout << it->first << ":" << it->second << std::endl;
		it++;
	}


}

int main(void)
{
	HashMapTest1();

	return 0;
}
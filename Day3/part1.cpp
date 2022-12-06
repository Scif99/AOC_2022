#include <cassert>
#include <fstream>

#include <array>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

/*
- Each line represents the items in a backback
- Each character in the line is an item
- The first half of the line represents the 1st compartment, the second represents the 2nd compartment

- Lower case/Upper case represent different types
- One item(character) is shared between the compartments
*/

//computes priority
int Priority(char c)
{
	return islower(c) ? c - 'a' + 1 : c - 'A' + 27;
}

//Note that each compartment has the same number of items
//hence the string is always even in size
char CommonItem(std::string line)
{
	/*Number of approaches
	1) for each element in first half, iterate over elements in 2nd half and check (O(n^2) time)
	2) Store first half in set, iterate over 2nd half and check with set (O(n) time, O(n) space)
	We'll go with 2nd approach
	*/

	assert(line.size() % 2 == 0); //check size is even...

	int half_size = line.size()/2;
	std::unordered_set<char> set;

	for (int i = 0;i < half_size;++i)
	{
		set.insert(line[i]);
	}

	int common_index = line.size();
	for (int i = half_size; i < line.size();++i)
	{
		if (set.contains(line[i]))
		{
			common_index = i;
			break;
		}
	}
	assert(common_index != line.size());//Each line MUST have a common element...
	return line[common_index];

	//auto common = std::find_if(std::begin(line) + half_size, std::end(line), [&set, &line](char c) {return set.contains(line[c]);} );
	//assert(common != std::end(line)); //Each line MUST have a common element...
	//return *common;
}



int main()
{
	std::ifstream file{ "day3.txt" };

	if (!file)
	{
		std::cerr << "Error: could not open file";
	}

	int total_priority{ 0 };

	while (file.peek() != EOF)
	{

		std::string line;
		std::getline(file, line);
		total_priority += Priority(CommonItem(line));
		auto c = CommonItem(line);
		std::cout << c << '\n';
	}
	std::cout << total_priority;
}


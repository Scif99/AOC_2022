#include <cassert>
#include <fstream>

#include <array>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

//Extract groups of 3
//Check for the common element

int Priority(char c)
{
	return islower(c) ? c - 'a' + 1 : c - 'A' + 27;
}


/*
* for a array of strings size n + m + p
1) We can do a triple-nested loop (O(N^3) time)
2) We can use sets to store common elements ( O(N) time O(n+m) space)

**There is another solution involving binary search that works in O(nlogn) time and constant space**
https://stackoverflow.com/questions/65728835/given-3-arrays-check-if-there-is-any-common-number
*/
char FindCommonElement(const std::array<std::string, 3>& group)
{
	std::unordered_set<char> set;
	for (const auto& c : group[0])
	{
		set.insert(c);
	}

	std::unordered_set<char> com; //stores elements common to first and second line in group
	for (const auto& c : group[1])
	{
		if (set.contains(c))
		{
			com.insert(c);
		}
	}

	int common_index = group[2].size();
	for(int i =0;i<group[2].size();++i)
	{
		if (com.contains(group[2][i]))
		{
			common_index = i;
		}
	}
	assert(common_index!=group[2].size());
	return group[2][common_index];
}


int main()
{
	std::ifstream file{ "day3.txt" };

	if(!file)
	{
		std::cerr << "file not found.";
	}

	int total_priority{ 0 };

	std::array<std::string, 3> group;
	int index{ 0 }; //index into group

	while (file.peek()!=EOF)
	{
		std::string line;
		std::getline(file, line);

		//when have reached end of group
		if (index == 3)
		{
			//do stuff with group
			total_priority += Priority(FindCommonElement(group));
			index = 0;
		}
		group[index] = line;
		++index;
	}
	std::cout<< total_priority + Priority(FindCommonElement(group));

}

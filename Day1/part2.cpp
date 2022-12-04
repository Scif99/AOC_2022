#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

/*
For part 2 we can store each elf's total calory count in a vector.
Then we can sort the vector in decreasing order and output the sum of first 3 elements;

This solution also solves part 1 by just outputting the first element instead of doing the above.
*/

std::vector<int> Inventories(const char* input)
{
	std::ifstream file(input);

	if (!file)
	{
		std::cerr << "Error: couldnt open file\n";
		return {};
	}

	std::vector<int> ans;

	int local_sum{ 0 }; //track the sum of calories carried by current dwarf

	while (file)
	{
		std::string line;
		std::getline(file, line);

		//If we find a blank line, then it is the end of the current elf's invent.
		if (line.empty())
		{
			ans.push_back(local_sum);
			local_sum = 0;
		}

		//Otherwise add it to current sum for this elf
		else
		{
			local_sum += std::stoi(line); //need to convert the string to an int
		}
	}
	return ans;
}


int main()
{
	std::vector<int> calory_counts = Inventories("day1.txt");
	std::sort(std::begin(calory_counts), std::end(calory_counts), [](int a, int b) {return a > b;}); //sort in decreasing order
	int Sumof3Largest = std::accumulate(std::begin(calory_counts), std::begin(calory_counts) + 3, 0);
	std::cout << Sumof3Largest;
}

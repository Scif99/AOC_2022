#include <cassert>
#include <fstream>

#include <array>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

/*
- The majority of the work in this comes from extracting numbers from the input...
- Input is a file where each line contains two ranges, something like 2-8,3-7
- We need some way to extract the numbers from each line, as a string
*/

struct Range
{
	int low;
	int high;

	friend bool operator==(const Range& first, const Range& second);
};

bool operator==(Range& first, Range& second)
{
	return (first.low == second.low) && (first.high = second.high);
}


/*
* PART 1
To check whether there is a full overlap, we just need to know which range has the smallest low value.
Then we can just check if that range also has the largest high value.
One special case is if both ranges have the same start. Then there will always be a full overlap...
*/
bool FullyContains(Range first, Range second)
{
	if (first.low == second.low) return true; 

	Range has_lowest = first.low < second.low ? first : second; //find the range whos low is the smallest
	Range other = (has_lowest == first) ? second : first;
	return has_lowest.high >= other.high;
}

/*
* PART 2
The solution becomes easier to see if you draw out the ranges on a number line
It's easier to check when ranges dont overlap...

Visually, draw the first range R1 on a number line
	Then, notice that if the second range R2 isn't to overlap, then either
		- It lies completely to the left of the first range
		- It lies completely to the right
	The first case is equivalent to saying that high2 is strictly less than low1
	The second is equivalent to saying that low2 is strictly greater than high1
*/
bool PartiallyContains(Range first, Range second)
{
	return !(second.high < first.low || second.low > first.high);
}


std::array<Range, 2> ParseRanges(const std::string& s)
{
	Range first;
	Range second;

	/*
	TO parse the ranges we can iterate through the string, storing the numbers into a buffer
	Once we reach a non-digit we know we've got the full number, so we can save it and clear the buffer
	Then we carry on, skipping the characters in between numbers (the format of lines is "a-b , c-d")
	*/
	std::string buffer;
	int index{ 0 };
	while (isdigit(s[index]))
	{
		buffer.push_back(s[index]);
		index++;
	}
	first.low = std::stoi(buffer);
	buffer.clear();
	++index; //skip the das'-' char

	while (isdigit(s[index]))
	{
		buffer.push_back(s[index]);
		++index;
	}
	first.high = std::stoi(buffer);
	buffer.clear();
	++index; //skip the ',' char

	//---------------------------------
	//2ND RANGE
	while (isdigit(s[index]))
	{
		buffer.push_back(s[index]);
		++index;
	}
	second.low = std::stoi(buffer);
	buffer.clear();
	++index; //skip the das'-' char

	while (index<s.size()) //last one we iterate to end of line
	{
		buffer.push_back(s[index]);
		++index;
	}
	second.high = std::stoi(buffer);

	return std::array<Range,2>{first, second};
}

int main()
{

	std::ifstream file{ "day4.txt" };

	if (!file)
	{
		std::cerr << "error couldnt open file\n";
	}

	int lines{0};
	int total_contained{ 0 };
	while (file.peek() != EOF)
	{
		std::string line;
		std::getline(file, line); //read line into string

		const auto ranges = ParseRanges(line);
		if (PartiallyContains(ranges[0], ranges[1]) /*FullyContains(ranges[0],ranges[1])*/)
			++total_contained;
	}
	std::cout << total_contained;
}

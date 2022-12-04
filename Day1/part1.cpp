/*
For part 1 we can compute the largest sum of calories without storing anything.
*/


int LargestInventory(const char* input)
{
	std::ifstream file(input);

	if (!file)
	{
		std::cerr << "Error: couldnt open file\n";
		return 1;
	}

	int local_sum{ 0 }; //track the largest sum of calories seen so far
	int global_max{ 0 }; //Track global max

	while (file)
	{
		std::string line;
		std::getline(file, line);

		//If we find a blank line, then it is the end of the current elf's invent.
		if (line.empty())
		{
			//Reset the counter for the next elf
			if (local_sum > global_max)
			{
				global_max = local_sum;
			}
			local_sum = 0;
		}

		//Otherwise add it to current sum for this elf
		else
		{
			local_sum += std::stoi(line); //need to convert the string to an int
		}
	}
	return global_max;
}

int main()
{
	std::cout<<LargestInventory("day1.txt");
}

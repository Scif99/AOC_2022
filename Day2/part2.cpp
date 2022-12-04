/*
PART TWO
Now, the second column of each line tells us the desired result of a round.
Therefore the meaning of X,Y,Z change to
- X = Lose
- Y = Draw
- Z = Win

So, given a line in the input:
	- We ned to convert the second char to a result
	- Then we need to compute the total score from that result
		- Note that we alread have the score associated with the result (the line tells us!)
		So what we need to work out is the score from the associated shape...
		That is, given the elf's shape and a result, we need to work out what shape the player would have needed to get that result
*/

enum class Result
{
	WIN,
	DRAW,
	LOSE
};

std::unordered_map<Result, int> ResultScores
{
	{Result::WIN, 6},
	{Result::DRAW, 3},
	{Result::LOSE, 0}
};

std::unordered_map<char, int> ShapeScores
{ 
	{'X', 1}, 
	{'Y', 2}, 
	{'Z', 3} 
};

//convenience function that converts a char to its associated result
Result charToResult(char c)
{
	static std::unordered_map<char, Result> map{ {'X', Result::LOSE}, {'Y', Result::DRAW}, {'Z', Result::WIN} };
	return map[c];
}


char PlayerShape(char elf, Result result)
{
	//elf chooses rock
	if (elf == 'A')
	{
		if (result == Result::DRAW) return 'X';
		if (result == Result::WIN) return 'Y';
		if (result == Result::LOSE) return 'Z';
	}

	//elf chooses paper
	if (elf == 'B')
	{

		if (result == Result::LOSE) return 'X';
		if (result == Result::DRAW) return 'Y';
		if (result == Result::WIN) return 'Z';

	}

	//elf chooses scissors
	if (elf == 'C')
	{
		if (result == Result::WIN) return 'X';
		if (result == Result::LOSE) return 'Y';
		if (result == Result::DRAW) return 'Z';
	}

}


int score(const char* input)
{
	std::ifstream file{input};

	if (!file)
	{
		std::cerr<<"ERROR: could not read file\n";
		return -1;
	}

	int total_score{ 0 };
	while (file)
	{
		std::string line;
		std::getline(file, line);

		if (line.empty()) break;

		char elf{ line[0] }; //elf's shape
    Result res{ charToResult(line[2]) }; //desired result
		int round_score = ShapeScores[PlayerShape(elf, res)] + ResultScores[res];

		total_score += round_score;
	}
	return total_score;
}

int main()
{


	std::cout<<score("day2.txt");

}

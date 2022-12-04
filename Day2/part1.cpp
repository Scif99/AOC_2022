#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

/*
Key numbers from problem

THEM
- A = Rock	
- B = Paper
- C = Scissors

YOU
- X = Rock
- Y = Paper
- Z = Scissors

SCORES
- Rock: 1
- Paper: 2
- Scissors: 3

- Loss = 0
- Draw = 3
- Win = 6
*/


enum class Result
{
	WIN,
	DRAW,
	LOSE
};

Result ComputeResult(char elf, char player)
{
	//elf chooses rock
	if (elf == 'A') 
	{
		if (player == 'X') return Result::DRAW; //player chooses rock
		if (player == 'Y') return Result::WIN; //player chooses paper
		if (player == 'Z') return Result::LOSE; //player chooses scissors
	}

	//elf chooses paper
	if (elf == 'B')
	{
		if (player == 'X') return Result::LOSE; //player chooses rock
		if (player == 'Y') return Result::DRAW; //player chooses paper
		if (player == 'Z') return Result::WIN; //player chooses scissors
	}

	//elf chooses scissors
	if (elf == 'C')
	{
		if (player == 'X') return Result::WIN; //player chooses rock
		if (player == 'Y') return Result::LOSE; //player chooses paper
		if (player == 'Z') return Result::DRAW; //player chooses scissors
	}

}

//returns the score associated with the shape that the player chose
int ShapeScore(char shape)
{
	static std::unordered_map<char, int> scores{ {'X', 1}, {'Y', 2}, {'Z', 3} };

	//if(!scores.contains(shape))
	return scores[shape];
}

//returns score associated with the result of a round (win/draw/loss)
int ResultScore(char elf, char player)
{
	static std::unordered_map<Result, int> scores{ {Result::WIN, 6}, {Result::DRAW, 3}, {Result::LOSE, 0} };

	return scores[ComputeResult(elf, player)];
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

		const char elf{ line[0] };
		const char player{ line[2] };
		int round_score = ShapeScore(player) + ResultScore(elf, player);
		total_score += round_score;
	}
	return total_score;
}

int main()
{

	std::cout<<score("day2.txt");

}

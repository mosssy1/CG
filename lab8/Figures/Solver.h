#pragma once
class Solver
{
public:
	Solver() = delete;

	std::vector<float> static Solve2(const std::vector<float>& coefs);
	std::vector<float> static Solve3(const std::vector<float>& coefs);
	std::vector<float> static Solve4(const std::vector<float>& coefs);

	bool static isZero(float number);
};

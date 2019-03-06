#include <iostream>
#include <string>
#include <vector>
#include <cmath>

std::vector <int> getSignPos(std::string line)
{
	std::vector <int> pos{};
	int i {1};
	pos.push_back(0);
	for (auto c: line)
	{
		if (c == '+' || c == '-')
			pos.push_back(i - 1);
		i++;
	}
	return (pos);
}

std::vector <double> getPolynom(std::string lhs, std::string rhs)
{
	int i {0};
	std::vector <double> reducedPolynom {};
	std::vector <int> lhs_pos = getSignPos(lhs);
	std::vector <int> rhs_pos = getSignPos(rhs);
	for (int num: lhs_pos)
		reducedPolynom.push_back(std::stod(lhs.substr(num)));
	for (int num: rhs_pos)
	{
		reducedPolynom.at(i) -= std::stod(rhs.substr(num));
		i++;
	}
	return (reducedPolynom);
}

std::string getLHS(std::string polynom_str)
{
	std::string lhs {};
	int i {0};
	while (polynom_str[i] != '\0' && polynom_str[i] != '=')
	{
		if (polynom_str[i] != ' ')
			lhs.push_back(polynom_str[i]);
		i++;
	}
	return (lhs);
}

std::string getRHS(std::string polynom_str)
{
	std::string rhs {};
	int i {0};
	while (polynom_str[i] != '\0' && polynom_str[i] != '=')
		i++;
	while (polynom_str[i] != '\0')
	{
		if (polynom_str[i] != ' ' && polynom_str[i] != '=')
			rhs.push_back(polynom_str[i]);
		i++;
	}
	return (rhs);
}

void printReducedForm(std::vector <double> &polynom)
{
	int i {0};
	std::cout << "Reduced form: ";
	for (double num: polynom)
	{
		if (num > 0 && i != 0)
			std::cout << "+ " << num << " * X^" << i << " ";
		else if (num < 0)
			std::cout << "- " << num * -1 << " * X^" << i << " ";
		else if (num != 0)
			std::cout << num << " * X^" << i << " ";
		i++;
	}
	std::cout << "= 0" << std::endl;
}

void solve2(std::vector <double> &polynom)
{
	double a = polynom.at(2);
	double b = polynom.at(1);
	double c = polynom.at(0);
	double d = (b * b - 4 * a * c);
	if (d >= 0.0)
	{
		double x1 = (-b + sqrt(d)) / (2 * a);
		double x2 = (-b - sqrt(d)) / (2 * a);
		std::cout << "The Discriminant is strictly positive, the two solutions are:\n";
		std::cout << "x1 = " << x1 << " x2 = " << x2 << std::endl;
	}
	else
	{
		std::cout << "The Discriminant is strictly negative, the two complex solutions are:\n";
		std::cout << "x1 = " << -1 * (b / 2 * a) << " + " << sqrt(-1 * d) / (2 * a) << "i" << std::endl;
		std::cout << "x2 = " << -1 * (b / 2 * a) << " - " << sqrt(-1 * d) / (2 * a) << "i";
	}
}

void solve1(std::vector <double> &polynom)
{
	double solution = (-1 * polynom.at(0) / polynom.at(1));
	std::cout << "The solution is: x = " << solution << std::endl;
}

int main()
{
//	std::string polynom_str {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"};
//	std::string polynom_str {"0 * X^0 + 0 * X^1 - 1 * X^2 = 0 * X^0"};
	std::string polynom_str {"37 * X^0 + 12 * X^1 + 1 * X^2 = 0 * X^0"};
	std::string lhs = getLHS(polynom_str);
	std::string rhs = getRHS(polynom_str);
	std::vector <double> reducedPolynom = getPolynom(lhs, rhs);
	int degree = reducedPolynom.size() - 1;
	printReducedForm(reducedPolynom);
	std::cout << "Polynomial degree: " << degree << std::endl;
	if (degree > 2)
	{
		std::cout << "Polynomial degree: " << degree << std::endl;
		std::cout << "The polynomial degree is strictly greater than 2, I'm afraid I can't solve that just yet, sorry.";
	}
	else if (degree == 2)
		solve2(reducedPolynom);
	else if (degree == 1)
		solve1(reducedPolynom);
	return (0);
}
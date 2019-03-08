#include <iostream>
#include <string>
#include <vector>

void printLine(int len)
{
	while (len-- > 0)
		std::cout << "-";
	std::cout << std::endl;
}

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
	size_t i {0};
	std::vector <double> reducedPolynom {};
	std::vector <int> lhs_pos = getSignPos(lhs);
	std::vector <int> rhs_pos = getSignPos(rhs);
	for (int num: lhs_pos)
	{
		if (isdigit(lhs[num]) || ((lhs[num] == '+' || lhs[num] == '-') && isdigit(lhs[num + 1])))
			reducedPolynom.push_back(std::stod(lhs.substr(num)));
	}
	for (int num: rhs_pos)
	{
		if (i < reducedPolynom.size())
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

std::string center(std::string input, int width) { 
    return (std::string((width - input.length()) / 2, ' ') + input);
}

std::string center(std::string str1, std::string str2, int width) { 
	std::string centered {};
	int spaces = (width - str1.length() - str2.length()) / 3;
    return (std::string(spaces, ' ') + str1 + std::string(spaces, ' ') + str2);
}

std::string removeZeros(std::string num)
{
	if (num.find(".000000") == std::string::npos)
		return (num);
	else
		return (num.erase(num.find(".000000")));
}

void printReducedForm(std::vector <double> &polynom)
{
	int i {0};
	char sign {'+'};
	std::string reducedForm {};
	std::cout << center("Reduced form:", 80) << std::endl;
	for (double num: polynom)
	{
		num >= 0.0 ? sign = '+' : sign = '-';
		if (i == 0)
			reducedForm = reducedForm + removeZeros(std::to_string(num)) + " ";
		else if (i == 1)
			reducedForm = reducedForm + sign + " " + removeZeros(std::to_string(num)) + " * X" + " ";
		else if (num > 0)
			reducedForm = reducedForm + sign + " " + removeZeros(std::to_string(num)) + " * X^" + std::to_string(i) + " ";
		else if (num < 0)
			reducedForm = reducedForm + sign + " " + removeZeros(std::to_string(num * 1)) + " * X^" + std::to_string(i) + " ";
		i++;
	}
	reducedForm = reducedForm + "= 0";
	std::cout << center(reducedForm, 80) << std::endl;
	printLine(80);
}

double ft_abs(double num)
{
	if (num < 0)
		num *= -1;
	return (num);
}

double ft_sqrt(double num)
{
	double oldGuess {0};
	double guess {1};
	
	if (num == 0.0)
		return (0.0);
	while (ft_abs(guess - oldGuess) > 0)
	{
		oldGuess = guess;
		guess = (guess + num/guess) / 2.0;
	}
	return (guess);
}

void solve2(std::vector <double> &polynom)
{
	double a = polynom.at(2);
	double b = polynom.at(1);
	double c = polynom.at(0);
	double d = (b * b - 4 * a * c);
	if (d >= 0.0)
	{
		double x1 = (-b + ft_sqrt(d)) / (2 * a);
		double x2 = (-b - ft_sqrt(d)) / (2 * a);
		std::cout << center("The Discriminant is strictly +", 80) << std::endl;
		printLine(80);
		std::cout << center("Solution(s):", 80) << std::endl;
		std::cout << center ("x1 = " + removeZeros(std::to_string(x1)), "x2 = " + removeZeros(std::to_string(x2)), 80) << std::endl;
	}
	else
	{	
		double real = -1 * (b / 2 * a);
		double complex = ft_sqrt(-1 * d) / (2 * a);
		std::cout << center("The Discriminant is strictly -", 80) << std::endl;
		printLine(80);
		std::cout << center("Complex solution(s):", 80) << std::endl;
		std::string x1 {};
		std::string x2 {};
		if (real == 0)
		{
			if (complex > 1)
			{
				x1 = "x1 = +" + removeZeros(std::to_string(complex)) + "i";
				x2 = "x2 = -" + removeZeros(std::to_string(complex)) + "i";
			}
			else
			{
				x1 = "x1 = +i";
				x2 = "x2 = -i";
			}
		}
		else
		{
			if (complex > 1)
			{
				x1 = "x1 = " + removeZeros(std::to_string(real)) + " + " + removeZeros(std::to_string(complex)) + "i";
				x2 = "x2 = " + removeZeros(std::to_string(real)) + " - " + removeZeros(std::to_string(complex)) + "i";
			}
			else
			{
				x1 = "x1 = " + removeZeros(std::to_string(real)) + " + " + "i";
				x2 = "x2 = " + removeZeros(std::to_string(real)) + " - " + "i";
			}
		}
		std::cout << center(x1, x2, 80) << std::endl;
	}
}

void solve1(std::vector <double> &polynom)
{
	double solution = (-1 * polynom.at(0) / polynom.at(1));
	std::cout << center("Solution:", 80) << std::endl;
	std::cout << center("x = " + std::to_string(solution), 80) << std::endl;
}

void printHeader()
{
	std::cout << std::endl;
	std::cout << center("######      ######                        ###", 80) << std::endl;
	std::cout << center("######      ##  ##                       ####", 80) << std::endl;
	std::cout << center("##          ##  ##                      ## ##", 80) << std::endl;
	std::cout << center("##          ######       #      #      ##  ##", 80) << std::endl;
	std::cout << center("##          ##            #    #           ##", 80) << std::endl;
	std::cout << center("######      ##             #  #            ##", 80) << std::endl;
	std::cout << center("######      ##              ##  #          ##", 80) << std::endl;
	std::cout << std::endl;
	printLine(80);
}

int main()
{
	std::string input {};
	do
	{
		system("CLS");
		printHeader();
		std::cout << "Enter a polynom: ";
		getline(std::cin, input);
		printLine(80);
//		std::string polynom_str {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"};
//		std::string polynom_str {"0 * X^0 + 0 * X^1 - 1 * X^2 = 0 * X^0"};
//		std::string polynom_str {"4 * X^0 + 3 * X^1 = 0 * X^0"};
//		std::string polynom_str {"37 * X^0 + 12 * X^1 + 1 * X^2 = 0 * X^0"};
//		std::string polynom_str {"1 * X^0 + 0 * X^1 + 1 * X^2 = 0 * X^0"};
		std::string polynom_str = input;
		std::string lhs = getLHS(polynom_str);
		std::string rhs = getRHS(polynom_str);
		std::vector <double> reducedPolynom = getPolynom(lhs, rhs);
		int degree = reducedPolynom.size() - 1;
		if (degree != 0)
			printReducedForm(reducedPolynom);
		std::cout << center("Polynomial degree: ", 78) << degree << std::endl;
		printLine(80);
		if (degree > 2)
			std::cout << "The polynomial degree is strictly greater than 2, I'm afraid I can't solve that just yet, sorry.";
		else if (degree == 2)
			solve2(reducedPolynom);
		else if (degree == 1)
			solve1(reducedPolynom);
		else if (degree == 0)
			std::cout << "All real numbers are a solution." << std::endl;
	printLine(80);
	std::cout << "Do you want to solve another polynom? Y/N ";
	getline(std::cin, input);
	} while (input == "y" || input == "Y" || input == "yes");
	return (0);
}
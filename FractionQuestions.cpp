/*
Robert Giglio III
10/17/2016
Case Project 1, pg 330 chapter 7
*/

#include<iostream>
#include<ctime>
using namespace std;

class Fraction
{
private:
	int wholeNumber;
	int numerator;
	int denominator;
public:
	const static char SLASH;
	Fraction(int = 0, int = 1);
	Fraction(int, int, int);
	//Fraction methods
	void reduceFraction();
	int getWholeNumber();
	int getNumerator();
	int getDenominator();
	Fraction calcRecip();
	//overloaded methods
	friend ostream& operator<<(ostream&, Fraction&);
	friend istream& operator >> (istream&, Fraction&);
	bool operator==(Fraction&);
	bool operator>(Fraction&);
	bool operator<(Fraction&);
	Fraction operator+(Fraction);
	Fraction operator-(Fraction);
	Fraction operator*(Fraction);
	Fraction operator/(Fraction);
};

const char Fraction::SLASH = '/';

Fraction::Fraction(int numer, int denom)
{
	wholeNumber = 0;
	numerator = numer;
	if (denom <= 0)
		denominator = 1;
	else
		denominator = denom;

	this->reduceFraction();
}

Fraction::Fraction(int whole, int numer, int denom)
{
	wholeNumber = whole;
	numerator = numer;
	if (denom <= 0)
		denominator = 1;
	else
		denominator = denom;

	this->reduceFraction();
}

void Fraction::reduceFraction()
{
	//determine if the fraction is more than 1
	if (numerator > denominator)
	{
		int reduce = numerator / denominator;
		wholeNumber += reduce;
		numerator = numerator % denominator;
	}
	//determine if the fraction can be further reduced
	for (int j = numerator; j > 0; j--)
	{
		if (numerator % j == 0)
		{
			if (denominator % j == 0)
			{
				numerator = numerator / j;
				denominator = denominator / j;
				break;
			}
		}
	}
	//when fraction is reduced to 1/1
	if (numerator == 1 && denominator == 1)
	{
		wholeNumber += 1;
		numerator = 0;
	}
	if (numerator == 0 && wholeNumber == 0)
	{
		denominator = 1;
	}
}

int Fraction::getWholeNumber()
{
	return wholeNumber;
}

int Fraction::getNumerator()
{
	return numerator;
}

int Fraction::getDenominator()
{
	return denominator;
}


ostream& operator<<(ostream& out, Fraction& frac)
{
	//display fractions reduced properly
	if (frac.wholeNumber == 0 && frac.numerator == 0)
	{
		out << "0";
	}
	else if (frac.wholeNumber == 0)
	{
		out << frac.numerator << Fraction::SLASH << frac.denominator;
	}
	else if (frac.numerator == 0)
	{
		out << frac.wholeNumber;
	}
	else
	{
		out << frac.wholeNumber << " " << frac.numerator << frac.SLASH << frac.denominator;
	}

	return out;
}


istream& operator >> (istream& in, Fraction& frac)
{
	frac.denominator = 0;
	cout << "Please enter an integer for the whole-number portion of the fraction: ";
	in >> frac.wholeNumber;
	cout << "Please enter an integer for the numerator of the fraction: ";
	in >> frac.numerator;
	while (frac.denominator < 1)
	{
		cout << "Please enter an integer (>0) for the denominator of the fraction: ";
		in >> frac.denominator;
	}
	cout << endl;
	return in;
}

bool Fraction::operator==(Fraction& f2)
{
	if (this->wholeNumber == f2.wholeNumber && this->numerator == f2.numerator && this->denominator == f2.denominator)
		return true;
	else
		return false;

}

bool Fraction::operator>(Fraction& f2)
{
	if (this->wholeNumber > f2.wholeNumber)
		return true;
	else
		if (this->denominator < f2.denominator)
			return true;
		else
			if (this->numerator > f2.numerator)
				return true;
			else
				return false;
}

bool Fraction::operator<(Fraction& f2)
{
	if (this->wholeNumber < f2.wholeNumber)
		return true;
	else
		if (this->denominator > f2.denominator)
			return true;
		else
			if (this->numerator < f2.numerator)
				return true;
			else
				return false;
}

Fraction Fraction::operator+(Fraction f2)
{
	Fraction f3;
	f3.wholeNumber = this->wholeNumber + f2.wholeNumber;
	f3.denominator = this->denominator * f2.denominator;

	f3.numerator = ((this->numerator * f2.denominator) + (f2.numerator * this->denominator));
	f3.reduceFraction();
	return f3;
}

Fraction Fraction::operator-(Fraction f2)
{
	Fraction f3;
	f3.wholeNumber = this->wholeNumber - f2.wholeNumber;
	f3.denominator = this->denominator * f2.denominator;
	f3.numerator = ((this->numerator * f2.denominator) - (f2.numerator * this->denominator));
	f3.reduceFraction();
	return f3;
}

Fraction Fraction::operator*(Fraction f2)
{
	int newNumerator1, newNumerator2;
	Fraction f3;
	newNumerator1 = (this->wholeNumber * this->denominator) + this->numerator;
	newNumerator2 = (f2.wholeNumber * f2.denominator) + f2.numerator;

	f3.numerator = newNumerator1 * newNumerator2;
	f3.denominator = this->denominator * f2.denominator;
	f3.wholeNumber = 0;
	f3.reduceFraction();
	return f3;

}

Fraction Fraction::calcRecip()
{
	int temp;
	Fraction recipricol;
	temp = this->numerator;
	recipricol.numerator = this->denominator;
	recipricol.denominator = temp;
	return recipricol;
}

Fraction Fraction::operator/(Fraction f2)
{
	Fraction recip = f2.calcRecip();
	Fraction f3 = this->operator*(recip);
	f3.reduceFraction();
	return f3;
}

//Math problem class
class MathProblem
{
private:
	Fraction first, second, user, correct;
	char op;
	bool isAnswerCorrect;
public:
	MathProblem();
	MathProblem(Fraction, Fraction, char op);
	char setOperator();
	void setCorrect();
	void swapFraction();
	void displayProblem();
	void askUserForAnswer();
	void showAnswer();
	void showIsCorrect();
	void cycle();
	bool getIsCorrect();
	static int strikes;
};

int strikes = 0;

MathProblem::MathProblem()
{
	first = second = user = correct = Fraction();
}

MathProblem::MathProblem(Fraction f1, Fraction f2, char oper)
{
	first = f1;
	second = f2;
	op = oper;
	isAnswerCorrect = false;
	user = Fraction();
}

char MathProblem::setOperator()
{
	cout << "Enter an operator ( + , - , * , / ): ";
	cin >> op;
	return op;
}

void MathProblem::setCorrect()
{
	if (op == '+')
		correct = first + second;
	else if (op == '-')
	{
		cout << "Checking fraction size...." << endl;
		if (first < second)
			swapFraction();
		
		correct = first - second;
	}
	else if (op == '*')
		correct = first * second;
	else if (op == '/')
		correct = first / second;
}

void MathProblem::swapFraction()
{
	Fraction temp;
	temp = first;
	first = second;
	second = temp;
}

void MathProblem::displayProblem()
{

	cout << "What is " << first << " " << op << " " << second << "?" << endl;
}

void MathProblem::askUserForAnswer()
{
	cout << "What is your answer:" << endl;
	cin >> user;
	user.reduceFraction();
	if (user == correct)
		isAnswerCorrect = true;
}

void MathProblem::showAnswer()
{
	cout << correct << endl;
}

void MathProblem::showIsCorrect()
{
	if (isAnswerCorrect)
		cout << "That is correct" << endl;
	else
		cout << "That is incorrect" << endl;
}

void MathProblem::cycle()
{
	setCorrect();
	displayProblem();
	askUserForAnswer();
	showIsCorrect();
	cout << "The correct answer is : ";
	showAnswer();
}

bool MathProblem::getIsCorrect()
{
	return isAnswerCorrect;
}

int main()
{
	const int MAX = 10;
	int number, number2;
	Fraction frac[MAX];
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX; i++)
	{
		number = (rand() % 5) + 1;
		number2 = 6 +(rand() % (10-6+1));
		if (number2 > 10)
			number2 - 6;
		frac[i] = Fraction(number, number2);
		frac[i].reduceFraction();
	}
	cout << "Ok! Now that we're loaded up are you ready for a drill?!" << endl;
	MathProblem problem[5];
	int numCorrect = 0, totalStrikes = 0;
	double avg;
	char oper = problem[0].setOperator();
	for (int i = 0; i < 5; i++)
	{
		problem[i] = MathProblem(frac[rand() % 10], frac[rand() % 10], oper);
		while (strikes < 3 && !problem[i].getIsCorrect())
		{
			problem[i].cycle();
			if (problem[i].getIsCorrect())
			{
				numCorrect += 1;
				strikes = 0;
			}
			else
			{
				strikes++;
				totalStrikes++;
			}
			cout << endl;
		}
	}
	avg = (numCorrect / 5.0) * 100;
	cout << "\n\nYou got " << numCorrect << " out of 5, which is " << avg << " percent." << endl;
	cout << "And you also got " << totalStrikes << " retries...." << endl;

	system("pause");
	return 0;
}
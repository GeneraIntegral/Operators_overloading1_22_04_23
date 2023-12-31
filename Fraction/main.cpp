#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

using std::cout;

// #define DEBUG
// #define Test

#define tab "\t"
#define delimiter cout << "|------------------------------------------------------------------------------|" << endl;
#define HOME_WORK1

// ���������� ������
class Fraction;

// ���������� ������������� ����������
Fraction operator+(Fraction Left, Fraction Right);
Fraction operator-(Fraction Left, Fraction Right);
Fraction operator*(Fraction Left, Fraction Right);
Fraction operator/(const Fraction& Left, const Fraction& Right);

bool operator==(const Fraction& Left, const Fraction& Right);
bool operator==(const double Left, const Fraction& Right);
bool operator!=(const Fraction& Left, const Fraction& Right);
bool operator<(const Fraction& Left, const Fraction& Right);
bool operator>(const Fraction& Left, const Fraction& Right);
bool operator<=(const Fraction& Left, const Fraction& Right);
bool operator>=(const Fraction& Left, const Fraction& Right);

// ���������� ������� ������������
void Test_Calculation_Operators(const Fraction& Left, const Fraction& Right);
void Test_Comparision_Operators(const Fraction& Left, const Fraction& Right);
void Test_Increment_Decrement_Operators(Fraction name);

void Test_Assignment_Operators(const Fraction& name);
class Fraction
{
private:
	int integer;     // ����� ����� �����
	int numerator;   // ��������� �����
	int denumerator; // ����������� �����
public:
	// get-set ������
	int get_int()const
	{
		return integer;
	}
	int get_num()const
	{
		return numerator;
	}
	int get_denum()const
	{
		return denumerator;
	}
	void set_int(int integer)
	{
		this->integer = integer;
	}
	void set_num(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denum(int denumerator)
	{
		denumerator != 0 ? this->denumerator = denumerator : this->denumerator = 1;
	}
	// Constructor
	Fraction()
	{
		integer = 0;
		numerator = 0;
		denumerator = 1;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		set_denum(denumerator);
#ifdef DEBUG
		cout << "1ArgConstructor";
#endif // DEBUG
	}
	Fraction(int numerator, int denumerator)
	{
		integer = 0;
		this->numerator = numerator;
		set_denum(denumerator);
#ifdef DEBUG
		cout << "Num / Denum constructor was used" << endl;
#endif // DEBUG
	}
	Fraction(int integer, int numerator, int denumerator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denum(denumerator);
#ifdef DEBUG
		cout << "Integer + Num / Denum constructor was used" << endl;
#endif // DEBUG
	}
	Fraction(double value, int precision = 100)
	{
		/* denumerator = precision;
		integer = (int)((value * denumerator) / denumerator);
		numerator = (int)(value * denumerator) % denumerator; */

		value += 1e-10;
		integer = value;
		value -= integer;
		denumerator = 1e9;
		numerator = value * denumerator;
		simplify();
#ifdef DEBUG
		cout << "DecimalConstructor was used\t" << this << endl;
#endif // DEBUG
	}
	// ����������� �����������
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denumerator = other.denumerator;
#ifdef DEBUG
		cout << "CopyConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Fraction()
	{
#ifdef DEBUG
		cout << "Destructor: \t" << this << endl;
#endif // DEBUG
	}

	// Type-cast operators:
	operator int()
	{
		toMixed();
		return integer;
	}
	operator double()
	{
		toImproper();
		return double(numerator) / denumerator;
	}
	// Method:
#ifdef DEBUG
	void Print() const
	{
		if (integer != 0)
			cout << integer << "|" << numerator << "/" << denumerator;
		else
			cout << numerator << "/" << denumerator;
		cout << endl;
	}
	// ����� ������� ����� ��� �����.
	string whichFraction() const
	{
		string result;
		if (integer > 0)
			return result = "����� ���������";
		else if (ifProper())
			return result = "����� ����������";
		else
			return result = "����� ������������";
	}
#endif // DEBUG
	   // ��������� �����
	Fraction& simplify()
	{
		int gcd = calculateGCD(numerator, denumerator);
		numerator /= gcd;
		denumerator /= gcd;
		return *this;
	}
	// Conversion Methods:
	// �������������� �� ������������ � ��������
	Fraction& toMixed()
	{
		integer += numerator / denumerator;
		numerator = numerator % denumerator;
		return *this;
	}
	// �� �������� � ������������
	Fraction& toImproper()
	{
		if (integer > 0)
		{
			numerator += integer * denumerator;
			integer = 0;
		}
		return *this;
	}
	// � ����������
	double todecimal() const
	{
		return (double)get_int() + ((double)get_num() / (double)get_denum());
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.toImproper();
		inverted.numerator ^= inverted.denumerator;
		inverted.denumerator ^= inverted.numerator;
		inverted.numerator ^= inverted.denumerator;
		return inverted;
	}
	// Operators : 
	Fraction& operator()(int integer, int numerator, int denumerator)
	{
		set_int(integer);
		set_num(numerator);
		set_denum(denumerator);
		return *this;
	}
	// �������� =
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denumerator = other.denumerator;
		return *this;
	}
	// �������� +=
	Fraction& operator+=(const Fraction& other)
	{
		return *this = *this + other;
	}
	// �������� -=
	Fraction& operator-=(const Fraction& other)
	{
		return *this = *this - other;
	}
	// �������� *=
	Fraction& operator*=(const Fraction& other)
	{
		this->numerator = (this->numerator + this->integer * this->denumerator) * (other.numerator + other.integer * other.denumerator);
		this->denumerator = this->denumerator * other.denumerator;
		simplify();
		toMixed();
		return *this;
	}
	// �������� /=
	Fraction& operator/=(const Fraction& other)
	{
		this->numerator = (this->numerator + this->integer * this->denumerator) * other.denumerator;
		this->denumerator = this->denumerator * (other.numerator + other.integer * other.denumerator);
		simplify();
		toMixed();
		return *this;
	}
	Fraction& operator++()
	{
		toMixed();
		integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		toMixed();
		Fraction old = *this;
		integer++;
		return old;
	}
	Fraction& operator--()
	{
		toMixed();
		integer--;
		return *this;
	}
	Fraction operator--(int)
	{
		toMixed();
		Fraction old = *this;
		integer--;
		return old;
	}
	// In-out
	friend istream& operator>>(istream& in, Fraction& name)
	{
		/* char slash = '/';
		char space = '|';
		in >> name.integer >> space >> name.numerator >> slash >> name.denumerator;
		return in; */
		const int size = 256;
		char buffer[size] = {};
		int number[3] = {};
		in.getline(buffer, size);
		int n = 0;                 // ���������� ��������� �����
		char delimiters[] = "() /";
		for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
		{
			number[n++] = atoi(pch);
		}
		name = Fraction();
		switch (n)
		{
		case 1: name.set_int(number[0]); break;
		case 2: name.set_num(number[0]); name.set_denum(number[1]); break;
		case 3: name(number[0], number[1], number[2]); break;
		}
		return in;
	}
	friend ostream& operator<<(ostream& out, const Fraction& name)
	{
		if (name.integer != 0)
			if (name.numerator != 0)
				out << name.integer << "|" << name.numerator << "/" << name.denumerator;
			else
				out << name.integer;
		else
			out << name.numerator << "/" << name.denumerator;
		return out;
	}
private:
	// ��������� ���������� ����� ��� ������������
	bool ifProper()const
	{
		return numerator < denumerator ? true : false;
	}
	// ���
	int calculateGCD(const int num, const int denum)const
	{
		if (denum == 0) {
			return num;
		}
		return calculateGCD(denum, num % denum);
	}
	// ���
	int calculateLCM(const int num, const int denum)const
	{
		int gcd = calculateGCD(num, denum);
		return (num * denum) / gcd;
	}
};
void main()
{
#ifdef Test
	setlocale(LC_ALL, "");
	Fraction A(2, 5, 7);
	Fraction B(1, 1, 8);
	Fraction C(10, 40);
	Fraction F(3.434);
	cout << F << endl;
	delimiter;
	Test_Calculation_Operators(A, C);
	delimiter;
	Test_Comparision_Operators(A, C);
	delimiter;
	Test_Increment_Decrement_Operators(A);
	delimiter;
	Test_Assignment_Operators(A);
	delimiter;
#endif // Test

#ifdef HOME_WORK1
	Fraction A = 2.33;
	cout << A << endl;
#endif // HOME_WORK1

}
// Operators:
Fraction operator+(Fraction Left, Fraction Right)
{
	Left.toImproper();
	Right.toImproper();
	return Fraction
	(
		(Left.get_num() * Right.get_denum()) + (Right.get_num() * Left.get_denum()),
		Left.get_denum() * Right.get_denum()
	).simplify().toMixed();
}
Fraction operator-(Fraction Left, Fraction Right)
{
	Left.toImproper();
	Right.toImproper();
	return Fraction
	(
		(Left.get_num() * Right.get_denum()) - (Right.get_num() * Left.get_denum()),
		Left.get_denum() * Right.get_denum()
	).simplify().toMixed();
}
Fraction operator*(Fraction Left, Fraction Right)
{
	Left.toImproper();
	Right.toImproper();
	return Fraction
	(
		Left.get_num() * Right.get_num(), Left.get_denum() * Right.get_denum()
	).simplify().toMixed();
}
Fraction operator/(const Fraction& Left, const Fraction& Right)
{
	return Left * Right.inverted();
}
bool operator==(const Fraction& Left, const Fraction& Right)
{
	return (int)(Left.todecimal() * 10000) == (int)(Right.todecimal() * 10000);
}
bool operator==(const double Left, const Fraction& Right)
{
	return (int)(Left * 10000) == (int)(Right.todecimal() * 10000);
}
bool operator!=(const Fraction& Left, const Fraction& Right)
{
	return !(Left == Right);
}
bool operator<(const Fraction& Left, const Fraction& Right)
{
	return Left.todecimal() < Right.todecimal() ? true : false;
}
bool operator>(const Fraction& Left, const Fraction& Right)
{
	return !(Left < Right);
}
bool operator<=(const Fraction& Left, const Fraction& Right)
{
	return Left < Right || Left == Right;
}
bool operator>=(const Fraction& Left, const Fraction& Right)
{
	return Left > Right || Left == Right;
}
// ���������� ������� ������������
void Test_Calculation_Operators(const Fraction& Left, const Fraction& Right)
{
	cout << "����� �������: " << Left << tab << "������ �������: " << Right << endl;
	cout << "�������� +: \t ���������: " << Left + Right << "\t" << (Left.todecimal() + Right.todecimal() == Left + Right ? " Correct " : " Wrong ") << endl;
	cout << "�������� -: \t ���������: " << Left - Right << "\t" << (Left.todecimal() - Right.todecimal() == Left - Right ? " Correct " : " Wrong ") << endl;
	cout << "�������� *: \t ���������: " << Left * Right << "\t" << (Left.todecimal() * Right.todecimal() == Left * Right ? " Correct " : " Wrong ") << endl;
	cout << "�������� /: \t ���������: " << Left / Right << "\t" << (Left.todecimal() / Right.todecimal() == Left / Right ? " Correct " : " Wrong ") << endl;
}
void Test_Comparision_Operators(const Fraction& Left, const Fraction& Right)
{
	cout << "����� �������: " << Left << tab << "������ �������: " << Right << endl;
	cout << "�������� ==: \t ���������: " << (Left == Right ? "Yes" : "No") << endl;
	cout << "�������� !=: \t ���������: " << (Left != Right ? "Yes" : "No") << endl;
	cout << "�������� <: \t ���������: " << (Left < Right ? "Yes" : "No") << endl;
	cout << "�������� >: \t ���������: " << (Left > Right ? "Yes" : "No") << endl;
	cout << "�������� <=: \t ���������: " << (Left <= Right ? "Yes" : "No") << endl;
	cout << "�������� >=: \t ���������: " << (Left >= Right ? "Yes" : "No") << endl;
}
void Test_Increment_Decrement_Operators(Fraction name)
{
	cout << "��������� ��������: " << name << endl;
	cout << "Increment++: " << name++ << tab << " > " << name << endl;
	cout << "++Increment: " << ++name << endl;
	cout << "Decrement--: " << name-- << tab << " > " << name << endl;
	cout << "--Decrement: " << --name << endl;
}
void Test_Assignment_Operators(const Fraction& name)
{
	cout << "�������: " << name << endl;
	Fraction Result;  

	Result = name;
	cout << "�������� = : " << Result << endl;
	Result += name;
	cout << "�������� += : " << Result << endl;
	Result -= name;
	cout << "�������� -= : " << Result << endl;
	Result *= name;
	cout << "�������� *= : " << Result << endl;
	Result /= name;
	cout << "�������� /= : " << Result << endl;
}
// this program shows how constructors and destructors work

#include <iostream>
#include <cassert>
using namespace std;
class big3
{
public:
	big3();
	big3(int n);

	big3(big3 &obj);
	// Copy constructor
	// Postcondition: a new object has been created with *P == *(obj.p) and p != obj.p

	~big3();
	// destructor
	// Postcondition: returns or releases the dynamic memory back to the system when a big-3 object goes out of scope

	big3& operator=(big3 &rhs);
	// Postcondition: rhs is returned by reference

	void display();

private:
	int *p;
};

big3::big3()		// default constructor
{
	p = new int[1];
	for (int i = 0; i < 9; i++)
	{
		p[i] = 1;
	}
}

big3::big3(int n)		// constructor with parameter
{
	p = new int[n];
	for (int i = 0; i < 9; i++)
	{
		p[i] = (n + 1);
	}
}





void big3::display()
{
	cout << "   &p = " << int(&p) << endl;
	cout << "    p = " << int(p) << endl;
	cout << "   *p = " << *p << endl;
}

big3& big3::operator=(big3 &rhs)
{
	if (&rhs != this)
		*p = *(rhs.p);

	return *this;
}

big3::big3(big3 &b)
{
	p = new int [];
	*p = *(b.p);
	/*data = new int[];
	for (int i = 0; i < capacity; i++)
	{
		*data = *(ctainer.data);
	}*/
}

big3::~big3()		// destructor
{
	cout << "Destructor called; dynamic memory returned!" << endl;
	delete p;
}

int main()
{
	big3 b1(11), b2, b3(b1);

	cout << "Object b1:" << endl;
	b1.display();
	cout << endl;

	cout << "Object b2:" << endl;
	b2 = b1;
	b2.display();
	cout << endl;

	cout << "Object b3:" << endl;
	b3.display();
	cout << endl;

	return 0;
}

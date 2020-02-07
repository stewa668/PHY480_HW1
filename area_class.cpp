//  file: area.cpp
//
//  This program calculates the area of a circle, given the radius.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02-Jan-2004  original version, for 780.20 Computational Physics
//      01-Jan-2010  updates to "To do" wishlist
//      12-Jan-2016  comment out "using namespace std;"
//
//  Notes:  
//   * compile with:  "g++ -o area.x area.cpp"
//
//  To do:
//   1. output the answer with higher precision (more digits)
//   2. use a "predefined" value of pi or generate it with atan
//   3. define an inline square function
//   4. split the calculation off into a function (subroutine)
//   5. output to a file (and/or input from a file)
//   6. add checks of the input (e.g., for non-positive radii)
//   7. rewrite using a Circle class
//
//*********************************************************************// 

// include files
#include <iostream>		// this has the cout, cin definitions
#include <iomanip>
#include <cmath>
#include <fstream>
using namespace std;		// if omitted, then need std::cout, std::cin 

//*********************************************************************//

const double pi = 4. * atan (1.);	// define pi as a constant 

class Circle
{
private:
  double radius;
  double circ;
  double area;
public:
  // Constructor
    Circle (double r);
  double GetRadius ();
  double GetArea ();
  double GetCirc ();
  void ChangeRadius (double r);
  void ChangeArea (double a);
  void ChangeCirc (double c);
};

Circle::Circle (double r)	//constructor
{
  radius = r;
  circ = 2. * pi * r;
  area = pi * r * r;
}

double
Circle::GetRadius ()
{
  return radius;
}

double
Circle::GetCirc ()
{
  return circ;
}

double
Circle::GetArea ()
{
  return area;
}

void
Circle::ChangeRadius (double r)
{
  radius = r;
  circ = 2. * pi * r;
  area = pi * r * r;
}

void
Circle::ChangeCirc (double c)
{
  radius = c / (2. * pi);
  circ = c;
  area = (c * c) / (4. * pi);
}

void
Circle::ChangeArea (double a)
{
  radius = sqrt (a / pi);
  circ = 2. * pi * sqrt (a / pi);
  area = a;
}

int
main ()
{
  double r;			// every variable is declared as int or double or ...
  ofstream out ("area_class.out");
  cout << "Enter the radius of a circle: ";	// ask for radius
  cin >> r;
  Circle circle (r);
  if (r > 0)
    {
      cout << "radius = " << setprecision (17) << circle.GetRadius () <<
	",  circumference = " << circle.GetCirc () <<
	",  area = " << circle.GetArea () << endl;
      out << "radius = " << setprecision (17) << circle.GetRadius () <<
	",  circumference = " << circle.GetCirc () <<
	",  area = " << circle.GetArea () << endl;
      cout << "" << endl;
      out << "" << endl;
    }
  else
    {
      cout << "whoops" << endl;
    }

  double a;
  cout << "Enter the area of a circle: ";	// ask for area, get other values.
  cin >> a;

  if (a > 0)
    {

      circle.ChangeArea (a);

      cout << "radius = " << setprecision (17) << circle.GetRadius () <<
	",  circumference = " << circle.GetCirc () <<
	",  area = " << circle.GetArea () << endl;
      out << "radius = " << setprecision (17) << circle.GetRadius () <<
	",  circumference = " << circle.GetCirc () <<
	",  area = " << circle.GetArea () << endl;
      cout << "" << endl;
      out << "" << endl;
    }
  else
    {
      cout << "whoops" << endl;
    }
  return 0;			// "0" for successful completion
}

//*********************************************************************//

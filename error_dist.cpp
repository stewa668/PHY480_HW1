// error_dist.cpp
//
// Time to make a histogram
// This should tell us the approximate distribution, though 
// we can't use matplotlib, which brings a tear to my eye.
//
// I will also say for the sake of convieniece that doubles 
// are representative of the exact answer.
//

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
#include <cmath>
using namespace std;

// Globals
const float xmin = -1e-7;
const float xmax = 1e-7;
const float xrange = 2e-7;	// Only solved analytically to reduce potential error
const int bins = 101;

int
main ()
{

  int y[bins] = {0};
  for (int v = 1; v < 10000; v++)
    {

      for (int j = 0; j < 5; j++)
	{
          float x1 = 1./sqrt(v);
          double x2 = 1./sqrt(v);
          double x = (x1 - x2)/x2;
	  int i = (x - xmin) * bins / xrange;
	  if (i < bins)
	    {
	      y[i] += 1;
	    }
	}

    }
  ofstream out ("error_dist.dat");
  float x = 0;
  for (int i = 0; i < bins; i++)
    {
      x = i * (xrange / bins) + xmin;	  
      out << setprecision (17) << setw (20) << x << "   " << y[i] << endl;
    }

}

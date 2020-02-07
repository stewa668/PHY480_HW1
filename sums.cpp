//  file: sums.cpp
//
// Difference summing up and down with a 1/N series
//
// I put answer to question in answers.txt
//
//*********************************************************************// 

// include files
#include <iostream>		// this has the cout, cin definitions
#include <iomanip>
#include <cmath>
#include <fstream>
using namespace std;		// if omitted, then need std::cout, std::cin 

//*********************************************************************//

float
SumUp (long N)			// function for sum up
{
  float S = 0;
  for (long n = 1; n <= N; n++)
    {
      S += (1. / n);
    }
  return S;
}

float
SumDown (long N)			// function for sum down
{
  float S = 0;
  for (long n = N; n >= 1; n--)
    {
      S += (1. / n);
    }
  return S;
}

int
main ()
{
  float Su, Sd, Error;
  ofstream out ("sums.dat");
  out << "# log(N) log(Error)" << endl;
  for (long N = 1; N < 1e9; N *= 2)
    {
      Su = SumUp (N);
      Sd = SumDown (N);
      Error = 2 * fabs (Su - Sd) / (fabs (Su) + fabs (Sd));
      out << setprecision (17) << log10 (N) << "  " << log10 (Error) << endl;
    }

  return 0;			// "0" for successful completion
}

//*********************************************************************//

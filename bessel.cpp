//  file: bessel.cpp 
//
//  Spherical Bessel functions via up and down recursion      
//
//  Notes:
//  bessel_log 
//  For x < l, downward recursion is the most accurate. This is essentially because
//  downward recursion fits to the J_ls that dominate for lower x values.
//  
//  For l < x < lmax/start, the difference between them is negligable. This is 
//  the "sweet zone" so to speak, and can be made quite large.
//  
//  For x > start, downward recursion falls apart. This is actually something that
//  can be remedied through a better choice of J_50 and J_49, but in our case, where
//  we set them equal, this breaking point becomes evident at around x = 50.5, where
//  J_50 = J_49 = J_48 = .. = J_1 = J_0. This is obviously wrong, and establishes a 
//  decent boundary in my opinion. 
//  
//************************************************************************

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
#include <cmath>
#include <gsl/gsl_sf_bessel.h>	// gsl Bessel special function header file
using namespace std;		// we need this when .h is omitted

// function prototypes 
double down_recursion (double x, int n, int m);	// downward algorithm 
double up_recursion (double x, int n);	// upward algorithm 

// global constants  
const double xmax = 100.0;	// max of x  
const double xmin = 0.1;	// min of x >0  
const double step = 0.1;	// delta x  
const int order = 10;		// order of Bessel function 
const int start = 50;		// used for downward algorithm 

//********************************************************************
int
main ()
{
  double ans_down, ans_up, relerr, gslthing, relerrg;

  // open an output file stream
  ofstream my_out ("bessel.dat");
  ofstream my_out2 ("bessel_log.dat");

  my_out << "# Spherical Bessel functions via up and down recursion" << endl;
  my_out << "# x    d_rec    u_rec    gsl    relerr_ud   relerr_dg" << endl;

  my_out2 << "# Spherical Bessel functions via up and down recursion" << endl;
  my_out2 << "# x    d_rec    u_rec    gsl    relerr_ud   relerr_dg" << endl;

  // step through different x values
  for (double x = xmin; x <= xmax; x += step)
    {
      ans_down = down_recursion (x, order, start);
      ans_up = up_recursion (x, order);
      gslthing = gsl_sf_bessel_jl (10, x);
      relerr = fabs (ans_down - ans_up) / (fabs (ans_down) + fabs (ans_up));
      relerrg = fabs (gslthing - ans_up) / (fabs (gslthing) + fabs (ans_up));

      my_out << fixed << setprecision (6) << setw (8) << x << " "
	<< scientific << setprecision (8)
	<< setw (15) << ans_down << " "
	<< setw (15) << ans_up << " "
	<< setw (15) << gslthing << " "
	<< setw (15) << relerr << " " << setw (15) << relerrg << endl;

      my_out2 << fixed << setprecision (6) << setw (8) << log10 (x) << " "
	<< scientific << setprecision (8)
	<< setw (15) << log10 (ans_down) << " "
	<< setw (15) << log10 (ans_up) << " "
	<< setw (15) << log10 (gslthing) << " "
	<< setw (15) << log10 (relerr) << " "
	<< setw (15) << log10 (relerrg) << endl;
    }
  cout << "data stored in bessel.dat and bessel_log.dat." << endl;

  // close the output file
  my_out.close ();
  return (0);
}


//------------------------end of main program----------------------- 

// function using downward recursion  
double
down_recursion (double x, int n, int m)
{
  double j[start + 2];		// array to store Bessel functions 
  j[m + 1] = j[m] = 1.;		// start with "something" (choose 1 here) 
  for (int k = m; k > 0; k--)
    {
      j[k - 1] = ((2. * double (k) + 1.) /x) * j[k] - j[k + 1];	// recur. rel.
    }
  double scale = (sin (x) / x) / j[0];	// scale the result 
  return (j[n] * scale);
}


//------------------------------------------------------------------ 

// function using upward recursion  
double
up_recursion (double x, int n)
{
  double term_three = 0.;
  double term_one = (sin (x)) / x;	// start with lowest order 
  double term_two = (sin (x) - x * cos (x)) / (x * x);	// next order
  for (int k = 1; k < n; k += 1)	// loop for order of function     
    {				// recurrence relation
      term_three = ((2. * double (k) + 1.) /x) * term_two - term_one;
      term_one = term_two;
      term_two = term_three;
    }
  return (term_three);
}

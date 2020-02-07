#  file: derivative_test.plt 
#
#  Gnuplot plot file for derivative_test output
#  
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
# 
#  Revision history
#   2004-01-24  original version for 780.20 session 5
#   2004-01-16  added postscript enhanced and comments for session 4
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Roundoff Error'
set xlabel 'Error'
set ylabel 'Counts'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [-1e-7:1e-7]
#set yrange [-8:0]

# fit the curve
#f1(x) = a1*x + b1
#fit [4:6] f1(x) "sums.dat" using ($1):($2) via a1, b1
#fit_title1 = sprintf("%-+4.1f*x %-+4.1f",a1,b1)

# set the terminal type to be the screen (which is x11 here)
set term x11

# plot the data as well as the fit, with appropriate titles 
plot "error_dist.dat" using ($1):($2) smooth freq with boxes # , \
 #    a1*x + b1 title fit_title1

# output the plot to the file derivative_test_plt.ps   
set out "error_dist.ps"
set term postscript color enhanced
replot
set out "error_dist.pdf"
set term pdf
replot

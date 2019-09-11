#set terminal dumb #lol
#set terminal pdf size 8, 8
#set output 'convergenceRate.pdf'

set datafile separator ","

set multiplot layout 2, 1 title "Task3 solution" font ",14"

set grid

set title 'Convergence Rate'
set xlabel 'Iteration'
set ylabel 'Error' 

set logscale y

plot \
'f1.csv' u ($0+1):1 w lp title 'Left Riemann Sum',\
'f1.csv' u ($0+1):2 w lp title 'Right Riemann Sum',\
'f1.csv' u ($0+1):3 w lp title 'Trapezoidal Rule',\
'f1.csv' u ($0+1):4 w lp title 'SimpsonRule'

plot \
'f2.csv' u ($0+1):1 w lp title 'Left Riemann Sum',\
'f2.csv' u ($0+1):2 w lp title 'Right Riemann Sum',\
'f2.csv' u ($0+1):3 w lp title 'Trapezoidal Rule',\
'f2.csv' u ($0+1):4 w lp title 'SimpsonRule'

unset multiplot

#set terminal qt
#set output
#replot
	

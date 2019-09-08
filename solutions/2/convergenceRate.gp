#set terminal dumb #lol
set terminal pdf
set output 'convergenceRate.pdf'

set grid

set title 'Convergence Rate'
set xlabel 'Iteration'
set ylabel 'Error' 

set logscale y

set xrange [0:21]

plot 'dichotomy.csv' u ($0+1):1 w lp title 'Dichotomy',\
'fixedPointIteration.csv' u ($0+1):1 w lp title 'Fixed Point Iteration method',\
'newthon.csv' u ($0+1):1 w lp title 'Newthon method', 0.0000005 title 'Error threshold' 

set terminal qt
set output
replot

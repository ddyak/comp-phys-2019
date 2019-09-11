#set terminal dumb #lol
set terminal pdf size 8, 8
set output 'NewtonMethod.pdf'

set datafile separator ","

set grid

set title 'Newthon Method'
set xlabel 'x'
set ylabel 'f(x)' 

plot 'interpolations.csv' u 1:2 w l title 'Lagrange',\
     'interpolations.csv' u 1:3 w l title 'Newton' 

set terminal qt
set output
replot
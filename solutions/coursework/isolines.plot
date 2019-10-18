set auto
set surface
unset contour
set cntrparam levels 5
set cntrparam linear
set samples 100
set logscale z
set hidden3d
set isosamples 60
set ticslevel 0.
set view 20,340	#HBB: ,1,2
set xlabel "x"
set ylabel "y"
Rosenbrock(x,y) = (1-x)**2 + 100*(y - x**2)**2

set title "Rosenbrock Function"
splot [-1.5:1.5] [-0.5:1.5] Rosenbrock(x,y)


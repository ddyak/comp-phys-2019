all: build
	xdg-open NewtonMethod.pdf

build:
	g++ --std=c++17 task5.cc -o task5
	./task5 1>/dev/null
	gnuplot interpolations.gp

clean:
	rm task5 *.csv

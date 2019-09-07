all: build
	xdg-open convergenceRate.pdf

build:
	g++ --std=c++17 task3.cc -o task3
	./task3
	gnuplot convergenceRate.gpi

clean:
	rm task3 *.csv

all: build
	xdg-open convergenceRate.pdf

build:
	g++ --std=c++17 task3.cc -o task3
	./task3 1>/dev/null
	gnuplot convergenceRate.gp

clean:
	rm task3 *.csv

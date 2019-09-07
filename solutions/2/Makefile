all:
	./task2
	xdg-open convergenceRate.pdf

build:
	g++ task2.cc -o task2
	./task2 1>/dev/null
	gnuplot convergenceRate.gpi

clean:
	rm task2 *.csv

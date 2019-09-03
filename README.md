Basics of computational physics. Autumn 2019, NSU, Physics Department.

The code is placed "as is".

D.Y.


### Requirements:

First: **Delete Windows, Install Linux**.

Second:
```console
git clone https://github.com/ddyak/comp-phys-2019
git submodule update --init
apt-get install python3-numpy
pip3 install numpy matplotlib
```

### Compile:

```console
g++ 8.cc -I/usr/include/python3.6 `python3.6-config --ldflags` -lpython3.6
```

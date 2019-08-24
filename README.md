Basics of computational physics. Autumn 2019, NSU, Physics Department.

The code is placed "as is".

D.Y.


**Requirements:**

0. Delete Windows, Install Linux.
1. git clone https://github.com/ddyak/comp-phys-2019
2. git submodule update --init
3. apt-get install python3-numpy
4. pip3 install numpy matplotlib

**Compile:**

g++ 8.cc -I/usr/include/python3.6 \`python3.6-config --ldflags\` -lpython3.6

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <limits>

template <typename T>
void foo()
{
    T e = 1;
    int iter{0};
    for (; (1 + e/2) != 1; e /= 2, ++iter);
    std::cout << "Machine e (or ULP): " << e << std::endl;
    std::cout << "Mantis depth (bits): " << iter << std::endl;

    std::vector<std::pair<T, std::string>> forcompare = {{1, "1"}, {1 + e / 2, "1+e/2"}, {1 + e, "1+e"}, {1 +  e + e / 2, "1+e+e/2"}};
    for (std::size_t i = 0; i < forcompare.size(); ++i)
        for (std::size_t j = i; j < forcompare.size(); ++j)
            std::cout << forcompare[i].second << " == " << forcompare[j].second << ": "
                      << (forcompare[i].first == forcompare[j].first) << std::endl;

    T temp = 1.;
    for (temp = 1., iter=0; temp < std::numeric_limits<T>::max(); temp*=2, ++iter);
    std::cout << "Max exponent: " << (iter - 1) << "\t: Max value: " << std::numeric_limits<T>::max() << std::endl; 
    for (temp = 1., iter=0; temp >= std::numeric_limits<T>::min(); temp/=2, --iter);
    std::cout << "Min exponent: " << (iter + 1) << "\t: Min value: " << std::numeric_limits<T>::min() << std::endl; 
}

int main()
{
    foo<float>(); // or float
    return 0;
}
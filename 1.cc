#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <limits>
#include <iomanip>
#include <typeinfo>

template <typename T>
void foo() 
{
    std::cout << "================================" << std::endl
              << "========== Type: " << typeid(T).name() << " =============" << std::endl
              << "================================" << std::endl;
    T e = 1;
    int iter;
    for (iter = 0; (1 + e/2) != 1; e /= 2, ++iter);
    std::cout << std::left << std::setw(21) << "Machine e (or ULP) :" << e << std::endl;
    std::cout << std::left << std::setw(21) << "Mantis depth (bits):" << iter << std::endl;

    const std::vector<std::pair<T, std::string>> forcompare = 
        {{1, "1"}, {1 + e / 2, "1+e/2"}, {1 + e, "1+e"}, {1 + e + e / 2, "1+e+e/2"}};
    
    for (std::size_t i = 0; i < forcompare.size(); ++i)
        for (std::size_t j = i; j < forcompare.size(); ++j)
            std::cout << std::right << std::setw(7) << forcompare[i].second << " == " 
                      << std::left  << std::setw(7) << forcompare[j].second << " : "
                      << std::boolalpha << (forcompare[i].first == forcompare[j].first) 
                      << std::endl;

    for (T temp = 1., iter = 0; temp < std::numeric_limits<T>::max(); temp*=2, ++iter);
    std::cout << "Max exponent :" << std::right << std::setw(5) << (iter - 1) 
              << "\nMax value: " << std::numeric_limits<T>::max() << std::endl; 
    for (T temp = 1., iter = 0; temp >= std::numeric_limits<T>::min(); temp/=2, --iter);
    std::cout << "Min exponent :" << std::right << std::setw(5) << (iter + 1) 
              << ":\nMin value: " << std::numeric_limits<T>::min() << std::endl; 
}

int main()
{
    foo<float>();
    foo<double>();
    return 0;
}

#include <iostream>

static const int iter = 10000;

float sum_desc()
{
    float sum{0.};
    for (int n = iter; n > 0; sum += (n % 2 ? -1.f : 1.f) / n--);
    return sum;
}

float sum_asc()
{ 
    float sum{0.};
    for (int n = 1; n <= iter; sum += (n % 2 ? -1.f : 1.f) / n++);
    return sum;
}

float sum_desc_separately()
{
    float sum_pos{0.}, sum_neg{0.};
    for (int n = iter - 1; n > 0; n-=2) sum_neg += -1.f / n;
    for (int n = iter    ; n > 0; n-=2) sum_pos += 1.f / n;
    return sum_pos + sum_neg;
}

float sum_asc_separately()
{
    float sum_pos{0.}, sum_neg{0.};
    for (int n = 1; n <= iter; n+=2) sum_neg += -1.f / n;
    for (int n = 2; n <= iter; n+=2) sum_pos += 1.f / n;
    return sum_pos + sum_neg;
}

int main()
{
    // Alternating Harmonic Series: ln2 = 0.69314718056 
    // In this task row is inverted => right answer -ln2
    std::cout << "1. descending:\t" << sum_desc() << std::endl;
    std::cout << "2. ascending:\t" << sum_asc() << std::endl;
    std::cout << "3. descending separately: " << sum_desc_separately() << std::endl;
    std::cout << "4. ascending separately:  " << sum_asc_separately() << std::endl;
    return 0;
}
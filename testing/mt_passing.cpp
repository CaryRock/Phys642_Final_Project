#include <iostream>
#include <random>

double Shift(double delta=0.75)
{
    static std::random_device rd;
    static std::seed_seq seed{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    static std::mt19937 mt(seed);
    static std::uniform_real_distribution<double> dist(-1,1);
    
    double shift = delta * dist(mt);

    return shift;
}

int main()
{

    for(int i = 0; i < 16; i++)
    {
        printf("%f\n",Shift());
    }

    return 0;
}

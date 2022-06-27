#include "matem.h"

double _k(double a, double b, double c, double d)
{
    return (b - a) / (d - c);
}

double _pk(double n)
{
    return M_PI * pow(n, 2);
}

double _d(double a, double b, double c)
{
    return pow(b, 2) - 4 * a * c;
}

double _lnv(double n, double k)
{
	return sqrt(pow(n, 2) + pow(k, 2));
}

double _ntp(double a, double b)
{
    return pow(a, b);
}

int _summ(int n, int k)
{
    return n + k;
}

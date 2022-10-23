#include <hw3.1.h>
#include <MyPotential.h>
#include <MyCosine.h>

std::complex<double> MyPotential::eval(const std::complex<double> r)
{
    std::complex<double> r2 = pow(r, 2);
    std::complex<double> r6 = pow(r, 6);
    std::complex<double> r_r2((r2.real() / (pow(r2.real(), 2) + pow(r2.imag(), 2))), (-r2.imag() / (pow(r2.real(), 2) + pow(r2.imag(), 2))));
    std::complex<double> r_r6((r6.real() / (pow(r6.real(), 2) + pow(r6.imag(), 2))), (-r6.imag() / (pow(r6.real(), 2) + pow(r6.imag(), 2))));
    

    return r2 - r6;
}

std::complex<double> MyCosine::eval(const std::complex<double> r)
{
    return cos(r);
}


/********************************/
#include <stdio.h>
#include <float.h>
#include <hw3.1.h>

double firstDerivative(Derivable& d, const double r)
{
    // Create complex input to derivable, imaginary part is step_size*i, which is ih
    double step_size = 10e-10;
    std::complex<double> complex_r(r, step_size);

    std::complex<double> output = d.eval(complex_r);
    
    return output.imag() / step_size;
}
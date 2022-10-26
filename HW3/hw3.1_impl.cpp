#include <hw3.1.h>
#include <MyPotential.h>
#include <MyCosine.h>

std::complex<double> MyPotential::eval(const std::complex<double> r)
{
  /* implement */
    std::complex<double> numerator(1.0, 0.0);
    return (numerator / pow(r, 2)) - (numerator / pow(r, 6)); 
}

std::complex<double> MyCosine::eval(const std::complex<double> r)
{
  /* implement */
    return cos(r);
}


/********************************/
#include <stdio.h>
#include <float.h>
#include <hw3.1.h>

double firstDerivative(Derivable& d, const double r)
{
    /* implement */
    // Create complex input to derivable, imaginary part is step_size*i, which is ih
    double step_size = 10e-10;
    std::complex<double> complex_r(r, step_size);

    std::complex<double> output = d.eval(complex_r);
    
    return output.imag() / step_size;
}
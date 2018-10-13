/* fft.cpp
 *
 * Author: William Anderson
 * Date: 8/28/2018
 *
 * FFT implementation based on Herbert Wilf's "Algorithms and Complexity"
 *
 * Problem statement:
 * (30 points) Fast Fourier Transform in two versions ([W] 2.5): dyadic
 * size ([W] p.53) and any size ([W] p.55).
 */

#include <iostream>
#include <complex>
#include <vector>

using std::complex;
using std::vector;

namespace P9DYADIC
{

/* Checks FFT() function arguments for validity */
bool check_args(int n, vector<complex<double>> x)
{

	if (!n)
	{
		std::cout << "Error: FFT size is zero. \n";
		return false;
	}

	if (!x.size())
	{
		std::cout << "Error: input vector is empty \n";
		return false;
	} else if (x.size() != (unsigned int)n)
	{
		std::cout << "Error: input vector size does not equal size argument \n";
		return false;
	}

	return true;
}

vector<complex<double>> FFT(int n, vector<complex<double>> x)
{
	vector<complex<double>> v_NULL = vector<complex<double>>();
	vector<complex<double>> fft;
	vector<complex<double>> evens, odds, u, v;
	complex<double> exp_arg, tau;
	complex<double> c_zero = complex<double>(0.0, 0.0);
	complex<double> i = complex<double>(0, 1); //i constant value
	double pi = 3.1415926535897932384626433832795;

	int j;
	int k;

	if (!check_args(n, x))
	{
		return v_NULL;
	}

	for (j = 0; j < n; j++)
	{
		fft.insert(fft.end(), c_zero);
	}

	if (n == 1)
	{
		fft[0] = x[0];
		return fft;
	} else
	{
		for (j = 0; j <= (n - 2); j += 2)
		{
			evens.push_back(x[j]);
			odds.push_back(x[j + 1]);
		}
	}

	u = FFT(n / 2, evens);
	v = FFT(n / 2, odds);

	for (k = 0; k < n; k++)
	{
		exp_arg = ((2 * pi * k) / n) * i;
		tau = std::exp(exp_arg);
		int index = k % (n / 2);
		fft[k] = u[index] + tau * v[index];
	}

	return fft;

}

}

namespace P9ALL
{
/* Imaginary unit constant */
complex<double> i = complex<double>(0, 1);
double pi = 3.1415926535897932384626433832795;

/* Function to represent: ξn = e2πi/n */
complex<double> xi(int n)
{
	if (n == 2)
	{
		return complex<double>(-1, 0);
	} else if (n == 4)
	{
		return i;
	} else
	{
		complex<double> result = std::exp((2 * pi / n) * i);
		/* Not sure why, but signs for imaginary component from this operation are reversed;
		 * swapping here to fix.
		 */
		result = complex<double>(real(result), -1 * imag(result));
		return result;
	}
}

/* This is_prime() is more efficient than my implementation, (simple brute force, decrementing
 * from n / 2), so I'm using it instead */

/* Credit: https://stackoverflow.com/questions/4424374/determining-if-a-number-is-prime
 * User: LostInTheCode*/
/* How this brute force piece works: All prime numbers (except 2 and 3) can be expressed
 * in the form 6k+1 or 6k-1, where k is a positive whole number. This code uses this fact,
 * and tests all numbers in the form of 6k+1 or 6k-1 less than the square root of the number
 * in question. This is in comparison to my original implementation which tests every number
 * which is less than the square root of the number in question.
 */
bool is_prime(int number)
{
	if (((!(number & 1)) && number != 2) || (number < 2)
			|| (number % 3 == 0 && number != 3))
		return (false);

	for (int k = 1; (36 * k * k - 12 * k) < number; ++k)
	{
		if ((number % (6 * k + 1) == 0) || (number % (6 * k - 1) == 0))
			return (false);
	}
	return true;
}

/* Brute force function to get factors, starts at n / 2 and decrements */
vector<int> get_factors(int n)
{
	int start = n / 2;

	vector<int> result = vector<int>();

	for (int j = start; j > 0; j--)
	{
		if (n % j == 0)
		{
			/* Found a factor */
			result.push_back(j);
			result.push_back(n / j);
			return result;
		}
	}
	std::cout << "Error: No factors for " << n << " found." << std::endl;

	/* Return NULL vector */
	return result;

}

/* Checks FFT() function arguments for validity */
bool check_args(int n, vector<complex<double>> x)
{

	if (!n)
	{
		std::cout << "Error: FFT size is zero. \n";
		return false;
	}

	if (!x.size())
	{
		std::cout << "Error: input vector is empty \n";
		return false;
	} else if (x.size() != (unsigned int)n)
	{
		std::cout << "Error: input vector size does not equal size argument \n";
		return false;
	}

	return true;
}

//Returns vector of complex numbers
vector<complex<double> > FFT(int n, vector<complex<double> > x)
{
	vector<complex<double>> v_NULL = vector<complex<double>>();
	vector<complex<double> > fft;
	complex<double> c_zero = complex<double>(0.0, 0.0);
	int j;
	int k;
	int m;

	if (!check_args(n, x))
	{
		return v_NULL;
	}

	for (j = 0; j < n; j++)
	{
		fft.push_back(c_zero);
	}

	if (is_prime(n))
	{
		/* n is prime */
		for (j = 0; j < n; j++)
		{
			/* use book's definition to calculate fft[j] */
			complex<double> sum = c_zero;
			for (k = 0; k < n; k++)
			{
				complex<double> term1 = x[k];
				complex<double> term2 = std::pow(xi(n), j * k);
				complex<double> toAdd = term1 * term2;
				sum += toAdd;
			}
			fft[j] = sum;
		}
		return fft;
	} else
	{
		/* n is composite */
		vector<int> factors = vector<int>();
		int r1, r2;

		factors = get_factors(n);

		if (factors.empty())
		{
			std::cout << "Found no factors for " << n << " exiting... \n";
			exit(EXIT_FAILURE);
		} else
		{
			r1 = factors[0];
			r2 = factors[1];
		}

		/* 'a' is a vector of vectors, of length r1 */
		vector<vector<complex<double>>> a;

		for (k = 0; k < r1; k++)
		{
			a.push_back(v_NULL);
		}

		for (k = 0; k < r1; k++)
		{
			/* initialize vector 'a' with null vectors */
			vector<complex<double>> newx = v_NULL;
			/* m = multiplier */
			for (m = 0; m < r2; m++)
			{
				complex<double> item = x[k + m * r1];
				newx.push_back(item);
			}

			/* recursive call to FFT() stored in 'a' */
			a[k] = FFT(r2, newx);
			/* check that a[k] has size r2 */
			if (a[k].size() != (unsigned int)r2)
			{
				std::cout << "ak vector is not size r2." << std::endl;
			}
		}

		for (j = 0; j < n; j++)
		{
			/* use book's definition to calculate fft[j] */
			complex<double> sum = c_zero;
			for (k = 0; k < r1; k++)
			{
				complex<double> term1 = a[k][j % r2];
				complex<double> term2 = pow(xi(n), k * j);
				complex<double> toAdd = term1 * term2;
				sum += toAdd;
			}
			fft[j] = sum;
		}
		return fft;
	}
}
}

int main(int argc, char** argv)
{
	std::cout << "========== Problem 9: FFT, Dyadic Size ========== \n";

	vector<complex<double>> v_NULL = vector<complex<double>>();
	vector<complex<double>> test_values;
	vector<complex<double>> results_fft;
	complex<double> item;

	int n = 16;
	int i;

	test_values = v_NULL;
	std::cout << "Input data (n = " << n << "):\n";
	for (i = 0; i < n; i++)
	{
		test_values.push_back(complex<double>(i, 0));
		if (std::imag(test_values[i]) >= 0)
		{
			std::cout << "[" << i << "] = " << std::real(test_values[i])
					<< " + " << std::imag(test_values[i]) << "i \n";
		} else
		{
			std::cout << "[" << i << "] = " << std::real(test_values[i])
					<< " - " << std::imag(test_values[i]) << "i \n";
		}
	}
	results_fft = P9DYADIC::FFT(n, test_values);

	std::cout << "\nFFT() results: \n";
	for (int i = 0; i < n; i++)
	{
		if (std::imag(results_fft[i]) >= 0)
		{
			std::cout << "[" << i << "] = " << std::real(results_fft[i]) << " + "
					<< std::imag(results_fft[i]) << "i \n";
		} else
		{
			std::cout << "[" << i << "] = " << std::real(results_fft[i]) << " - "
					<< std::imag(results_fft[i]) << "i \n";
		}
	}

	std::cout << "\nMATLAB results: \n" << "   1.0e+02 * \n"
			<< "([0] = 1.2000 + 0.0000i\n" << "[1] = -0.0800 + 0.4022i\n"
			<< "[2] = -0.0800 + 0.1931i\n" << "[3] = -0.0800 + 0.1197i\n"
			<< "[4] = -0.0800 + 0.0800i\n" << "[5] = -0.0800 + 0.0535i\n"
			<< "[6] = -0.0800 + 0.0331i\n" << "[7] = -0.0800 + 0.0159i\n"
			<< "[8] = -0.0800 + 0.0000i\n" << "[9] = -0.0800 - 0.0159i\n"
			<< "[10] = -0.0800 - 0.0331i\n" << "[11] = -0.0800 - 0.0535i\n"
			<< "[12] = -0.0800 - 0.0800i\n" << "[13] = -0.0800 - 0.1197i\n"
			<< "[14] = -0.0800 - 0.1931i\n" << "[15] = -0.0800 - 0.4022i)\n";

	std::cout << "\n========== Problem 9: FFT, Any Size ========== \n";
	results_fft = v_NULL;
	n = 9;

	test_values = v_NULL;
	std::cout << "Input data (n = " << n << "):\n";
	for (i = 0; i < n; i++)
	{
		item = complex<double>(i, n - i);
		test_values.push_back(item);
		if (std::imag(test_values[i]) >= 0)
		{
			std::cout << "[" << i << "] = " << std::real(test_values[i])
					<< " + " << std::imag(test_values[i]) << "i \n";
		} else
		{
			std::cout << "[" << i << "] = " << std::real(test_values[i])
					<< " - " << std::imag(test_values[i]) << "i \n";
		}
	}

	results_fft = P9ALL::FFT(n, test_values);

	std::cout << "\nFFT() results: \n";
	for (i = 0; i < n; i++)
	{
		if (std::imag(results_fft[i]) >= 0)
		{
			std::cout << "[" << i << "] = " << std::real(results_fft[i]) << " + "
					<< std::imag(results_fft[i]) << "i \n";
		} else
		{
			std::cout << "[" << i << "] = " << std::real(results_fft[i]) << " - "
					<< std::abs(std::imag(results_fft[i])) << "i \n";
		}
	}

	std::cout << "\nMATLAB Results: \n" << "[0] = 36.0000 + 45.0000i \n"
			<< "[1] = 7.8636 + 16.8636i \n" << "[2] = 0.8629 + 9.8629i \n"
			<< "[2] = -1.9019 + 7.0981i \n" << "[4] = -3.7065 + 5.2935i \n"
			<< "[3] = -5.2935 + 3.7065i \n" << "[6] = -7.0981 + 1.9019i \n"
			<< "[4] = -9.8629 - 0.8629i \n" << "[8] = -16.8636 - 7.8636i \n";
	return 0;
}


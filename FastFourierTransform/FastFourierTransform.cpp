#include <complex>
#include <iostream>
#include <vector>
const double PI = acos(-1);

using namespace std;
using cd = complex<double>;

void FFT(vector<cd>& a, bool invert)
{
	int n = a.size();

	if (n == 1)
		return;

	vector<cd> a0(n / 2);
	vector<cd> a1(n / 2);

	for (int i = 0; 2 * i < n; i++)
	{
		a0[i] = a[2 * i];
		a1[i] = a[2 * i + 1];
	}

	FFT(a0, invert);
	FFT(a1, invert);

	double ang = 2 * PI / n * (invert ? -1 : 1);
	cd w(1);
	cd wn(cos(ang), sin(ang));

	for (int i = 0; 2 * i < n; i++)
	{
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		
		if (invert)
		{
			a[i] /= 2;
			a[i + n / 2] /= 2;
		}

		w *= wn;
	}
}

vector<int> Multiply(vector<int> const& a, vector<int> const& b)
{
	vector<cd> fa(a.begin(), a.end());
	vector<cd> fb(b.begin(), b.end());
	int n = 1;
	
	while (n < a.size() + b.size())
		n <<= 1;

	fa.resize(n);
	fb.resize(n);

	FFT(fa, false);
	FFT(fb, false);

	for (int i = 0; i < n; i++)
		fa[i] *= fb[i];

	FFT(fa, true);

	vector<int> result(n);

	for (int i = 0; i < n; i++)
		result[i] = round(fa[i].real());

	return result;
}

int main()
{
	vector<int> polynom1 = { 1, 2, 3 };
	vector<int> polynom2 = { 4, 5 };

	vector<int> result = Multiply(polynom1, polynom2);

	for (int coeff : result)
	{
		cout << coeff << " ";
	}
}
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<int> lnum;

const int base = 1000 * 1000 * 1000;

class Arifm {
	static size_t max(size_t a, size_t b) {
		return a > b ? a : b;
	}
	static int mypow(int num, int base) {
		int ans = 1;
		for (int i = 0; i < base; i++) {
			ans *= num;
		}
		return ans;
	}

 public:

	lnum random(int length) { //15 - 9 + 6
		lnum a(0);
		for (int i = length; i > 0; i -= 9)
			if (i > 9)
				a.push_back(base + rand() % mypow(10, 9));
			else
				a.push_back(rand() % mypow(10, i));
		return a;
	}

	void print(lnum a) {
		printf("%d", a.empty() ? 0 : a.back());
		for (int i = (int)a.size() - 2; i >= 0; --i)
			printf("%09d", a[i]);
		printf("\n");
	}

	lnum read(string s) {
		lnum a(0);
		for (int i = (int)s.length(); i > 0; i -= 9)
			if (i < 9)
				a.push_back(atoi(s.substr(0, i).c_str()));
			else
				a.push_back(atoi(s.substr(i - 9, 9).c_str()));
		return a;
	}

	void sum(lnum a, lnum b) {
		int carry = 0;
		for (size_t i = 0; i < max(a.size(), b.size()) || carry; ++i) {
			if (i == a.size())
				a.push_back(0);
			a[i] += carry + (i < b.size() ? b[i] : 0);
			carry = a[i] >= base;
			if (carry)  a[i] -= base;
		}
	}

	void sub(lnum a, lnum b) {
		int carry = 0;
		for (size_t i = 0; i < b.size() || carry; ++i) {
			a[i] -= carry + (i < b.size() ? b[i] : 0);
			carry = a[i] < 0;
			if (carry) a[i] += base;
		}
		while (a.size() > 1 && a.back() == 0)
			a.pop_back();
	}

	lnum prod(lnum a, lnum b) {
		lnum c(a.size() + b.size());
		for (size_t i = 0; i < a.size(); ++i)
			for (int j = 0, carry = 0; j < (int)b.size() || carry; ++j) {
				long long cur = c[i + j] + a[i] * 1ll * (j < (int)b.size() ? b[j] : 0) + carry;
				c[i + j] = int(cur % base);
				carry = int(cur / base);
			}
		while (c.size() > 1 && c.back() == 0)
			c.pop_back();

		return c;
	}
};

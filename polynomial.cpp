#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 200000;

//#define TYPE1 // double
#define TYPE2 // module
#define LINE
//#define LIM (:: n)

#ifdef TYPE2
const int MOD = 998244353, G = 3;
#endif

#ifdef TYPE1

const double pi2 = acos(-1) * 2;

struct Complex
{
    double a, b;

    Complex(): a(0), b(0) {}
    Complex(double _a): a(_a), b(0) {}
    Complex(double _a, double _b): a(_a), b(_b) {}
} cur[N];

inline Complex operator + (const Complex a, const Complex b)
{
    return Complex(a.a + b.a, a.b + b.b);
}

inline Complex operator - (const Complex a, const Complex b)
{
    return Complex(a.a - b.a, a.b - b.b);
}

inline Complex operator * (const Complex a, const Complex b)
{
    return Complex(a.a * b.a - a.b * b.b, a.a * b.b + a.b * b.a);
}

inline Complex operator / (const Complex a, const Complex b)
{
    return Complex((a.a * b.a + a.b * b.b) / (b.a * b.a + b.b * b.b), (a.b * b.a - a.a * b.b) / (b.a * b.a + b.b * b.b));
}

void fft(Complex *a, int n, int ty)
{
    for (int i = n >> 1, j = 1; j < n; j++)
    {
        if (i < j) swap(a[i], a[j]);
        int k = n >> 1;
        while (i & k) i ^= k, k >>= 1;
        i ^= k;
    }
    for (int m = 2; m <= n; m <<= 1)
    {
        cur[0] = Complex(1, 0);
        Complex w = Complex(cos(pi2 / m * ty), sin(pi2 / m * ty));
        for (int i = 1; i < (m >> 1); i++)
            cur[i] = cur[i - 1] * w;
        for (int i = 0; i < n; i += m)
            for (int j = i; j < i + (m >> 1); j++)
            {
                Complex u = a[j], v = a[j + (m >> 1)] * cur[j - i];
                a[j] = u + v;
                a[j + (m >> 1)] = u - v;
            }
    }
    if (ty == -1)
        for (int i = 0; i < n; i++)
            a[i] = a[i] / n;
}

Complex get_inv(Complex a)
{
    return 1 / a;
}

#endif

#ifdef TYPE2

int pw(int a, int b)
{
    int re = 1;
    while (b)
    {
        if (b & 1)
            re = (ll)re * a % MOD;
        a = (ll)a * a % MOD;
        b >>= 1;
    }
    return re;
}

struct Data
{
    int a;

    Data(): a(0) {}
    Data(int _a): a(_a) {}
    Data(ll _a): a(_a % MOD) {}
} cur[N], inv[N];

inline Data operator + (const Data a, const Data b)
{
    return a.a >= MOD - b.a ? - MOD + a.a + b.a : a.a + b.a;
}

inline Data operator - (const Data a, const Data b)
{
    return a.a < b.a ? - b.a + a.a + MOD : a.a - b.a;
}

inline Data operator * (const Data a, const Data b)
{
    return (ll)a.a * b.a % MOD;
}

inline Data pw(Data a, int b)
{
    Data re = 1;
    while (b)
    {
        if (b & 1)
            re = re * a;
        a = a * a;
        b >>= 1;
    }
    return re;
}

Data operator / (const Data a, const Data b)
{
    return b.a < N ? a * inv[b.a] : a * pw(b, MOD - 2);
}

void fft(Data *a, int n, int ty)
{
    for (int i = n >> 1, j = 1; j < n; j++)
    {
        if (i < j) swap(a[i], a[j]);
        int k = n >> 1;
        while (i & k) i ^= k, k >>= 1;
        i ^= k;
    }
    for (int m = 2; m <= n; m <<= 1)
    {
        cur[0] = 1;
        Data w;
        if (ty == 1)
            w = pw(G, (MOD - 1) / m);
        else
            w = pw(G, (MOD - 1) - (MOD - 1) / m);
        for (int i = 1; i < (m >> 1); i++)
            cur[i] = cur[i - 1] * w;
        for (int i = 0; i < n; i += m)
            for (int j = i; j < i + (m >> 1); j++)
            {
                Data u = a[j], v = a[j + (m >> 1)] * cur[j - i];
                a[j] = u + v;
                a[j + (m >> 1)] = u - v;
            }
    }
    if (ty == -1)
    {
        Data t = pw(n, MOD - 2);
        for (int i = 0; i < n; i++)
            a[i] = a[i] * t;
    }
}

Data get_inv(Data a)
{
    return 1 / a;
}

void pre_inv()
{
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++)
        inv[i] = inv[MOD % i] * (MOD - MOD / i);
}

#endif

template<class T> struct Poly
{
    vector<T> a;

    T &operator [] (const int u)
    {
        return a[u];
    }
    const T &operator [] (const int u) const
    {
        return a[u];
    }
    const int len() const
    {
        return a.size() - 1;
    }

    void set_length(int n)
    {
        a.resize(n + 1);
        for (int i = 0; i <= n; i++)
            a[i] = 0;
    }

    void set_values(T *_a, int n)
    {
        a.resize(n + 1);
        for (int i = 0; i <= n; i++)
            a[i] = _a[i];
    }

#ifdef TYPE1
    void set_values(double *_a, int n)
    {
        a.resize(n + 1);
        for (int i = 0; i <= n; i++)
            a[i] = _a[i];
    }
#endif

#ifdef TYPE2
    void set_values(int *_a, int n)
    {
        a.resize(n + 1);
        for (int i = 0; i <= n; i++)
            a[i] = _a[i];
    }
    void set_values(ll *_a, int n)
    {
        a.resize(n + 1);
        for (int i = 0; i <= n; i++)
            a[i] = _a[i];
    }
#endif

    Poly() {}
    Poly(int n)
    {
        set_length(n);
    }
    Poly(T *_a, int n)
    {
        set_values(_a, n);
    }
#ifdef TYPE1
    Poly(double *_a, int n)
    {
        set_values(_a, n);
    }
#endif
#ifdef TYPE2
    Poly(int *_a, int n)
    {
        set_values(_a, n);
    }
    Poly(ll *_a, int n)
    {
        set_values(_a, n);
    }
#endif
};

template<class T> void print(const Poly<T> &a)
{
#ifdef TYPE1
    printf("%.3lf", a[0].a);
    for (int i = 1; i <= a.len(); i++)
        printf(" %.3lf", a[i].a);
    puts("");
#endif
#ifdef TYPE2
    printf("%d", a[0].a);
    for (int i = 1; i <= a.len(); i++)
        printf(" %d", a[i].a);
    puts("");
#endif
}

#ifdef TYPE1
template<class T> void print_ll(const Poly<T> &a)
{
    printf("%lld", ll(a[0].a + 0.5));
    for (int i = 1; i <= a.len(); i++)
        printf(" %lld", ll(a[i].a + 0.5));
    puts("");
}
#endif

template<class T> void print(T *a, int n)
{
#ifdef TYPE1
    printf("%.3lf", a[0]);
    for (int i = 1; i <= n; i++)
        printf(" %.3lf", a[i]);
    puts("");
#endif
#ifdef TYPE2
    printf("%d", a[0]);
    for (int i = 1; i <= n; i++)
        printf(" %d", a[i]);
    puts("");
#endif
}

#ifdef TYPE1
template<class T> void print_ll(T *a, int n)
{
    printf("%lld", ll(a[0] + 0.5));
    for (int i = 1; i <= n; i++)
        printf(" %lld", ll(a[i] + 0.5));
    puts("");
}
#endif

template<class T> Poly<T> operator * (const Poly<T> &a, const T &b)
{
    Poly<T> re = a;
    for (int i = 0; i <= re.len(); i++)
        re[i] = re[i] * b;
    return re;
}

template<class T> Poly<T> operator / (const Poly<T> &a, const T &b)
{
    Poly<T> re = a;
    for (int i = 0; i <= re.len(); i++)
        re[i] = re[i] / b;
    return re;
}

template<class T> void copy(const Poly<T> &a, int m, Poly<T> &b, int n)
{
    b.a.resize(n + 1);
    if (m < n)
    {
        for (int i = 0; i <= m; i++)
            b[i] = a[i];
        for (int i = m + 1; i <= n; i++)
            b[i] = 0;
    } else
    {
        for (int i = 0; i <= n; i++)
            b[i] = a[i];
    }
}

template<class T> void copy(const Poly<T> &a, int m, T *b, int n)
{
    if (m < n)
    {
        for (int i = 0; i <= m; i++)
            b[i] = a[i];
        for (int i = m + 1; i <= n; i++)
            b[i] = 0;
    } else
    {
        for (int i = 0; i <= n; i++)
            b[i] = a[i];
    }
}

template<class T> void copy(T *a, int m, Poly<T> &b, int n)
{
    b.a.resize(n + 1);
    if (m < n)
    {
        for (int i = 0; i <= m; i++)
            b[i] = a[i];
        for (int i = m + 1; i <= n; i++)
            b[i] = 0;
    } else
    {
        for (int i = 0; i <= n; i++)
            b[i] = a[i];
    }
}

template<class T> void copy(T *a, int m, T *b, int n)
{
    if (m < n)
    {
        for (int i = 0; i <= m; i++)
            b[i] = a[i];
        for (int i = m + 1; i <= n; i++)
            b[i] = 0;
    } else
    {
        for (int i = 0; i <= n; i++)
            b[i] = a[i];
    }
}

template<class T> void add(T *a, int n, T *b, int m, T *c)
{
    for (int i = 0; i <= max(n, m); i++)
        c[i] = 0;
    for (int i = 0; i <= n; i++)
        c[i] = c[i] + a[i];
    for (int i = 0; i <= m; i++)
        c[i] = c[i] + b[i];
}

#ifdef LINE

namespace temp_add
{
#ifdef TYPE1
    Complex t1[N], t2[N], t3[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N], t3[N];
#endif
}

template<class T> Poly<T> operator + (const Poly<T> &a, const Poly<T> &b)
{
    using namespace temp_add;
    copy(a, a.len(), t1, a.len());
    copy(b, b.len(), t2, b.len());
    add(t1, a.len(), t2, b.len(), t3);
    Poly<T> re;
    copy(t3, max(a.len(), b.len()), re, max(a.len(), b.len()));
    return re;
}

#endif

template<class T> void subtract(T *a, int n, T *b, int m, T *c)
{
    for (int i = 0; i <= max(n, m); i++)
        c[i] = 0;
    for (int i = 0; i <= n; i++)
        c[i] = c[i] + a[i];
    for (int i = 0; i <= m; i++)
        c[i] = c[i] - b[i];
}

#ifdef LINE

namespace temp_subtract
{
#ifdef TYPE1
    Complex t1[N], t2[N], t3[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N], t3[N];
#endif
}

template<class T> Poly<T> operator - (const Poly<T> &a, const Poly<T> &b)
{
    using namespace temp_subtract;
    copy(a, a.len(), t1, a.len());
    copy(b, b.len(), t2, b.len());
    subtract(t1, a.len(), t2, b.len(), t3);
    Poly<T> re;
    copy(t3, max(a.len(), b.len()), re, max(a.len(), b.len()));
    return re;
}

#endif

namespace temp_multiply
{
#ifdef TYPE1
    Complex t1[N], t2[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N];
#endif
}

template<class T> void multiply(T *a, int n, T *b, int m, T *c)
{
    using namespace temp_multiply;
    int t = n + m;
    if (n <= 20 && m <= 20)
    {
        for (int i = 0; i <= t; i++) t1[i] = 0;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                t1[i + j] = t1[i + j] + a[i] * b[j];
        for (int i = 0; i <= t; i++) c[i] = t1[i];
    } else
    {
        int len = 1;
        while (len < t + 5) len <<= 1;
        copy(a, n, t1, len - 1);
        copy(b, m, t2, len - 1);
        fft(t1, len, 1);
        fft(t2, len, 1);
        for (int i = 0; i < len; i++)
            t1[i] = t1[i] * t2[i];
        fft(t1, len, -1);
        copy(t1, t, c, t);
    }
}

template<class T> void multiply2(T *a, int n, T *b, int m, T *c)
{
    using namespace temp_multiply;
    int t = n + m;
    if (n <= 20 && m <= 20)
    {
        for (int i = 0; i < t; i++) t1[i] = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                t1[i + j] = t1[i + j] + a[i] * b[j];
        for (int i = 0; i < n; i++)
            t1[i + m] = t1[i + m] + a[i];
        for (int j = 0; j < m; j++)
            t1[n + j] = t1[n + j] + b[j];
        for (int i = 0; i < t; i++) c[i] = t1[i];
    } else
    {
        int len = 1;
        while (len < t + 5) len <<= 1;
        copy(a, n - 1, t1, len - 1);
        t1[n] = 1;
        copy(b, m - 1, t2, len - 1);
        t2[m] = 1;
        fft(t1, len, 1);
        fft(t2, len, 1);
        for (int i = 0; i < len; i++)
            t1[i] = t1[i] * t2[i];
        fft(t1, len, -1);
        copy(t1, t - 1, c, t - 1);
    }
}

#ifdef LINE

namespace temp_multiply2
{
#ifdef TYPE1
    Complex t1[N], t2[N], t3[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N], t3[N];
#endif
}

template<class T> Poly<T> operator * (const Poly<T> &a, const Poly<T> &b)
{
    using namespace temp_multiply2;
    copy(a, a.len(), t1, a.len());
    copy(b, b.len(), t2, b.len());
    multiply(t1, a.len(), t2, b.len(), t3);
    Poly<T> re;
#ifdef LIM
    copy(t3, a.len() + b.len(), re, min(a.len() + b.len(), LIM));
#else
    copy(t3, a.len() + b.len(), re, a.len() + b.len());
#endif
    return re;
}

#endif

namespace temp_inv
{
#ifdef TYPE1
    Complex t1[N], t2[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N];
#endif
}

template<class T> void poly_inv(T *a, T *b, int n)
{
    using namespace temp_inv;
    if (n == 0)
    {
        b[0] = get_inv(a[0]);
        return ;
    }
    poly_inv(a, b, n / 2);
    int len = 1;
    while (len < n * 2 + 5) len <<= 1;
    copy(b, n / 2, t1, len - 1);
    copy(a, n, t2, len - 1);
    fft(t1, len, 1);
    fft(t2, len, 1);
    for (int i = 0; i < len; i++)
        t1[i] = t1[i] * 2 - t1[i] * t1[i] * t2[i];
    fft(t1, len, -1);
    copy(t1, n, b, n);
}

#ifdef LINE

namespace temp_inv2
{
#ifdef TYPE1
    Complex t1[N], t2[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N];
#endif
}

template<class T> Poly<T> poly_inv(const Poly<T> &a)
{
    using namespace temp_inv2;
    copy(a, a.len(), t1, a.len());
    poly_inv(t1, t2, a.len());
    Poly<T> re;
    copy(t2, a.len(), re, a.len());
    return re;
}

#endif

namespace temp_mod
{
#ifdef TYPE1
    Complex t1[N], t2[N], t3[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N], t3[N];
#endif
}

template<class T> void poly_div_mod(T *a, int n, T *b, int m, T *c, T *d)
{
    using namespace temp_mod;
    copy(a, n, t1, n);
    reverse(t1, t1 + n + 1);
    copy(b, m, t2, m);
    reverse(t2, t2 + m + 1);
    copy(t2, m, t2, n - m);
    poly_inv(t2, t3, n - m);
    multiply(t1, n - m, t3, n - m, t3);
    reverse(t3, t3 + n - m + 1);
    copy(t3, n - m, c, n - m);
    copy(b, m, t2, m);
    multiply(t2, m, t3, n - m, t1);
    copy(a, n, t2, n);
    subtract(t2, n, t1, n, t3);
    copy(t3, m - 1, d, m - 1);
}

template<class T> void poly_mod(T *a, int n, T *b, int m, T *c)
{
    using namespace temp_mod;
    copy(a, n, t1, n);
    reverse(t1, t1 + n + 1);
    copy(b, m, t2, m);
    reverse(t2, t2 + m + 1);
    copy(t2, m, t2, n - m);
    poly_inv(t2, t3, n - m);
    multiply(t1, n - m, t3, n - m, t3);
    reverse(t3, t3 + n - m + 1);
    copy(b, m, t2, m);
    multiply(t2, m, t3, n - m, t1);
    copy(a, n, t2, n);
    subtract(t2, n, t1, n, t3);
    copy(t3, m - 1, c, m - 1);
}

template<class T> void poly_mod2(T *a, int n, T *b, int m, T *c)
{
    using namespace temp_mod;
    copy(a, n, t1, n);
    reverse(t1, t1 + n + 1);
    copy(b, m - 1, t2, m);
    t2[m] = 1;
    reverse(t2, t2 + m + 1);
    copy(t2, m, t2, n - m);
    poly_inv(t2, t3, n - m);
    multiply(t1, n - m, t3, n - m, t3);
    reverse(t3, t3 + n - m + 1);
    copy(b, m - 1, t2, m);
    t2[m] = 1;
    multiply(t2, m, t3, n - m, t1);
    copy(a, n, t2, n);
    subtract(t2, n, t1, n, t3);
    copy(t3, m - 1, c, m - 1);
}

#ifdef LINE

namespace temp_mod2
{
#ifdef TYPE1
    Complex t1[N], t2[N], t3[N], t4[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N], t3[N], t4[N];
#endif
}

template<class T> Poly<T> operator / (const Poly<T> &a, const Poly<T> &b)
{
    using namespace temp_mod2;
    copy(a, a.len(), t1, a.len());
    copy(b, b.len(), t2, b.len());
    poly_div_mod(t1, a.len(), t2, b.len(), t3, t4);
    Poly<T> re;
    copy(t3, a.len() - b.len(), re, a.len() - b.len());
    return re;
}

template<class T> Poly<T> operator % (const Poly<T> &a, const Poly<T> &b)
{
    using namespace temp_mod2;
    copy(a, a.len(), t1, a.len());
    copy(b, b.len(), t2, b.len());
    poly_div_mod(t1, a.len(), t2, b.len(), t3, t4);
    Poly<T> re;
    copy(t4, b.len() - 1, re, b.len() - 1);
    return re;
}

#endif

template<class T> void derivative(T *a, T *b, int n)
{
    for (int i = 1; i <= n; i++)
        b[i - 1] = a[i] * i;
    b[n] = 0;
}

#ifdef LINE

namespace temp_derivative
{
#ifdef TYPE1
    Complex t1[N], t2[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N];
#endif
}

template<class T> Poly<T> derivative(const Poly<T> &a)
{
    using namespace temp_derivative;
    copy(a, a.len(), t1, a.len());
    derivative(t1, t2, a.len());
    Poly<T> re;
    copy(t2, max(a.len() - 1, 0), re, max(a.len() - 1, 0));
    return re;
}

#endif

template<class T> void integrate(T *a, T *b, int n)
{
    for (int i = n - 1; i >= 0; i--)
        b[i + 1] = a[i] / (i + 1);
    b[0] = 0;
}

#ifdef LINE

namespace temp_integrate
{
#ifdef TYPE1
    Complex t1[N], t2[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N];
#endif
}

template<class T> Poly<T> integrate(const Poly<T> &a)
{
    using namespace temp_integrate;
    copy(a, a.len(), t1, a.len());
    integrate(t1, t2, a.len() + 1);
    Poly<T> re;
#ifdef LIM
    copy(t2, a.len() + 1, re, min(a.len() + 1), LIM);
#else
    copy(t2, a.len() + 1, re, a.len() + 1);
#endif
    return re;
}

#endif

namespace temp_ln
{
#ifdef TYPE1
    Complex t1[N], t2[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N];
#endif
}

template<class T> void poly_ln(T *a, T *b, int n)
{
    using namespace temp_ln;
    derivative(a, t1, n);
    poly_inv(a, t2, n);
    multiply(t1, n - 1, t2, n, t1);
    integrate(t1, t2, n);
    copy(t2, n, b, n);
}

#ifdef LINE

namespace temp_ln2
{
#ifdef TYPE1
    Complex t1[N], t2[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N];
#endif
}

template<class T> Poly<T> poly_ln(const Poly<T> &a)
{
    using namespace temp_ln2;
    copy(a, a.len(), t1, a.len());
    poly_ln(t1, t2, a.len());
    Poly<T> re;
    copy(t2, a.len(), re, a.len());
    return re;
}

#endif

namespace temp_exp
{
#ifdef TYPE1
    Complex t1[N], t2[N], t3[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N], t3[N];
#endif
}

template<class T> void poly_exp(T *a, T *b, int n)
{
    using namespace temp_exp;
    if (n == 0)
    {
        b[0] = 1;
        return ;
    }
    poly_exp(a, b, n / 2);
    copy(b, n / 2, t1, n);
    poly_ln(t1, t2, n);
    int len = 1;
    while (len < n + n / 2 + 5) len <<= 1;
    copy(t1, n / 2, t1, len - 1);
    copy(t2, n, t2, len - 1);
    copy(a, n, t3, len - 1);
    fft(t1, len, 1);
    fft(t2, len, 1);
    fft(t3, len, 1);
    for (int i = 0; i < len; i++)
        t1[i] = t1[i] - (t2[i] - t3[i]) * t1[i];
    fft(t1, len, -1);
    copy(t1, n, b, n);
}

#ifdef LINE

namespace temp_exp2
{
#ifdef TYPE1
    Complex t1[N], t2[N];
#endif
#ifdef TYPE2
    Data t1[N], t2[N];
#endif
}

template<class T> Poly<T> poly_exp(const Poly<T> &a)
{
    using namespace temp_exp2;
    copy(a, a.len(), t1, a.len());
    poly_exp(t1, t2, a.len());
    Poly<T> re;
    copy(t2, a.len(), re, a.len());
    return re;
}

#endif

namespace temp_evaluate
{
#ifdef TYPE1
    Complex t1[N * 20], t2[N * 20];
#endif
#ifdef TYPE2
    Data t1[N * 20], t2[N * 20];
#endif
}

template<class T> void poly_evaluate_build(int dep, int l, int r, T *v)
{
    using namespace temp_evaluate;
    if (l == r)
    {
        t1[dep * N + l] = 0 - v[l];
        return ;
    }
    int mid = l + r >> 1;
    poly_evaluate_build(dep + 1, l, mid, v);
    poly_evaluate_build(dep + 1, mid + 1, r, v);
    multiply2(t1 + (dep + 1) * N + l, mid - l + 1, t1 + (dep + 1) * N + mid + 1, r - mid, t1 + dep * N + l);
}

template<class T> void poly_evaluate_query(int dep, int l, int r, T *v)
{
    using namespace temp_evaluate;
    if (l == r)
    {
        v[l] = t2[dep * N + l];
        return ;
    }
    int mid = l + r >> 1;
    poly_mod2(t2 + dep * N + l, r - l, t1 + (dep + 1) * N + l, mid - l + 1, t2 + (dep + 1) * N + l);
    poly_evaluate_query(dep + 1, l, mid, v);
    poly_mod2(t2 + dep * N + l, r - l, t1 + (dep + 1) * N + mid + 1, r - mid, t2 + (dep + 1) * N + mid + 1);
    poly_evaluate_query(dep + 1, mid + 1, r, v);
}

template<class T> void poly_evaluate(T *a, int n, T *b, T *c, int m)
{
    using namespace temp_evaluate;
    poly_evaluate_build(0, 0, m - 1, b);
    poly_mod2(a, n, t1, m, t2);
    poly_evaluate_query(0, 0, m - 1, c);
}

#ifdef LINE

namespace temp_evaluate2
{
#ifdef TYPE1
    Complex t1[N];
#endif
#ifdef TYPE2
    Data t1[N];
#endif
}

template<class T> void poly_evaluate(const Poly<T> &a, T *b, T *c, int m)
{
    using namespace temp_evaluate2;
    copy(a, a.len(), t1, a.len());
    poly_evaluate(t1, a.len(), b, c, m);
}

#endif

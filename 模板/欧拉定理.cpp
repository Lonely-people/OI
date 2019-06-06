#include <cstdio>

int a, m, phi = 1;
int bm, flag;

int qPow(int b, int e) {
    int a = 1;
    for (; e; e >>= 1, b = (long long)b * b % m)
        if(e & 1) a = (long long)a * b % m;
    return a;
}

int main() {
    scanf("%d%d", &a, &m);
    a %= m;
    int mm = m;
    for (int i = 2; i * i <= mm; ++i) {
        if (mm % i) continue;
        phi *= i - 1;
        mm /= i;
        while (mm % i == 0)
            phi *= i,
            mm /= i;
    } if (mm > 1) phi *= mm - 1;
    char ch;
    while ((ch = getchar()) < '0' || ch > '9') ;
    while (bm = bm * 10ll + (ch ^ '0'), (ch = getchar()) >= '0' && ch <= '9')
        if (bm >= phi) flag = 1, bm %= phi;
    if (bm >= phi) flag = 1, bm %= phi;
    if (flag) bm += phi;
    printf("%d", qPow(a, bm));
    return 0;
}

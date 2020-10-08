// 【UR #13】Sanrd
// min25筛
// https://uoj.ac/problem/188
/*
S(x,y) 表示[1,x]中最小质因数大于等于Prime[y]的值对答案的贡献
枚举大于等于Prime[y]的质数Prime[i]，以及其幂次e，其对S(x,y)的贡献是
S(x/(Prime[i]**e),i+1)+Prime[i]*(\phi[x/(Prime[i]**e)]-i+1)
\phi[x] 表示小于等于x质数的个数
前半部分是去除了这个因子后的答案，后半部分是最小质因数是Prime[i]，且Prime[i]能对答案做出贡献的值的数目
 */
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;
bool isPrime[MAXN];
int prime[MAXN];
void euler() {
  memset(isPrime, true, sizeof isPrime);
  isPrime[1] = false;
  for (int i = 2; i < MAXN; i++) {
    if (isPrime[i]) prime[++prime[0]] = i;
    for (int j = 1; j <= prime[0] && i * prime[j] < MAXN; j++) {
      isPrime[i * prime[j]] = false;
      if (i % prime[j] == 0) break;
    }
  }
}
int sqrtN;
long long n;
long long g0[MAXN];
inline int getIndex(long long x) {
  if (x > sqrtN) return (sqrtN * 2 - n / x + 1);
  return x;
}
inline long long getValue(int index) {
  if (index <= sqrtN) return index;
  return n / (sqrtN * 2 + 1 - index);
}
long long init(long long n) {
  for (int i = 1; i <= sqrtN * 2; i++) g0[i] = getValue(i) - 1;
  for (int i = 1; i <= prime[0] && 1ll * prime[i] * prime[i] < n; i++) {
    for (int j = sqrtN * 2; j >= 1; j--) {
      long long t = getValue(j);
      if (1ll * prime[i] * prime[i] > t) break;
      g0[j] = g0[j] - (g0[getIndex(t / prime[i])] -
                       g0[getIndex(i == 1 ? 1 : prime[i - 1])]);
    }
  }
}
long long S(long long x, int y) {
  if (1ll * prime[y] * prime[y] > x) return 0;
  if (x <= 1) return 0;
  long long ret = 0;
  for (int i = y; 1ll * prime[i] * prime[i] <= x; i++) {
    long long now = prime[i];
    for (int e = 1; now * prime[i] <= x; e++, now *= prime[i]) {
      ret += S(x / now, i + 1) + prime[i] * (g0[getIndex(x / now)] - i + 1);
    }
  }
  return ret;
}
long long cal(long long n) {
  ::n = n;
  sqrtN = sqrt(n);
  init(n);
  return S(n, 1);
}
int main() {
  euler();
  long long l, r;
  cin >> l >> r;
  cout << cal(r) - cal(l - 1) << endl;
  return 0;
}
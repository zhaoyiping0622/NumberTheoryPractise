// 简单的函数
// min25筛
// https://loj.ac/problem/6053
#include <bits/stdc++.h>
using namespace std;
const int MAXM = 1e6 + 5;
const int MOD = 1e9 + 7;
const int SQRTMAXN = 1e5 + 5;
bool isPrime[MAXM];
int prime[MAXM];
int f[MAXM];
int fPrimeSum[MAXM];
long long n;
int sqrtN;
constexpr int powm(long long a, int b) {
  long long ret = 1;
  while (b) {
    if (b & 1) ret = ret * a % MOD;
    a = a * a % MOD;
    b >>= 1;
  }
  return ret;
}
const long long INV2 = powm(2, MOD - 2);
void euler() {
  memset(isPrime, true, sizeof isPrime);
  isPrime[1] = false;
  f[1] = 1;
  for (int i = 2; i < MAXM; i++) {
    if (isPrime[i]) f[i] = i ^ 1, prime[++prime[0]] = i;
    for (int j = 1; j <= prime[0] && i * prime[j] < MAXM; j++) {
      isPrime[i * prime[j]] = false;
      if (i % prime[j] == 0) {
        int t = i;
        int cnt = 1;
        while (t % prime[j] == 0) t /= prime[j], cnt++;
        f[i * prime[j]] = (f[t] * (prime[j] ^ cnt)) % MOD;
        break;
      }
      f[i * prime[j]] = (f[i] * f[prime[j]]) % MOD;
    }
  }
}
// [i for i in 1..sqrtN 1..sqrtN]
// [n/(i-sqrtN) for i in sqrtN+1..2sqrtN]
int getIndex(long long x) {
  if (x <= sqrtN) return x;
  return 2 * sqrtN + 1 - n / x;
}
long long getValue(int index) {
  if (index > sqrtN) return n / (2 * sqrtN + 1 - index);
  return index;
}
int g1[SQRTMAXN << 1];
int g0[SQRTMAXN << 1];
void init() {
  euler();
  for (int i = 2; i < MAXM; i++)
    fPrimeSum[i] = (fPrimeSum[i - 1] + (isPrime[i] ? f[i] : 0)) % MOD;
  sqrtN = (int)sqrt(n);
  auto sumN = [](long long x) {
    x %= MOD;
    return (x + 1) * x % MOD * INV2 % MOD;
  };
  auto sum1 = [](long long x) { return x % MOD; };
  for (int i = 1; i <= sqrtN * 2; i++)
    g1[i] = sumN(getValue(i)), g0[i] = sum1(getValue(i));
  for (int j = 1; j <= prime[0] && 1ll * prime[j] * prime[j] <= n; j++) {
    for (int i = 2 * sqrtN; i >= 1; i--) {
      long long t = getValue(i);
      if (1ll * prime[j] * prime[j] > t) break;
      g1[i] = (g1[i] -
               1ll * prime[j] *
                   (g1[getIndex(t / prime[j])] -
                    (g1[getIndex(j == 1 ? 1 : prime[j - 1])]) + MOD) %
                   MOD +
               MOD) %
              MOD;
      g0[i] = (g0[i] -
               (g0[getIndex(t / prime[j])] -
                (g0[getIndex(j == 1 ? 1 : prime[j - 1])])) +
               MOD) %
              MOD;
    }
  }
}
int getFPrimeSum(long long x) {
  if (x == 1) return 0;
  x = getIndex(x);
  return (g1[x] - g0[x] + 2ll + MOD) % MOD;
}
int S(long long x, int j) {
  int ret =
      (getFPrimeSum(x) - getFPrimeSum(j == 1 ? 1 : prime[j - 1]) + MOD) % MOD;
  for (int k = j; 1ll * prime[k] * prime[k] <= x; k++) {
    long long now = prime[k];
    for (int e = 1; now * prime[k] <= x; e++, now *= prime[k]) {
      ret = (ret + 1ll * (prime[k] ^ e) * S(x / now, k + 1) +
             (prime[k] ^ (e + 1))) %
            MOD;
    }
  }
  return ret;
}
int main() {
  cin >> n;
  init();
  cout << S(n, 1) + 1;
  return 0;
}
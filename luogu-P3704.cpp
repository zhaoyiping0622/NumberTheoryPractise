// [SDOI2017]数字表格
// 莫比乌斯反演
// https://www.luogu.com.cn/problem/P3704
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;
int f[MAXN];
int mu[MAXN];
int prime[MAXN];
bool isPrime[MAXN];
int fT[MAXN];
int fInv[MAXN];
int fTMul[MAXN];
int powm(long long a, int b) {
  a %= MOD;
  int ret = 1;
  while (b) {
    if (b & 1) ret = ret * a % MOD;
    a = a * a % MOD;
    b >>= 1;
  }
  return ret;
}
void euler() {
  memset(isPrime, true, sizeof isPrime);
  isPrime[1] = false;
  mu[1] = 1;
  f[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    if (isPrime[i]) mu[i] = -1, prime[++prime[0]] = i;
    f[i] = (f[i - 1] + f[i - 2]) % MOD;
    for (int j = 1; j <= prime[0] && i * prime[j] < MAXN; j++) {
      isPrime[i * prime[j]] = false;
      if (i % prime[j] == 0) {
        mu[i * prime[j]] = 0;
        break;
      }
      mu[i * prime[j]] = -mu[i];
    }
  }
}
int main() {
  int t;
  ios::sync_with_stdio(false);
  cin.tie(0);
  euler();
  for (int i = 1; i < MAXN; i++) {
    fInv[i] = powm(f[i], MOD - 2);
    fT[i] = 1;
  }
  for (int i = 2; i < MAXN; i++) {
    for (int j = 1; i * j < MAXN; j++) {
      if (mu[j] == 1) {
        fT[i * j] = 1ll * fT[i * j] * f[i] % MOD;
      } else if (mu[j] == -1) {
        fT[i * j] = 1ll * fT[i * j] * fInv[i] % MOD;
      }
    }
  }
  fTMul[1] = fT[1];
  for (int i = 2; i < MAXN; i++) fTMul[i] = 1ll * fTMul[i - 1] * fT[i] % MOD;
  fTMul[0] = 1;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    int ret = 1;
    for (int i = 1; i <= n; i++) {
      int a = n / i;
      int b = m / i;
      if (a == 0 || b == 0) break;
      int r = min(n / a, m / b);
      ret = 1ll * ret *
            powm(1ll * fTMul[r] * powm(fTMul[i - 1], MOD - 2) % MOD,
                 1ll * a * b % (MOD - 1)) %
            MOD;
      i = r;
    }
    cout << ret << "\n";
  }
  return 0;
}
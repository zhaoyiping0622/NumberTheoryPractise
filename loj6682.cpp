// 梦中的数论
// min25筛
// https://loj.ac/problem/6682
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;
const int MOD = 998244353;
long long n;
bool isPrime[MAXN];
int prime[MAXN];
int sqrtN;
int g0[MAXN << 1];
long long w[MAXN << 1];
int id1[MAXN];
int id2[MAXN];
constexpr int powm(long long a, int b) {
  a %= MOD;
  int ret = 1;
  while (b) {
    if (b & 1) ret = (ret * a) % MOD;
    a = a * a % MOD;
    b >>= 1;
  }
  return ret;
}
const int INV2 = powm(2, MOD - 2);
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
int getIndex(long long x) {
  if (x <= sqrtN) return id1[x];
  return id2[n / x];
}
void init() {
  sqrtN = sqrt(n);
  for (int i = 1; i <= sqrtN * 2; i++) {
    if (i <= sqrtN)
      w[i] = i, id1[i] = i;
    else
      w[i] = n / (2 * sqrtN - i + 1), id2[n / w[i]] = i;
    g0[i] = (w[i] - 1) % MOD;
  }
  for (int i = 1; i <= prime[0] && 1ll * prime[i] * prime[i] <= n; i++) {
    long long now = prime[i];
    for (int j = sqrtN * 2; j >= 1; j--) {
      long long t = w[j];
      if (prime[i] > t / prime[i]) break;
      g0[j] = (g0[j] - (g0[getIndex(t / prime[i])] - (i - 1)) + MOD) % MOD;
    }
  }
}
int S2(long long x, int y) {
  if (prime[y] > x) return 0;
  int ret = (g0[getIndex(x)] - y + 1) * 4 % MOD;
  for (int i = y; 1ll * prime[i] * prime[i] <= x; i++) {
    long long now = prime[i];
    for (int j = 1; now * prime[i] <= x; j++, now *= prime[i]) {
      ret = (ret + 1ll * (S2(x / now, i + 1)) * (j + 1) % MOD * (j + 1) +
             (j + 2) * (j + 2)) %
            MOD;
    }
  }
  return ret;
}
int S1(long long x, int y) {
  if (prime[y] > x) return 0;
  int ret = (g0[getIndex(x)] - y + 1) * 2 % MOD;
  for (int i = y; 1ll * prime[i] * prime[i] <= x; i++) {
    long long now = prime[i];
    for (int j = 1; now * prime[i] <= x; j++, now *= prime[i]) {
      ret = (ret + 1ll * (S1(x / now, i + 1)) * (j + 1) + (j + 2)) % MOD;
    }
  }
  return ret;
}
int main() {
  euler();
  cin >> n;
  init();
  cout << (S2(n, 1) - S1(n, 1) + MOD) * 1ll * INV2 % MOD;
  return 0;
}
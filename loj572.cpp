#include <bits/stdc++.h>
using namespace std;
unsigned powm(unsigned a, unsigned b) {
  unsigned ret = 1;
  while (b) {
    if (b & 1) ret *= a;
    a *= a;
    b >>= 1;
  }
  return ret;
}
const int MAXN = 1e5 + 5;
bool isPrime[MAXN];
int prime[MAXN];
unsigned primeK[MAXN];
int sqrtN;
unsigned g0[MAXN];
unsigned n, k;
int id1[MAXN];
int id2[MAXN];
unsigned w[MAXN << 1];
inline int getIndex(unsigned x) { return x <= sqrtN ? id1[x] : id2[n / x]; }
inline unsigned getValue(int index) { return w[index]; }
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
void init() {
  sqrtN = sqrt(n);
  for (int i = 1; i <= sqrtN * 2; i++)
    if (i <= sqrtN)
      w[i] = i, id1[i] = i;
    else
      w[i] = n / (sqrtN * 2 + 1 - i), id2[n / w[i]] = i;
  for (int i = 1; i <= sqrtN * 2; i++) {
    g0[i] = getValue(i) - 1;
  }
  for (int i = 1; i <= prime[0] && prime[i] <= n / prime[i]; i++) {
    for (int j = 2 * sqrtN; j >= 1; j--) {
      unsigned t = getValue(j);
      if (prime[i] > t / prime[i]) break;
      g0[j] = g0[j] - (g0[getIndex(t / prime[i])] - (i - 1));
    }
  }
}
unsigned Sfk(unsigned x, unsigned y) {
  if (x <= 1) return 0;
  if (prime[y] * prime[y] > x) return 0;
  unsigned ret = 0;
  for (unsigned i = y; prime[i] * prime[i] <= x; i++) {
    unsigned t = primeK[i];
    for (unsigned now = prime[i]; now <= x / prime[i]; now *= prime[i]) {
      ret += Sfk(x / now, i + 1) + t * (g0[getIndex(x / now)] - i + 1);
    }
  }
  return ret;
}
unordered_map<unsigned, unsigned> fkSumCache;
unsigned fkSum(unsigned n) {
  if (fkSumCache.count(n)) return fkSumCache[n];
  return fkSumCache[n] = Sfk(n, 1) + g0[getIndex(n)];
}
unsigned sCache[MAXN << 1];
bool vis[MAXN << 1];
unsigned S(unsigned n) {
  if (n == 0) return 0;
  int id = getIndex(n);
  if (vis[id]) return sCache[id];
  unsigned ret = fkSum(n);
  for (unsigned i = 2; i <= n; i++) {
    unsigned a = n / i;
    unsigned r = n / a;
    ret -= (r - i + 1) * S(a);
    i = r;
  }
  vis[id] = true;
  return sCache[id] = ret;
}
int main() {
  euler();
  cin >> n >> k;
  for (int i = 1; i <= prime[0]; i++) primeK[i] = powm(prime[i], k);
  init();
  unsigned ans = 0;
  for (unsigned i = 1; i <= n; i++) {
    unsigned a = n / i;
    unsigned r = n / a;
    ans += a * a * (S(r) - S(i - 1));
    i = r;
  }
  cout << ans;
  return 0;
}
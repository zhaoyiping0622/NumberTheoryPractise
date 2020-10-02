// 【模板】杜教筛（Sum）
// 杜教筛
// https://www.luogu.com.cn/problem/P4213
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e7 + 5;
int mu[MAXN];
int prime[MAXN];
bool isPrime[MAXN];
int phi[MAXN];
long long muSum[MAXN];
long long phiSum[MAXN];
unordered_map<int, long long> muSumCache;
unordered_map<int, long long> phiSumCache;
void euler() {
  memset(isPrime, true, sizeof isPrime);
  isPrime[0] = isPrime[1] = false;
  mu[1] = 1;
  phi[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    if (isPrime[i]) prime[++prime[0]] = i, mu[i] = -1, phi[i] = i - 1;
    for (int j = 1; j <= prime[0] && i * prime[j] < MAXN; j++) {
      isPrime[i * prime[j]] = false;
      if (i % prime[j] == 0) {
        phi[i * prime[j]] = phi[i] * prime[j];
        break;
      } else
        mu[i * prime[j]] = -mu[i], phi[i * prime[j]] = phi[i] * (prime[j] - 1);
    }
  }
}
void init() {
  euler();
  for (int i = 1; i < MAXN; i++) {
    phiSum[i] = phi[i] + phiSum[i - 1];
    muSum[i] = mu[i] + muSum[i - 1];
  }
}
long long getPhiSum(int x) {
  if (x < MAXN) return phiSum[x];
  if (phiSumCache.count(x)) return phiSumCache[x];
  long long ans = 0;
  for (int i = 2; i <= x; i++) {
    int a = x / i;
    int r = x / a;
    ans += (r - i + 1) * getPhiSum(a);
    i = r;
  }
  ans = 1ll * x * (x + 1) / 2 - ans;
  phiSumCache[x] = ans;
  return ans;
}
long long getMuSum(int x) {
  if (x < MAXN) return muSum[x];
  if (muSumCache.count(x)) return muSumCache[x];
  long long ans = 0;
  for (int i = 2; i <= x; i++) {
    int a = x / i;
    int r = x / a;
    ans += (r - i + 1) * getMuSum(a);
    i = r;
  }
  ans = 1ll - ans;
  muSumCache[x] = ans;
  return ans;
}
int main(int argc, char const *argv[]) {
  int t;
  ios::sync_with_stdio(false);
  cin.tie(0);
  init();
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    cout << getPhiSum(n) << " " << getMuSum(n) << "\n";
  }
  return 0;
}

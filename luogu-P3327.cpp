// [SDOI2015]约数个数和
// 莫比乌斯反演
// https://www.luogu.com.cn/problem/P3327
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 6;
bool isPrime[MAXN];
int prime[MAXN];
int mu[MAXN];
int sum[MAXN];
void euler() {
  memset(isPrime, true, sizeof isPrime);
  isPrime[0] = isPrime[1] = false;
  mu[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    if (isPrime[i]) prime[++prime[0]] = i, mu[i] = -1;
    for (int j = 1; j <= prime[0] && i * prime[j] < MAXN; j++) {
      isPrime[i * prime[j]] = false;
      if (i % prime[j] == 0)
        break;
      else
        mu[i * prime[j]] = -mu[i];
    }
  }
}
long long cal[MAXN];
long long getCal(int x) {
  long long ans = 0;
  for (int i = 1; i <= x; i++) {
    int a = x / i;
    int r = x / a;
    ans += 1ll * a * (r - i + 1);
    i = r;
  }
  return ans;
}
long long solve(int n, int m) {
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    int a = n / i;
    int b = m / i;
    if (a == 0 || b == 0) break;
    int r = min(n / a, m / b);
    ans += (sum[r] - sum[i - 1]) * cal[a] * cal[b];
    i = r;
  }
  return ans;
}
int main(int argc, char const *argv[]) {
  int t;
  ios::sync_with_stdio(false);
  cin.tie(0);
  euler();
  for (int i = 1; i < MAXN; i++) sum[i] = sum[i - 1] + mu[i];
  for (int i = 1; i < MAXN; i++) {
    cal[i] = getCal(i);
  }
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    cout << solve(n, m) << "\n";
  }
  return 0;
}

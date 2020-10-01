// YY的GCD
// 莫比乌斯反演
// https://www.luogu.com.cn/problem/P2257
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e7 + 5;
int mu[MAXN];
bool isPrime[MAXN];
int prime[MAXN];
long long sum[MAXN];
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

int main(int argc, char const *argv[]) {
  int t;
  ios::sync_with_stdio(false);
  cin.tie(0);
  euler();
  for (int i = 1; i < MAXN; i++) {
    if (isPrime[i]) {
      for (int j = 1, k = i; k < MAXN; k += i, j++) {
        sum[k] += mu[j];
      }
    }
    sum[i] += sum[i - 1];
  }
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    long long ans = 0;
    for (int i = 1; i < MAXN; i++) {
      int a = m / i;
      int b = n / i;
      if (a == 0 || b == 0) break;
      int r = min(m / a, n / b);
      ans += 1ll * a * b * (sum[r] - sum[i - 1]);
      i = r;
    }
    cout << ans << "\n";
  }

  return 0;
}

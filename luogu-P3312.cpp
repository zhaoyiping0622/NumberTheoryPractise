// [SDOI2014]数表
// 莫比乌斯反演
// https://www.luogu.com.cn/problem/P3312
#include <bits/stdc++.h>
using namespace std;
class query {
 public:
  int n, m, a;
  int num;
  long long ans;
};
const int MAXN = 1e5 + 5;
long long dSum[MAXN];
bool isPrime[MAXN];
int prime[MAXN];
int mu[MAXN];
void euler() {
  memset(isPrime, true, sizeof isPrime);
  isPrime[0] = isPrime[1] = false;
  dSum[1] = 1;
  mu[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    if (isPrime[i]) prime[++prime[0]] = i, dSum[i] = i + 1, mu[i] = -1;
    for (int j = 1; j <= prime[0] && i * prime[j] < MAXN; j++) {
      isPrime[i * prime[j]] = false;
      if (i % prime[j] == 0) {
        int t = i;
        while (t % prime[j] == 0) t /= prime[j];
        dSum[i * prime[j]] = dSum[i] * prime[j] + dSum[t];
        break;
      } else {
        dSum[i * prime[j]] = dSum[i] * (prime[j] + 1);
        mu[i * prime[j]] = -mu[i];
      }
    }
  }
}
long long sum[MAXN];
inline int lowbit(int x) { return x & -x; }
void add(int lo, int x) {
  for (; lo < MAXN; lo += lowbit(lo)) sum[lo] += x;
}
long long getSum(int lo) {
  long long ret = 0;
  for (; lo; lo -= lowbit(lo)) ret += sum[lo];
  return ret;
}
int main(int argc, char const *argv[]) {
  int q;
  ios::sync_with_stdio(false);
  cin.tie(0);
  euler();
  cin >> q;
  vector<query> allQueries;
  for (int i = 0; i < q; i++) {
    int n, m, a;
    cin >> n >> m >> a;
    query qq;
    qq.num = i;
    qq.n = n;
    qq.m = m;
    qq.a = a;
    allQueries.push_back(qq);
  }
  sort(allQueries.begin(), allQueries.end(),
       [&](query a, query b) { return a.a < b.a; });
  vector<pair<int, int>> alldSum;
  for (int i = 1; i < MAXN; i++) {
    alldSum.push_back(make_pair(i, dSum[i]));
  }
  sort(alldSum.begin(), alldSum.end(),
       [](pair<int, int> a, pair<int, int> b) { return a.second > b.second; });
  for (auto &x : allQueries) {
    while (alldSum.size() && alldSum.back().second <= x.a) {
      auto x = alldSum.back();
      for (int i = 1, j = x.first; j < MAXN; j += x.first, i++) {
        add(j, mu[i] * x.second);
      }
      alldSum.pop_back();
    }
    int n = x.n;
    int m = x.m;
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
      int a = n / i;
      int b = m / i;
      if (a == 0 || b == 0) break;
      int r = min(n / a, m / b);
      ans += (getSum(r) - getSum(i - 1)) * a * b;
      i = r;
    }
    x.ans = ans;
  }
  sort(allQueries.begin(), allQueries.end(),
       [](query a, query b) { return a.num < b.num; });
  for (auto x : allQueries) cout << x.ans % (1ll << 31) << "\n";
  return 0;
}

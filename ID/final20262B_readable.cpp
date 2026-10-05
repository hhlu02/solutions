#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
template <class T> using V = vector<T>;
using ll = long long;

const ll INF = 1e18;

struct FT { // []
    V<ll> s;
    FT(int n) : s(n) {}
    void add(int i, ll x) {
        for (; i < sz(s); i += i & -i) s[i] += x;
    }
    ll sum(int i) {
        ll res = 0;
        for (; i > 0; i -= i & -i) res += s[i];
        return res;
    }
    ll sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    cin >> N >> Q;
    FT ft(N + 1);
    V<ll> A(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        ft.add(i, A[i]);
    }
    while (Q--) {
        char op;
        cin >> op;
        if (op == '!') {
            int X;
            ll v;
            cin >> X >> v;
            ft.add(X, v - A[X]);
            A[X] = v;
        } else {
            int K;
            cin >> K;
            auto check = [&](int i) -> bool {
                return ft.sum(i - 1) <= ft.sum(i + K, N);
            };
            int lo = 0, hi = N - K + 1;
            while (lo < hi) {
                int mid = lo + (hi - lo + 1) / 2;
                check(mid) ? lo = mid : hi = mid - 1;
            }
            auto get = [&](int i, int K) -> ll {
                return (K > 1 ? ft.sum(i, i + K - 1) : 0) + abs(ft.sum(i - 1) - ft.sum(i + K, N));
            };
            ll ans = INF;
            if (lo > 0) ans = min(ans, get(lo, K));
            if (lo < N - K + 1) ans = min(ans, get(lo + 1, K));
            if (ans == INF) ans = -1;
            cout << ans << "\n";
        }
    }
    return 0;
}

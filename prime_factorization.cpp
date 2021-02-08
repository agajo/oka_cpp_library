#include <string>
#include <iostream>
#include <vector>
#include <utility> //pair

using namespace std;
// 問題が起こるまでintは使用禁止2020-04-13
using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); ++i)

// =========素因数分解Aここから下をコピペ============
// 試し割りによる方法。O(√n)です。m回やるならO(m√n)
// 返り値は{素数、その個数}のvector
vector<pair<ll, ll>> primeFactorizationA(ll n)
{
    vector<pair<ll, ll>> ans;
    ll k = n;
    for (ll i = 2; i * i <= n; i++)
    {
        ll count = 0;
        while (k % i == 0)
        {
            count++;
            k /= i;
        }
        if (count > 0)
            ans.push_back({i, count});
    }
    if (k != 1)
        ans.push_back({k, 1});
    return ans;
}

// =========素因数分解Aここまで============

// =========素因数分解Bここから下をコピペ============
// 事前に(1でない)最小約数を記録した配列を作る。
// 事前計算O(nlogn)、分解一回はO(logn)
// m回やるならO((n+m)logn)
// nが10^6を超えている時は使えない！！！！
vector<ll> makeMinDivisers(ll n)
{
    vector<ll> mins(n + 1);
    rep(i, n + 1) mins[i] = i;
    for (ll i = 2; i * i <= n; ++i)
    {
        if (mins[i] % i == 0)
        {
            for (ll j = 0; i + j <= n; j += i)
            {
                if (mins[i + j] == i + j)
                    mins[i + j] = i;
            }
        }
    }
    return mins;
}

// minDivisersをコピーせずに使い回すため、参照渡し
// 返り値は{素数、その個数}のvector
vector<pair<ll, ll>> primeFactorizationB(ll n, vector<ll> &minDivisers)
{
    if (n > minDivisers.size() - 1)
    {
        cout << "error! n must be <= minDivisers.size()-1" << endl;
    }
    else if (n <= 1)
    {
        cout << "error! n must be >= 2" << endl;
    }
    vector<pair<ll, ll>> result;
    ll x = n;
    ll lastDiviser = minDivisers[n];
    ll count = 0;
    while (x != 1)
    {
        if (minDivisers[x] == lastDiviser)
        {
            ++count;
            x = x / minDivisers[x];
        }
        else
        {
            result.push_back(pair<ll, ll>{lastDiviser, count});
            lastDiviser = minDivisers[x];
            count = 0;
        }
    }
    result.push_back(pair<ll, ll>{lastDiviser, count});
    return result;
}
// =========素因数分解Bここまで============

int main()
{
    ll n = 1000000;
    vector<vector<pair<ll, ll>>> resultA;
    for (ll i = n - 9; i <= n; ++i)
    {
        resultA.push_back(primeFactorizationA(i));
    }
    for (ll i = resultA.size() - 10; i < resultA.size(); ++i)
    {
        cout << n + i - 9 << " = ";
        for (ll j = 0; j < resultA[i].size(); ++j)
        {
            cout << get<0>(resultA[i][j]) << "^" << get<1>(resultA[i][j]) << " * ";
        }
        cout << endl;
    }
    cout << endl;
    vector<ll> minDivisers = makeMinDivisers(n + 2);
    vector<vector<pair<ll, ll>>> resultB;
    for (ll i = n - 9; i <= n; ++i)
    {
        resultB.push_back(primeFactorizationB(i, minDivisers));
    }
    for (ll i = resultB.size() - 10; i < resultB.size(); ++i)
    {
        cout << n + i - 9 << " = ";
        for (ll j = 0; j < resultB[i].size(); ++j)
        {
            cout << get<0>(resultB[i][j]) << "^" << get<1>(resultB[i][j]) << " * ";
        }
        cout << endl;
    }

    return 0;
}
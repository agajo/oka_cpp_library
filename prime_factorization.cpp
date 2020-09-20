#include <string>
#include <iostream>
#include <vector>
#include <utility> //pair

using namespace std;
// 問題が起こるまでintは使用禁止2020-04-13
using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); ++i)

// =========ここから下をコピペ============

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
vector<pair<ll, ll>> primeFactorization(ll n, vector<ll> &minDivisers)
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

int main()
{
    ll n = 1000000;
    vector<ll> minDivisers = makeMinDivisers(n + 2);
    vector<vector<pair<ll, ll>>> result;
    for (ll i = 2; i < n; ++i)
    {
        result.push_back(primeFactorization(i, minDivisers));
    }
    for (ll i = result.size() - 10; i < result.size(); ++i)
    {
        cout << i + 2 << " = ";
        for (ll j = 0; j < result[i].size(); ++j)
        {
            cout << get<0>(result[i][j]) << "^" << get<1>(result[i][j]) << " * ";
        }
        cout << endl;
    }

    return 0;
}
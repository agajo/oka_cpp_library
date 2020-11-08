#include <string>
#include <iostream>
#include <vector>
#include <utility> //pair

using namespace std;
// 問題が起こるまでintは使用禁止2020-04-13
using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); ++i)

// =========ここから下をコピペ============

vector<ll> allDivisors(ll n)
{

    vector<ll> result;

    for (ll i = 1; i <= n / i; ++i)
    {

        if (n % i == 0)
        {
            result.push_back(i);
            if (n / i != i)
            {
                result.push_back(n / i);
            }
        }
    }

    sort(result.begin(), result.end());

    return result;
}

// ===========コピペここまで==============

int main()
{
    ll n;
    // cin >> n;
    n = 36;
    vector<ll> result = allDivisors(n);
    for (auto itr = result.begin(); itr != result.end(); ++itr)
    {
        cout << (*itr) << endl;
    }
}
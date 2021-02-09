#include <string>
#include <iostream>
#include <stack>
#include <queue> // priority_queue も入ってる
#include <set>   // 要素数は size() で取得 multisetもある
#include <map>
#include <array> // sizeはコンパイル時定数で固定
#include <vector>
#include <numeric>   // accumulate, gcd
#include <algorithm> // count_ifに必要
#include <iomanip>   // cout << setprecision(15) << x で小数の出力精度を指定
#include <tuple>
#include <utility> //pair
#include <cmath>
#include <random>

using namespace std;
using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); ++i)

ll power(ll base, ll exponent)
{
    ll ans = 1;
    rep(i, exponent)
    {
        ans *= base;
    }
    return ans;
}

int main()
{
    cout << power(2, 0) << endl;
    cout << power(2, 10) << endl;
    cout << power(2, 62) << endl;
    // ↓ overflow!! ↓
    // cout << power(2, 63) << endl;
    return 0;
}
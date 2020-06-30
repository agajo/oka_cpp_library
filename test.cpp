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

using namespace std;
// 問題が起こるまでintは使用禁止2020-04-13
using ll = long long;

// template <class InputIterator, class T>
// bool contains_itr(InputIterator iterator, const T &value)
// {
//     if (find(iterator.begin(), iterator.end(), value) == iterator.end())
//         return false;
//     else
//         return true;
// }

// template <class T>
// bool contains_set(set<T> st, const T &value)
// {
//     if (st.find(value) == st.end())
//     {
//         return false;
//     }
//     else
//     {
//         return true;
//     }
// }

int main()
{
    set<string> xs;
    string s;
    cin >> s;
    xs.insert(s);
    if (xs.contains("ABC"))
    {
        cout << "ARC";
    }
    else
    {
        cout << "ABC";
    }
}
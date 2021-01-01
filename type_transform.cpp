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
// 問題が起こるまでintは使用禁止2020-04-13
using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); ++i)

int main()
{
    ll z1 = 15;
    ll z2 = 31;
    ll z3 = 7;
    ll p = 3.1415; // これエラーにならずに3になるので注意
    double pi = 3.14159265;
    char c = '6';
    string s = "1234";
    string n = "-4321";
    string d = "6.28";
    int i = 987;
    char a = 'j';

    // 整数→小数
    double x1 = (double)z1;
    cout << setprecision(15) << x1 << endl;
    // 小数→整数
    ll x2 = p;
    cout << x2 << endl;
    // 整数の割り算の結果を小数として
    double x3 = (double)z1 / z2;
    cout << setprecision(15) << x3 << endl;
    // 文字→整数
    ll x4 = ll{c - '0'};
    cout << x4 << endl;
    // 整数→文字
    char x5 = '0' + z3;
    cout << x5 << endl;
    // 整数→文字列
    string x6 = to_string(z1);
    cout << x6 << endl;
    // 小数→文字列
    string x7 = to_string(z1);
    cout << x7 << endl;
    // 文字列→整数(負の数も)
    ll x8 = stoll(n);
    cout << x8 << endl;
    // 文字列→小数
    double x9 = stod(d);
    cout << x9 << endl;
    // int→ll
    ll x10 = ll{i};
    cout << x10 << endl;
    // アルファベット→何番目(0-indexed)か
    ll x11 = a - 'a';
    cout << x11 << endl;
    // 何番目(0-indexed)か→アルファベット
    char x12 = 'a' + z3;
    cout << x12 << endl;
    return 0;
}
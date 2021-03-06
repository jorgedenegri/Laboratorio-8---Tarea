#include <iostream>
#include <algorithm>
#include <random>
#include <math.h>
#include <vector>
using namespace std;
int powmod (int a, int b, int p) 
{
    int res = 1;
    while (b)
    {
        if (b & 1)
        {
            res = int (res * 1ll * a % p);
            --b;
        }
        else
        {
            a = int (a * 1ll * a % p);
            b >>= 1;
        }
    }  
    return res;
}
bool witness(int a, int n)
{
    int car = 1;
    int f = 0, g=1;
    bool enc = false;
    while (car*2 <= n - 1)
    {
        f++;
        car = car*2;
        while (car*g <= n - 1)
        {
            if (car*g == n - 1 && g % 2 != 0)
            {
                enc = true;
                break;
            }
            g++;
        }
        if (enc==true)
        {
            break;
        }
        g = 0;
    }
    if (!enc)
    {
        return false;
    }

    int pre_x = powmod(a, g, n);
    int x; 
    if (pre_x == 1 || pre_x == n-1)
    {
        return false;
    }
    for (int i = 1; i < f; i++)
    {
        x = powmod(pre_x, 2, n);
        if (x == n - 1)
        {
            return false;
        }
        pre_x = x;
    }
    return true;
}
int random_int(int a, int b)
{
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> distr(a, b);

    return distr(gen);
}
bool miller_rabin(int n, int s)
{
    int a;
    for (int i = 1; i <= s; i++)
    {
        a = random_int(1, n - 1);
        if (witness(a, n))
        {
            return true;
        }
    }
    return false;
}
int generate_prime_candidate(int b)
{
    int n = random_int(0, pow(2, b));
    int m = pow(2, (b - 5)) + 1;
    n = n | m;
    
    return n;
}
int generate_prime(int b)
{
    int s = 32;
    int n = generate_prime_candidate(b);
    while (miller_rabin(n, s))
    {
        n += 2;
    }
    return n;
}
int main(void)
{
   int cant = 0;
   int n;
  vector<int> res;

   while (res.size() != 100)
   {
       n = generate_prime(10);
       if (n % 2 != 0)
       {
           if (!(find(res.begin(), res.end(), n) != res.end()))
           {
               res.push_back(n);
               cant++;
           }
       }
   }
   int j = 0;
   for (int i = 0; i < res.size(); i++)
   {
       if (j == 20)
       {
           cout << endl;
           j = 0; 
       }
       j++;
       cout << res[i] << ",";
   }
   cout<<endl;
   cout << "en total "<<cant<<" primos"<<endl;
}

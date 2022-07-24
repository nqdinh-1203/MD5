#include <iostream>
#include <string>
#include <math.h>
#include <bitset>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

unsigned int s[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

uint32_t K[64] = {
    0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,
    0xa8304613,0xfd469501,0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
    0x6b901122,0xfd987193,0xa679438e,0x49b40821,0xf61e2562,0xc040b340,
    0x265e5a51,0xe9b6c7aa,0xd62f105d,0x2441453,0xd8a1e681,0xe7d3fbc8,
    0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,
    0x676f02d9,0x8d2a4c8a,0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
    0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,0x289b7ec6,0xeaa127fa,
    0xd4ef3085,0x4881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
    0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,
    0xffeff47d,0x85845dd1,0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
    0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
};

uint32_t a0 = 0x67452301;
uint32_t b0 = 0xEFCDAB89;
uint32_t c0 = 0x98BADCFE;
uint32_t d0 = 0x10325476;

void reverseStr(string& str)
{
    int n = str.length();

    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

/* string int_to_64bitsbin(int n)
{
    string bin = "";
    while(n != 0)
    {
        bin += to_string(n%2);
        n /= 2;
    }

    int add = 64 - bin.length();
    for (int i = 0; i < add; i++)
    {
        bin += "0";
    }
    reverseStr(bin);

    return bin;
} */

string to_512bits(string m)
{
    string bin = "";
    string b = "";

    for (int i = 0; i < m.length(); ++i)
        b += bitset<8>(m.c_str()[i]).to_string();

    cout << b.length() << endl;

    int add = 448 - b.length();
    bin += b;
    bin += "1";

    for (int i = 0; i < add - 1; i++)
        bin += "0";

    bin += bitset<64>(b.length()).to_string();

    return bin;
}

inline uint32_t stoui32(const string& s)
{
    istringstream reader(s);
    uint32_t val = 0;
    reader >> val;
    return val;
}

vector<uint32_t> md5_hash(string m)
{
    string m_bin = to_512bits(m);
    vector<uint32_t> w;

    for (int i = 0; i < m_bin.length(); i+=32)
    {
        string sub = m_bin.substr(i, 32);
        w.push_back(stoui32(sub));
    }    /* for (uint32_t i : w)
    {
        cout << i << endl;
    } */

    uint32_t A = a0;
    uint32_t B = b0;
    uint32_t C = c0;
    uint32_t D = d0;

    for (int i = 0; i < 64; i++)
    {
        uint32_t f;
        int g;

        if(i >= 0 && i <= 15)
        {
            f = (B&C) | ((~B)&D);
            g = i;
        }
        else
        if(i >= 16 && i <= 31)
        {
            f = (D&B) | ((~D)&C);
            g = (5*i + 1) % 16;
        }
        else
        if(i >= 32 && i <= 47)
        {
            f = B^C^D;
            g = (3*i + 5) % 16;
        }
        else
        {
            f = C^(B | (~D));
            g = (7*i) % 16;
        }
        f += (A + K[i] + w[g]);
        A = D;
        D = C;
        C = B;
        B += ((f << s[i]) | (f >> (32 - s[i])));
    }

    a0 += A;
    b0 += B;
    c0 += C;
    d0 += D;

    vector<uint32_t> res = {a0, b0, c0, d0};

    return res;
}

int main()
{
    //cout << to_512bits("fit.hcmus");

    vector<uint32_t> result = md5_hash("fit.hcmus");

    printf("Digest: %2.2x%2.2x%2.2x%2.2x\n", result[0], result[1], result[2], result[3]);
    return 0;
}

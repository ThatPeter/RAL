#include <iostream>
#include <vector>
#include <bitset>
#include <string>

int BerlekampMassey(std::vector<int> s)
{
    int L, N, m, d;
    int n = s.size();

    std::vector<int> c = s;
    std::vector<int> b = s;
    std::vector<int> t = s;

    b[0] = 1;
    c[0] = 1;
    N = 0;
    L = 0;
    m = -1;

    while (N < n)
    {
        d = s[N];
        for (int i = 1; i <= L; i++) 
        {
            d ^= c[i] & s[N - i];
        }

        if (d == 1)
        {
            t = c;
            for (int i = 0; (i + N - m) < n; i++)
            {
                c[i + N - m] ^= b[i];  
            }

            if (L <= (N >> 1))
            {
                L = N + 1 - L;
                m = N;
                b = t;
            }
        }
        N++;
    }

    return L;
}

int pow(int base, int exponent)
{
    int number = 1;
    for (int i = 0; i < exponent; i++)
    {
        number *= base;
    }
    return number;
}

constexpr int size(int n)
{
    return 2 << (n - 1);
}

std::vector<std::vector<int>> GetSequences(int n)
{
    std::vector<std::vector<int>> sequences;
    for (int i = 0; i < pow(2, n); i++)
    {
        std::bitset<2 << 20> bits(i);
        std::vector<int> sequence;
        for (int i = 0; i < n; i++)
        {
            sequence.push_back(bits[i]);
        }
        sequences.push_back(sequence);
    }
    
    return sequences;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Please specify the sequence size.\n";
        return -1;
    }

    if (argc > 2)
    {
        std::cout << "Invalid usage.\n";
        return -1;
    }

    std::string sequenceSize = argv[1];

    int n = std::stoi(sequenceSize); //16;

    if (n < 1 || n > pow(2,20)) //??????? 
    {
        std::cout << "For performance reasons, only integers in range 1-20 are allowed.\n";
        return -1;
    }

    std::vector<std::vector<int>> sequences = GetSequences(n);

    std::vector<int> results(n + 1, 0);

    for (int i = 0; i < sequences.size(); i++)
    {
        results[BerlekampMassey(sequences[i])]++;
    }

    for (int i = 0; i < n + 1; i++)
    {
        std::cout << i << ": " << results[i] << "\n";
    }

    return 0;
}
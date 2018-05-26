#include <iostream>
#include <vector>
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

void processSequence(std::vector<int>& results, const std::string answer)
{
    std::vector<int> toProcess;
    for (char c : answer)
    {
        toProcess.push_back(std::stoi(std::string(&c)));
    }
    results[BerlekampMassey(toProcess)]++;
}

void stringProcessing(std::vector<int>& results, std::string s, int digitsLeft)
{
    if (digitsLeft == 0) 
    {
        processSequence(results, s);
        return;
    }
    else
    {
        stringProcessing(results, s + "0", digitsLeft - 1);
        stringProcessing(results, s + "1", digitsLeft - 1);
    }
}

void process(std::vector<int>& results, int length)
{
    std::string s;
    stringProcessing(results, s, length);
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
    int n = std::stoi(sequenceSize);

    std::cout << "Zadana dlzka postupnosti: " << n << "\nPocitam...\n\n";

    std::string s;
        
    std::vector<int> results(n + 1, 0);

    process(results, n);

    std::cout << "Format:\ni: p\t,kde p je pocet postupnosti s linearnou zlozitostou i dlzky n\n\n";
    for (int i = 0; i < n + 1; i++)
    {
        std::cout << i << ": " << results[i] << "\n";
    }

    return 0;
}
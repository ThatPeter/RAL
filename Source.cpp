#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <queue>

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
/*
std::vector<std::vector<int>> GetSequences(std::vector<std::string> answer)
{
    std::vector<std::vector<int>> sequences;
    for (auto vec : answer)
    {
        std::vector<int> toPushBack;
        for (char c : vec)
        {
            toPushBack.push_back(std::stoi(std::string(&c)));
        }
        sequences.push_back(toPushBack);
    }

    return sequences;
}


void getStrings(std::vector<std::string>& answer , std::string s, int digitsLeft)
{
    if (digitsLeft == 0) // the length of string is n
        answer.push_back(s);
    else
    {
        getStrings(answer, s + "0", digitsLeft - 1);
        getStrings(answer, s + "1", digitsLeft - 1);
    }
}
*/
/*
std::vector<std::vector<int>> GetSequences(std::queue<std::string> answer)
{
    std::vector<std::vector<int>> sequences;

    while (answer.size() >= 1)
    {
        std::string str = answer.front();
        answer.pop();
        std::vector<int> toPushBack;
        for (char c : str)
        {
            toPushBack.push_back(std::stoi(std::string(&c)));
        }
        sequences.push_back(toPushBack);
    }

    return sequences;
}


void getStrings(std::queue<std::string>& answer, std::string s, int digitsLeft)
{
    if (digitsLeft == 0) // the length of string is n
        answer.push(s);
    else
    {
        getStrings(answer, s + "0", digitsLeft - 1);
        getStrings(answer, s + "1", digitsLeft - 1);
    }
}

int main(int argc, char** argv)
{   
    try {
        argc = 2;
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


        //  std::string sequenceSize = argv[1];
         // int n = std::stoi(sequenceSize);
        int n = 23;
        std::queue<std::string> gf2StringVectors;
        std::string s;
        getStrings(gf2StringVectors, s, n);

        std::vector<std::vector<int>> sequences = GetSequences(gf2StringVectors);

        std::vector<int> results(n + 1, 0);

        for (int i = 0; i < sequences.size(); i++)
        {
            results[BerlekampMassey(sequences[i])]++;
        }

        for (int i = 0; i < n + 1; i++)
        {
            std::cout << i << ": " << results[i] << "\n";
        }
    }
    catch (std::invalid_argument& ia)
    {
        std::cout << ia.what();
    }

    return 0;
}
*/
void processSequence(std::vector<int>& results, std::string answer)
{
    std::vector<int> toPushBack;
    for (char c : answer)
    {
        toPushBack.push_back(std::stoi(std::string(&c)));
    }
    results[BerlekampMassey(toPushBack)]++;
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
    argc = 2;
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


    //  std::string sequenceSize = argv[1];
    // int n = std::stoi(sequenceSize);
    int n = 30;
    std::string s;
        
    std::vector<int> results(n + 1, 0);

    process(results, n);

    for (int i = 0; i < n + 1; i++)
    {
        std::cout << i << ": " << results[i] << "\n";
    }


    return 0;
}
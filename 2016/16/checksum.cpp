#include <iostream>
#include <string_view>
#include <string>

std::string dragonCurve(std::string a)
{
    std::string b{};
    for (int i = a.length()-1; i>=0; i-- )
    {
        if (a[i] == '1')
        {
            b += '0';
        }
        else
        {
            b += '1';
        }
    }
    return a + "0" + b;
}

std::string generateCheckSum(std::string in)
{
    std::string out{};
    for (int i = 0; i < in.length(); i+=2)
    {
        if (in[i] == in[i+1])
        {
            out += '1';
        }
        else
        {
            out += '0';
        }
    }
    return out;
}

int main(int argc, char const *argv[])
{
    
    if (! (argc >1) )
    {
        std::cout << "Ange vilket problem!\n";
        return -1;
    }
    std::string_view problem{argv[1]};
    std::string input, part;
    int length;
    if (problem == "test") 
    {
        input = "10000";
        length = 20;
        part = "A";
    } 
    else if (problem == "input")
    {
        input = "00111101111101000";
        part = "A";
        length = 272;
    }
    else if (problem == "inputB")
    {
        input = "00111101111101000";
        length = 35651584;
        part = "B";
    }
    else
    {
        std::cout << "Ange test eller input!\n";
    }

    //std::cout << problem << '\n';
    //std::cout << input << '\n';

    while(input.length() < length)
    {
        input = dragonCurve(input);
    }

    //std::cout << input << '\n';

    input = input.substr(0,length);

    while (input.length() % 2 == 0)
    {
        input = generateCheckSum(input);
    }

    std::cout << "Answer part " << part << ": " << input << '\n';

    return 0;
}

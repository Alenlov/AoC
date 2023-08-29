#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
    int max = 3012210;
    std::vector<int> elves;
    for (int i = 0; i < max; i ++) elves.emplace_back(1);
    bool remove = false;
    while(elves.size() > 1)
    {
        std::cout << "Remaining: " << elves.size() << '\n';
        for (std::vector<int>::iterator it = elves.begin(); it != elves.end();)
        {
            if (remove)
            {
                std::cout << "Removing " << *it << '\n';
                it = elves.erase(it);
            }
            else
            {
                ++it;
            }
            remove = !remove;
        }
    }

    std::cout << "Answer part A: " << elves[0] << '\n';

    return 0;
}

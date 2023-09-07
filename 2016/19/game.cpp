#include <iostream>
#include <list>

int main(int argc, char const *argv[])
{
    int max = 3012210;
    std::list<int> elves;
    for (int i = 0; i < max; i ++) elves.emplace_back(i+1);
    bool remove = false;
    while(elves.size() > 1)
    {
        std::cout << "Remaining: " << elves.size() << '\n';
        for (std::list<int>::iterator it = elves.begin(); it != elves.end();)
        {
            if (remove)
            {
                //std::cout << "Removing " << *it << '\n';
                it = elves.erase(it);
            }
            else
            {
                ++it;
            }
            remove = !remove;
        }
    }

    std::cout << "Answer part A: " << *elves.begin() << '\n';

    std::list<int> elvesB;
    for (int i = 0; i < max; i ++) elvesB.emplace_back(i+1);
    std::list<int>::iterator curElf = elvesB.begin(), toRemove = elvesB.begin();
    std::advance(toRemove, elvesB.size()/2);
    while(elvesB.size() > 1)
    {
        std::cout << "Removing " << *toRemove << std::endl;
        toRemove = elvesB.erase(toRemove);
        if (toRemove == elvesB.end()) toRemove = elvesB.begin();
        std::cout << "Remaining: " << elvesB.size() << '\n';
        if (elvesB.size() % 2 == 0) {
            ++toRemove;
            if (toRemove == elvesB.end()) toRemove = elvesB.begin();
        }
    }

    std::cout << "Answer part B: " << *elvesB.begin() << '\n';

    return 0;
}

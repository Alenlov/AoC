#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <list>

std::map<char,int> cardVal{ {'A',14}, {'K',13}, {'Q',12}, {'J',11}, {'T',10}, {'9',9}, {'8',8}, {'7',7}, {'6',6}, {'5',5}, {'4',4}, {'3',3}, {'2',2} };
std::map<char,int> cardValB{ {'A',14}, {'K',13}, {'Q',12}, {'J',1}, {'T',10}, {'9',9}, {'8',8}, {'7',7}, {'6',6}, {'5',5}, {'4',4}, {'3',3}, {'2',2} };

std::vector<std::string> splitLine(std::string line, std::string split = " ")
{
    std::vector<std::string> vectorOfStrings;
    std::size_t indx = 0;
    std::size_t newIndx = 0;

    while(newIndx != std::string::npos)
    {
        newIndx = line.find(split, indx);
        if((newIndx - indx) > 0)
        {
            vectorOfStrings.push_back(line.substr(indx, newIndx - indx));
        }
        indx = newIndx + split.size();
    }
    return vectorOfStrings;
}

struct hand
{
    std::string cards;
    long score, bid;

    bool operator>(const hand& rhs) const
    {
        if (score != rhs.score)
        {
            return score > rhs.score;
        }
        else
        {
            for (int i{0}; i < cards.size(); i++)
            {
                if (cards[i] != rhs.cards[i])
                {
                    return cardVal[cards[i]] > cardVal[rhs.cards[i]];
                }
            }
        }
        return false;
    }

    bool operator<(const hand& rhs) const
    {
        if (score != rhs.score)
        {
            return score < rhs.score;
        }
        else
        {
            for (int i{0}; i < cards.size(); i++)
            {
                if (cards[i] != rhs.cards[i])
                {
                    return cardVal[cards[i]] < cardVal[rhs.cards[i]];
                }
            }
        }
        return false;
    }

};

struct handB
{
    std::string cards;
    long score, bid;

    bool operator>(const handB& rhs) const
    {
        if (score != rhs.score)
        {
            return score > rhs.score;
        }
        else
        {
            for (int i{0}; i < cards.size(); i++)
            {
                if (cards[i] != rhs.cards[i])
                {
                    return cardValB[cards[i]] > cardValB[rhs.cards[i]];
                }
            }
        }
        return false;
    }

    bool operator<(const handB& rhs) const
    {
        if (score != rhs.score)
        {
            return score < rhs.score;
        }
        else
        {
            for (int i{0}; i < cards.size(); i++)
            {
                if (cards[i] != rhs.cards[i])
                {
                    return cardValB[cards[i]] < cardValB[rhs.cards[i]];
                }
            }
        }
        return false;
    }

};

long calcSCore(std::string cards)
{
    std::map<char,int> cardCount;
    for (char c : cards)
    {
        ++cardCount[c];
    }
    if (cardCount.size() == 1)
    {
        return 7;
    }
    else if (cardCount.size() == 2)
    {
        int oneCount = cardCount.begin()->second;
        if(oneCount == 1 || oneCount == 4)
        {
            return 6;
        }
        else
        {
            return 5;
        }
    }
    else if (cardCount.size() == 3)
    {
        int maxCount{0};
        for (auto const [c,n] : cardCount)
        {
            if (n > maxCount) maxCount = n;
        }
        if (maxCount == 3)
        {
            return 4;
        }
        else
        {
            return 3;
        }
    }
    else if (cardCount.size() == 4)
    {
        return 2;
    }
    else if (cardCount.size() == 5)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return -1;
    
    
} 

long calcSCoreB(std::string cards)
{
    std::map<char,int> cardCount;
    for (char c : cards)
    {
        ++cardCount[c];
    }
    int numJ = cardCount['J'];
    if (numJ == 0) return calcSCore(cards);
    int highestNotJ{0};
    for (auto const [c,n] : cardCount)
    {
        if (c != 'J')
        {
            if (n > highestNotJ)
            {
                highestNotJ = n;
            }
        }
    }
    if (cardCount.size() == 1)
    {
        return 7;
    }
    else if (cardCount.size() == 2)
    {
        return 7;
    }
    else if (cardCount.size() == 3)
    {
        if (highestNotJ + numJ == 4)
        {
            return 6;
        }
        else if (highestNotJ + numJ == 3)
        {
            return 5;
        }
    }
    else if (cardCount.size() == 4)
    {
        return 4;
    }
    else if (cardCount.size() == 5)
    {
        return 2;
    }
    else
    {
        return 0;
    }
    return -1;
    
    
} 

int main(int argc, char const *argv[])
{
    std::ifstream myfile;
    std::string line;
    if (argc > 1)
    {
        myfile.open(argv[1]);
    }
    else
    {
        return -1;
    }
    std::vector<hand> hands;
    std::vector<handB> handsB;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            std::vector<std::string> split = splitLine(line, " ");
            hand h;
            h.cards = split[0];
            h.bid = std::stol(split[1]);
            h.score = calcSCore(split[0]);
            //std::cout << h.cards << " " << h.bid << " " << h.score << std::endl;
            hands.push_back(h);
            handB hb;
            hb.cards = split[0];
            hb.bid = std::stol(split[1]);
            hb.score = calcSCoreB(split[0]);
            handsB.push_back(hb);

        }
    }
    myfile.close();
    std::sort(hands.begin(), hands.end());
    long ansA{0}, rank{0};
    for (hand h : hands)
    {
        ++rank;
        ansA += h.bid * rank;
        //std::cout << h.cards << " " << h.bid << " " << h.score << std::endl;
    }
    std::cout << "Answer part A: " << ansA << std::endl;
    std::sort(handsB.begin(), handsB.end());
    long ansB{0}, rankB{0};
    for (handB h : handsB)
    {
        ++rankB;
        ansB += h.bid * rankB;
        //std::cout << h.cards << " " << h.bid << " " << h.score << std::endl;
    }
    std::cout << "Answer part B: " << ansB << std::endl;
    
}
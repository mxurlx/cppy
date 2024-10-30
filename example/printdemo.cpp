#include "cppy.h"

using namespace cppy;

int main()
{
    std::string a = "blablabla";
    std::vector v = {"sa", "as", "y"};
    std::vector<std::deque<int>> matrix = {{23,45,46}, {31,44,97},{12,98,32}};
    std::deque<int> myDeque = {1, 2, 3};
    std::list<int> myList = {1, 2, 3};
    std::forward_list<int> mylList = {1, 2, 3};
    std::set<int> mySet = {3, 1, 2};
    std::multiset<int> myMultiSet = {3, 1, 2, 1};
    std::multimap<std::string, int> myMultiMap = {{"Alice", 25}, {"Bob", 30}, {"Frank", 28}};
    std::map<std::string, int> map{{"1", 1}, {"2", 2}};
    std::unordered_set<int> myUnorderedSet = {3, 1, 2};
    std::unordered_multiset<int> myUnorderedMultiSet = {3, 1, 2, 1};
    std::unordered_map<std::string, int> myUnorderedMap = {{"Alice", 25}, {"Bob", 30}};
    std::unordered_multimap<std::string, int> myUnorderedMultiMap = {{"Alice", 25}, {"Bob", 30}, {"Frank", 28}};
    std::tuple<int, double, std::string> myTuple(1, 3.14, "hey");

    print(Sep{"\n\n"}, Flush{true}, End{"\nEnd"},
        a, map, v, myDeque, myList, mylList,
        mySet, myMultiSet, myMultiMap, myUnorderedSet,
        myUnorderedMultiSet, myUnorderedMap, myUnorderedMultiMap, matrix, myTuple,
        1, "two", 't', true, 3.4f);
}

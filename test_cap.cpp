#include <iostream>
#include <vector>
#include <iterator>
int main()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    for (std::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
    {
        std::cout << it[1];
    } 
 }
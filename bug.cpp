#include <iostream>
#include <vector>


#include "test_data.h"
#include "lcs.h"

void bug()
{
    std::cout << "bug!" << "\n";
    std::vector<int> vo(256);
    std::fill(vo.begin(), vo.end(), -1);
    std::cout << "lcs_bug = " << lcs_e(a9, a10, vo) << "\n";
}
/*
 * test_main.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#include <iostream>
#include <string>
#include <zge/vector.h>

using namespace std;
using namespace zge;

static unsigned testVector()
{
    ZVec2 vec;
}

int main(int argc, char **argv)
{
    unsigned testStatus = 0;
    
    testStatus = testVector();
    
    if (testStatus == 0) {
        cout << "All tests passed!" << endl;
    }
    return testStatus;
}

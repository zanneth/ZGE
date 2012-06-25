/*
 * test_main.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#include <iostream>
#include <string>
#include <zge/geometry.h>

using namespace std;
using namespace zge;

static unsigned testMatrix()
{
    cout << __FUNCTION__ << endl;
    
    ZMatrix<float> matrix = ZMatrix<float>::identityMatrix();
    cout << matrix.getDescription() << endl;
    
    return 0;
}

static unsigned testPerspective()
{
    cout << __FUNCTION__ << endl;
    
    float aspect = 1024.0 / 768.0;
    ZMatrixf matrix = ZMatrixf::perspectiveMatrix(DEGREES_TO_RADIANS(45.0), aspect, 0.1, 100.0);
    cout << matrix.getDescription() << endl;
    
    return 0;
}

int main(int argc, char **argv)
{
    unsigned testStatus = 0;
    
    testStatus = testMatrix();
    testStatus = testPerspective();
    
    if (testStatus == 0) {
        cout << "All tests passed!" << endl;
    }
    return testStatus;
}

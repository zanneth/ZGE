/*
 * test_main.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#include <iostream>
#include <string>

#include <zge/vector.h>
#include <zge/matrix.h>

using namespace std;
using namespace zge;

static unsigned testVector()
{
    float arr[3] = { 1.0, 2.0, 3.0 };
    
    ZVec3 vec(arr);
    
    cout << vec.getDescription() << endl;
    vec.x = 10.0;
    vec.y *= 100.0;
    vec.z = 0.0;
    
    cout << vec.getDescription() << endl;
    cout << vec.y << endl;
    
    ZVec2 vec2(arr);
    cout << vec2.getDescription() << endl;
    vec2.x = 0;
    cout << vec2.getDescription() << endl;
    
    return 0;
}

static unsigned testMatrix()
{
    ZMatrix4 mat = ZMatrix4::identity();
    cout << mat.getDescription() << endl;
    
    return 0;
}

int main(int argc, char **argv)
{
    unsigned testStatus = 0;
    
    testStatus =    testVector();
    testStatus &=   testMatrix();
    
    if (testStatus == 0) {
        cout << "All tests passed!" << endl;
    }
    return testStatus;
}

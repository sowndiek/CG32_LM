#include <iostream>
using namespace std;

int main() {
    const int originX = 100;
    const int originY = 50;
    const int scale = 10;
    int xMath, yMath;

    cout << "Enter Mx: ";
    cin >> xMath;


    cout << "Enter My: ";
    cin >> yMath;


    //int resultX = xMath * 3;
    //int resultY = yMath * 2;
    //cout << "Gx = " << resultX << endl;
    //cout << "Gy = " << resultY << endl;

    //int xGraphical = (xMath + screenWidth) / 2;
    //int yGraphical = screenHeight / 2 - yMath;

    int xGraphical = originX + (xMath * scale);
    int yGraphical = originY - (yMath * scale);

    cout << "Graphical Coordinates:" << endl;
    cout << "X: " << xGraphical << ", Y: " << yGraphical << endl;



    return 0;
}

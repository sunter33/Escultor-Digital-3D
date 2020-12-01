#include "sculptor.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

int main(){


    Sculptor projeto(100,100,100);

    projeto.setColor(0.99,0.1,0.1,1);
    projeto.putSphere(50,50,50,25);
    projeto.cutSphere(50,50,70,20);

    projeto.setColor(0.73,0.55,0.38,1);
    projeto.putSphere(50,50,65,18);

    projeto.setColor(1,1,1,1);
    projeto.putEllipsoid(64,62,70,1,1,2);

    projeto.setColor(1,1,1,1);
    projeto.putEllipsoid(58,67,70,1,1,2);

    projeto.setColor(0.85,0.85,0.85,1);
    projeto.putSphere(60,63,50,11);


    projeto.writeOFF("C:/Users/sunter/Desktop/C Projects/Projeto/cogumelo.off");

}

#include "sculptor.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    _nx = _ny = _nz = 0;

    v = new Voxel **[_nx];

    for(int i=0; i<_nx ; i++){
        v[i] = new Voxel *[_ny];
        for(int j=0 ; j<_ny ; j++){
            v[i][j] = new Voxel[_nz];
            for(int k=0; k<_nz ; k++){
                v[i][j][k].isOn = false;
            }
        }
    }
}

Sculptor::~Sculptor(){
    int i, j, k;
    delete[] v;
}

void Sculptor::setColor(float r_, float g_, float b_, float alpha_){
            r = r_;
            g = g_;
            b = b_;
            a = alpha_;
}

void Sculptor::putVoxel(int x, int y, int z){
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
        v[x][y][z].isOn = true;

}

void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i, j, k;
    for(i = x0; i <= x1; i++){
            for (j = y0; j <= y1; j++){
                    for(k = z0; k <= z1; k++){
                            putVoxel(i,j,k);
                        }
                }
        }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i, j, k;
    for(i = x0; i <= x1; i++){
            for (j = y0; j <= y1; j++){
                    for(k = z0; k <= z1; k++){
                            cutVoxel(i,j,k);
                        }
                }
        }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    int i, j, k;
    for(i = xcenter - radius; i < xcenter + radius; i++){
            for(j = ycenter - radius; j < ycenter + radius; j++){
                    for(k = zcenter - radius; k < zcenter + radius; k++){
                            if((i-xcenter)*(i-xcenter) + (j-ycenter)*(j-ycenter)+(k-zcenter)*(k-zcenter)<=(radius)*(radius)){
                                putVoxel(i,j,k);
                                }
                        }
                }
        }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    int i, j, k;
    for(i = xcenter - radius; i < xcenter + radius; i++){
            for(j = ycenter - radius; j < ycenter + radius; j++){
                    for(k = zcenter - radius; k < zcenter + radius; k++){
                            if((i-xcenter)*(i-xcenter) + (j-ycenter)*(j-ycenter)+(k-zcenter)*(k-zcenter)<=(radius)*(radius)){
                                    cutVoxel(i,j,k);


                                }
                        }
                }
        }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int i, j, k;
    for(i = xcenter - rx; i < xcenter + rx; i++){
        for(j = ycenter - ry; j < ycenter + ry; j++){
                for(k = zcenter - rz; k < zcenter + rz; k++){
                        if(((i-xcenter)*(i-xcenter))/(rx*rx) + ((j-ycenter)*(j-ycenter))/(ry*ry)+((k-zcenter)*(k-zcenter))/(rz*rz)<=1){
                               putVoxel(i,j,k);
                            }
                    }
            }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int i, j, k;
    for(i = xcenter - rx; i <= xcenter + rx; i++){
        for(j = ycenter - ry; j <= ycenter + ry; j++){
            for(k = zcenter - rz; k <= zcenter + rz; k++){
                if(((i-xcenter)*(i-xcenter))/(rx*rx) + ((j-ycenter)*(j-ycenter))/(ry*ry)+((k-zcenter)*(k-zcenter))/(rz*rz)<=1){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(char* filename){

    int i=0, j=0, k=0;
    putVoxel(i,j,k);
    ofstream arq;
    int total=0;
    for(int i = 0; i<nz; i++)
    {
        for(int j = 0; j<ny; j++)
        {
            for(int k = 0; k<nx; k++)
            {
                if(v[i][j][k].isOn == true)
                {
                    total++;
                }
            }
        }
    }
    int vertices=total*8, faces=total*6;
    arq.open(filename);
    arq<<"OFF"<<endl;
    arq<<vertices<<" "<<faces<<" 0"<<endl;

    for(int i = 0; i<nz; i++)
    {
        for(int j = 0; j<ny; j++)
        {
            for(int k = 0; k<nx; k++)
            {
                if(v[i][j][k].isOn == true)
                {
                    arq<<i-0.5<<" "<<j+0.5<<" "<<k-0.5<<endl;
                    arq<<i-0.5<<" "<<j-0.5<<" "<<k-0.5<<endl;
                    arq<<i+0.5<<" "<<j-0.5<<" "<<k-0.5<<endl;
                    arq<<i+0.5<<" "<<j+0.5<<" "<<k-0.5<<endl;
                    arq<<i-0.5<<" "<<j+0.5<<" "<<k+0.5<<endl;
                    arq<<i-0.5<<" "<<j-0.5<<" "<<k+0.5<<endl;
                    arq<<i+0.5<<" "<<j-0.5<<" "<<k+0.5<<endl;
                    arq<<i+0.5<<" "<<j+0.5<<" "<<k+0.5<<endl;                }
            }
        }
    }

    int oito=0;

    for(int i = 0; i<nz; i++)
    {
        for(int j = 0; j<nx; j++)
        {
            for(int k = 0; k<ny; k++)
            {
                if(v[i][j][k].isOn == true)
                {
                    int vvv=oito*8;
                    arq<<"4 "<<vvv<< " "<< vvv+3<<" "<< vvv+2 <<" "<< vvv+1;
                    arq<<" "<< v[i][j][k].r <<" "<< v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    arq<<"4 "<< vvv+4<< " "<< vvv +5<<" "<< vvv+6 <<" "<< vvv+7;
                    arq<<" "<< v[i][j][k].r <<" "<< v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    arq<<"4 "<< vvv<< " " << vvv+1<<" "<< vvv+5 <<" "<< vvv+4;
                    arq<<" "<< v[i][j][k].r <<" "<< v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    arq<<"4 "<< vvv<< " " << vvv+4<<" "<< vvv+7 <<" "<< vvv+3;
                    arq<<" "<< v[i][j][k].r <<" "<< v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    arq<<"4 "<< vvv+3<<" " << vvv+7<<" "<< vvv+6 <<" "<< vvv+2;
                    arq<<" "<< v[i][j][k].r << " "<< v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    arq<<"4 "<< vvv+1 <<" "<< vvv +2<<" "<< vvv+6 <<" "<< vvv+5;
                    arq<<" "<<v[i][j][k].r << " "<< v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    oito++;
                }
                }
            }
        }
    arq.close();
}

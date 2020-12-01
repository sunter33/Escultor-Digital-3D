#ifndef SCULPTOR_H
#define SCULPTOR_H
#include <iostream>

using namespace std;

struct Voxel {
  float r,g,b; // Colors
  float a; // Transparency
  bool isOn; // Included or not
};

class Sculptor {
protected:
  Voxel ***v; // 3D matrix
  int nx,ny,nz; // Dimensions
  float r,g,b,a; // Current drawing color
public:

  /**
  * @brief E um construtor para Sculptor
  * @details inicializa o voxel
  */
  Sculptor(int _nx, int _ny, int _nz);

  /**
  * @brief O destrutor libera a memoria alocada
  *
  */
  ~Sculptor();

  /**
  * @brief Esse metodo serve para colorir a escultura
  *
  * @param r_ Valor a ser atribuido para a cor vermelha
  * @param g_ Valor a ser atribuido para a cor verde
  * @param b_ Valor a ser atribuido para a cor azul
  * @param alpha_ Valor a ser atribuido para a transparencia da escultura
  */
  void setColor(float r, float g, float b, float alpha);

  /**
  * @brief Ativa o voxel
  */
  void putVoxel(int x, int y, int z);

  /**
  * @brief Desativa o voxel na posiçao (x,y,z)
  */
  void cutVoxel(int x, int y, int z);

  /**
  * @brief Ativa todos os voxels no intervalo (x,y,z) dados
  */
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);

  /**
  * @brief Desativa todos os voxels no intervalo (x,y,z) dados
  */
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);

  /**
  * @brief Ativa os voxels que tornam a equaçao da esfera verdadeira
  * @param radius E o raio da esfera
  */
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);

  /**
  * @brief Desativa os voxels que tornam a equaçao da esfera verdadeira
  * @param radius E o raio da esfera
  */
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);

  /**
  * @brief Ativa os voxels que satisfazem a equaçao da elipse
  */
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

  /**
  * @brief Desativa os voxels que satisfazem a equaçao da elipse
  */
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

  /**
  * @brief Grava a escultura no formato OFF
  * @param filename E o nome da escultura dado pelo usuario
  */
  void writeOFF(char* filename);
};

#endif //SCULPTOR_H

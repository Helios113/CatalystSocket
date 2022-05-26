#include <catalyst_node.hpp>
#include <catalyst_socket.hpp>
#include <mpi.h>
#include <iostream>
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv) ;
    InitializeCatalyst("script.py");

    int totalElements = 1;
    for (int i = 0; i < 20; i++)
    {
        std::vector<double> x = {};
        std::vector<double> y = {};
        std::vector<double> z = {};
        std::vector<int> p = {};

        for(int j = 0; j < totalElements;j++)
        {
            z.push_back(j*1.0+i); //0
            z.push_back(j*1.0+i); //1
            z.push_back(j*1.0+i); //2
            z.push_back(j*1.0+1+i);//3
            // x.push_back(j*1.0);

            y.push_back((i+1)*0.0);
            y.push_back((i+1)*1.0);
            y.push_back((i+1)*0.0);
            y.push_back((i+1)*0.0);
            // y.push_back(0.0);

            x.push_back(0.0+i);
            x.push_back(1.0+i);
            x.push_back(2.0+i);
            x.push_back(2.0+i);

            p.push_back(0+3*j);
            p.push_back(1+3*j);
            p.push_back(2+3*j);

            p.push_back(0+3*j);
            p.push_back(1+3*j);
            p.push_back(3+3*j);

            p.push_back(0+3*j);
            p.push_back(3+3*j);
            p.push_back(2+3*j);

            p.push_back(3+3*j);
            p.push_back(1+3*j);
            p.push_back(2+3*j);
        }


        
        catalyst_node *c = new catalyst_node(x, y, z, p, i+1);
        ExecuteCatalyst(*c);
    }

    FinalizeCatalyst();
    MPI_Finalize();
}
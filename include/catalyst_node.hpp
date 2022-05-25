#ifndef catalyst_node_h
#define catalyst_node_h

#include <catalyst.h>
#include <conduit.hpp>
#include <conduit_cpp_to_c.hpp>
#include <vector>

class catalyst_node
{
private:
    conduit::Node data_node;

    // default value used for dimension size
    int nx = 3;
    int cycle = 0;
    double time = 0;

public:
    catalyst_node(std::vector<double> &x,
                  std::vector<double> &y,
                  std::vector<double> &z,
                  std::vector<int> &p,
                  int c);
    ~catalyst_node();
    conduit::Node *node() { return &data_node; }
    int* getCycle();
    double* getTime();
};

#endif
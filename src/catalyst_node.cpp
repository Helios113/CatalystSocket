#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <catalyst_node.hpp>



template <typename T>
static void _addField(conduit_node *node, const std::string &name, const char *association, T &field)
{
    conduit_node_set_path_char8_str(node, ("fields/" + name + "/association").c_str(), association);
    conduit_node_set_path_char8_str(node, ("fields/" + name + "/topology").c_str(), "mesh");
    conduit_node_set_path_external_float64_ptr(node, ("fields/" + name + "/values").c_str(),
                                               &field.front(), field.size());
}

template <typename T>
static void _addField(conduit_node *node, const std::string &name, const char *association,
                      T &fx, T &fy, T &fz)
{
    conduit_node_set_path_char8_str(node, ("fields/" + name + "/association").c_str(), association);
    conduit_node_set_path_char8_str(node, ("fields/" + name + "/topology").c_str(), "mesh");
    conduit_node_set_path_external_float64_ptr(node, ("fields/" + name + "/values/u").c_str(),
                                               &fx.front(), fx.size());
    conduit_node_set_path_external_float64_ptr(node, ("fields/" + name + "/values/v").c_str(),
                                               &fy.front(), fy.size());
    conduit_node_set_path_external_float64_ptr(node, ("fields/" + name + "/values/w").c_str(),
                                               &fz.front(), fz.size());
}

catalyst_node::catalyst_node(std::vector<double> &x,
                             std::vector<double> &y,
                             std::vector<double> &z,
                             std::vector<int> &p,
                             int c)
{

    // set the current cycle
    cycle = c;
    time = c/10.0;
    // HowTo: Construct a conduit node
    // Using a mesh blueprint from
    // https://llnl-conduit.readthedocs.io/en/latest/blueprint_mesh.html
    // set coordinate type to explicit coordinates
    // others available
    std::cout << "Before node"<<std::endl;
    data_node = conduit::Node();

    // Tell conduit we will use Cartesian coordinates
    data_node["coordsets/coords/type"]= "explicit";
    // and set the data
    // if all of this is not done the node will become invalid
    data_node["coordsets/coords/values/x"].set(&x.front(), x.size());
    data_node["coordsets/coords/values/y"].set(&y.front(), y.size());
    data_node["coordsets/coords/values/z"].set(&z.front(), z.size());
    // the second name is required but not set so one can use anything
    // this follows the structured pattern 
    // https://llnl-conduit.readthedocs.io/en/latest/blueprint_mesh.html#:~:text=optional%2C%20default%20%3D%20%7B0%2C0%2C0%7D)-,structured,-%3A%20An%20implicit%20topology
    data_node["topologies/mesh/type"]= "unstructured";
    data_node["topologies/mesh/coordset"]= "coords";
    data_node["topologies/mesh/elements/shape"]="tri";
    
    data_node["topologies/mesh/elements/connectivity"].set(&p.front(), p.size());

    data_node["fields/p/association"].set("vertex");
    data_node["fields/p/topology"].set("mesh");
    data_node["fields/p/values"].set(&p.front(), p.size());
    // 3 (0,0)-0 (1,0)-1 (2,1)-2
    // 021


    // add pressure to each element
    // _addField(data_node, "p", "vertex", p);
}

catalyst_node::~catalyst_node()
{
    // never gets used will cause issues.
    // data_node needs to be a pointer not an object
    // hence the & needs to be removed
    if((&data_node)->is_root())
    {
        delete &data_node;
    }
}
int* catalyst_node::getCycle()
{
    return &cycle;
}
double* catalyst_node::getTime()
{
    return &time;
}

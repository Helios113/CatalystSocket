
#include <sstream>
#include <iostream>
#include <vector>
#include <catalyst_socket.hpp>
#include <stdio.h>
void InitializeCatalyst(const std::string& scripts)
{
	// create a conduit node which will be passed to Catalyst
	// conduit_node *node = conduit_node_create();
	std::ostringstream str;
	str << "catalyst/scripts/sample";
	conduit::Node* tmp = new conduit::Node();
	(*tmp)["catalyst/scripts/sample"].set(scripts);
	catalyst_initialize(tmp);
	delete tmp;
// 	conduit_node_set_path_char8_str(node, str.str().c_str(), scripts.c_str());
// 	// call initialize with arguments
// 	catalyst_initialize(node);
// 	// destroy node
// 	conduit_node_destroy(node);
}

void ExecuteCatalyst(catalyst_node &obj)
{
	std::cout<<"In Execute"<<std::endl;
	// create a conduit node which will be passed to Catalyst
    conduit::Node* work_node = new conduit::Node();

	// set the cycle property of the node
	//std::cout<<*obj.getCycle()<<std::endl;
	(*work_node).set_path_int64("catalyst/state/cycle",*(obj.getCycle()));
	//(*work_node)["catalyst/state/timestep"]  = *obj.getCycle();
	// set the time property of the node
	(*work_node).set_path_float64("catalyst/state/time",*(obj.getTime()));
	// conduit_node_set_path_float64(node, "catalyst/state/time", obj.getTime());

	// set the type of the data

	(*work_node)["catalyst/channels/grid/type"] = "mesh";
	//conduit_node_set_path_char8_str(node, "catalyst/channels/grid/type", "mesh");

	// set the data in the node by giving it the filled node
	(*work_node)["catalyst/channels/grid/data"].set(*obj.node());
	//conduit_node_set_path_external_node(node, "catalyst/channels/grid/data", );
	(*work_node).print();
	// call catalyst and pass the populated conduit node
	// change the cpp node to a c node
	catalyst_execute(work_node);

	// destroy the populated node once catalyst is done
	// if I construct my nodes correctly I can skip this new creation
	// and directly pass the node to catalyst
	if(work_node->is_root())
    {
        delete work_node;
    }
	//conduit_node_destroy(node);
}

void FinalizeCatalyst()
{
	// same as ExecuteCatalyst
	conduit::Node* tmp = new conduit::Node();
	catalyst_finalize(tmp);
	delete tmp;
}
#include <string>
#include <ostream>
#include <iostream>
#include "Instance.h"

using std::cout;
using std::cerr;
using std::endl;

std::string convertIntToString(int val)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << val;
	string test = ss.str();
	return test;
}

int main(int argc, char *argv[]) {
//		int MAXDIST = 100;
//		int MAXCAPACITY = 10;

	   Ptr<Instance::Manager> manager = shippingInstanceManager();

	    if (manager == NULL) {
	        cerr << "Unexpected NULL manager." << endl;
	        return 1;
	    }

	    Ptr<Instance> stats = manager->instanceNew("myStats", "Stats");
	    stats = manager->instanceNew("myStats2", "Stats");

	    if (stats == NULL) {
	        cerr << "Unexpected NULL stats." << endl;
	        return 1;
	    }

	    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");

	    if (fleet == NULL) {
	        cerr << "Unexpected NULL." << endl;
	        return 1;
	    }

	    fleet->attributeIs("Truck,speed,Day", "20.0");
	    fleet->attributeIs("Truck,capacity,Day", "50");
	    fleet->attributeIs("Truck,cost,Day", "20.0");

	    fleet->attributeIs("Plane,speed,Day", "200.0");
	    fleet->attributeIs("Plane,capacity,Day", "500");
	    fleet->attributeIs("Plane,cost,Day", "200.0");

//	    fleet->attributeIs("Truck,speed,Night", "60.0");
//	    fleet->attributeIs("Truck,capacity,Night", "20");
//
//	    fleet->attributeIs("Daytime", "10.0,18.0");

	    //2 customers - 2 terminals
	    Ptr<Instance> customer1 = manager->instanceNew("customer1", "Customer");
	    Ptr<Instance> customer2 = manager->instanceNew("customer2", "Customer");
	    Ptr<Instance> terminal1 = manager->instanceNew("terminal1", "Truck terminal");
	    Ptr<Instance> terminal2 = manager->instanceNew("terminal2", "Truck terminal");


	    Ptr<Instance> truckSeg[10];
	    for(int i=0; i<10; i++){
	    	if(i<2){
	    		string segname = "segment" + convertIntToString(i);
	    		truckSeg[i] = manager->instanceNew(segname, "Plane segment");

	    		truckSeg[i]->attributeIs("Capacity", "2");
	    		truckSeg[i]->attributeIs("length", "100");

	    		continue;
	    	}

	    	string segname = "segment" + convertIntToString(i);
	    	truckSeg[i] = manager->instanceNew(segname, "Truck segment");

	    	truckSeg[i]->attributeIs("Capacity", "2");
	    	truckSeg[i]->attributeIs("length", "100");
	    }

	    //customer1 - terminal1
	    truckSeg[0]->attributeIs("source", "customer1");
	    truckSeg[1]->attributeIs("source", "terminal1");
	    truckSeg[0]->attributeIs("return segment", "segment1");

	    //customer1 - terminal2
	    truckSeg[2]->attributeIs("source", "customer1");
	    truckSeg[3]->attributeIs("source", "terminal2");
	    truckSeg[2]->attributeIs("return segment", "segment3");

	    //customer2 - terminal1
	    truckSeg[4]->attributeIs("source", "customer2");
	    truckSeg[5]->attributeIs("source", "terminal1");
	    truckSeg[4]->attributeIs("return segment", "segment5");

	    //customer2 - terminal2
	    truckSeg[6]->attributeIs("source", "customer2");
	    truckSeg[7]->attributeIs("source", "terminal2");
	    truckSeg[6]->attributeIs("return segment", "segment7");

	    //terminal1- terminal2
	    truckSeg[8]->attributeIs("source", "terminal1");
	    truckSeg[9]->attributeIs("source", "terminal2");
	    truckSeg[8]->attributeIs("return segment", "segment9");


	    Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");

	    if (conn == NULL) {
	        cerr << "Unexpected NULL conn." << endl;
	        return 1;
	    }

	    // -- Statistics queries
	    cout << "===== Stats attributes =====" << endl;
	    cout << " --- Segments --- " << endl;
	    cout << "# Truck segments : " << stats->attribute("Truck segment") << endl;
	    cout << "# Boat segments : " << stats->attribute("Boat segment") << endl;
	    cout << "# Plane segments : " << stats->attribute("Plane segment") << endl;
	    cout << "Expediting %     : " << stats->attribute("expedite percentage") << endl;
	    cout << " --- Terminals --- " << endl;
	    cout << "# Plane terminals: " << stats->attribute("Plane terminal") << endl;
	    cout << "# Boat terminals: " << stats->attribute("Boat terminal") << endl;
	    cout << "# Truck terminals: " << stats->attribute("Truck terminal") << endl;
	    cout << " --- Ports and customers --- " << endl;
	    cout << "# Ports          : " << stats->attribute("Port") << endl;
	    cout << "# Customers	  : " << stats->attribute("Customer") << endl;


	    conn->attributeIs("routing algorithm", "dijkstra");
	    conn->attributeIs("priority", "time");


	    Ptr<Instance> activityManager = manager->instanceNew("activityManager", "ActivityManager");

	    if(argc > 1){
	    	if(strcmp(argv[1], "-realtime") == 0){
	    		cout << "Running in Real time mode" << endl;
	    		activityManager = manager->instanceNew("activityManager", "RealTimeActivityManager");
	    	}
	    }

	    if (activityManager == NULL) {
	        cerr << "Unexpected NULL stats." << endl;
	        return 1;
	    }

	    customer1->attributeIs("Destination", "customer2");
	    customer1->attributeIs("Shipment Size", "100");
	    customer1->attributeIs("Transfer Rate", "20.0");
	    customer1->attributeIs("run", "yes");


	    activityManager->attributeIs("time", "100.0");
	    customer1->attributeIs("Transfer Rate", "0");

	    activityManager->attributeIs("time", "150.0");

	    //Status values
	    cout << "*************\n Statistics \n***************" << endl;
	    cout << "Destination : Shipments Received : " << customer2->attribute("Shipments Received") << endl;
	    cout << "Destination : Average Latency : " << customer2->attribute("Average Latency") << endl;
	    cout << "Destination : Total Cost : " << customer2->attribute("Total Cost") << endl;

	    cout << "Segment : Shipments Received : " << truckSeg[5]->attribute("Shipments Received") << endl;
	    cout << "Segment : Shipments Refused : " << truckSeg[5]->attribute("Shipments Refused") << endl;

	    cout << "All Segments : Total Shipments Received : " << stats->attribute("Total Shipments Received") << endl;
	    cout << "All Segments : Total Shipments Refused : " << stats->attribute("Total Shipments Refused") << endl;
	    cout << "All Segments : Avg Shipments Received : " << stats->attribute("Average Shipments Received") << endl;
	    cout << "All Segments : Avg Shipments Refused: " << stats->attribute("Average Shipments Refused") << endl;

	    cout << "Done!" << endl;
	    return 0;
}

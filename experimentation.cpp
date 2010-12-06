#include <string>
#include <ostream>
#include <iostream>
#include "Instance.h"

using std::cout;
using std::cerr;
using std::endl;

static void badInstanceManager();
static void badTruckTerminal();
static void badTruckSegment();

std::string convertIntToString(int val)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << val;
	string test = ss.str();
	return test;
}

int main(int argc, char *argv[]) {
	
	try
	{
		int MAXDIST = 10;
		int MAXCAPACITY = 10;

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

	    fleet->attributeIs("Truck,speed,Night", "60.0");
	    fleet->attributeIs("Truck,capacity,Night", "20");

	    fleet->attributeIs("Daytime", "10.0,18.0");

	    //100 sources
	    Ptr<Instance> source[100];
	    string custom = "source";
	    for(int i=0; i<100; i++){
	    	string sourcename = custom + convertIntToString(i);
	    	source[i] = manager->instanceNew(sourcename, "Customer");

	    	//shipments
//	    	if(i == 1){
//	    		source[i]->attributeIs("Destination", "destination");
//	    		source[i]->attributeIs("Shipment Size", "100");
//	    		source[i]->attributeIs("Transfer Rate", "2.0");
//	    		source[i]->attributeIs("run", "yes");
//	    	}
	    }

	    //Destination
	    Ptr<Instance> destination = manager->instanceNew("destination", "Customer");

	    //Truck routes
	    custom = "truckSeg";
	    for (int i=0; i<100; i++){
	    	string truckSegName1 = custom + "1" +  convertIntToString(i);
	    	string truckSegName2 = custom + "2" + convertIntToString(i);
	    	string sourcename = "source" + convertIntToString(i);
	    	Ptr<Instance> truckSeg1 = manager->instanceNew(truckSegName1, "Truck segment");
	    	Ptr<Instance> truckSeg2 = manager->instanceNew(truckSegName2, "Truck segment");
	    	truckSeg1->attributeIs("source", sourcename);
	    	truckSeg2->attributeIs("source", "destination");
	    	truckSeg1->attributeIs("return segment", truckSegName2);

	    	truckSeg1->attributeIs("length", convertIntToString(MAXDIST));
	    	truckSeg2->attributeIs("length", convertIntToString(MAXDIST));
	    	truckSeg1->attributeIs("Capacity", convertIntToString(MAXCAPACITY));
	    	truckSeg2->attributeIs("Capacity", convertIntToString(MAXCAPACITY));
	    }

	    //One Terminal
	    Ptr<Instance> terminalT = manager->instanceNew("terminalT", "Truck terminal");

	    //Connection to Destination
	    Ptr<Instance> truckSegDest1 = manager->instanceNew("truckSeg_Dest1", "Truck segment");
	    Ptr<Instance> truckSegDest2 = manager->instanceNew("truckSeg_Dest2", "Truck segment");
	    truckSegDest1->attributeIs("source", "terminalT");
	    truckSegDest2->attributeIs("source", "destination");
	    truckSegDest1->attributeIs("return segment", "truckSeg_Dest2");
	    truckSegDest1->attributeIs("length", convertIntToString(MAXDIST));
	    truckSegDest2->attributeIs("length", convertIntToString(MAXDIST));
    	truckSegDest1->attributeIs("Capacity", convertIntToString(MAXCAPACITY));
    	truckSegDest2->attributeIs("Capacity", convertIntToString(MAXCAPACITY));


	    //10 Terminals
	    Ptr<Instance> terminals[10];
	    Ptr<Instance> sourceRight[10];
	    custom = "terminal";
	    for(int i=0; i<10; i++){
	    	string sourcename = custom + convertIntToString(i);
	    	terminals[i] = manager->instanceNew(sourcename, "Truck terminal");

	    	/////
		    string custom = "sourceRight";
		    for(int j=0; j<10; j++){
		    	string sourcename = custom + convertIntToString(i) + "_" + convertIntToString(j);
		    	sourceRight[i] = manager->instanceNew(sourcename, "Customer");

		    	//shipments
			    sourceRight[i]->attributeIs("Destination", "destination");
			    sourceRight[i]->attributeIs("Shipment Size", "100");
			    sourceRight[i]->attributeIs("Transfer Rate", "2.0");
			    sourceRight[i]->attributeIs("run", "yes");
		    }

		    //Truck routes
		    custom = "truckSeg";
		    for (int j=0; j<10; j++){
		    	string truckSegName1 = custom + "1" +  convertIntToString(i) + "_" + convertIntToString(j);
		    	string truckSegName2 = custom + "2" + convertIntToString(i) + "_" + convertIntToString(j);
		    	string sourcenameRight = "sourceRight" + convertIntToString(i) + "_" + convertIntToString(j);
		    	Ptr<Instance> truckSeg1 = manager->instanceNew(truckSegName1, "Truck segment");
		    	Ptr<Instance> truckSeg2 = manager->instanceNew(truckSegName2, "Truck segment");
		    	truckSeg1->attributeIs("source", sourcename);
		    	truckSeg2->attributeIs("source", sourcenameRight);
		    	truckSeg1->attributeIs("return segment", truckSegName2);

		    	truckSeg1->attributeIs("length", convertIntToString(MAXDIST));
		    	truckSeg2->attributeIs("length", convertIntToString(MAXDIST));
		    	truckSeg1->attributeIs("Capacity", convertIntToString(MAXCAPACITY));
		    	truckSeg2->attributeIs("Capacity", convertIntToString(MAXCAPACITY));
		    }

	    	/////
	    }

	    //Truck routes
	    custom = "truckSegTerm";
	    for (int i=0; i<10; i++){
	    	string truckSegName1 = custom + "1" +  convertIntToString(i);
	    	string truckSegName2 = custom + "2" + convertIntToString(i);
	    	string sourcename = "terminal" + convertIntToString(i);
	    	Ptr<Instance> truckSeg1 = manager->instanceNew(truckSegName1, "Truck segment");
	    	Ptr<Instance> truckSeg2 = manager->instanceNew(truckSegName2, "Truck segment");
	    	truckSeg1->attributeIs("source", sourcename);
	    	truckSeg2->attributeIs("source", "terminalT");
	    	truckSeg1->attributeIs("return segment", truckSegName2);

	    	truckSeg1->attributeIs("length", convertIntToString(MAXDIST));
	    	truckSeg2->attributeIs("length", convertIntToString(MAXDIST));
	    	truckSeg1->attributeIs("Capacity", convertIntToString(MAXCAPACITY));
	    	truckSeg2->attributeIs("Capacity", convertIntToString(MAXCAPACITY));
	    }


	    Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");

	    if (conn == NULL) {
	        cerr << "Unexpected NULL conn." << endl;
	        return 1;
	    }

//	    cout << "**** explore source1 : distance 10000 ****" << endl;
//	    cout << conn->attribute("explore source1 : distance 10000") << endl;
//	    cout << endl;
//
//	    cout << "*** connect source1 : destination ****" << endl;
//	    cout << conn->attribute("connect source1 : destination") << endl;
//	    cout << endl;

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

	    Ptr<Instance> activityManager = manager->instanceNew("activityManager", "ActivityManager");

	    if (activityManager == NULL) {
	        cerr << "Unexpected NULL stats." << endl;
	        return 1;
	    }

//	    sourceRight[0]->attributeIs("Destination", "destination");
//	    sourceRight[0]->attributeIs("Shipment Size", "100");
//	    sourceRight[0]->attributeIs("Transfer Rate", "2.0");
//	    sourceRight[0]->attributeIs("run", "yes");


	    activityManager->attributeIs("time", "100.0");
//	    activityManager->attributeIs("time", "250.0");

	    //Status values
	    cout << "*************\n Shipment Statistics \n***************" << endl;
	    cout << "Destination : Shipments Received : " << destination->attribute("Shipments Received") << endl;
	    cout << "Destination : Average Latency : " << destination->attribute("Average Latency") << endl;
	    cout << "Destination : Total Cost : " << destination->attribute("Total Cost") << endl;

	    cout << "Segment : Shipments Received : " << truckSegDest1->attribute("Shipments Received") << endl;
	    cout << "Segment : Shipments Refused : " << truckSegDest1->attribute("Shipments Refused") << endl;

	    cout << "All Segments : Total Shipments Received : " << stats->attribute("Total Shipments Received") << endl;
	    cout << "All Segments : Total Shipments Refused : " << stats->attribute("Total Shipments Refused") << endl;
	    cout << "All Segments : Avg Shipments Received : " << stats->attribute("Average Shipments Received") << endl;
	    cout << "All Segments : Avg Shipments Refused: " << stats->attribute("Average Shipments Refused") << endl;

	    cout << "Done!" << endl;
	    return 0;
	}
	catch(Fwk::Exception e)
	{
		cout << e.what() << endl;
	}
	catch(...)
	{
	}
}


//static void badInstanceManager() {
//    cerr << "Unexpected Null pointer from shippingInstanceManager" << endl;
//}
//
//static void badTruckTerminal() {
//    cerr << "Unable to create terminal1" << endl;
//}
//
//static void badTruckSegment() {
//    cerr << "You need to update the "
//        "instanceNew() function to create all types " << endl <<
//        "of nodes and interfaces." << endl;
//}

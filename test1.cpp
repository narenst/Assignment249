#include <string>
#include <ostream>
#include <iostream>
#include "Instance.h"

using std::cout;
using std::cerr;
using std::endl;
//sdhkdshf
static void badInstanceManager();
static void badTruckTerminal();
static void badTruckSegment();

int main(int argc, char *argv[]) {
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

	    fleet->attributeIs("Boat, speed", "60");
	    fleet->attributeIs("Truck, capacity", "50");
	    fleet->attributeIs("Plane, cost", "20");
	    cout << "fleet->attribute('Boat, speed'): " << fleet->attribute("Boat, speed") << endl;

	    // --- Create instances
	    // -- Locations
	    // customers
	    Ptr<Instance> customer1 = manager->instanceNew("customer1", "Customer");
	    Ptr<Instance> customer2 = manager->instanceNew("customer2", "Customer");
	    // ports
	    Ptr<Instance> port1 = manager->instanceNew("port1", "Port");

	    Ptr<Instance> planeTerminal1 = manager->instanceNew("planeTerminal1", "Plane terminal");
		Ptr<Instance> planeTerminal2 = manager->instanceNew("planeTerminal2", "Plane terminal");

	    if (customer1 == NULL || customer2 == NULL || port1 == NULL) {
	        cerr << "Unexpected NULL customer or port." << endl;
		return 1;
	    }

	    // -- Segments
	    // boat
	    Ptr<Instance> boatSeg1 = manager->instanceNew("boatSeg1", "Boat segment");
	    Ptr<Instance> boatSeg2 = manager->instanceNew("boatSeg2", "Boat segment");

//	    boatSeg2 = manager->instanceNew("boatSeg2", "Boat segment");

	    // truck
	    Ptr<Instance> truckSeg1 = manager->instanceNew("truckSeg1", "Truck segment");
	    Ptr<Instance> truckSeg2 = manager->instanceNew("truckSeg2", "Truck segment");

	    Ptr<Instance> planeSeg1 = manager->instanceNew("planeSeg1", "Plane segment");
		Ptr<Instance> planeSeg2 = manager->instanceNew("planeSeg2", "Plane segment");
		Ptr<Instance> planeSeg3 = manager->instanceNew("planeSeg3", "Plane segment");
		Ptr<Instance> planeSeg4 = manager->instanceNew("planeSeg4", "Plane segment");
		Ptr<Instance> planeSeg5 = manager->instanceNew("planeSeg5", "Plane segment");
		Ptr<Instance> planeSeg6 = manager->instanceNew("planeSeg6", "Plane segment");
		Ptr<Instance> planeSeg7 = manager->instanceNew("planeSeg7", "Plane segment");

	    if (boatSeg1 == NULL || boatSeg2 == NULL || truckSeg1 == NULL || truckSeg2 == NULL) {
	        cerr << "Unexpected NULL segment." << endl;
	        return 1;
	    }

	    // connections
	    // customer1 <---> port1
	    truckSeg1->attributeIs("source", "customer1");
	    truckSeg2->attributeIs("source", "port1");
	    truckSeg1->attributeIs("return segment", "truckSeg2");
	    cout << "truckSeg1->attribute('source'): " << truckSeg1->attribute("source") << endl;

	    // customer2 <---> port1
	    boatSeg1->attributeIs("source", "customer2");
	    boatSeg2->attributeIs("source", "port1");
	    boatSeg1->attributeIs("return segment", "boatSeg2");
	    cout << "boatSeg1->attribute('return segment'): " << boatSeg1->attribute("return segment") << endl;

//	    boatSeg1->attributeIs("source", "");

//	    //port1 <-> planeTerminal1
//	    planeSeg1->attributeIs("source", "port1");
//		planeSeg2->attributeIs("source", "planeTerminal1");
//		planeSeg1->attributeIs("return segment", "planeSeg2");
//
//	    //customer2 <-> planeTerminal2
//	    planeSeg3->attributeIs("source", "customer2"); //planeTerminal1 customer2
//		planeSeg4->attributeIs("source", "planeTerminal2");
//		planeSeg3->attributeIs("return segment", "planeSeg4");
//
//	    //planeTerminal1 <-> planeTerminal2
//	    planeSeg5->attributeIs("source", "planeTerminal1");
//		planeSeg6->attributeIs("source", "planeTerminal2");
//		planeSeg5->attributeIs("return segment", "planeSeg6");
//		planeSeg6->attributeIs("return segment", "planeSeg5");

	    	    //port1 <-> planeTerminal1
	    	    planeSeg1->attributeIs("source", "port1");
	    		planeSeg2->attributeIs("source", "planeTerminal1");
	    		planeSeg1->attributeIs("return segment", "planeSeg2");

	    	    //customer1 <-> planeTerminal1
	    	    planeSeg3->attributeIs("source", "customer1"); //planeTerminal1 customer2
	    		planeSeg4->attributeIs("source", "planeTerminal1");
	    		planeSeg3->attributeIs("return segment", "planeSeg4");

	    	    //customer2  <-> planeTerminal1
	    	    planeSeg5->attributeIs("source", "planeTerminal1");
	    		planeSeg6->attributeIs("source", "customer2");
	    		planeSeg7->attributeIs("source", "customer2");
	    		planeSeg5->attributeIs("return segment", "planeSeg6");
//	    		planeSeg6->attributeIs("return segment", "planeSeg5");
	    		cout << "customer2->attribute('segment1'): " << customer2->attribute("segment1") << endl;
	    		cout << "customer2->attribute('segment2'): " << customer2->attribute("segment2") << endl;
	    		cout << "customer2->attribute('segment3'): " << customer2->attribute("segment3") << endl;
	    		planeSeg6->attributeIs("source", "");
	    		cout << "customer2->attribute('segment1'): " << customer2->attribute("segment1") << endl;
	    		cout << "customer2->attribute('segment2'): " << customer2->attribute("segment2") << endl;
	    		cout << "customer2->attribute('segment3'): " << customer2->attribute("segment3") << endl;

	    // -- Segment lengths
	    boatSeg1->attributeIs("length", "400");
	    boatSeg2->attributeIs("length", "400");
	    truckSeg1->attributeIs("length", "900");
	    truckSeg2->attributeIs("length", "900");

	    // -- Segment difficulties
	    boatSeg1->attributeIs("difficulty", "1");
	    boatSeg2->attributeIs("difficulty", "1");
	    truckSeg1->attributeIs("difficulty", "1");
	    truckSeg2->attributeIs("difficulty", "1");

	    // -- Segment expedite support
	    boatSeg1->attributeIs("expedite support", "yes");
	    boatSeg2->attributeIs("expedite support", "yes");
	    truckSeg1->attributeIs("expedite support", "yes");
	    truckSeg2->attributeIs("expedite support", "yes");
	    planeSeg1->attributeIs("expedite support", "yes");
//	    planeSeg2->attributeIs("expedite support", "yes");

	    // -- Connectivity queries
	    Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");

	    if (conn == NULL) {
	        cerr << "Unexpected NULL conn." << endl;
	        return 1;
	    }

	    cout << "**** explore customer1 : distance 1500 ****" << endl;
	    cout << conn->attribute("explore customer1 : distance 2500 cost 3000 ") << endl;
	    cout << endl;

	    cout << "*** connect customer2 : customer1 ****" << endl;
	    cout << conn->attribute("connect customer2 : customer1") << endl;
	    cout << endl;

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


	    Ptr<Instance> activity = manager->instanceNew("myActivity", "Activity");

	    if (activity == NULL) {
	        cerr << "Unexpected NULL stats." << endl;
	        return 1;
	    }

	    activity->attributeIs("customer1", "customer2");


	    //  RealTimeManager::Ptr realTimeManager = realTimeManagerInstance();
	    //  realTimeManager->realTimePassedIs(6.0);

	    // Stop injection activity from the first two customers
//	    loc[0]->attributeIs("Transfer Rate", "0");
//	    loc[1]->attributeIs("Transfer Rate", "0");

//	    activityManager->nowIs(24.0);
	    //  realTimeManager->realTimePassedIs(18.0);

//	    printSimStats();



	    cout << "Done!" << endl;
	    return 0;

/*
    Ptr<Instance::Manager> manager = shippingInstanceManager();

    if (manager == NULL) {
        badInstanceManager();
        return 1;
    }


    Ptr<Instance> a = manager->instanceNew("terminal1", "Truck terminal");
    Ptr<Instance> a1 = manager->instanceNew("terminal2", "Truck terminal");

    if (a == NULL) {
        badTruckTerminal();
        return 1;
    }

    Ptr<Instance> b = manager->instanceNew("seg1", "Truck segment");
    Ptr<Instance> c = manager->instanceNew("seg2", "Truck segment");

    if (b == NULL || c == NULL) {
        badTruckSegment();
        return 1;
    }

    b->attributeIs("source", "terminal1");
    c->attributeIs("source", "terminal1");

    b->attributeIs("length", "100.1");
    b->attributeIs("difficulty", "3.1");
    b->attributeIs("expedite support", "yes");
    b->attributeIs("return segment", "seg2");

//  cout << a->attribute("segment2") << endl;

    cout << "\n\n";
    cout << b->attribute("source") << endl;
    cout << b->attribute("length") << endl;
    cout << b->attribute("difficulty") << endl;
    cout << b->attribute("expedite support") << endl;
    cout << b->attribute("return segment") << endl;
    cout << c->attribute("return segment") << endl;

    cout << "\nNow A\n";
    cout << a->attribute("segment1") << endl;
    cout << a->attribute("segment2") << endl;

//    cout << "\n Delete Tests\n" ;
//    b->attributeIs("source", "");

    Ptr<Instance> stats = manager->instanceNew("stats", "Stats");
    cout << "\n Stats Tests\n" ;
    cout << stats->attribute("Truck terminal") << endl;
    cout << stats->attribute("Truck segment") << endl;
    cout << stats->attribute("Boat terminal") << endl;
    cout << stats->attribute("Boat segment") << endl;
    cout << stats->attribute("Plane terminal") << endl;
	cout << stats->attribute("Plane segment") << endl;
	cout << stats->attribute("Port") << endl;
	cout << stats->attribute("Customer") << endl;
	cout << stats->attribute("expedite percentage") << endl;

	Ptr<Instance> fleet = manager->instanceNew("fleet", "Fleet");
	fleet->attributeIs("Truck, speed", "10.1");
	fleet->attributeIs("Truck, cost", "100.12");
	fleet->attributeIs("Truck, capacity", "200");

	fleet->attributeIs("Boat, speed", "20.1");
	fleet->attributeIs("Boat, cost", "200.12");
	fleet->attributeIs("Boat, capacity", "400");

	fleet->attributeIs("Plane, speed", "40.1");
	fleet->attributeIs("Plane, cost", "400.12");
	fleet->attributeIs("Plane, capacity", "800");

	Ptr<Instance> conn = manager->instanceNew("conn", "Conn");
	cout << "explore terminal1 : distance 1500" << endl;
	cout << conn->attribute("explore terminal1 : distance 1000") << endl;
	cout << "explore terminal1 : terminal2" << endl;
	cout << conn->attribute("connect terminal1 : terminal2") << endl;

    cout << "Done!" << endl;

    return 0;
*/
}

static void badInstanceManager() {
    cerr << "Unexpected Null pointer from shippingInstanceManager" << endl;
}

static void badTruckTerminal() {
    cerr << "Unable to create terminal1" << endl;
}

static void badTruckSegment() {
    cerr << "You need to update the "
        "instanceNew() function to create all types " << endl <<
        "of nodes and interfaces." << endl;
}

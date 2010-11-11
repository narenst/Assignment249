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

//naren = master
//slave
//slave2

int main(int argc, char *argv[]) {
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
	conn->attribute("test a b c");

    cout << "Done!" << endl;

    return 0;
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

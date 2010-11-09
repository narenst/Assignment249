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
//    c->attributeIs("source", "terminal1");

    b->attributeIs("length", "100.1");
    b->attributeIs("difficulty", "3.1");
    b->attributeIs("expedite support", "yes");


//  cout << a->attribute("segment2") << endl;

    cout << "\n\n";
    cout << b->attribute("source") << endl;
    cout << b->attribute("length") << endl;
    cout << b->attribute("difficulty") << endl;
    cout << b->attribute("expedite support") << endl;

    cout << "Now A\n";
    cout << a->attribute("segment1") << endl;

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

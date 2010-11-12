#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include "Instance.h"
#include "Engine.h"
#include "singletons.h"

namespace Shipping {

using namespace std;

//
// Conversion fucntions
//
float convertToDouble(std::string const& s)
{
   std::istringstream i(s);
   float x;
   if (!(i >> x))
     return -1.0;
   else
	 return x;
}

float convertToInt(std::string const& s)
{
   std::istringstream i(s);
   int x;
   if (!(i >> x))
     return -1;
   else
	 return x;
}

std::string convertDoubleToString(double val)
{
	stringstream ss (stringstream::in | stringstream::out);
	if(round(val) == val)
		ss << val;
	else
		ss << setprecision(3) << val;

	string test = ss.str();
	return test;
}

std::string convertIntToString(int val)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << val;
	string test = ss.str();
	return test;
}

void Tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters = " ")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

//
// Instance Manager - Singleton class to manage all instances
//

class ManagerImpl : public Instance::Manager {
public:
    ManagerImpl();

    // Manager method
    Ptr<Instance> instanceNew(const string& name, const string& type);

    // Manager method
    Ptr<Instance> instance(const string& name);

    // Manager method
    void instanceDel(const string& name);

private:
    map<string,Ptr<Instance> > instance_;
    Ptr<Instance> statsRepinstance_;
    Ptr<Instance> connectivityRepinstance_;
    Ptr<Instance> fleetRepinstance_;
};

//
// Location Class is the super class for more specific classes like
// Terminal, Customer, Port
//

class LocationRep : public Instance {
protected:
	Location::Ptr location_;

public:

    LocationRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);

    Location::Ptr location(){ return location_; }

    void locationIs(Location::Ptr loc){ location_ = loc; }
private:
    Ptr<ManagerImpl> manager_;

    int segmentNumber(const string& name);

};

//
// Handler class for all segment instances
//

class SegmentRep : public Instance {
protected:
	Segment::Ptr segment_;

public:

    SegmentRep(const string& name, const string& mode, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    	segment_ = Segment::SegmentNew(Fwk::String(name));

    	if (mode == "Truck segment"){
    		segment_->modeIs(truck_);
    	}

    	if (mode == "Boat segment"){
    		segment_->modeIs(boat_);
    	}

    	if (mode == "Plane segment"){
    		segment_->modeIs(plane_);
    	}
    }

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);

    Segment::Ptr segment(){ return segment_; }

    void segmentIs(Segment::Ptr seg){ segment_ = seg; }
private:
    Ptr<ManagerImpl> manager_;

};

class StatsRep : public Instance {
public:
    StatsRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    	//segment_ = Segment::SegmentNew(Fwk::String(name));
    	//instance_ = this;
    }

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);

    //Segment::Ptr segment(){ return segment_; }

    //void segmentIs(Segment::Ptr seg){ segment_ = seg; }

private:
    Ptr<ManagerImpl> manager_;
	//Ptr<StatsRep> instance_;
};

//
// Connectivity handler
//

class ConnectivityRep : public Instance {
public:
    ConnectivityRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    	//segment_ = Segment::SegmentNew(Fwk::String(name));
    	instance_ = true;
    }

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);

    //Segment::Ptr segment(){ return segment_; }

    //void segmentIs(Segment::Ptr seg){ segment_ = seg; }

private:
    Ptr<ManagerImpl> manager_;
	bool instance_;
};

//
// Fleet handler

//
class FleetRep : public Instance {
public:
    FleetRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    	//segment_ = Segment::SegmentNew(Fwk::String(name));
    	instance_ = true;
    }

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);

    //Segment::Ptr segment(){ return segment_; }

    //void segmentIs(Segment::Ptr seg){ segment_ = seg; }

private:
    Ptr<ManagerImpl> manager_;
	bool instance_;
};

//
// 3 subclasses of Terminal - each terminal type
//
class TruckTerminalRep : public LocationRep {
public:

    TruckTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        // Nothing else to do.
    	Terminal::Ptr terminal = Terminal::TerminalNew(Fwk::String(name));
    	terminal->modeIs(truck_);
    	location_ = terminal;
    }
};

class BoatTerminalRep : public LocationRep {
public:

    BoatTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        // Nothing else to do.
    	Terminal::Ptr terminal = Terminal::TerminalNew(Fwk::String(name));
    	terminal->modeIs(boat_);
    	location_ = terminal;
    }

};

class PlaneTerminalRep : public LocationRep {
public:

    PlaneTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        // Nothing else to do.
    	Terminal::Ptr terminal = Terminal::TerminalNew(Fwk::String(name));
    	terminal->modeIs(plane_);
    	location_ = terminal;
    }

};

//
// Specific types for Customer and Port
//
class CustomerRep : public LocationRep {
public:

    CustomerRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        // Nothing else to do.
    	Customer::Ptr customer = Customer::CustomerNew(Fwk::String(name));
    	location_ = customer;
    }

};

class PortRep : public LocationRep {
public:

    PortRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        // Nothing else to do.
    	Port::Ptr port = Port::PortNew(Fwk::String(name));
    	location_ = port;
    }

};

ManagerImpl::ManagerImpl() {
}

//
// New instance creation. Handles singletons for some types. Checks for
// repeating instance names
//

Ptr<Instance> ManagerImpl::instanceNew(const string& name, const string& type) {

    if (type == "Stats"){
    	if(statsRepinstance_ != NULL)
    		return statsRepinstance_;

    	Ptr<StatsRep> t = new StatsRep(name, this);
		instance_[name] = t;
		statsRepinstance_ = t;
		return t;
    }

    if (type == "Fleet"){
    	if(fleetRepinstance_ != NULL)
    		return fleetRepinstance_;

		Ptr<FleetRep> t = new FleetRep(name, this);
		instance_[name] = t;
		fleetRepinstance_ = t;
		return t;
	}

    if (type == "Conn"){
    	if(connectivityRepinstance_!= NULL)
			return connectivityRepinstance_;

		Ptr<ConnectivityRep> t = new ConnectivityRep(name, this);
		instance_[name] = t;
		connectivityRepinstance_ = t;
		return t;
	}

	if(instance_[name] != NULL){
		cerr << "instance name already exists" << endl;
		return NULL;
	}

    if (type == "Truck segment" || type == "Boat segment" || type == "Plane segment"){
    	Ptr<SegmentRep> t = new SegmentRep(name, type, this);
		instance_[name] = t;
		return t;
    }

    if (type == "Truck terminal"){
		Ptr<TruckTerminalRep> t = new TruckTerminalRep(name, this);
		instance_[name] = t;
		return t;
	}

    if (type == "Boat terminal") {
        Ptr<BoatTerminalRep> t = new BoatTerminalRep(name, this);
		instance_[name] = t;
		return t;
    }

    if (type == "Plane terminal") {
		Ptr<PlaneTerminalRep> t = new PlaneTerminalRep(name, this);
		instance_[name] = t;
		return t;
	}

    if (type == "Port") {
		Ptr<PortRep> t = new PortRep(name, this);
		instance_[name] = t;
		return t;
	}

    if (type == "Customer") {
		Ptr<CustomerRep> t = new CustomerRep(name, this);
		instance_[name] = t;
		return t;
	}

    cerr << "invalid parameter - instanceNew" << endl;
    return NULL;
}

Ptr<Instance> ManagerImpl::instance(const string& name) {
    map<string,Ptr<Instance> >::const_iterator t = instance_.find(name);
    return t == instance_.end() ? NULL : (*t).second;
}

void ManagerImpl::instanceDel(const string& name) {
}


string LocationRep::attribute(const string& name) {
    int i = segmentNumber(name);
    if (i != 0) {
        //cout << "Tried to read interface " << i;
        //Location::SegmentIteratorConst segIter = location()->segmentIterConst();
        Segment::Ptr s = location()->segment(ordinaltypes::Index(i-1));
        if(s != NULL)
        	return s->name();
    }
//  cout << "invalid segment number" << endl;
  	cerr << "invalid attribute - LocationRep" << endl;
  	return "";
}


void LocationRep::attributeIs(const string& name, const string& v) {
    //nothing to do
	cout << "LocationRep attributeIs\n";
}

//
// Segment accessor / mutators
//
string SegmentRep::attribute(const string& name) {

	if(name == "source"){
		return segment_->source()->name();
	}

	if (name == "return segment"){
		return segment_->returnSegment()->name();
	}

	if (name == "difficulty"){
		return convertDoubleToString(segment_->difficulty().value());
	}

	if (name == "length"){
		return convertDoubleToString(segment_->length().value());
	}

	if (name == "expedite support"){
		if(segment_->expediteSupport().value())
			return "yes";
		else
			return "no";
	}

	cerr << "invalid attribute - SegmentRep" << endl;
    return "";
}


void SegmentRep::attributeIs(const string& name, const string& v) {
    //nothing to do
//	cout << "SegmentRep attributeIs\n";
	if(name == "source"){
		if (v==""){
			segment_->sourceIs(NULL);
			return;
		}
		if (manager_->instance(v) == NULL){
			cerr << "location does not exist";
			return;
		}
		Ptr<LocationRep> locationRep = dynamic_cast<LocationRep*>(manager_->instance(v).ptr());
		Location::Ptr location = locationRep->location();
		segment_->sourceIs(location.ptr());
		return;
	}

	if (name == "difficulty"){
		Difficulty d = Difficulty(convertToDouble(v));
		segment_->difficultyIs(d);
		return;
	}

	if (name == "length"){
		Mile m = Mile(convertToDouble(v));
		segment_->lengthIs(m);
		return;
	}

	if (name == "expedite support"){
		if(v == "yes")
			segment_->expediteSupportIs(ExpediteSupport(true));
		else
			segment_->expediteSupportIs(ExpediteSupport(false));

		return;
	}

	if (name == "return segment"){
		Ptr<SegmentRep> segmentRep = dynamic_cast<SegmentRep*>(manager_->instance(v).ptr());
		Segment::Ptr segment = segmentRep->segment();
		segment_->returnSegmentIs(segment.ptr());
		return;
	}

	cerr << "invalid attribute - SegmentRep";
}

//
// Stats accessor - No working mutators
//
string StatsRep::attribute(const string& name) {

    if (name == "Truck terminal"){
        return convertIntToString(Stats::instance()->numberTruckTerminal().value());
    }

    if (name == "Truck segment"){
//    	cout << "TRUCK SEGMENTS : " << Stats::instance()->numberTruckSegment().value() << endl;
        return convertIntToString(Stats::instance()->numberTruckSegment().value());
    }

    if (name == "Boat terminal") {
        return convertIntToString(Stats::instance()->numberBoatTerminal().value());
    }

    if (name == "Boat segment"){
		return convertIntToString(Stats::instance()->numberBoatSegment().value());
    }

    if (name == "Plane terminal") {
    	return convertIntToString(Stats::instance()->numberPlaneTerminal().value());
	}

    if (name == "Plane segment"){
		return convertIntToString(Stats::instance()->numberPlaneSegment().value());
    }

    if (name == "Port") {
    	return convertIntToString(Stats::instance()->numberPorts().value());
	}

    if (name == "Customer") {
    	return convertIntToString(Stats::instance()->numberCustomers().value());
	}

    if (name == "expedite percentage") {
//    	cout << "PERC " << Stats::instance()->percentExpediteShipping().value() << endl;
    	return convertDoubleToString(Stats::instance()->percentExpediteShipping().value());
	}

    cerr << "invalid attribute - StatsRep" << endl;
    return "";
}

void StatsRep::attributeIs(const string& name, const string& v) {
	//Nothing
}

//
// Connectivity accessor - No working mutators
//

void ConnectivityRep::attributeIs(const string& name, const string& v) {
	//Nothing
}

string ConnectivityRep::attribute(const string& name) {

	string delim = " ";
	vector <string> tokens;

	Tokenize(name, tokens, " ");
//
//	for(int i=0; i!=tokens.size(); i++){
//		cout << i << " : " << tokens[i] << endl;
//	}

	if(tokens[0] == "explore"){
		Ptr<LocationRep> locationRep = dynamic_cast<LocationRep*>(manager_->instance(tokens[1]).ptr());
		Location::Ptr loc1 = locationRep->location();
		Connectivity::instance()->sourceIs(loc1.ptr());

//		cout << "## source is : " << loc1.ptr()->name() << endl;

		for(int i=3; i<tokens.size(); i++){
			string attr = tokens[i];

			if(attr == "distance"){
				string val = tokens[++i];
//				cout << "## distance is (str): " << val << endl;
//				cout << "## distance is (double): " << convertToDouble(val) << endl;
				Connectivity::instance()->distanceIs(Mile(convertToDouble(val)));
			}

			if(attr == "cost"){
				string val = tokens[++i];
				Connectivity::instance()->costIs(Dollar(convertToDouble(val)));
			}

			if(attr == "time"){
				string val = tokens[++i];
				Connectivity::instance()->timeIs(Hour(convertToDouble(val)));
			}

			if(attr == "expedited"){
				Connectivity::instance()->expeditedIs(ExpediteSupport(true));
			}
		}

		Connectivity::instance()->typeIs(Connectivity::explore_);
		return Connectivity::instance()->path();
	}
	if(tokens[0] == "connect"){
		Ptr<LocationRep> locationRep = dynamic_cast<LocationRep*>(manager_->instance(tokens[1]).ptr());
		Location::Ptr loc1 = locationRep->location();
		Connectivity::instance()->sourceIs(loc1.ptr());

		locationRep = dynamic_cast<LocationRep*>(manager_->instance(tokens[3]).ptr());
		Location::Ptr loc2 = locationRep->location();
		Connectivity::instance()->destinationIs(loc2.ptr());

		Connectivity::instance()->typeIs(Connectivity::connect_);
		return Connectivity::instance()->path();
	}

	cerr << "invalid attribute - ConnectivityRep" << endl;
    return "";
}

//
// Fleet accessor / mutators
//

string FleetRep::attribute(const string& name) {
	//Nothing
	string delim = " ";
	vector <string> tokens;
	Tokenize(name, tokens, ", ");

	if(tokens[0] == "Truck"){
		Fleet::instance()->typeIs(truck_);
	}
	if(tokens[0] == "Boat"){
		Fleet::instance()->typeIs(boat_);
	}
	if(tokens[0] == "Plane"){
		Fleet::instance()->typeIs(plane_);
	}

	if(tokens[1] == "speed"){
		return convertDoubleToString(Fleet::instance()->type()->speed().value());
	}
	if(tokens[1] == "cost"){
		return convertDoubleToString(Fleet::instance()->type()->cost().value());
	}
	if(tokens[1] == "capacity"){
		return convertIntToString(Fleet::instance()->type()->capacity().value());
	}

	cerr << "invalid attribute - FleetRep" << endl;
	return "";
}

void FleetRep::attributeIs(const string& name, const string& v) {
	string delim = " ";
	vector <string> tokens;
	Tokenize(name, tokens, ", ");

	if(tokens[0] == "Truck"){
		Fleet::instance()->typeIs(truck_);
	}
	if(tokens[0] == "Boat"){
		Fleet::instance()->typeIs(boat_);
	}
	if(tokens[0] == "Plane"){
		Fleet::instance()->typeIs(plane_);
	}

	if(tokens[1] == "speed"){
		Fleet::instance()->type()->speedIs(MilePerHour(convertToDouble(v)));
		return;
	}
	if(tokens[1] == "cost"){
		Fleet::instance()->type()->costIs(Dollar(convertToDouble(v)));
		return;
	}
	if(tokens[1] == "capacity"){
		Fleet::instance()->type()->capacityIs(NumberOfEntities(convertToInt(v)));
		return;
	}

	cerr << "invalid attribute - FleetRep" << endl;
}

static const string segmentStr = "segment";
static const int segmentStrlen = segmentStr.length();

int LocationRep::segmentNumber(const string& name) {
    if (name.substr(0, segmentStrlen) == segmentStr) {
        const char* t = name.c_str() + segmentStrlen;
        return atoi(t);
    }
    return 0;
}


}

/*
 * This is the entry point for your library.
 * The client program will call this function to get a handle
 * on the Instance::Manager object, and from there will use
 * that object to interact with the middle layer (which will
 * in turn interact with the engine layer).
 */
Ptr<Instance::Manager> shippingInstanceManager() {
    return new Shipping::ManagerImpl();
}


#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include "Instance.h"
#include "Engine.h"
#include "singletons.h"

namespace Shipping {

using namespace std;

//
// Rep layer classes
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

std::string convertDoubleToString(double val)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << val;
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
};

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

Ptr<Instance> ManagerImpl::instanceNew(const string& name, const string& type) {
    if (type == "Truck terminal"){
        Ptr<TruckTerminalRep> t = new TruckTerminalRep(name, this);
        instance_[name] = t;
        return t;
    }

    if (type == "Truck segment" || type == "Boat segment" || type == "Plane segment"){
    	Ptr<SegmentRep> t = new SegmentRep(name, type, this);
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

    if (type == "Stats"){
    	Ptr<StatsRep> t = new StatsRep(name, this);
		instance_[name] = t;
		return t;
    }

    if (type == "Fleet"){
        	Ptr<FleetRep> t = new FleetRep(name, this);
    		instance_[name] = t;
    		return t;
	}

    if (type == "Conn"){
			Ptr<ConnectivityRep> t = new ConnectivityRep(name, this);
			instance_[name] = t;
			return t;
	}

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
        else
        	return "";
    }
    return "";
}


void LocationRep::attributeIs(const string& name, const string& v) {
    //nothing to do
	cout << "LocationRep attributeIs\n";
}

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
			return "true";
		else
			return "false";
	}

    return "";
}


void SegmentRep::attributeIs(const string& name, const string& v) {
    //nothing to do
	cout << "SegmentRep attributeIs\n";
	if(name == "source"){
		Ptr<LocationRep> locationRep = dynamic_cast<LocationRep*>(manager_->instance(v).ptr());
		Location::Ptr location = locationRep->location();
		segment_->sourceIs(location.ptr());
	}

	if (name == "difficulty"){
		Difficulty d = Difficulty(convertToDouble(v));
		segment_->difficultyIs(d);
	}

	if (name == "length"){
		Mile m = Mile(convertToDouble(v));
		segment_->lengthIs(m);
	}

	if (name == "expedite support"){
		if(v == "yes")
			segment_->expediteSupportIs(ExpediteSupport(true));
		else
			segment_->expediteSupportIs(ExpediteSupport(false));
	}

	if (name == "return segment"){
		Ptr<SegmentRep> segmentRep = dynamic_cast<SegmentRep*>(manager_->instance(v).ptr());
		Segment::Ptr segment = segmentRep->segment();
		segment_->returnSegmentIs(segment.ptr());
	}
}

string StatsRep::attribute(const string& name) {

    if (name == "Truck terminal"){
        return convertIntToString(Stats::instance()->numberTruckTerminal().value());
    }

    if (name == "Truck segment"){
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
    	cout << "PERC " << Stats::instance()->percentExpediteShipping().value() << endl;
    	return convertDoubleToString(Stats::instance()->percentExpediteShipping().value());
	}

    return "";
}

void StatsRep::attributeIs(const string& name, const string& v) {
	//Nothing
}

void ConnectivityRep::attributeIs(const string& name, const string& v) {
	//Nothing
}

string ConnectivityRep::attribute(const string& name) {

	string delim = " ";
	vector <string> tokens;

	Tokenize(name, tokens, " ");

//	for(int i=0; i!=tokens.size(); i++){
//		cout << i << " : " << tokens[i] << endl;
//	}


    return "";
}

string FleetRep::attribute(const string& name) {
	//Nothing
	return "";
}

void FleetRep::attributeIs(const string& name, const string& v) {
    if (name == "Truck, speed"){

    }
    if (name == "Truck, cost"){

    }
    if (name == "Truck, capacity"){

    }
    if (name == "Boat, speed"){

    }
    if (name == "Boat, cost"){

    }
    if (name == "Boat, capacity"){

    }
    if (name == "Plane, speed"){

    }
    if (name == "Plane, cost"){

    }
    if (name == "Plane, capacity"){

    }
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


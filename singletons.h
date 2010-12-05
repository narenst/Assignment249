#ifndef SINGLETONS_H_
#define SINGLETONS_H_

#include "Location.h"
#include <map>
#include "Shipment.h"
/*
 * Stores the capacity cost and speed of a particular
 * type of fleet -> either truck, or plane or boat
 */
class FleetDetail {
public:
	void capacityIs(NumberOfEntities capacity) { capacity_ = capacity;}
	void costIs(Dollar cost) { cost_ = cost;}
	void speedIs(MilePerHour speed) { speed_ = speed; }
	
	NumberOfEntities capacity() { return capacity_;}
	Dollar cost() { return cost_;}
	MilePerHour speed() { return  speed_; }
	
	FleetDetail(): capacity_(1), cost_(1.0), speed_(1.0) {}
private:
	NumberOfEntities capacity_;
	Dollar cost_;
	MilePerHour speed_;
};


/*
 * Singleton class!
 * Stores object instances of FleetDetails which in turn contains
 * details of the different types of fleet
 */
class Fleet {
public:
    static Fleet* instance() {
		
	    if(! instanceFlag)
		{
			single = new Fleet();
			instanceFlag = true;
			return single;
		}
		else
		{
			return single;
		}	
		
	}
	
    ~Fleet()
    {
		instanceFlag = false;
    }
	
	void typeIs( Mode mode);
	
	FleetDetail* type() {
		return type_;
	}
	
	Fwk::String path() const {
		return path_;
	}
	
	
	
private:
	static bool instanceFlag;
    static Fleet *single;
	Fleet() {
	}
	Fwk::String path_;
	FleetDetail* type_;
	FleetDetail truckDetail_;
	FleetDetail planeDetail_;
	FleetDetail boatDetail_;
};

/*
 * Singleton class!
 * Stores general statistics about the simulation, including
 * number of entities of various types and also the percentage
 * of segments with expedite support..
 */
class Stats{
	
public:
    static Stats* instance() {
		
	    if(! instanceFlag)
		{
			single = new Stats();
			instanceFlag = true;
			return single;
		}
		else
		{
			return single;
		}	
		
	}
	
	void notifierIs(Terminal* l) {
		notifierIs(l);
	}
	
    ~Stats()
    {
		Stats::instanceFlag = false;
    }
	
	// Accessors
	PercentExpediteShipping percentExpediteShipping() { 
		return percentExpediteShipping_;
	}

	NumberOfEntities numberExpediteShippingSegments() {
		return numberExpediteShippingSegments_;
	}
		
	NumberOfEntities numberPorts(){
		return numberPorts_;
	}
	
	NumberOfEntities numberCustomers(){
		return numberCustomers_;
	}
	
	NumberOfEntities numberBoatTerminal(){
		return numberBoatTerminal_;
	}
	
	NumberOfEntities numberTruckTerminal(){
		return numberTruckTerminal_;
	}
	
	NumberOfEntities numberPlaneTerminal(){
		return numberPlaneTerminal_;
	}
	
	NumberOfEntities numberBoatSegment(){
		return numberBoatSegment_;
	}
	
	NumberOfEntities numberTruckSegment(){
		return numberTruckSegment_;
	}
	
	NumberOfEntities numberPlaneSegment(){
		return numberPlaneSegment_;
	}
	
	void percentExpediteShippingIs(PercentExpediteShipping p) { 
		percentExpediteShipping_ = p;
	}
	
	//Incrementors
	
	void numberExpediteShippingSegmentsInc(NumberOfEntities n) {
		numberExpediteShippingSegments_ = numberExpediteShippingSegments_ + n;
	}
	
	void numberPortsInc(NumberOfEntities n){
		numberPorts_ = numberPorts_ + n;
	}
	
	void numberCustomersInc(NumberOfEntities n){
		numberCustomers_ = numberCustomers_ + n;
	}
	
	void numberBoatTerminalInc(NumberOfEntities n){
		numberBoatTerminal_ = numberBoatTerminal_ + n;
	}
	
	void numberTruckTerminalInc(NumberOfEntities n){
		numberTruckTerminal_ = numberTruckTerminal_ + n;
	}
	
	void numberPlaneTerminalInc(NumberOfEntities n){
		numberPlaneTerminal_ = numberPlaneTerminal_ + n;
	}
	
	void numberBoatSegmentInc(NumberOfEntities n){
		numberBoatSegment_ = numberBoatSegment_ + n;
	}
	
	void numberTruckSegmentInc(NumberOfEntities n){
		numberTruckSegment_ = numberTruckSegment_ + n;
	}

	void numberPlaneSegmentInc(NumberOfEntities n){
		numberPlaneSegment_ = numberPlaneSegment_ + n;
	}

	//Decrementors
	
	void numberExpediteShippingSegmentsDec(NumberOfEntities n) {
		numberExpediteShippingSegments_ = numberExpediteShippingSegments_ - n;
	}
	
	void numberPortsDec(NumberOfEntities n){
		numberPorts_ = numberPorts_ - n;
	}
	
	void numberCustomersDec(NumberOfEntities n){
		numberCustomers_ = numberCustomers_ - n;
	}
	
	void numberBoatTerminalDec(NumberOfEntities n){
		numberBoatTerminal_ = numberBoatTerminal_ - n;
	}
	
	void numberTruckTerminalDec(NumberOfEntities n){
		numberTruckTerminal_ = numberTruckTerminal_ - n;
	}
	
	void numberPlaneTerminalDec(NumberOfEntities n){
		numberPlaneTerminal_ = numberPlaneTerminal_ - n;
	}
	
	void numberBoatSegmentDec(NumberOfEntities n){
		numberBoatSegment_ = numberBoatSegment_ - n;
	}
	
	void numberTruckSegmentDec(NumberOfEntities n){
		numberTruckSegment_ = numberTruckSegment_ - n;
	}
	
	void numberPlaneSegmentDec(NumberOfEntities n){
		numberPlaneSegment_ = numberPlaneSegment_ - n;
	}
	
private:
	
	static bool instanceFlag;
    static Stats *single;
	//private constructor

    Stats() :		
	percentExpediteShipping_(0.0),
	numberExpediteShippingSegments_(0),
	numberPorts_(0),
	numberCustomers_(0),
	numberBoatTerminal_(0),
	numberTruckTerminal_(0),
	numberPlaneTerminal_(0),
	numberBoatSegment_(0),
	numberTruckSegment_(0),
	numberPlaneSegment_(0) {
    }
	
	//These attributes are updated when new segments/ terminals are added
	PercentExpediteShipping percentExpediteShipping_;
	NumberOfEntities numberExpediteShippingSegments_;
	NumberOfEntities numberPorts_;
	NumberOfEntities numberCustomers_;
	NumberOfEntities numberBoatTerminal_;
	NumberOfEntities numberTruckTerminal_;
	NumberOfEntities numberPlaneTerminal_;
	NumberOfEntities numberBoatSegment_;
	NumberOfEntities numberTruckSegment_;
	NumberOfEntities numberPlaneSegment_;
};

/*
 * Singleton class!
 * Stores details of the connectivity query. The user of this interface
 * sets various attributes first and then runs the query to find the 
 * paths by just accessing the path() method.
 */
class Connectivity {
public:
	static Connectivity* instance() {
		
	    if(! instanceFlag)
		{
			single = new Connectivity();
			instanceFlag = true;
			return single;
		}
		else
		{
			return single;
		}	
		
	}
    ~Connectivity()
    {
		instanceFlag = false;
    }
	
	enum ConnectivityType {connect_ = 0, explore_ = 1};
	
	ConnectivityType type() const { return type_; }
	void typeIs(ConnectivityType t) { 
		type_ = t; 
		path_ = computePaths();
		distanceIs(0.0);
		costIs(0.0);
		timeIs(0.0);
		expeditedIs(false);
	}
	
	Fwk::String path() { return path_; }
	
	void sourceIs(Location* source) { source_ = source;}
	void destinationIs(Location* destination) { destination_ = destination;}
	void distanceIs(Mile distance) { distance_ = distance; }
	void costIs (Dollar cost) { cost_ = cost; }
	void timeIs (Hour time) { time_ = time; }
	void expeditedIs (ExpediteSupport expedited) { expedited_ = expedited; }
	
private:
	static bool instanceFlag;
    static Connectivity *single;
	Connectivity() : distance_(0.0),
					 cost_(0.0),
					 time_(0.0),
					 expedited_(false) {	
	}
	
	Fwk::String computePaths();
	Fwk::String path_;
	ConnectivityType type_;
	Location* source_;
	Location* destination_;
	Mile distance_;
	Dollar cost_;
	Hour time_;
	ExpediteSupport expedited_;
	
};


/*
 * Singleton class!
 * Helps in routing shipments through appropriate segments
 * 
 * 
 */
class Router {
public:
	static Router* instance() {
		
	    if(! instanceFlag)
		{
			single = new Router();
			instanceFlag = true;
			return single;
		}
		else
		{
			return single;
		}	
		
	}
    ~Router()
    {
		instanceFlag = false;
    }
	
	enum RoutingAlgorithm{ bfs_ = 0, dijkstra_ = 1 };
	
	
	RoutingAlgorithm routingAlgorithm() const { return ralgo_; }
	
	void routingAlgoritmIs(RoutingAlgorithm ralgo) { ralgo_ = ralgo; }
	
	void shipmentIs( Shipment::Ptr shipment) {
		
		computeLocationAndSegment(shipment);
		
	}
	
	Location::Ptr location() { return location_; }
	
	Segment::Ptr segment() { return segment_; }
	
	Hour time() { return time_; }
	
	Dollar cost() { return cost_; }	

	void locationIs(vector<Location::Ptr> l) {
		preprocess(l);
	}
	
	
private:
	static bool instanceFlag;
    static Router *single;
	Router() : time_(0.0), cost_(0.0){	
	}
	

    void preprocess(vector<Location::Ptr> l);
	
	bool connect(Location::Ptr, Location::Ptr, Fwk::String&, Fwk::String&);
	
	void computeLocationAndSegment(Shipment::Ptr);

	void segmentUpdateHelper( Shipment::Ptr, Location::Ptr currentLocation);
	
	RoutingAlgorithm ralgo_;
	
	Dollar cost_;
	Hour time_;
	Location::Ptr location_;
	Segment::Ptr segment_;
	
	map < Fwk::String, size_t > locationMap;
	vector<vector<bool> > connectivityBit;
	vector<vector<Fwk::String> > connectByTime;
	vector<vector<Fwk::String> > connectByCost;
	
	vector<Location::Ptr> localLocationList;
	enum nodeType {
		UNSEEN = 0,
		FRINGE = 1,
		INTREE = 2
	};
	
};

#endif /* SINGLETONS_H_ */

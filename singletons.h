#ifndef SINGLETONS_H_
#define SINGLETONS_H_

#include "Common.h"

class Location;

class FleetDetail: public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<FleetDetail const> PtrConst;
	typedef Fwk::Ptr<FleetDetail> Ptr;
	void capacityIs(NumberOfEntities capacity) { capacity_ = capacity;}
	void costIs(Dollar cost) { cost_ = cost;}
	void speedIs(MilePerHour speed) { speed_ = speed; }
	
	NumberOfEntities capacity() { return capacity_;}
	Dollar cost() { return cost_;}
	MilePerHour speed() { return  speed_; }
	
private:
	NumberOfEntities capacity_;
	Dollar cost_;
	MilePerHour speed_;
};

class Fleet {
public:
    static Fleet* instance() {
		
	    if(! instanceFlag)
		{
			Fleet::single = new Fleet();
			Fleet::instanceFlag = true;
			return Fleet::single;
		}
		else
		{
			return Fleet::single;
		}	
		
	}
	
    ~Fleet()
    {
		Fleet::instanceFlag = false;
    }
	
	void typeIs( Mode mode);
	FleetDetail::Ptr type() {
		return type_;
	}
	
	
private:
	static bool instanceFlag;
    static Fleet *single;
	Fleet() {
	}
	
	FleetDetail::Ptr type_;
	FleetDetail::Ptr truckDetail_;
	FleetDetail::Ptr planeDetail_;
	FleetDetail::Ptr boatDetail_;
};

class Stats {
	
public:
    static Stats* instance() {
		
	    if(! Stats::instanceFlag)
		{
			Stats::single = new Stats();
			Stats::instanceFlag = true;
			return Stats::single;
		}
		else
		{
			return Stats::single;
		}	
		
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
    Stats():
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
	
	//When EntityNew or EntityDel is executed, these attributes are updated.
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

class Connectivity {
public:
	static Connectivity* instance() {
		
	    if(! Connectivity::instanceFlag)
		{
			Connectivity::single = new Connectivity();
			Connectivity::instanceFlag = true;
			return Connectivity::single;
		}
		else
		{
			return Connectivity::single;
		}	
		
	}
    ~Connectivity()
    {
		Connectivity::instanceFlag = false;
    }
	
	enum ConnectivityType {connect_ = 0, explore_ = 1};
	
	ConnectivityType type() const { return type_; }
	void typeIs(ConnectivityType t) { 
		type_ = t; 
		computePaths();
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
	
	void computePaths();
	
	Fwk::String path_;
	ConnectivityType type_;
	Location* source_;
	Location* destination_;
	Mile distance_;
	Dollar cost_;
	Hour time_;
	ExpediteSupport expedited_;
	
};

#endif /* SINGLETONS_H_ */
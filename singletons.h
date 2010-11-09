

#ifndef SINGLETONS_H_
#define SINGLETONS_H_

#include "Common.h"
#include "Location.h"


class PercentExpediteShipping : public Ordinal<PercentExpediteShipping, double> {
public:
	PercentExpediteShipping(double val) : Ordinal<PercentExpediteShipping, double>(val) { }
};


class NumberOfEntities : public Ordinal<NumberOfEntities, unsigned int> {
public:
	NumberOfEntities(unsigned int val) : Ordinal<NumberOfEntities, unsigned int>(val) { }

	const NumberOfEntities& operator=(const Ordinal<NumberOfEntities,
												unsigned int>& v)
	{ this->value_ = v.value(); return *this; }
	
	Ordinal<NumberOfEntities, unsigned int> operator-(const Ordinal<NumberOfEntities,
										 unsigned int>& other)
	{ return (this->value_ - other.value()); }
	
};

class Stats {
	
public:
	
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
/*
class Connectivity {
	enum ConnectivityType {connect_ = 0, explore_ = 1} ;
	ConnectivityType type;

	
	const { return mode_; } 
	Connectivity(); 
	void typeIs(ConnectivityType type);
	void srcIs(Location::Ptr src);
	void destIs(Location dest);
	void distanceIs(float dist);
	void costIs (float cost);
	void timeIs (float time);
	void expeditedIs (bool expedited);
	
private:
	string computePaths(); //Compute the paths
	Location::Ptr src;
	Location::Ptr dest;
	float distance;
	float cost;
	float time;
	bool expedited;
	
};


enum {boat, truck, plane} vehicleType;  
class vehicle {
	float cost;
	float speed;
	float capacity;
	enum vehicleType vType;
};

class Fleet {
	//Rep layer will use this if it wants to know number of vehicles
	Fleet();
	//map<string, Vehicle> fleetTypes;
	//map<string,Vehicle> fleetTypes();
};

*/
#endif /* SINGLETONS_H_ */
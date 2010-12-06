#ifndef SHIPMENT_H_
#define SHIPMENT_H_

#include "Location.h"

/* 
 * Stores various details about each shipment including the number of packages
 * it has, the source and destination of the shipment.
 */
class Shipment : public Fwk::NamedInterface {
	
public:
	typedef Fwk::Ptr<Shipment const> PtrConst;
	typedef Fwk::Ptr<Shipment> Ptr;
	
	NumberOfEntities packages() const { return packages_; }
	void packagesIs(NumberOfEntities n) { packages_ = n; }
	
	Location::Ptr source() const { return source_; }
	void sourceIs(Location::Ptr source) { source_ = source; }
	
	Location::Ptr destination() const { return destination_; }
	void destinationIs(Location::Ptr destination) { destination_ = destination; }

    ~Shipment() {}
	
	static Shipment::Ptr ShipmentNew(Fwk::String s) {
		Ptr m = new Shipment(s);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}
	
protected:

	Fwk::String name_;
	Location::Ptr source_;
	Location::Ptr destination_;
	NumberOfEntities packages_;
	explicit Shipment(Fwk::String name): Fwk::NamedInterface(name), packages_(0) {
		name_ = name;
	}
	
};

#endif /* SHIPMENT_H_ */

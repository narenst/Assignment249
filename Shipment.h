#ifndef SHIPMENT_H_
#define SHIPMENT_H_

#include "Location.h"

class Shipment : public Fwk::NamedInterface {
	
public:
	typedef Fwk::Ptr<Shipment const> PtrConst;
	typedef Fwk::Ptr<Shipment> Ptr;
	
	NumberOfEntities packages() const { return packages_; }
	void packagesIs(NumberOfEntities n) { packages_ = n; }
	
	Location* source() const { return source_; }
	void sourceIs(Location* source) { source_ = source; }
	
	Location* destination() const { return destination_; }
	void destinationIs(Location* destination) { destination_ = destination; }


    ~Shipment();
	
	static Shipment::Ptr ShipmentNew() {
		Ptr m = new Shipment();
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}
	
protected:

	Location* source_;
	Location* destination_;
	NumberOfEntities packages_;
	explicit Shipment();
};

#endif /* SHIPMENT_H_ */

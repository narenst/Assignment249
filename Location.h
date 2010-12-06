#ifndef LOCATION_H_
#define LOCATION_H_

#include "Common.h"
#include "Segment.h"
#include <vector>

using namespace std;

/* 
 * This stores details of the location Including the list of segments
 * associated with it.
 */
class Location : public Fwk::NamedInterface {

public:
	typedef Fwk::Ptr<Location const> PtrConst;
	typedef Fwk::Ptr<Location> Ptr;

	typedef vector<Segment::Ptr> SegmentList;

	
	SegmentList segments() const {
		return segment_;
	}

	Segment::PtrConst segment(Index index) const {
		if(index >= segment_.size())
			return NULL;
		else {
			return segment_[index.value()];
		}
	}
	Segment::Ptr segment(Index index) {
		if(index >= segment_.size())
			return NULL;
		else {
			return segment_[index.value()];
		}
	}
	//Segments added one at a time. Incremental numbering done here.
	//(IsThroughPoint?)


	class Notifiee : public virtual Fwk::NamedInterface::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		Fwk::String name() const { return notifier_->name(); }

		bool isNonReferencing() const { return isNonReferencing_; }
		Location::PtrConst notifier() const { return notifier_; }
		Location::Ptr notifier() { return const_cast<Location *>(notifier_.ptr()); }

		// Non-const interface =============================================
		~Notifiee();
		Notifiee const * lrNext() const { return lrNext_; }
		Notifiee * lrNext() { return lrNext_; }
		virtual void notifierIs(const Location::PtrConst& _notifier);
		void isNonReferencingIs(bool _isNonReferencing);
		virtual void onSegmentNew( Segment::Ptr ) {}
		virtual void onSegmentDel( Fwk::String _name ) {}
		virtual void onSegmentDel( Segment::Ptr ) {}
		virtual void onLocationNew( Location::Ptr ) {}

		void lrNextIs(Notifiee * _lrNext) {
			lrNext_ = _lrNext;
		}
		static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
			m->referencesDec(1);
			// decr. refer count to compensate for initial val of 1
			return m;
		}
		// Constructors ====================================================
	protected:
		Notifiee * lrNext_;
		Location::PtrConst notifier_;
		bool isNonReferencing_;
		Notifiee(): Fwk::NamedInterface::Notifiee(), isNonReferencing_(false) {}
	};

	static Location::Ptr LocationNew(Fwk::String _name) {
		Location::Ptr m = new Location(_name);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}
	
	typedef Fwk::ListRaw<Notifiee> NotifieeList;

	typedef NotifieeList::IteratorConst NotifieeIteratorConst;
	NotifieeIteratorConst notifieeIterConst() const { return notifiee_.iterator(); }

	U32 notifiees() const { return notifiee_.members(); }

	typedef NotifieeList::Iterator NotifieeIterator;
	NotifieeIterator notifieeIter() { return notifiee_.iterator(); }

	// Non-const interface =============================================
    ~Location();
	void segmentDel(Fwk::String _name);
	Segment::Ptr segmentIs(Segment::Ptr segment);

protected:
	SegmentList segment_;
	
	void newNotifiee( Location::Notifiee * n ) const {
		Location* me = const_cast<Location*>(this);
		me->notifiee_.newMember(n);
	}
	void deleteNotifiee( Location::Notifiee * n ) const {
		Location* me = const_cast<Location*>(this);
		me->notifiee_.deleteMember(n);
	}
	NotifieeList notifiee_;
	explicit Location(Fwk::String _name);

};
class Customer : public Location {
public:
	typedef Fwk::Ptr<Customer const> PtrConst;
	typedef Fwk::Ptr<Customer> Ptr;

	NumberOfEntities shipmentsReceived() const { return shipmentsReceived_; }
	void shipmentsReceivedInc() { shipmentsReceived_ = shipmentsReceived_ + 1; }
	
	Hour averageLatency() const { return averageLatency_; }
	void averageLatencyIs( Hour averageLatency) { averageLatency_ = averageLatency; }
	
	Dollar totalCost() const { return totalCost_; }
	void totalCostIs( Dollar totalCost) { totalCost_ = totalCost; }
	
	class Notifiee : public virtual Location::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		
		Customer::PtrConst notifier() const { return  dynamic_cast<Customer const*>(Location::Notifiee::notifier().ptr()); }
		Customer::Ptr notifier() { return dynamic_cast<Customer *>(const_cast<Location *>(Location::Notifiee::notifier().ptr())); }
		
		// Non-const interface =============================================
		virtual void onCustomerNew( Customer* ){}
		static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
			m->referencesDec(1);
			// decr. refer count to compensate for initial val of 1
			return m;
		}
		// Constructors ====================================================
	protected:
		Notifiee(): Location::Notifiee() {}
	};

	static Customer::Ptr CustomerNew(Fwk::String _name) {
		Ptr m = new Customer(_name);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}

protected:
	NumberOfEntities shipmentsReceived_;
	Hour averageLatency_;
	Dollar totalCost_;
	explicit Customer(Fwk::String _name);
};

class Port : public Location{
public:
	typedef Fwk::Ptr<Port const> PtrConst;
	typedef Fwk::Ptr<Port> Ptr;
	//Any segment / mode is fine

	class Notifiee : public virtual Location::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		
		Port::PtrConst notifier() const { return  dynamic_cast<Port const*>(Location::Notifiee::notifier().ptr()); }
		Port::Ptr notifier() { return dynamic_cast<Port *>(const_cast<Location *>(Location::Notifiee::notifier().ptr())); }
		
		// Non-const interface =============================================
		virtual void onPortNew( Port* ){}
		static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
			m->referencesDec(1);
			// decr. refer count to compensate for initial val of 1
			return m;
		}
		// Constructors ====================================================
	protected:
		Notifiee(): Location::Notifiee() {}
	};
	static Port::Ptr PortNew(Fwk::String _name) {
		Ptr m = new Port(_name);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}
protected:
	explicit Port(Fwk::String _name);
};

class Terminal : public Location{
public:
	typedef Fwk::Ptr<Terminal const> PtrConst;
	typedef Fwk::Ptr<Terminal> Ptr;

	Mode mode () const { return mode_; }
	void modeIs(Mode);
	//Check segment mode matches
	
	class Notifiee : public virtual Location::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		
		Terminal::PtrConst notifier() const { return  dynamic_cast<Terminal const*>(Location::Notifiee::notifier().ptr()); }
		Terminal::Ptr notifier() { return dynamic_cast<Terminal *>(const_cast<Location *>(Location::Notifiee::notifier().ptr())); }
		
		// Non-const interface =============================================
		virtual void onTerminalNew( Terminal* ){}
		virtual void onMode( Mode, Mode){}
		static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
			m->referencesDec(1);
			// decr. refer count to compensate for initial val of 1
			return m;
		}
		// Constructors ====================================================
	protected:
		Notifiee(): Location::Notifiee() {}
	};
	
	static Terminal::Ptr TerminalNew(Fwk::String _name) {
		Ptr m = new Terminal(_name);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}
	

protected:
	Mode mode_;
	explicit Terminal(Fwk::String _name);
};


#endif /* LOCATION_H_ */

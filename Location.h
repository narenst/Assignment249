#ifndef LOCATION_H_
#define LOCATION_H_

#include "Common.h"
#include "Segment.h"

class Location : public Fwk::NamedInterface {

public:
	typedef Fwk::Ptr<Location const> PtrConst;
	typedef Fwk::Ptr<Location> Ptr;

	typedef Fwk::HashMap< Segment, Fwk::String, Segment, Segment::PtrConst, Segment::Ptr > SegmentMap;


	Segment::PtrConst segment(Fwk::String name) const {
		return segment_[name];
	}
	Segment::Ptr segment(Fwk::String name) {
		return segment_[name];
	}


	U32 segments() const { return segment_.members(); }
	U32 segmentVersion() const { return segment_.version(); }

	typedef SegmentMap::IteratorConst SegmentIteratorConst;
	SegmentIteratorConst segmentIterConst() const { return segment_.iterator(); }
	SegmentIteratorConst segmentIterConst( Fwk::String name ) const {
		return segment_.iterator( name ); }

	typedef SegmentMap::Iterator SegmentIterator;
	SegmentIterator segmentIter() { return segment_.iterator(); }
	SegmentIterator segmentIter( Fwk::String name ) {
		return segment_.iterator( name); }


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


	typedef Fwk::ListRaw<Notifiee> NotifieeList;

	typedef NotifieeList::IteratorConst NotifieeIteratorConst;
	NotifieeIteratorConst notifieeIterConst() const { return notifiee_.iterator(); }

	U32 notifiees() const { return notifiee_.members(); }

	typedef NotifieeList::Iterator NotifieeIterator;
	NotifieeIterator notifieeIter() { return notifiee_.iterator(); }

	// Non-const interface =============================================
    ~Location();
	Segment::Ptr segmentDel(Fwk::String _name);
	Segment::Ptr segmentIs(Segment::Ptr segment);

	static Location::Ptr LocationNew(Fwk::String _name) {
		Ptr m = new Location(_name);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}

protected:
	SegmentMap segment_;

	explicit Location(Fwk::String _name);
	void newNotifiee( Location::Notifiee * n ) const {
		Location* me = const_cast<Location*>(this);
		me->notifiee_.newMember(n);
	}
	void deleteNotifiee( Location::Notifiee * n ) const {
		Location* me = const_cast<Location*>(this);
		me->notifiee_.deleteMember(n);
	}
	NotifieeList notifiee_;

};
class Customer : public Location {
	typedef Fwk::Ptr<Customer const> PtrConst;
	typedef Fwk::Ptr<Customer> Ptr;
	//Any segment can be added
	//Is not a through point - chk when computing paths

	static Customer::Ptr CustomerNew(Fwk::String _name) {
		Ptr m = new Customer(_name);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}

protected:
	explicit Customer(Fwk::String _name);
};

class Port : public Location{
	typedef Fwk::Ptr<Port const> PtrConst;
	typedef Fwk::Ptr<Port> Ptr;
	//Any segment / mode is fine
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
	enum Mode {truck_ = 0, boat_ = 1, plane_ = 2} ;

	static inline Mode truck() { return truck_; }
	static inline Mode boat() { return boat_; }
	static inline Mode plane() { return plane_; }

	Mode mode () const { return mode_; }


	void modeIs(Mode);
	//Check segment mode matches
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

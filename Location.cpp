
#include "Location.h"
#include "singletons.h"


class CustomerReactor : public Customer::Notifiee {
public:
	void onSegmentNew(Segment::Ptr p) {
//		std::cout<< "Segment Attached";
	}
	
	void onCustomerNew(Customer* p) {
		Stats::instance()->numberCustomersInc(NumberOfEntities(1));
	}
    static CustomerReactor* CustomerReactorIs(Customer *s) {
		CustomerReactor *m = new CustomerReactor(s);
		return m;
    }
protected:
    CustomerReactor(Customer *t) : Customer::Notifiee() {
		notifierIs(t);
    }
	
};


class PortReactor : public Port::Notifiee {
public:
	void onSegmentNew(Segment::Ptr p) {
//		std::cout<< "Segment Attached";
	}
	
	void onPortNew(Port* p) {
		Stats::instance()->numberPortsInc(NumberOfEntities(1));
	}
    static PortReactor* PortReactorIs(Port *s) {
		PortReactor *m = new PortReactor(s);
		return m;
    }
protected:
    PortReactor(Port *t) : Port::Notifiee() {
		notifierIs(t);
    }
	
};

class TerminalReactor : public Terminal::Notifiee {
public:
	void onSegmentNew(Segment::Ptr p) {
//		std::cout<< "Segment Attached";

	}
	void onTerminalNew(Terminal* p) {
		incrementStat(p->mode());
	}
	void onMode(Mode old, Mode current) {
		decrementStat(old);
		incrementStat(current);
	}
	
    static TerminalReactor* TerminalReactorIs(Terminal *s) {
		TerminalReactor *m = new TerminalReactor(s);
		return m;
    }
	
private:
	void decrementStat(Mode m) {
		
		switch ( m.value() )  {
				
			case plane_:
				Stats::instance()->numberPlaneTerminalDec(NumberOfEntities(1));
				break;
			case boat_:
				Stats::instance()->numberBoatTerminalDec(NumberOfEntities(1));
				break;
			case truck_:
				Stats::instance()->numberTruckTerminalDec(NumberOfEntities(1));
				break;
				
		}
	}
	void incrementStat(Mode m) {
		switch ( m.value() )  {
				
			case plane_:
				Stats::instance()->numberPlaneTerminalInc(NumberOfEntities(1));
				break;
			case boat_:
				Stats::instance()->numberBoatTerminalInc(NumberOfEntities(1));
				break;
			case truck_:
				Stats::instance()->numberTruckTerminalInc(NumberOfEntities(1));
				break;
				
		}
	}
protected:
    TerminalReactor(Terminal *t) : Terminal::Notifiee() {
		notifierIs(t);
    }
	
};

//----------| NotifieeConst Implementation |------------//

Location::Notifiee::~Notifiee() {
	if(notifier_) {
		notifier_->deleteNotifiee(this);
	}
	if(notifier_&&isNonReferencing()) notifier_->newRef();
}



void Location::Notifiee::notifierIs(const Location::PtrConst& _notifier) {
	Location::Ptr notifierSave(const_cast<Location *>(notifier_.ptr()));
	if(_notifier==notifier_) return;
	notifier_ = _notifier;
	if(notifierSave) {
		notifierSave->deleteNotifiee(this);
	}
	if(_notifier) {
		_notifier->newNotifiee(this);
	}
	if(isNonReferencing_) {
		if(notifierSave) notifierSave->newRef();
		if(notifier_) notifier_->deleteRef();
	}
}

void
Location::Notifiee::isNonReferencingIs(bool _isNonReferencing){
	if(_isNonReferencing==isNonReferencing_) return;
	isNonReferencing_ = _isNonReferencing;
	if(notifier_) {
		if(_isNonReferencing) notifier_->deleteRef();
		else notifier_->newRef();
	}
}

//----------| Notifiee Implementation |------------//

Location::~Location() {
	SegmentList::iterator itr = segment_.begin();
	while(itr != segment_.end()) { 
		segmentDel((*itr)->name());
		itr = segment_.begin();
	}
}

void
Location::segmentDel(Fwk::String _name) {
	
	SegmentList::iterator itr = segment_.begin();
	while(itr != segment_.end()) { 
		if ((*itr)->name() == _name) {
			itr = segment_.erase(itr);
			break;
		}
		else 
			++itr;
	}
	if(itr == segment_.end()) return ;
retryDel:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		n->onSegmentDel(_name);
		if( ver != notifiee_.version() ) goto retryDel;
	} catch(...) { n->onNotificationException(); }
}

Segment::Ptr
Location::segmentIs(Segment::Ptr segment) {
	
	Fwk::String name = segment->name();
	
	SegmentList::iterator itr = segment_.begin();
	while(itr != segment_.end()) { 
		if ((*itr)->name() == segment->name()) {
			break;
		}
		else {
			itr++;
		}

	}
	if(itr != segment_.end()) {
		throw Fwk::NameInUseException(name);
	} else {
		segment_.push_back(segment);
	}
retryNew:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		n->onSegmentNew(segment);
		if( ver != notifiee_.version() ) goto retryNew;
	} catch(...) { n->onNotificationException(); }
	return segment;
}

Location::Location(Fwk::String _name): Fwk::NamedInterface(_name) {
	
	
retryNew:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		n->onLocationNew(this);
		if( ver != notifiee_.version() ) goto retryNew;
	} catch(...) { n->onNotificationException(); }
	

}

Customer::Customer(Fwk::String _name): Location::Location(_name) {

	CustomerReactor::CustomerReactorIs(this);
retryNew:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		
		dynamic_cast<Customer::Notifiee*>(n.ptr())->onCustomerNew(this);
		if( ver != notifiee_.version() ) goto retryNew;
	} catch(...) { n->onNotificationException(); }
	
}

Port::Port(Fwk::String _name): Location::Location(_name) {
	PortReactor::PortReactorIs(this);
retryNew:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		dynamic_cast<Port::Notifiee*>(n.ptr())->onPortNew(this);
		if( ver != notifiee_.version() ) goto retryNew;
	} catch(...) { n->onNotificationException(); }
	
}

Terminal::Terminal(Fwk::String _name): mode_(plane_) ,Location::Location(_name)  {
	TerminalReactor::TerminalReactorIs(this);
retryNew:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		dynamic_cast<Terminal::Notifiee*>(n.ptr())->onTerminalNew(this);
		if( ver != notifiee_.version() ) goto retryNew;
	} catch(...) { n->onNotificationException(); }
}

void Terminal::modeIs(Mode m){
	if (mode_ == m) return;
	Mode old = mode_;
	mode_ = m;
	
	retryNew:
		U32 ver = notifiee_.version();
		if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
			dynamic_cast<Terminal::Notifiee*>(n.ptr())->onMode(old, mode_);
			if( ver != notifiee_.version() ) goto retryNew;
		} catch(...) { n->onNotificationException(); }	
}





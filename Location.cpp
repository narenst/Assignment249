
#include "Location.h"

class Port::Notifiee;
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
	SegmentReactor::SegmentReactorIs(segment.ptr());
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

retryNew:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		
		dynamic_cast<Customer::Notifiee*>(n.ptr())->onCustomerNew(this);
		if( ver != notifiee_.version() ) goto retryNew;
	} catch(...) { n->onNotificationException(); }
	
}

Port::Port(Fwk::String _name): Location::Location(_name) {
	
retryNew:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		dynamic_cast<Port::Notifiee*>(n.ptr())->onPortNew(this);
		if( ver != notifiee_.version() ) goto retryNew;
	} catch(...) { n->onNotificationException(); }
	
}

Terminal::Terminal(Fwk::String _name): mode_(plane_) ,Location::Location(_name)  {

retryNew:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		dynamic_cast<Terminal::Notifiee*>(n.ptr())->onTerminalNew(this);
		if( ver != notifiee_.version() ) goto retryNew;
	} catch(...) { n->onNotificationException(); }
}

void Terminal::modeIs(Mode m){
	mode_ = m;
}





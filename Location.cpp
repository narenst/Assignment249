
#include "Location.h"


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
	SegmentIterator i = segmentIter();
	while(i.ptr())
	{
		segmentDel(i->name());
		i = segmentIter();
	}
}

Segment::Ptr
Location::segmentDel(Fwk::String _name) {
	Segment::Ptr m = segment_.deleteMember(_name);
	if(!m) return 0;
retryDel:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		n->onSegmentDel(_name);
		n->onSegmentDel(m);
		if( ver != notifiee_.version() ) goto retryDel;
	} catch(...) { n->onNotificationException(); }
	return m;
}

Segment::Ptr
Location::segmentIs(Segment::Ptr segment) {
	Fwk::String name = segment->fwkKey();
	Segment::Ptr m = segment_[name];
	if(m) {
		throw Fwk::NameInUseException(name);
	} else {
		m = segment;
		segment_.newMember(m);
	}
	SegmentReactor::SegmentReactorIs(m.ptr());
retryNew:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		n->onSegmentNew(segment);
		if( ver != notifiee_.version() ) goto retryNew;
	} catch(...) { n->onNotificationException(); }
	return segment;
}

Location::Location(Fwk::String _name): Fwk::NamedInterface(_name) {

}

Customer::Customer(Fwk::String _name): Location::Location(_name) {

}

Port::Port(Fwk::String _name): Location::Location(_name) {

}

Terminal::Terminal(Fwk::String _name): Location::Location(_name) {

}

void Terminal::modeIs(Terminal::Mode m){
	mode_ = m;
}

Fwk::String valueToStrep(Fwk::String s) { return s; }

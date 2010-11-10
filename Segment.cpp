
#include "Segment.h"
#include "Location.h"

//----------| NotifieeConst Implementation |------------//

Segment::Notifiee::~Notifiee() {
	if(notifier_) {
		notifier_->deleteNotifiee(this);
	}
	if(notifier_&&isNonReferencing()) notifier_->newRef();
}



void Segment::Notifiee::notifierIs(const Segment::PtrConst& _notifier) {
	Segment::Ptr notifierSave(const_cast<Segment *>(notifier_.ptr()));
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
Segment::Notifiee::isNonReferencingIs(bool _isNonReferencing){
	if(_isNonReferencing==isNonReferencing_) return;
	isNonReferencing_ = _isNonReferencing;
	if(notifier_) {
		if(_isNonReferencing) notifier_->deleteRef();
		else notifier_->newRef();
	}
}


void Segment::modeIs(Mode mode) {

	if(mode_ == mode) return;
	mode_ = mode;
retrytissue:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		n->onMode();
		if( ver != notifiee_.version() ) goto retrytissue;
	} catch(...) { n->onNotificationException(); }

}

void Segment::lengthIs(Mile length) {
	if(length_ == length) return;
	length_ = length;
retrytissue:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		n->onLength();
		if( ver != notifiee_.version() ) goto retrytissue;
	} catch(...) { n->onNotificationException(); }
}

void Segment::sourceIs(Location* source) {

	if(source_ == source) return;
	source_ = source;
	source_->segmentIs(Fwk::Ptr<Segment>(this));
retrytissue:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		n->onSource();
		if( ver != notifiee_.version() ) goto retrytissue;
	} catch(...) { n->onNotificationException(); }
}

void Segment::returnSegmentIs(Segment::Ptr returnSegment) {
	if(returnSegment_ == returnSegment) return;
	returnSegment_ = returnSegment;
	returnSegment_->returnSegmentIs(Fwk::Ptr<Segment>(this));
retrytissue:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		n->onReturnSegment();
		if( ver != notifiee_.version() ) goto retrytissue;
	} catch(...) { n->onNotificationException(); }
}

void Segment::difficultyIs(Difficulty difficulty) {

	if(difficulty_ == difficulty) return;
	difficulty_ = difficulty;
retrytissue:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		n->onDifficulty();
		if( ver != notifiee_.version() ) goto retrytissue;
	} catch(...) { n->onNotificationException(); }
}

void Segment::expediteSupportIs(ExpediteSupport expediteSupport) {

	if(expediteSupport_ == expediteSupport) return;
	expediteSupport_ = expediteSupport;
retrytissue:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		n->onExpediteSupport();
		if( ver != notifiee_.version() ) goto retrytissue;
	} catch(...) { n->onNotificationException(); }
}

Segment::~Segment() {

}

Segment::Segment(Fwk::String name): Fwk::NamedInterface(name), mode_(plane_), difficulty_(1.0), length_(1.0), expediteSupport_(false) {
	name_ = name;

}



#ifndef SEGMENT_H_
#define SEGMENT_H_
#include <queue>
#include "Common.h"

class Location;


/* 
 * Stores various details about each segment including the type , source, pointer to
 * return segment, length, difficulty and whether it has support for expedite delivery.
 */
class Segment : public Fwk::NamedInterface {

public:
	typedef Fwk::Ptr<Segment const> PtrConst;
	typedef Fwk::Ptr<Segment> Ptr;

	Fwk::String name() const { return name_; }

	Mode mode () const { return mode_; }
	void modeIs(Mode);

	Location* source() const { return source_; }
	void sourceIs(Location* source_);

	Mile length() const { return length_; }
	void lengthIs(Mile length);

	Ptr returnSegment() const { return returnSegment_; }
	void returnSegmentIs(Ptr segment_);

	NumberOfEntities capacity() const { return capacity_; }
	void capacityIs(NumberOfEntities capacity) { capacity_ = capacity; }

	NumberOfEntities shipmentsReceived() const { return shipmentsReceived_; }
	NumberOfEntities shipmentsRefused() const { return shipmentsRefused_; }
	void shipmentsRefusedInc() { 
		shipmentsRefused_ = shipmentsRefused_ + 1;
	}
	
	NumberOfEntities usage () const { return usage_; }
	void usageInc(Hour time_);
	void usageDec() {
		usage_ = usage_ - 1; 
		scheduledActivities_.pop();
	}
	
	Hour waitingTime() const{
		return scheduledActivities_.top();
	}
	
	Difficulty difficulty() const { return difficulty_; }
	void difficultyIs(Difficulty difficulty);

	ExpediteSupport expediteSupport() const { return expediteSupport_; }
	void expediteSupportIs(ExpediteSupport expediteSupport_);

	class Notifiee : public virtual Fwk::NamedInterface::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		Fwk::String name() const { return notifier_->name(); }

		bool isNonReferencing() const { return isNonReferencing_; }
		Segment::PtrConst notifier() const { return notifier_; }
		Segment::Ptr notifier() { return const_cast<Segment *>(notifier_.ptr()); }
		Notifiee const * lrNext() const { return lrNext_; }
		Notifiee * lrNext() { return lrNext_; }

		// Non-const interface =============================================
		~Notifiee();
		virtual void notifierIs(const Segment::PtrConst& _notifier);
		void isNonReferencingIs(bool _isNonReferencing);
		virtual void onSource() {}
		virtual void onLength() {}
		virtual void onDifficulty() {}
		virtual void onExpediteSupport(ExpediteSupport) {}
		virtual void onReturnSegment() {}
		virtual void onMode(Mode, Mode) {}
		virtual void onSegmentNew( Segment* ) {}

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
		Segment::PtrConst notifier_;
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
    ~Segment();

	static Segment::Ptr SegmentNew(Fwk::String _name) {
		Ptr m = new Segment(_name);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}
	

protected:
	priority_queue< Hour > scheduledActivities_;
	Mile length_;
	Location* source_;
	Mode mode_;
	Ptr returnSegment_;
	explicit Segment(Fwk::String name_);
	Difficulty difficulty_;
	ExpediteSupport expediteSupport_;
	NumberOfEntities capacity_;
	NumberOfEntities usage_;
	NumberOfEntities shipmentsReceived_;
	NumberOfEntities shipmentsRefused_;
	Fwk::String name_;

	mutable Segment::Ptr fwkHmNext_;

	void newNotifiee( Segment::Notifiee * n ) const {
		Segment* me = const_cast<Segment*>(this);
		me->notifiee_.newMember(n);
	}
	void deleteNotifiee( Segment::Notifiee * n ) const {
		Segment* me = const_cast<Segment*>(this);
		me->notifiee_.deleteMember(n);
	}
	NotifieeList notifiee_;
};

#endif /* SEGMENT_H_ */

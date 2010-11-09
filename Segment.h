

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "Common.h"
#include "Nominal.h"

class Location;

class Segment : public Fwk::NamedInterface {

public:
	typedef Fwk::Ptr<Segment const> PtrConst;
	typedef Fwk::Ptr<Segment> Ptr;

	Fwk::String name() const { return name_; }

	enum Mode {truck_ = 0, boat_ = 1, plane_ = 2} ;

	static inline Mode truck() { return truck_; }
	static inline Mode boat() { return boat_; }
	static inline Mode plane() { return plane_; }

	Mode mode () const { return mode_; }
	void modeIs(Mode);

	Location* source() const { return source_; }
	void sourceIs(Location* source_);

	Miles length() const { return length_; }
	void lengthIs(Miles length);

	Ptr returnSegment() const { return returnSegment_; }
	void returnSegmentIs(Ptr segment_);


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
		virtual void onExpediteSupport() {}
		virtual void onReturnSegment() {}
		virtual void onMode() {}

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
	Miles length_;
	Location* source_;
	Mode mode_;
	Ptr returnSegment_;
	explicit Segment(Fwk::String name_);
	Difficulty difficulty_;
	ExpediteSupport expediteSupport_;

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


class SegmentReactor : public Segment::Notifiee {
public:
	void onExpediteSupport() {
		std::cout<< "Expedited";
		
	}
    static SegmentReactor* SegmentReactorIs(Segment *s) {
		SegmentReactor *m = new SegmentReactor(s);
		return m;
    }
protected:
    SegmentReactor(Segment *t) : Segment::Notifiee() {
		notifierIs(t);
    }
};
#endif /* SEGMENT_H_ */

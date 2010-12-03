#include "ActivityReactor.h"
#include "../Instance.h"

static int num = 0;

TransportActivityReactor::TransportActivityReactor(Fwk::Ptr<Activity::Manager> manager,
		Activity* activity, double rate, Location::Ptr cust1, Location::Ptr cust2):
		Notifiee(activity), rate_(rate), activity_(activity), manager_(manager){
	source = cust1;
	dest = cust2;
	cur = source;
}

void TransportActivityReactor::onStatus() {
	//  Queue::Ptr q = NULL;

	ActivityImpl::ManagerImpl::Ptr managerImpl = Fwk::ptr_cast<ActivityImpl::ManagerImpl>(manager_);
	switch (activity_->status()) {

	case Activity::executing:
		//I am executing now
		num++;
		cout << "TransportActivityReactor : " << num << endl;
		//	q = managerImpl->queue();
		//	std::cout << activity_->name() <<" enqueueing number " << num << endl;
		//	q->enQ(num);
		//	num++;
		break;

	case Activity::free:
		//when done, automatically enqueue myself for next execution
		activity_->nextTimeIs(Time(activity_->nextTime().value() + rate_));
		activity_->statusIs(Activity::nextTimeScheduled);
		break;

	case Activity::nextTimeScheduled:
		//add myself to be scheduled
		manager_->lastActivityIs(activity_);
		break;

	default:
		break;
    }

}
/*
void ConsumerActivityReactor::onStatus() {
    Queue::Ptr q = NULL;
    int n = 0;
    ActivityImpl::ManagerImpl::Ptr managerImpl = Fwk::ptr_cast<ActivityImpl::ManagerImpl>(manager_);

    switch (activity_->status()) {
    case Activity::executing:
	//I am executing now
	q = managerImpl->queue();
	n = q->deQ();
	cout << activity_->name() << " dequeing number " << n << endl;
	break;
	
    case Activity::free:
	//When done, automatically enqueue myself for next execution
	activity_->nextTimeIs(Time(activity_->nextTime().value() + rate_));
	activity_->statusIs(Activity::nextTimeScheduled);
	break;

    case Activity::nextTimeScheduled:
	//add myself to be scheduled
	manager_->lastActivityIs(activity_);
	break;

    default:
	break;
    }

}
*/

#include "ActivityReactor.h"
#include "../Instance.h"
#include "../Common.h"
#include "../Instance.h"
#include "../Shipment.h"
#include "../singletons.h"

static int num = 0;

TransportActivityReactor::TransportActivityReactor(string name, Fwk::Ptr<Activity::Manager> manager,
		Activity* activity, NumberOfEntities number, Location::Ptr cust1, Location::Ptr cust2):
		Notifiee(activity), activity_(activity), manager_(manager){

	source = cust1;
	dest = cust2;
	cur = source;
	noOfPackages = number;
	name_ = name;

}

void TransportActivityReactor::onStatus() {
	//  Queue::Ptr q = NULL;

	ActivityImpl::ManagerImpl::Ptr managerImpl = Fwk::ptr_cast<ActivityImpl::ManagerImpl>(manager_);
//	int a = rand();
//	stringstream s;
//	s<<a;
	//TODO: Change name
	Shipment::Ptr shipment = Shipment::ShipmentNew(name_);
	double jump;

	switch (activity_->status()) {

	case Activity::executing:
		//I am executing now
		num++;
		cout << name_ << " : (" << noOfPackages.value() << ") from " <<
				cur->name() << " towards " << dest->name();
		shipment->sourceIs(cur);
		shipment->destinationIs(dest);
		shipment->packagesIs(noOfPackages);
		Router::instance()->shipmentIs(shipment);
		cur = Router::instance()->location();
		cout << " reached  " << cur->name() << endl;

		//TODO: Randomly sleeping for sometime change to right time from Raj's code
		jump = 1.0 * (rand()%30);
//		activity_->nextTimeIs(activity_->nextTime().value() + jump);

		//TODO: Remove from the manager Terminate condition
		if(cur->name() == dest->name()){
			activity_->statusIs(Activity::deleted);
		}
		break;

	case Activity::free:
		//when done, automatically enqueue myself for next execution

//		activity_->nextTimeIs(Time(activity_->nextTime().value() + rate_));
		activity_->nextTimeIs(Time(activity_->nextTime().value() + jump));
		activity_->statusIs(Activity::nextTimeScheduled);
		break;

	case Activity::nextTimeScheduled:
		//add myself to be scheduled
		manager_->lastActivityIs(activity_);
		break;

	case Activity::deleted:
//		manager_->activityDel(this->n);
		break;
	default:
		break;
    }

}

void gen_random(char *s, const int len) {
	static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len] = 0;
}


ActivityInjectorReactor::ActivityInjectorReactor(string name, Fwk::Ptr<Activity::Manager> manager,
		Activity* activity, double rate, NumberOfEntities number, Location::Ptr cust1, Location::Ptr cust2):
		Notifiee(activity), activity_(activity), manager_(manager){

	source = cust1;
	dest = cust2;
	noOfPackages = number;
	name_ = name;
	rate_ = rate;
}


void ActivityInjectorReactor::onStatus() {
	Activity::Manager::Ptr activityManager = activityManagerInstance();
	char *activityName;
	string activityNameStr;
	Activity::Ptr transportAcvitity;

	switch (activity_->status()) {

	case Activity::executing:
	    activityName = (char *) calloc(10, sizeof(char));
	    gen_random(activityName, 10);
	    activityNameStr.assign(activityName);
	    cout << "**********Firing new shippment***********" << endl;
	    transportAcvitity = activityManager->activityNew(activityNameStr);

	    transportAcvitity->lastNotifieeIs(new TransportActivityReactor(activityNameStr, activityManager,
	    		transportAcvitity.ptr(), NumberOfEntities(noOfPackages), source, dest));

	    transportAcvitity->nextTimeIs(activity_->nextTime());
	    transportAcvitity->statusIs(Activity::nextTimeScheduled);
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

	case Activity::deleted:
//		manager_->activityDel(this->n);
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


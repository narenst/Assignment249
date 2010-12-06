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
	target = NULL;

	totalCost = 0;
	startTime = 0;
}

void TransportActivityReactor::onStatus() {

	ActivityImpl::ManagerImpl::Ptr managerImpl = Fwk::ptr_cast<ActivityImpl::ManagerImpl>(manager_);
	Shipment::Ptr shipment = Shipment::ShipmentNew(name_);
	double currentTime = activity_->nextTime().value();
	if(firstTime){
		startTime = activity_->nextTime().value();
		firstTime = false;
	}

	switch (activity_->status()) {

	case Activity::executing:

		//See if shipment already in motion
		if(target != NULL){
			cur = target;
			target = NULL;

			//dec segment
			curSegment->usageDec();
//			cout << name_ << " : (" << noOfPackages.value() << ") reached " << cur->name() << endl;
		}

		//see if shipment reached dest
		if(cur->name() == dest->name()){
//			cout << name_ << "Reached final customer" << endl;
			//ENDTIME
			double totalTime = currentTime - startTime;
//			cout << " %%%%%% TOTAL LATENCY : " << totalTime << endl;

			Customer *custDest;
			try {
				custDest = dynamic_cast<Customer*>((Location*)dest.ptr());
			}
			catch (exception& e) {
				cout << "Use customer location name: " << e.what();
			}

			custDest->totalCostIs(Dollar(custDest->totalCost().value() + totalCost));

			if(custDest->averageLatency().value() > 0.0)
				custDest->averageLatencyIs(Hour((custDest->averageLatency().value()+totalTime)/2));
			else
				custDest->averageLatencyIs(Hour(totalTime));

			custDest->shipmentsReceivedInc();
			// dest-> cost = totalCost;
			// dest-> time = totalTime;
			// dest-> totalShipments ++;
			activity_->statusIs(Activity::deleted);
			break;
		}

		//now find out the next path
		num++;

		shipment->sourceIs(cur);
		shipment->destinationIs(dest);
		shipment->packagesIs(noOfPackages);

		try{
			Router::instance()->shipmentIs(shipment);
		}catch(Fwk::EntityIdInUseException& e){
			jump = Router::instance()->time().value();
			jump = jump - currentTime;
//			cout << "JUMP val : " << jump << endl;
			activity_->statusIs(Activity::waiting);
			break;
		}

//		cout << name_ << " : (" << noOfPackages.value() << ") from " <<
//				cur->name() << " towards " << dest->name() << endl;

		target = Router::instance()->location();
		jump = Router::instance()->time().value();
		curSegment = Router::instance()->segment();
		totalCost += Router::instance()->cost().value();

//		cout << "Using segment of len " << curSegment->length().value() << endl;

		//inc segment
		curSegment->usageInc(currentTime + jump);

//		cout << " will reach  " << target->name() << " in " << jump << " hours " << endl;

		//TODO: Remove from the manager Terminate condition
		break;

	case Activity::free:
		//when done, automatically enqueue myself for next execution
//		activity_->nextTimeIs(Time(activity_->nextTime().value() + rate_));
		activity_->nextTimeIs(Time(currentTime + jump));
		activity_->statusIs(Activity::nextTimeScheduled);
		break;

	case Activity::nextTimeScheduled:
		//add myself to be scheduled
		manager_->lastActivityIs(activity_);
		break;

	case Activity::deleted:
//		manager_->activityDel(this->n);
		break;

	case Activity::waiting:
		activity_->nextTimeIs(Time(currentTime + jump));
		manager_->lastActivityIs(activity_);
//		activity_->statusIs(Activity::nextTimeScheduled);
//		activity_->statusIs(Activity::executing);


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
//	    cout << "**********Firing new shippment***********" << endl;
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

FleetParamsReactor::FleetParamsReactor(string name, Fwk::Ptr<Activity::Manager> manager,
		Activity* activity, Hour startOfDay, Hour endOfDay):
		Notifiee(activity), activity_(activity), manager_(manager),
		startOfDay_(startOfDay), endOfDay_(endOfDay){

	firstTime = true;
}


void FleetParamsReactor::onStatus() {
	Activity::Manager::Ptr activityManager = activityManagerInstance();
	string activityNameStr;
	double currentTime = activity_->nextTime().value();

	switch (activity_->status()) {

	case Activity::executing:
		if(firstTime){
			nextDay = true;
			nextJump = startOfDay_.value();
			Fleet::instance()->useInstance(night_);
			firstTime = false;
			break;
		}

		if(nextDay){
			nextDay = false;
			nextJump = endOfDay_.value()-startOfDay_.value();
			Fleet::instance()->useInstance(day_);
		}else{
			nextDay = true;
			nextJump = (24.0-endOfDay_.value())+startOfDay_.value();
			Fleet::instance()->useInstance(night_);
		}
		break;

	case Activity::free:
		activity_->nextTimeIs(Time(activity_->nextTime().value() + nextJump));
		activity_->statusIs(Activity::nextTimeScheduled);
		break;

	case Activity::nextTimeScheduled:
		manager_->lastActivityIs(activity_);
		break;

	case Activity::deleted:
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


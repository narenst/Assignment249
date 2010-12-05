#ifndef __ACTIVITY_REACTOR_H__
#define __ACTIVITY_REACTOR_H__

#include "ActivityImpl.h"
#include "../Location.h"
#include "../Ordinals.h"

class TransportActivityReactor : public Activity::Notifiee {
 public:
	TransportActivityReactor(string name, Fwk::Ptr<Activity::Manager> manager, Activity*
			 activity, NumberOfEntities number, Location::Ptr cust1,
			 Location::Ptr cust2);
    void onStatus();

 protected:
    Activity::Ptr activity_;
    Fwk::Ptr<Activity::Manager> manager_;
	Location::Ptr source;
	Location::Ptr dest;
	Location::Ptr cur;
	Location::Ptr target;
	Segment::Ptr curSegment;
	NumberOfEntities noOfPackages;
	string name_;
	double jump;
};

//Injector
class ActivityInjectorReactor : public Activity::Notifiee {
 public:
	ActivityInjectorReactor(string name, Fwk::Ptr<Activity::Manager> manager, Activity*
			 activity, double rate, NumberOfEntities number, Location::Ptr cust1,
			 Location::Ptr cust2);
    void onStatus();

 protected:
    Activity::Ptr activity_;
    Fwk::Ptr<Activity::Manager> manager_;
	Location::Ptr source;
	Location::Ptr dest;
	Location::Ptr cur;
	NumberOfEntities noOfPackages;
	string name_;
	double rate_;
};

/*
class ConsumerActivityReactor : public Activity::Notifiee {
 public:
 ConsumerActivityReactor(Fwk::Ptr<Activity::Manager> manager, Activity*
			 activity, double rate)
     : Notifiee(activity), rate_(rate), activity_(activity), manager_(manager) {}

    void onStatus();

 protected:
    double rate_;
    Activity::Ptr activity_;
    Fwk::Ptr<Activity::Manager> manager_;

};
    */
    

#endif

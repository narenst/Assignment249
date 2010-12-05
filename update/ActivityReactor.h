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
	bool firstTime;
	double totalCost;
	double startTime;
};

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

class FleetParamsReactor : public Activity::Notifiee {
 public:
	FleetParamsReactor(string name, Fwk::Ptr<Activity::Manager> manager, Activity*
			 activity, Hour startOfDay, Hour endOfDay);
    void onStatus();

 protected:
    Activity::Ptr activity_;
    Fwk::Ptr<Activity::Manager> manager_;
	string name_;
	Hour startOfDay_;
	Hour endOfDay_;
	double nextJump;
	bool nextDay;
	bool firstTime;
};


#endif

#ifndef __ACTIVITY_REACTOR_H__
#define __ACTIVITY_REACTOR_H__

#include "ActivityImpl.h"
#include "../Location.h"

class TransportActivityReactor : public Activity::Notifiee {
 public:
	TransportActivityReactor(Fwk::Ptr<Activity::Manager> manager, Activity*
			 activity, double rate, Location::Ptr cust1, Location::Ptr cust2);
    void onStatus();

 protected:
    double rate_;
    Activity::Ptr activity_;
    Fwk::Ptr<Activity::Manager> manager_;
	Location::Ptr source;
	Location::Ptr dest;
	Location::Ptr cur;
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

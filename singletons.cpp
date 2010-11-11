#include "singletons.h"
#include "Location.h"

#include <queue>

using namespace std;

bool Fleet::instanceFlag = false;
Fleet* Fleet::single = NULL;	

bool Connectivity::instanceFlag = false;
Connectivity* Connectivity::single = NULL;	

bool Stats::instanceFlag = false;
Stats* Stats::single = NULL;	


void Fleet::typeIs( Mode mode) {
	
	switch ( mode.value() )  {
		case plane_:
			type_ = planeDetail_;
			break;
		case boat_:
			type_ = boatDetail_;
			break;
		case truck_:
			type_ = truckDetail_;
			break;
	 }

}

struct Node {
	Location* l;
	Mile distance;
	Dollar cost;
	
	Node () : distance(0.0), cost(0.0){
		
	}
};

void Connectivity::computePaths() {
	
	queue<struct Node> q;
	struct Node temp;
	temp.l = source_;
	temp.distance = 0.0;
	temp.cost = 0.0;

	q.push(temp);
	
	while (!q.empty()) {
		
		Location* first = q.front().l;
		//path.append()
						
		for (Location::SegmentList::iterator i = first->segments().begin(); i!=first->segments().end(); ++i) {
			Segment::Ptr returnSegment = (*i)->returnSegment();
			if (returnSegment != NULL) {
				struct Node n;
				n.l = returnSegment->source();
				n.distance = (q.front().distance + (*i)->length()).value();
				Fleet::instance()->typeIs((*i)->mode());
				n.cost = q.front().cost.value() + (*i)->length().value() * Fleet::instance()->type()->cost().value();
				//pathList.append(
				q.push(n);
			}
			
			q.pop();
		}
		
		
	}
	

}

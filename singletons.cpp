#include "singletons.h"
#include "Location.h"

#include <queue>
#include <iomanip>

using namespace std;
#include <map> 
#include <algorithm>
#include <iterator>
#include <vector>
#include <limits>

bool Fleet::instanceFlag = false;
Fleet* Fleet::single = NULL;	

bool Connectivity::instanceFlag = false;
Connectivity* Connectivity::single = NULL;	

bool Stats::instanceFlag = false;
Stats* Stats::single = NULL;	


void Fleet::typeIs( Mode mode) {
	
	switch ( mode.value() )  {
		case plane_:
			type_ = &planeDetail_;
			break;
		case boat_:
			type_ = &boatDetail_;
			break;
		case truck_:
			type_ = &truckDetail_;
			break;
	 }

}



struct Node {
	Location* l;
	Mile distance;
	Dollar cost;
	Hour time_;
	Fwk::String path;
	ExpediteSupport expedite_;
	map < string, bool> visited;
	Node () : distance(0.0), cost(0.0), time_(0.0), expedite_(true){
		
	}
};

Fwk::String convertFloatToString(float val)
{
	stringstream ss (stringstream::in | stringstream::out);
	if(round(val) == val)
		ss << val;
	else
		ss << setprecision(3) << val;
	Fwk::String test = ss.str();
	return test;
}

Fwk::String convertBoolToString(bool val) {
	if (val == true)
		return Fwk::String("yes");
	else
		return Fwk::String("no");	
}
	
	
Fwk::String Connectivity::computePaths() {
	
	Fwk::String finalPath;
	
	if (type_ == explore_) {
		
		if (cost_ == 0.0)
			cost_ = numeric_limits<double>::max( );

		if (distance_ == 0.0)
			distance_ = numeric_limits<double>::max( );
		
		if (time_ == 0.0)
			time_ = numeric_limits<double>::max( );
			
		vector < Fwk::String > paths;
		queue<struct Node> q;
		struct Node temp;
		temp.l = source_;
		temp.distance = 0.0;
		temp.cost = 0.0;
		temp.time_ = 0.0;
		temp.path = source_->name();
		temp.visited[source_->name()] = true;
		q.push(temp);
		
		
		
		
		while (!q.empty()) {
			
			Location* first = q.front().l;
			Location::SegmentList s = first->segments();
			for (Location::SegmentList::iterator i = s.begin(); i != s.end(); ++i) {
				Segment::Ptr returnSegment = (*i)->returnSegment();
				
				if (returnSegment != NULL) {
					
					if (expedited_.value() && !((*i)->expediteSupport().value()))
						break;
					
					Location* rs = returnSegment->source();
					
					if ( !q.front().visited[rs->name()] ) {

						struct Node n;
						n.l = rs;
						n.distance = (q.front().distance + (*i)->length()).value();
						Fleet::instance()->typeIs((*i)->mode());
						n.cost = q.front().cost.value() + (*i)->length().value() * Fleet::instance()->type()->cost().value() * (*i)->difficulty().value() ;
						
						if (Fleet::instance()->type()->speed().value()!= 0.0)
							n.time_ = q.front().time_.value() + (*i)->length().value() / Fleet::instance()->type()->speed().value();
						
						if (n.cost <= cost_  && n.distance <= distance_ && n.time_ <= time_) {

							Fwk::String path;
							path += q.front().path;
							path += "(";
							path += (*i)->name();
							path += ":";
							path += convertFloatToString((*i)->length().value());
							path += ":";
							path += (*i)->returnSegment()->name();
							path += ") ";
							path += rs->name();
							
							paths.push_back(path);
							n.path = path;
							n.visited.insert(q.front().visited.begin(), q.front().visited.end());
							n.visited[rs->name()] = true;
							q.push(n);						
						}
					}
				}
			}
			q.pop();
		}
		
		
		
		for (vector < Fwk::String >::iterator i=paths.begin(); i!=paths.end(); ++i) {
				finalPath += (*i);
				finalPath += "\n";
		}
		
	}
	else {
		
		
		vector < Fwk::String > paths;
		queue<struct Node> q;
		struct Node temp;
		temp.l = source_;
		temp.distance = 0.0;
		temp.cost = 0.0;
		temp.time_ = 0.0;
		temp.path = source_->name();
		temp.visited[source_->name()] = true;
		temp.expedite_ = true;
		
		q.push(temp);
		

		
		while (!q.empty()) {
			
			Location* first = q.front().l;
			Location::SegmentList s = first->segments();
			for (Location::SegmentList::iterator i = s.begin(); i != s.end(); ++i) {
				Segment::Ptr returnSegment = (*i)->returnSegment();
				
				if (returnSegment != NULL) {
					
					Location* rs = returnSegment->source();
					
					if ( !q.front().visited[rs->name()] ) {
				
						Fwk::String path;
						path += q.front().path;
						path += "(";
						path += (*i)->name();
						path += ":";
						path += convertFloatToString((*i)->length().value());
						path += ":";
						path += (*i)->returnSegment()->name();
						path += ") ";
						path += rs->name();
						
						struct Node n;
						n.l = rs;
						n.distance = (q.front().distance + (*i)->length()).value();
						Fleet::instance()->typeIs((*i)->mode());
						n.cost = q.front().cost.value() + (*i)->length().value() * Fleet::instance()->type()->cost().value() * (*i)->difficulty().value() ;
						
						if (Fleet::instance()->type()->speed().value()!= 0.0)
							n.time_ = q.front().time_.value() + (*i)->length().value() / Fleet::instance()->type()->speed().value();
						
						n.path = path;
						n.visited.insert(q.front().visited.begin(), q.front().visited.end());
						n.visited[rs->name()] = true;
						if ( !(*i)->expediteSupport().value())
							n.expedite_ = false;
						else {
							n.expedite_ = q.front().expedite_;
						}

						
						if (rs != destination_) {
							q.push(n);			
						}
						else {
							Fwk::String temp = convertFloatToString(n.cost.value()) + " " + convertFloatToString(n.time_.value()) + " " + convertBoolToString(false) + "; ";
							paths.push_back(temp + path);
							if(n.expedite_.value()){
								temp = convertFloatToString(n.cost.value()*1.5) + " " + convertFloatToString(n.time_.value()/1.3) + " " + convertBoolToString(true) + "; " ;
								paths.push_back(temp + path);
							}
						}

					}
				}
			}
			q.pop();
		}
		
		for (vector < Fwk::String >::iterator i=paths.begin(); i!=paths.end(); ++i) {
			finalPath += (*i);
			finalPath += "\n";
		}
		 
	}

	
	return finalPath;
		
}
	




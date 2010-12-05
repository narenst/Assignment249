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
Fleet* Fleet::single1 = NULL;
Fleet* Fleet::single2 = NULL;

bool Connectivity::instanceFlag = false;
Connectivity* Connectivity::single = NULL;	

bool Stats::instanceFlag = false;
Stats* Stats::single = NULL;	

bool Router::instanceFlag = false;
Router* Router::single = NULL;

/* 
 * Sets the type attribute in Fleet class. 
 * The attribute stores information about the type of
 * segment we are trying to set details for.
 */
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

void Router::computeLocationAndSegment(Shipment::Ptr shipment) {

	Fwk::String locationTime, locationCost;


	if (connect(shipment->source(), shipment->destination(), locationTime, locationCost)) {
		if (locationCost != "") {
			location_ = localLocationList[locationMap[locationCost]];
			segmentUpdateHelper(shipment, location_);
		}
		else if (locationTime != "") {
			location_ = localLocationList[locationMap[locationTime]];
		}
		else {
			throw SegmentInUseException("Some Segment is in use in this section");
		}
	}
	else {
		throw  NotConnectedException("The source and destination are not connected") ;
	}

	
}

void Router::segmentUpdateHelper( Shipment::Ptr shipment,  Location::Ptr currentLocation) {


	Location::SegmentList s = shipment->source()->segments();
	for (Location::SegmentList::iterator i = s.begin(); i != s.end(); ++i) {
		Segment::Ptr returnSegment = (*i)->returnSegment();
		
		if (returnSegment != NULL) {
			
			Location* rs = returnSegment->source();
			if (rs == currentLocation.ptr()){
				segment_ = (*i);
				
				Fleet::instance()->typeIs((*i)->mode());
				if (Fleet::instance()->type()->speed().value()!= 0.0) {
					time_ =  (*i)->length().value() / Fleet::instance()->type()->speed().value();
					time_ = time_.value() * ceil((shipment->packages() / Fleet::instance()->type()->capacity()).value());
				}
				cost_ = (*i)->length().value() * Fleet::instance()->type()->cost().value() * (*i)->difficulty().value() ;
				
				break;
			}
		}
	}
	
}



void Router::preprocess(vector<Location::Ptr> l) {

	localLocationList = l;
	
	/*
	
	
	// Set up sizes. (HEIGHT x WIDTH)
	connectivityBit.resize(size);
	connectByTime.resize(size);
	connectByCost.resize(size);
	for (int i = 0; i < size; ++i) {
		connectivityBit[i].resize(size);
		connectByTime[i].resize(size);
		connectByCost[i].resize(size);
	}
	
	*/
	
	size_t size = l.size();
	for (int i = 0; i < size; ++i) {
		locationMap[l[i]->name()] = i;
	}
	
	
	/*
		
		for (int j = i; j < size; ++j) {
			Fwk::String locationTime, locationCost;
			connectivityBit[i][j] = connect(l[i], l[j], locationTime, locationCost);
			connectByTime[i][j] = locationTime;
			connectByCost[i][j] = locationCost;
		}
	}
	 */
}

 


/* 
 * Stores the details being used in the path finding 
 * graph search algorithm. Incrementally stores the distance,
 * cost, time , visited locations, etc for a particular path
 */
struct DistanceNode {
	Location::Ptr l;
	Dollar cost;
	Fwk::String path;
	map < string, bool> visited;
	DistanceNode () : cost(0.0){
		
	}
};

bool Router::connect(Location::Ptr source_, Location::Ptr destination_, Fwk::String& sT, Fwk::String& sC) {
	
	if (ralgo_ == bfs_) {
		
		queue<struct DistanceNode> q;
		struct DistanceNode temp;
		temp.l = source_;
		temp.cost = 0.0;
		temp.path = Fwk::String();
		temp.visited[source_->name()] = true;
		
		q.push(temp);
		
		double minCost = numeric_limits<double>::max();
		double time = -1.0;
		
		while (!q.empty()) {
			
			Location::Ptr first = q.front().l;
			Location::SegmentList s = first->segments();
			for (Location::SegmentList::iterator i = s.begin(); i != s.end(); ++i) {
				Segment::Ptr returnSegment = (*i)->returnSegment();
				
				if (returnSegment != NULL) {
					
					Location* rs = returnSegment->source();
					
					if ( !q.front().visited[rs->name()]) {
						
						
						if( (*i)->usage() >= (*i)->capacity() ) {
							cout << (*i)->usage().value() << (*i)->capacity().value() << endl;
							time = (*i)->waitingTime().value();
							(*i)->shipmentsRefusedInc();
							Stats::instance()->totalShipmentsRefusedInc();
							continue;
						}
						
						
						
						try {
							
							if (dynamic_cast<Customer*>((Location*)rs) && rs != destination_.ptr()) {
								continue;
							}
						}
						catch (exception& e) {
							cout << "Exception: " << e.what();
						}						
						
						
						Fwk::String path;
						path += q.front().path;
						path += rs->name();
						path += ";";
						
						struct DistanceNode n;
						n.l = rs;
						
						Fleet::instance()->typeIs((*i)->mode());
						n.cost = q.front().cost.value() + (*i)->length().value() * Fleet::instance()->type()->cost().value() * (*i)->difficulty().value() ;
						n.path = path;
						n.visited.insert(q.front().visited.begin(), q.front().visited.end());
						n.visited[rs->name()] = true;

						if (rs != destination_.ptr()) {
							q.push(n);			
						}
						else {
							if (n.cost.value() < minCost) {
								minCost = n.cost.value();
								sC = n.path.substr(0, n.path.find(";"));
								
							}
						}
						
					}
				}
			}
			q.pop();
		}
		
		if (time!=-1.0) {
			time_ = time;
			return true;
		}
		
		if (sC == "")
			return false;
		else {
			return true;
		}
	}
	else {

		deque<Fwk::String> fringeList;

		map <Fwk::String, nodeType > status;
		map <Fwk::String, Fwk::String > parent;
		map <Fwk::String, double > cost;
		double time = -1.0;
		
		size_t size = localLocationList.size();
		
		for (int i = 0; i<size; ++i) {
			status[localLocationList[i]->name()] = UNSEEN;
			parent[localLocationList[i]->name()] = Fwk::String();
			cost[localLocationList[i]->name()] = 0.0;
		}
		Fwk::String src = source_->name();
		Fwk::String dest = destination_->name();
		status[src] = INTREE;
		cost[src] = 0.0;
		
		while( src != dest) {
			Location::SegmentList s = localLocationList[locationMap[src]]->segments();
			for (Location::SegmentList::iterator i = s.begin(); i != s.end(); ++i) {
				Segment::Ptr returnSegment = (*i)->returnSegment();
				
				if (returnSegment != NULL) {
					
					
					if( (*i)->usage() >= (*i)->capacity() ) {
						cout << (*i)->usage().value() << (*i)->capacity().value() << endl;
						time = (*i)->waitingTime().value();
						(*i)->shipmentsRefusedInc();
						Stats::instance()->totalShipmentsRefusedInc();
						continue;
					}
					
					
					Location* rs = returnSegment->source();
					
					try {
						
						if (dynamic_cast<Customer*>((Location*)rs) && rs != destination_.ptr()) {
							continue;
						}
					}
					catch (exception& e) {
						cout << "Exception: " << e.what();
					}	
					
					Fwk::String dest = rs->name();
					Fleet::instance()->typeIs((*i)->mode());
					double cost_ = (*i)->length().value() * Fleet::instance()->type()->cost().value() * (*i)->difficulty().value() ;
					if ((status[dest] == FRINGE) && cost[src] + cost_ < cost[dest]) {
						parent[dest] = src;
						cost[dest] = cost[dest] + cost_;
					}
					else if (status[dest] == UNSEEN) {
						status[dest] = FRINGE;
						parent[dest] = src;
						cost[dest] = cost[dest] + cost_;
						fringeList.push_front(dest);
					}
				}
			}
				
			if (fringeList.empty()){
				if (time!=-1.0) {
					time_ = time;
					return true;
				}
				else {
					return false;
				}
				//break;
			}
			else {
				src = fringeList.front();
				double minCost = cost[src];
				for ( deque< Fwk::String >::iterator it= fringeList.begin()+1; it != fringeList.end(); ++it) {
				
					Fwk::String temp = (*it);
					if (cost[temp] < minCost) {
						src = temp;
						minCost = cost[temp];
					}
				}
				
				fringeList.erase(find(fringeList.begin(), fringeList.end(),src));
				status[src] = INTREE;
			}
		}// end of main while loop
		
		sC = dest;
		while (parent[sC] != source_->name()){
			sC = parent[sC];
		}
	
		return true;
		
	}//end of djikistra else
}

/* 
 * Stores the details being used in the path finding 
 * graph search algorithm. Incrementally stores the distance,
 * cost, time , visited locations, etc for a particular path
 */
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

/*
 * Converts a floating point value to a string
 * with required precision.
 */
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

/*
 * Converts a boolean value to a string 
 *  either 'yes' or 'no'
 */
Fwk::String convertBoolToString(bool val) {
	if (val == true)
		return Fwk::String("yes");
	else
		return Fwk::String("no");	
}
	
/*
 * Computes the path for either a explore query or a connect query 
 * and returns the path as a string in the required format.
 */
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
	




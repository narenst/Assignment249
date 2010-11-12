/*
 * Ordinals.h
 *
 *  Created on: Nov 9, 2010
 *      Author: naren
 */

#ifndef ORDINALS_H_
#define ORDINALS_H_

#include "Nominal.h"
using namespace std;




namespace ordinaltypes{
	
	typedef enum {truck_ = 0, boat_ = 1, plane_ = 2} mode_;
	
	class Mode : public Ordinal<Mode, mode_> {
	public:
		Mode(mode_ val) : Ordinal<Mode, mode_>(val) { }
	};
	
	
	class PercentExpediteShipping : public Ordinal<PercentExpediteShipping, double> {
	public:
		PercentExpediteShipping(double val) : Ordinal<PercentExpediteShipping, double>(val) {
			if(val < 0.0 || val > 100.0){
				cerr << "invalid parameter - PercentExpediteShipping" << endl;
			}
		}
	};
	
	
	class NumberOfEntities : public Ordinal<NumberOfEntities, unsigned int> {
	public:
		NumberOfEntities(unsigned int val) : Ordinal<NumberOfEntities, unsigned int>(val) { }
		
		const NumberOfEntities& operator=(const Ordinal<NumberOfEntities,
										  unsigned int>& v)
		{ this->value_ = v.value(); return *this; }
		
		Ordinal<NumberOfEntities, unsigned int> operator-(const Ordinal<NumberOfEntities,
														  unsigned int>& other)
		{ return (this->value_ - other.value()); }
		
	};

	class Mile : public Ordinal<Mile, double> {
	public:
		Mile(float val) : Ordinal<Mile, double>(val) {
			if(val < 0.0){
				cerr << "invalid parameter - Mile" << endl;
			}
		}
	};

		
	class MilePerHour : public Ordinal<MilePerHour, double> {
	public:
		MilePerHour(float val) : Ordinal<MilePerHour, double>(val) {
			if(val < 0.0){
				cerr << "invalid parameter - MilePerHour" << endl;
			}
		}
	};
	
	class Dollar : public Ordinal<Dollar, double> {
	public:
		Dollar(float val) : Ordinal<Dollar, double>(val) {
			if(val < 0.0){
				cerr << "invalid parameter - Dollar" << endl;
			}
		}
	};
	
	class Hour : public Ordinal<Hour, double> {
	public:
		Hour(float val) : Ordinal<Hour, double>(val) {
			if(val < 0.0){
				cerr << "invalid parameter - Hour" << endl;
			}
		}
	};

	class Difficulty : public Ordinal<Difficulty, double> {
	public:
		Difficulty(float val) : Ordinal<Difficulty, double>(val) {
			if(val < 1.0 || val > 5.0){
				cerr << "invalid parameter - Difficulty" << endl;
			}
		}
	};


	class ExpediteSupport : public Nominal<ExpediteSupport, bool> {
	public:
		ExpediteSupport(bool val) : Nominal<ExpediteSupport, bool>(val) { }
	};


	class Index : public Ordinal<Index, unsigned int> {
	public:
		Index(unsigned int val) : Ordinal<Index, unsigned int>(val) { }
	};

}

#endif /* ORDINALS_H_ */

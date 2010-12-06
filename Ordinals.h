/*
 * Ordinals.h
 *
 *  Created on: Nov 9, 2010
 *      Author: naren
 */

#ifndef ORDINALS_H_
#define ORDINALS_H_

#include "fwk/Exception.h"
#include "update/Nominal.h"

using namespace std;

namespace ordinaltypes{
	
	typedef enum {truck_ = 0, boat_ = 1, plane_ = 2} mode_;
	typedef enum {day_ = 0, night_ = 1} type_;
	
	class Mode : public Ordinal<Mode, mode_> {
	public:
		Mode(mode_ val) : Ordinal<Mode, mode_>(val) { }
	};
	
	class FleetInstanceType : public Ordinal<FleetInstanceType, type_> {
	public:
		FleetInstanceType(type_ val) : Ordinal<FleetInstanceType, type_>(val) { }
	};
	
	class AverageEntitites : public Ordinal<AverageEntitites, double> {
	public:
		AverageEntitites(double val) : Ordinal<AverageEntitites, double>(val) {
			if(val < 0.0 ){
				cerr << "invalid parameter - AverageEntitites" << endl;
				throw Fwk::RangeException("Average Entities value incorrect");
			}
		}
	};
	
	class PercentExpediteShipping : public Ordinal<PercentExpediteShipping, double> {
	public:
		PercentExpediteShipping(double val) : Ordinal<PercentExpediteShipping, double>(val) {
			if(val < 0.0 || val > 100.0){
				cerr << "invalid parameter - PercentExpediteShipping" << endl;
				throw Fwk::RangeException("PercentExpediteShipping value incorrect");
			}
		}
	};
	
	
	class NumberOfEntities : public Ordinal<NumberOfEntities, unsigned int> {
	public:
		NumberOfEntities(unsigned int val) : Ordinal<NumberOfEntities, unsigned int>(val) { }
		NumberOfEntities() : Ordinal<NumberOfEntities, unsigned int>(0) { }
		
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
				throw Fwk::RangeException("Mile value incorrect");
			}
		}
	};

		
	class MilePerHour : public Ordinal<MilePerHour, double> {
	public:
		MilePerHour(float val) : Ordinal<MilePerHour, double>(val) {
			if(val < 0.0){
				cerr << "invalid parameter - MilePerHour" << endl;
				throw Fwk::RangeException("MilePerHour value incorrect");
			}
		}
	};
	
	class Dollar : public Ordinal<Dollar, double> {
	public:
		Dollar(float val) : Ordinal<Dollar, double>(val) {
			if(val < 0.0){
				cerr << "invalid parameter - Dollar" << endl;
				throw Fwk::RangeException("Dollar value incorrect");
			}
		}
	};
	
	class Hour : public Ordinal<Hour, double> {
	public:
		Hour(float val) : Ordinal<Hour, double>(val) {
			if(val < 0.0){
				cerr << "invalid parameter - Hour" << endl;
				throw Fwk::RangeException("Hour value incorrect");
			}
		}
	};

	class Difficulty : public Ordinal<Difficulty, double> {
	public:
		Difficulty(float val) : Ordinal<Difficulty, double>(val) {
			if(val < 1.0 || val > 5.0){
				cerr << "invalid parameter - Difficulty" << endl;
				throw Fwk::RangeException("Difficulty value incorrect");
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

/*
 * Ordinals.h
 *
 *  Created on: Nov 9, 2010
 *      Author: naren
 */

#ifndef ORDINALS_H_
#define ORDINALS_H_

#include "Nominal.h"





namespace ordinaltypes{
	
	typedef enum {truck_ = 0, boat_ = 1, plane_ = 2} mode_;
	
	class Mode : public Ordinal<Mode, mode_> {
	public:
		Mode(mode_ val) : Ordinal<Mode, mode_>(val) { }
	};
	
	
	
	
	class PercentExpediteShipping : public Ordinal<PercentExpediteShipping, double> {
	public:
		PercentExpediteShipping(double val) : Ordinal<PercentExpediteShipping, double>(val) { }
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
		Mile(float val) : Ordinal<Mile, double>(val) { }
	};

		
	class MilePerHour : public Ordinal<MilePerHour, double> {
	public:
		MilePerHour(float val) : Ordinal<MilePerHour, double>(val) { }
	};
	
	class Dollar : public Ordinal<Dollar, double> {
	public:
		Dollar(float val) : Ordinal<Dollar, double>(val) { }
	};
	
	class Hour : public Ordinal<Hour, double> {
	public:
		Hour(float val) : Ordinal<Hour, double>(val) { }
	};

	class Difficulty : public Ordinal<Difficulty, double> {
	public:
		Difficulty(float val) : Ordinal<Difficulty, double>(val) { }
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

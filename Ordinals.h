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

class Miles : public Ordinal<Miles, double> {
public:
	Miles(float val) : Ordinal<Miles, double>(val) { }
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

#pragma once

#include "../global.h"
#include "../moea.h"


enum Instruction{GENE,OBJ};

template <class MOEOT>
class moeaOutputer
{
public:
	moeaOutputer(){};
	virtual ~moeaOutputer(){};
	/**
	 *string
	 */
	virtual void operator()(const string _message)=0;
	/**
	 *Time
	 */
	virtual void operator()(const Timer &timer)=0;
	/**
	 *pop
	 */
	 virtual void operator()(const eoPop<MOEOT> & _pop,\
							Instruction ins)=0;
	/**
	 *arch
	 */
	virtual void operator()(const moeoArchive < MOEOT > & _arch,\
							Instruction ins)=0;

	/**
	 * measure IGD
	 */
	 virtual void operator()(const moeaMeasurer &_measurer)=0;
// private:
// 	ostream output;
};
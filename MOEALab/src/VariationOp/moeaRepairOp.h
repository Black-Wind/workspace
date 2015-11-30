#pragma once

#include "../global.h"

template<class MOEOT>
class moeaRepairOp : public eoMonOp<MOEOT>
{
public:
	/// The class name.
	virtual std::string className() const {
		return "moeaRepairOp";
	}

	/**
	* Do it!
	* @param _eo The indi undergoing the mutation
	*/
	bool operator()(MOEOT& _eo)
	{return false;}
};

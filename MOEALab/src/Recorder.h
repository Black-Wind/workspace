#pragma once

#include "moea.h"
template <class MOEOT>
class moeaRecorder
{
public:
	moeaRecorder(string _filePathRoot):filePathRoot(_filePathRoot){}
	void setPath(string _filePathRoot){filePathRoot=_filePathRoot;}
	/**
	 *Time
	 */

	/**
	 *OBJ
	 */

	/**
	 * GENE
	 */
	/**
	 * IGD,...
	 */
private:
	string filePathRoot;
};
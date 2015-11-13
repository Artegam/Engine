#ifndef UNITTESTSET_H
#define UNITTESTSET_H

#include <vector>
#include "UnitTest.h"

using namespace std;

class UnitTestSet : public UnitTest {
	protected:
		vector<UnitTest *> testGroup;
		
	public:
		void executer();
		void resultat();
		void addTest(UnitTest * test);
};

#endif
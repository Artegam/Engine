#ifndef UNITTESTLOADER_H
#define UNITTESTLOADER_H

#include "UnitTest.h"
#include "UnitTestSet.h"



class UnitTestLoader : public UnitTest {

	private:
		UnitTestSet root;

	public:
		void executer();
		void charger();

};

#endif
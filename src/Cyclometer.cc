#include <cstdlib>
#include <iostream>
#include "CyclometerIterator.h"
#include "CyclometerContext.h"
#include "Enums.h"


int main(int argc, char *argv[]) {
	printf("starting \n");
	CyclometerIterator theItor = CyclometerIterator();
	CyclometerContext* myContext1 = new CyclometerContext(theItor);
	myContext1->accept(MODEBUTTONPRESS);
	//myContext1.accept(EVENT.MODEBUTTONPRESS);
/*
	int x = 0;
    while(true){
        x++;
        x--;
    }
    */
}

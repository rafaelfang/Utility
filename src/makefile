convert: jsoncpp.o AlignmentResult.o CNFSearchResult.o CNFSearchImpl.o HHRNRImpl.o HHRNRResult.o HHRImpl.o HHRResult.o BLANRImpl.o BLANRResult.o BLAPDBImpl.o BLAPDBResult.o Driver.o UtilityInterface.o 
	g++ jsoncpp.o AlignmentResult.o CNFSearchResult.o CNFSearchImpl.o HHRNRImpl.o HHRNRResult.o HHRImpl.o HHRResult.o BLANRImpl.o BLANRResult.o BLAPDBImpl.o BLAPDBResult.o Driver.o UtilityInterface.o  -o convert

jsoncpp.o: jsoncpp.cpp
	g++ -c jsoncpp.cpp
	
AlignmentResult.o: AlignmentResult.cpp
	g++ -c AlignmentResult.cpp
	
CNFSearchImpl.o: CNFSearchImpl.cpp
	g++ -c CNFSearchImpl.cpp
	
CNFSearchResult.o: CNFSearchResult.cpp
	g++ -c CNFSearchResult.cpp
		
HHRImpl.o: HHRImpl.cpp
	g++ -c HHRImpl.cpp
	
HHRResult.o: HHRResult.cpp
	g++ -c HHRResult.cpp
	
HHRNRImpl.o: HHRNRImpl.cpp
	g++ -c HHRNRImpl.cpp
	
HHRNRResult.o: HHRNRResult.cpp
	g++ -c HHRNRResult.cpp
	
BLAPDBImpl.o: BLAPDBImpl.cpp
	g++ -c BLAPDBImpl.cpp
	
BLAPDBResult.o: BLAPDBResult.cpp
	g++ -c BLAPDBResult.cpp

BLANRImpl.o: BLANRImpl.cpp
	g++ -c BLANRImpl.cpp
	
BLANRResult.o:BLANRResult.cpp
	g++ -c BLANRResult.cpp
		
Driver.o: Driver.cpp
	g++ -c Driver.cpp
	
UtilityInterface.o: UtilityInterface.cpp
	g++ -c UtilityInterface.cpp

clean:
	rm *.o convert
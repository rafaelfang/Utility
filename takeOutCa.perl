#!/usr/local/bin/perl
#
# take out the Ca from full pdb
#


$proteinNameList = $ARGV[0];

open(nameList,"$proteinNameList");

@names=<nameList>;
close(nameList);

foreach $name(@names) {
	$name=~ s/\s*$//;

	$proteinName = "/home/spnf2f/dataset/casp10/native/${name}.pdb";
	
	print "$proteinName \n";
	$outputFileName=$name."Ca.txt";
	open(FILE1,"$proteinName");
	open(FILE2,">$outputFileName");
	@lines=<FILE1>;
	close(FILE1);
	$substr="CA";
	foreach $line(@lines) {
		
		if (index($line, $substr) != -1) {
			
			print FILE2 "$line \n";
		} 
		
	}
	print FILE2 "TER\n";
	close(FILE2);
	
}

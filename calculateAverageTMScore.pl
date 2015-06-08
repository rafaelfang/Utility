#!/usr/local/bin/perl
#
# calculate average TM score for each protein
#
use Math::Trig; #USE THIS MODULE

$proteinNameList = $ARGV[0];
#$outputFile=$ARGV[1];
open(nameList,"$proteinNameList");
#open(outputFile,">>$outputFile");
@names=<nameList>;
close(nameList);

foreach $name(@names) {
	$name=~ s/\s*$//;

	$proteinScoreName = "/home/cf797/test/testTMScore/${name}Score.txt";
	open(scores,"$proteinScoreName");
	@score=<scores>;
	close(scores);
	$counter=0;
	$sum=0.0;
	foreach $row(@score){
		@values = split('\t', $row);
		$counter++;
		$sum=$sum+$values[1];

	}
	$average=$sum/$counter;
	print "$name,$average\n";	
}

#close(outputFile);
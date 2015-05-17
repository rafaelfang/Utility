#!/usr/local/bin/perl
#
# testing Utility module in batch
#


$filename = $ARGV[0];
$timeLogFilename=$ARGV[1];
open(FILE1,"$filename");
open(FILE2,">>$timeLogFilename");
@lines=<FILE1>;
close(FILE1);

foreach $line(@lines) {
	
	$cmd1 = "./convert -blaPDB $line";
	$cmd2 = "./convert -blaNR $line";
	$cmd3 = "./convert -hhr $line";
	$cmd4 = "./convert -hhrNR $line";
	print $cmd."\n";
	$start_run = time();
	system($cmd1);
	system($cmd2);
	system($cmd3);
	system($cmd4);
	$end_run = time();
	$run_time = $end_run - $start_run;
	print FILE2 "$line running time: $run_time \n";
}
close(FILE2);



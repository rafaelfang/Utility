#!/usr/local/bin/perl
#
# batch testing the TM score
#


$proteinNameList = $ARGV[0];

open(nameList,"$proteinNameList");

@names=<nameList>;
close(nameList);

foreach $name(@names) {
	$name=~ s/\s*$//;

	$caProteinName = "/home/cf797/test/CaPDBFiles/${name}Ca.txt";
	$dirname="/home/cf797/test/outputResultFolder/${name}/BLAPDB/pdbFiles";
	opendir(DIR, $dirname) or die "can't opendir $dirname: $!";
	while (defined($file = readdir(DIR))) {
		$cmd = "~spnf2f/bin/pscore -que $dirname/$file -base $caProteinName -score t -p >> ${name}Score.txt";
		#print $cmd."\n";
		system($cmd);
	}

	closedir(DIR);
	
	
	
}

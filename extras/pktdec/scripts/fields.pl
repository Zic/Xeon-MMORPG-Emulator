
use strict;

open(FD, "<UpdateFields.h");
open(FD2, ">Const.h");

my $fieldName = '';
my $fieldIndex = 0;
my $status = 0;
my $skip;
while (my $line = <FD>) {

	$skip = 0;
	if ($line =~ m!enum! and $status == 1) {
		print FD2 "};\n";
		$status = 0;
		$fieldName = '';
		$fieldIndex = 0;
	}


	if ($line =~ m!^enum EObjectFields!) {
		print FD2 "\nconst char *objectFields[] = {\n";
		$status = 1;
	}

	if ($line =~ m!^enum EUnitFields!) {
		print FD2 "\nconst char *unitFields[] = {\n";
		$status = 1;
	}

	if ($line =~ m!^[\s]*UNIT_END[\s]*!) {
		$skip = 1;
	}

	if ($status == 1 and $skip == 0) {
		if ($line =~ m![\s]*([\w_]*)!) {
			print $1 . "\n";
			my $name = $1;
			if ($line =~ m!(0x[\d\w]*)!) {
				my $index = hex($1);
				print "$index\n";

				if ($index < $fieldIndex) {
					$fieldIndex = -1;
				}

				my $count = 1;
				while ($fieldIndex != $index) {
					print FD2 "/* 0x" . $fieldIndex++ . "*/ \"" . $fieldName . "_" . $count++ . "\",\n";
				}

				$fieldName = $name;
				$fieldIndex = $index+1;
				printf FD2 "/* 0x%04X */ \"%s\",\n", $index, $name;
			}
		}
	}
}

close(FD);
close(FD2);

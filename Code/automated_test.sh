SRC=c-
TST_BANK=testDataA4

#$ files=("allbad.c-" "varassign.c-" "allgood.c-")

# update build
make clean
make parser

#for filename in $files
#do
#	echo $filename
#	./$SRC -P $TST_BANK/$filename > test.out
#	diff -y test.out $TST_BANK/${filname:-3}.out
	

# test allbad.c-
echo EXP4.C-
./$SRC -P $TST_BANK/exp4.c- > test.out
diff -y test.out $TST_BANK/exp4.out


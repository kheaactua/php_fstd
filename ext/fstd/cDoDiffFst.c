
#include <stdio.h>

int diffFst_(char*,int*,char*, char*,int*,char*, char*,int*,char*, float*, int*, int*);
void smallFortran_(char *, int *);

int main() {

	char *filA="tlm.fst", *filB="bf10.fst", *filO="bf10.fst";
	int len_filA=7, len_filB=8, len_filO=8;
	char *nomvarA="o3_ ", *nomvarB="o3_ ", *newnomvar="tmp5";

	float change=1.01;
	int ier=7;
	int val_false=0;

	//printf("Read arguments:\nfilA: %s (%d), nomvara: %s\nfilB: %s (%d), nomvarB: %s\nfilO: %s (%d), nomvarO: %s\nChange: %0.3f\n", filA,len_filA,nomvarA, filB,len_filB,nomvarB, filO,len_filO,newnomvar, change);

	//ier = diffFst_(filA,len_filA,nomvarA, filB,len_filB,nomvarB, filO,len_filO,newnomvar, change, val_false, val_false);
	ier = diffFst_(filA,&len_filA,nomvarA, filB,&len_filB,nomvarB, filO,&len_filO,newnomvar, &change, &val_false, &val_false);
	//ier = diffFst_("tlm.fst",&len_filA,"o3_", "bf10.fst",&len_filB,"o3_", "tmp.fst",&len_filO,"tmp", 1.1, 0, 0);

	//ier = smallFortran_(len_filA);
	//smallfortran_(filB, &len_filB);
	smallFortran_(filB, &len_filB);
	//ier = smallFortran_(8);
}

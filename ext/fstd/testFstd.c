#include <stdio.h>
#include <stdlib.h>

int c_fnom(int, char*, char*, int);
int c_fstouv(int, char*);
int c_fstluk(float*, int, int*, int*, int*);
int c_fstinf(int iun, int *ni, int *nj, int *nk, int datev,char *in_etiket, int ip1,int ip2,int ip3, char *in_typvar, char *in_nomvar);
int c_fstfrm(int);
int c_fclos(int);

int main() {

	int iun=10, ier;

	int ni,nj,nk,key,i,j;
	const int m1=-1; // a constant

	char *fname = "test.fst";
	char *nomvar = "o3_ ";

	int time=100; // ip2
	int layer = 1;
	int ip1 = 12001;

	//float *(*fld);
	float *fld;

	ier = c_fnom(iun, fname, "STD+RND", 1);
	if (ier<0) {
		printf("Could not open %s!\n", fname);
		return ier;
	}

	ier = c_fstouv(iun, " ");
	if (ier<0) {
		printf("Could not open %s!\n", fname);
		return ier;
	} else {
//		printf("%s open (with fstouv)!\n", fname);
	}

//	printf("Looking for %s at time=%d, layer=%d\n", nomvar, time, layer);
	key = c_fstinf(iun, &ni, &nj, &nk, m1," ", ip1, time, m1, " ", nomvar);

	/* Return ni,nj  Should be done be reference right now.. */
	if (key<0) {
		printf("Error, could not find key\n");
		return;
	}
	printf("nomvar=%s, ni=%d, nj=%d\n", nomvar, ni, nj);

	// Allocate a field
	//!fld = malloc(ni*nj*sizeof(float*));

	// Read the field pointed by the given key
	ier = c_fstluk(fld, key, &ni, &nj, &nk);

	/* Close the file */
	ier=c_fstfrm(iun);
	ier=c_fclos(iun);

	printf("\n");	
	for (i=0; i<ni; i++) {
		for (j=0; j<nj; j++) {
			// Values come transposed..
			printf("%15.6E", *(fld+(ni*j)+i));
			if (j<nj-1) printf(", ");
		}
		printf("\n");
	}
	printf("\nDone.\n");

	//!free(fld);
}

#include <stdio.h>
#include <stdlib.h>

/* Define page table as dynamic structure containing virtual page and page frame
   and initialize variable as pointer to structure */
	struct node {
		int vp =0;
		int pf = 0;
	} *pt = NULL;
	typedef struct node entry;
/* Declare global var's */

int  num_entries, page_size, mainmmemory_size, replacement_policy, i, pf, vp, a;

/**************************************************************/
void set_Parameters() {
/* Declare local var's */

/* Prompt for main memory size(for page frames), page size, and replacement policy */
printf("Please enter main memory size: \n");
scanf("%d", &mainmmemory_size);

printf("Please enter the page size: \n");
scanf("%d", &page_size);

printf("Please enter the replacement policy: (1=LRU, 0=FIFO): \n");
scanf("%d", &replacement_policy);

num_entries = mainmmemory_size/page_size;
/* Allocate and initialize page table based on number of entries */
    pt = (entry *) malloc (num_entries *sizeof(entry));
    /* initialize each VP to default value: for - loop*/
    for(a=0; a < 4; a++){
        pt[a].vp = -1;
        pt[a].pf = -1;
}
return;
}



/***************************************************************/
void mapping()
{
/* Declare local var's */
int virtual_add, real_add, VP, Offset, temporary_VP, temporary_pf;
int a,b,c;
/* Prompt for virtual address */
printf("Please enter the virtual address that you wish to access: \n");
scanf("%d", &virtual_add);

/* Translate virtual mem addr to virtual page and offset*/
VP = virtual_add/page_size;
Offset = virtual_add % page_size; //reference the slides

/* Check for end of table, unallocated entry, or matched entry in table
 while none of three cases, keep looping */
    for (a = 0; num_entries > a; a++) {
        if (pt[a].vp == vp) {
            real_add = (pt[a].pf * page_size) + Offset;

            if (replacement_policy == 0) {
                int put_pf,put_vp;
                for (b = a; b < num_entries - 1; b++) {
                    put_pf = pt[b].pf;
                    put_vp = pt[b].vp;
                    pt[b] = pt[b+1];
                    pt[b+1].pf = put_pf;
                    pt[b+1].vp = put_vp;
                }
            }
            printf("Virtual Address: %d Maps to Physical Address %d\n", virtual_add, real_add);
            a = num_entries - 1;
        }

        else if (pt[a].vp == -1) {
            pt[a].vp = vp;
            pt[a].pf = a;
            printf("Page Fault!\n");
            a = num_entries - 1;

        }

        else if (a == num_entries - 1) {
            pt[0].vp = vp;
            for (c = 0; c < num_entries - 1; c++) {
                temporary_pf = pt[c].pf;
                temporary_VP = pt[c].vp;
                pt[c] = pt[c+1];
                pt[c+1].pf = temporary_pf;
                pt[c+1].vp = temporary_VP;
            }
            printf("Page Fault!\n");
        }
    }
    return;

}
/* In case of end of table, replace either LRU or FIFO entry (top entry in page table), print message */

/* In case of unallocated entry, set entry according to virtual page and page frame, print message */

/* In case of hit in page table, calculate physical address and print message, update page table if LRU policy */



/***************************************************************/
void Table()
{
/* Declare local var's */
int j;
/* For each valid entry in page table */
	/* print virtual page number and corresponding page frame number */
	printf("============================= \n");
	printf("       VP ||    PF");
	printf("===============================\n");
	for(j = 0; num_entries > j; j++){
        if(pt[a].pf != -1 && pt[a].vp != -1){
            printf("%d", pt[a].vp);
            printf("%d", pt[a].pf);
            printf("\n----------------------\n");
        }
	}
	return;
}



/**************************************************************/
int main() {
/* Declare local var's */
    int option = 0;

/* Until user quits */
    /* print menu of options, prompt for user input, and select appropriate option */
    while (option != 4) {
        printf("\n\n");
        printf("Virtual Memory to Main Memory Map:");
        printf("\n\n");
        printf("1) Enter the parameters \n");
        printf("2) Map Virtual Address to Physical Address \n");
        printf("3) Print Page Table \n");
        printf("4) Quit\n");

        printf("\n");
        printf("Enter Selection: ");
        scanf("%d", &option);
        printf("\n");
        switch (option) {
            case 1: {
                set_Parameters();
                break;
            }
            case 2: {
                mapping();
                break;
            }
            case 3: {
                Table();
                break;
            }
            case 4: {
                printf("Quitting\n");
                break;

            }
            default:
                printf("Invalid. Try Again. \n");
        }//switch
    }

        return 1;
    }
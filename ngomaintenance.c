#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
struct member{
	char name[50];
	int age;
	int memId;
	int year;
}m;
long int size = sizeof(m);
FILE *fp,*ft;
int uniqueid(){
        struct member temp;
        int t,u=1;
		srand((unsigned int) time(0) + getpid());
		t=10000+(rand()%99999);
		srand(rand());
		rewind(fp);
		while (fread(&temp, size, 1, fp)){
		    if(temp.memId==t){
                u=0;
                break;
		    }
        }
        if(u==0){
            uniqueid();
        }
        return t;
}
void addmember(){
    system("cls");
    fseek(fp,0,SEEK_END);
	char repeat='Y';
    while (toupper(repeat)=='Y'){
	    printf("\nEnter Name : ");
	    fflush(stdin);
	    scanf("%s",m.name);
		printf("\nEnter Age : ");
		fflush(stdin);
		scanf("%d",&m.age);
		printf("\nEnter the year of joining: ");
		fflush(stdin);
		scanf("%d",&m.year);
		printf("\nWait for a minute......");
		printf("\nGenerating Member ID......");
		getch();
		printf("\nMember ID:");
        m.memId=uniqueid();
		printf("%d",m.memId);
		fseek(fp,0,SEEK_END);
		fwrite(&m,sizeof(m),1,fp);
		printf("\nWant to add another record (Y/N) : ");
		fflush(stdin);
		scanf("%c",&repeat);

	}
}
void viewmembers(){
	system("cls");
	rewind(fp);
	printf("\nMEMBER ID\t\tNAME\t\tAGE\t\tYEAR OF JOINING\n",m.memId,m.name,m.age,m.year);
	while (fread(&m, size, 1, fp) == 1){
		printf("\n%d\t\t\t%s\t\t%d\t\t %d",m.memId,m.name,m.age,m.year);
	}
	printf("\n\n\n\t");
	getch();
}
void removemember()
{
	system("cls");
	int memid,found=0;
	char repeat='Y';
	while (toupper(repeat)=='Y'){
		viewmembers();
        printf("\nEnter the Member ID to delete: ");
	    fflush(stdin);
	    scanf("%d",&memid);
	    ft = fopen("del.txt", "wb");
	    rewind(fp);
	    while (fread(&m, size,1, fp)== 1){
	        if (memid!=m.memId){
			    fwrite(&m, size, 1, ft);
		    }
		    else if (memid==m.memId){
		    	found=1;
			}
	    }
	    if (found==0){
	    	printf("No such entry found");
		}
	fclose(fp);
	fclose(ft);
	remove("members.txt");
	rename("del.txt","members.txt");
	fp=fopen("members.txt","rb+");
	printf("\nWant to delete another record (Y/N) :");
	fflush(stdin);
	scanf("%c",&repeat);
	}
}
void updatemember(){
	system("cls");
    int memid,found;
	char repeat='Y';
    while (toupper(repeat)=='Y'){
		found=0;
		printf("\nEnter Member ID to update: ");
		scanf("%d",&memid);
		rewind(fp);
		while (fread(&m, size, 1, fp)==1) {
		    if(memid==m.memId){
		    	printf("\nEnter the details to update:");
		    	printf("\nEnter Name : ");
				fflush(stdin);
	            scanf("%s",m.name);
		        printf("\nEnter Age : ");
		        fflush(stdin);
		        scanf("%d",&m.age);
	        	printf("\nEnter the year of joining: ");
		        fflush(stdin);
		        scanf("%d",&m.year);
				fseek(fp,-size,SEEK_CUR);
				fwrite(&m,size,1,fp);
				found=1;
				break;
			}
		}
		if(!found){
            printf("No such entry found");
		}
		printf("\nWant to update another record (Y/N) :");
		fflush(stdin);
		scanf("%c",&repeat);
	}
}
void searchmember(){
	system("cls");
	int memid,found;
	char repeat='Y';
	while (toupper(repeat)=='Y'){
		found=0;
        printf("\nEnter the Member ID to search: ");
	    fflush(stdin);
	    scanf("%d",&memid);
	    rewind(fp);
	    printf("\nMEMBER ID\t\tNAME\t\tAGE\t\tYEAR OF JOINING\n",m.memId,m.name,m.age,m.year);
	    while (fread(&m, size,1, fp)== 1){
	        if (memid==m.memId){
			    printf("\n%d\t\t\t%s\t\t%d\t\t %d\n",m.memId,m.name,m.age,m.year);
			    found=1;
			    break;
		    }
	    }
	    if (!found){
	    	printf("No such entry found");
		}
	printf("\nWant to search another record (Y/N) :");
	fflush(stdin);
	scanf("%c",&repeat);
	}
}
int main()
{
	int c;
	fp = fopen("members.txt","rb+");
	if (fp == NULL) {
		fp = fopen("members.txt","wb+");
		if (fp == NULL) {
			printf("\nCannot open file...");
			exit(1);
		}
	}
	printf("\n\n\n\n\n\n\t\t\t\t=====================================================");
	printf("\n\t\t\t\t||                                                 ||");
	printf("\n\n");
	printf("\n\t\t\t\t||          NGO MEMBERS LIST MAINTENANCE           ||");
	printf("\n\n");
	printf("\n\t\t\t\t||                                                 ||");
	printf("\n\t\t\t\t====================================================\n");
    getch();
	while (1) {
		system("cls");
		printf("\n1. Add Members\n");
		printf("\n2. View Members List\n");
		printf("\n3. Search Members\n");
		printf("\n4. Update Members\n");
		printf("\n5. Remove Members\n");
		printf("\n6. Close Application\n");
		printf("\nENTER YOUR CHOICE...\n");
		fflush(stdin);
		scanf("%d",&c);
		switch(c){
		case 1:
			addmember();
			break;
	    case 2:
	    	viewmembers();
			break;
		case 3:
		    searchmember();
			break;
		case 4:
			updatemember();
			break;
		case 5:
			removemember();
			break;
		case 6:
			fclose(fp);
			exit(0);
			break;
		default:
			printf("\nWrong Choice......\n");
			getch();
		}
	}

	return 0;
}

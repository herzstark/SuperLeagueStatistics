#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_WORDS 20

struct player{								//creating structure
	char name[MAX_WORDS];
	char surname[MAX_WORDS];
	int goal;
	int assist;
	int rc;
	int ps;
};

struct player *Load_Statistics_Table(char *file);			//Defining all the
void Display_Statistics_Table(struct player *adress);		//functions
int Search(struct player *adress,char search_For[]);
void No_Red_Card(struct player *adress);
void Player_With_Highest_Goal (struct player *adress);
void Storing_Statistics(struct player *adress,char *file);

int main(int argc,char *argv[]){     //main() using as a function
	int j=0;
	char isim[20];
	struct player *adress=NULL;
	adress=Load_Statistics_Table(argv[1]); //getting the first file

	if(adress!=NULL)
	{
		printf("Score records file has been successully loaded!\nFollowing records have been loaded\n");
		Display_Statistics_Table(adress);
		while(1)																													//Main loop
		{																															//For use functions.
			printf("Enter the name of the player (Exit - X, No Red Card - NR, Player with Highest Goal - G): ");
			scanf("%s",&isim);
			fflush(stdin);
			j=Search(adress,isim);
			if(!strcmp(isim,"x") || !strcmp(isim,"X"))
			{
				printf("Storing statistics.txt on exit with the following data:\nPlayer\t\tPS\tPassSuccessRate\n");
				Storing_Statistics(adress,argv[2]);  //getting the statistics.txt
				printf("Bye!");
				return EXIT_SUCCESS;
			}

			else if(!strcmp(isim,"nr") || !strcmp(isim,"NR"))
				No_Red_Card(adress);
			else if(!strcmp(isim,"g") || !strcmp(isim,"G"))
				Player_With_Highest_Goal(adress);
			else if(j >= 0)
				{
					printf("%s %s has %d goals, %d assist, %d red cards, %d successful passes.\n",(adress+j)->name,(adress+j)->surname,(adress+j)->goal,(adress+j)->assist,(adress+j)->rc,(adress+j)->ps);
				}
			else	printf("That player is unknown! Please try again!");
		}

	}
	else printf("File not found..."); //wrong condition

}

struct player *Load_Statistics_Table(char *file)
{
	int i=0;
	struct player *p1=NULL;
	FILE *players_txt=NULL;
	players_txt = fopen(file,"r");

	if(players_txt!=NULL)
	{
		p1 = ( struct player* ) malloc( sizeof(struct player)); 	//dynamic allocation
		while (!feof(players_txt))
		{
			fscanf(players_txt,"%s %s %d %d %d %d",&(p1+i)->name,&(p1+i)->surname,&(p1+i)->goal,&(p1+i)->assist,&(p1+i)->rc,&(p1+i)->ps); //scaning the file for its content
			i++;
			p1 = ( struct player* ) realloc(p1, (i+1)*sizeof(struct player)); //reallocaation
		}
		fclose(players_txt); //close the file
		p1[i].goal=-1;
	}
	else return NULL;

	return p1;
}

void Display_Statistics_Table(struct player *adress)
{
	int j=0;
	while (adress[j].goal!=-1)
	{
		printf("%s %s %d %d %d %d\n",(adress+j)->name,(adress+j)->surname,(adress+j)->goal,(adress+j)->assist,(adress+j)->rc,(adress+j)->ps); //printing condition
		j++;
	}
	return ;
}

int Search(struct player *adress,char search_For[])
{
	int j=0;
	while (adress[j].goal!=-1)
	{
		if(!strcmp((adress+j)->name,search_For))
			return j;
		j++;
	}
	return -1;
}
void No_Red_Card(struct player *adress)
{
	int j=0;
	while (adress[j].goal!=-1)
	{
		if((adress+j)->rc==0)
			printf("%s %s \n",(adress+j)->name,(adress+j)->surname);	//red card condition
		j++;
	}

	return;
}

void Player_With_Highest_Goal (struct player *adress)
{
	int j=0,max,point;
	max=adress[0].goal;
	while (adress[j].goal!=-1)
	{
		if(max < adress[j].goal)
		{
			max = adress[j].goal;
			point=j;
		}
		j++;
	}
	printf("%s %s! He has %d goals.\n",(adress+point)->name,(adress+point)->surname,(adress+point)->goal);
	return ;
}

void Storing_Statistics(struct player *adress,char *file)
{
	FILE *statistiscs_txt=NULL;
	statistiscs_txt=fopen(file,"w"); //write statistic_txt
	int j=0;
	while (adress[j].goal!=-1)
	{
		printf("%s %s \t%d \t%d\n",(adress+j)->name,(adress+j)->surname,(adress+j)->ps,((adress+j)->ps)*5);
		fprintf(statistiscs_txt,"%s %s %d %d\n",(adress+j)->name,(adress+j)->surname,(adress+j)->ps,((adress+j)->ps)*5);
		j++;
	}
	fclose(statistiscs_txt); //close the file
	return ;
}

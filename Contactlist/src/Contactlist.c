#include "stdio.h"
#include "stdlib.h"
#include "sys/uio.h"
#include "string.h"
#define getch() getpass("")
void ViewList(int iCurpage);
void ViewData(int iCount);
void ClearScreen();
struct contacts
{
	char cNameBuf[50];
	char cTelBuf[80];
	char cOfficTelBuf[80];
	char cHomeTelBuf[80];
	char cQQNumber[60];
	char cAddress[128];
};

char TitleText[]="*  Simple contactbook  *\0";

char MenuText[6][28]={
"1. Add contacts\0",
"2. Search Number\0",
"3. contacts List\0",
"4. contacts Data\0",
"5. Delete contacts\0",
"6. Exit System\0"};

char InputTip[6][30]={
"Input Name:\0",
"Input Telephone:\0",
"Input Office Number:\0",
"Input Home Number:\0",
"Input QQ Number:\0",
"Input Address:\0"};

char CheckTip[]={"Number is Empty£¬Please Retry\0"};

char SearchText[6][30]={
"Name:\0",
"Telephone:\0",
"Office Number:\0",
"Home Number:\0",
"QQ Number:\0",
"Address:\0"
};
char InputTelTip[]="Please input the number\0";

char ListTitle[7][30]={
"Index\0",
"Name\0",
"Telephone\0",
"Office Number\0",
"Home Number\0",
"QQ Number\0",
"Address\0"};

char ViewText[6][30]={
"Name:\0",
"Telephone:\0",
"Office Number:\0",
"Home Number:\0",
"QQ Number:\0",
"Address:\0"};

char DeleteTip[]="Please Input Delete Data Index?\0";

char PageInductText[4][128]={
"Press '1' Show Next page,any key return\0",
"Press '2' Show Previous page,Press '1' Show Next page,any key return\0",
"Press '2' Show Previous page,any key return\0",
"any key return\0"};

char DataInductText[4][128]={
"Press '1' Show Next data,any key return\0",
"Press '2' Show Previous data,Press '1' Show Next data,any key return\0",
"Press '2' Show Previous data,any key return\0",
"any key return\0"};

void ShowWelcome(){ //welcome page
	printf("**************************\n");
	printf("*                        *\n");
	printf("%s\n",TitleText);
	printf("*                        *\n");
	printf("**************************\n");
}

void ClearScreen(){
system("clear");
}

void ShowRootMenu(){ //print out Menu
	int i;
	printf("Choose:\n");
	for(i=0;i<6;i++){
		printf("%s\n",MenuText[i]);
	}
}

int GetFileDataCount(){//count how many contacts saved
	FILE *file;
	int iFileLenth=0;
	file=fopen("contacts.dat","r"); //reading
	if(file!=NULL)
	{
		fseek(file,0,SEEK_END);//setting offset to end
		iFileLenth=ftell(file);//return file postion
		fclose(file);
		return iFileLenth/sizeof(struct contacts);
	}
	else
		return 0;
}

void ListWaitUser(int iCurpage){ //allow usr to flip pages
	int iKey;
	int iPkey=0;
	int iNkey=0;
	int iDataTotalPage;
	int iDataTotalCount;
	iDataTotalCount=GetFileDataCount();
	if(iDataTotalCount==0)
		iDataTotalPage=0;
	else
		iDataTotalPage=iDataTotalCount/20+1;

	if(iCurpage==1 && iCurpage>1)
	{
		printf("%s\n",PageInductText[0]);
		iNkey=1;iPkey=0;
	}
	else if(iCurpage>1 && iCurpage<iDataTotalPage)
	{
		printf("%s\n",PageInductText[1]);
		iNkey=1;iPkey=1;
	}
	else if(iCurpage==iDataTotalPage && iCurpage>1)
	{
		printf("%s\n",PageInductText[2]);
		iNkey=0;iPkey=1;
	}
	else
	{
		printf("%s\n",PageInductText[3]);
	}
	scanf("%d",&iKey);
	if(iKey==2 && iPkey==1)
		ViewList(--iCurpage);
	if(iKey==1&& iNkey==1)
		ViewList(++iCurpage);
}


void DataWaitUser(int iCurData){//allow usr to see previous or next data
	int iDataTotalCount;
	int iKey;
	int iPkey=0;
	int iNkey=0;
	iDataTotalCount=GetFileDataCount();
	if(iCurData==1 && iDataTotalCount>1)
	{
		printf("%s\n",DataInductText[0]);
		iNkey=1;iPkey=0;
	}
	else if(iCurData>1 && iCurData< iDataTotalCount)
	{
		printf("%s\n",DataInductText[1]);
		iNkey=1;iPkey=1;
	}
	else if(iCurData==iDataTotalCount && iDataTotalCount>1)
	{
		printf("%s\n",DataInductText[2]);
		iNkey=0;iPkey=1;
	}
	else
	{
		printf("%s\n",DataInductText[3]);
		iNkey=0;iPkey=0;
	}
	scanf("%d",&iKey);
	if(iKey==2 && iPkey==1)
		ViewData(--iCurData);
	if(iKey==1 && iNkey==1)
		ViewData(++iCurData);
}	

int GetSelect(){
	int iSel;
	scanf("%d",&iSel);
	if(iSel<0 && iSel>5){
		printf("Input Error!!!!\n");
		return 0;
	}
	else
		return iSel;
}

int CheckInput(char *buffer){ //check if buffer is empty
	if(buffer[0]=='\0')
		return 0;
	if(strlen(buffer)<=0)
		return 0;
	return 1;
}

void SavecontactsToFile(struct contacts* pcontacts)
{
	FILE *file;
	file=fopen("contacts.dat","a"); //apend mode
	fwrite(pcontacts,1,sizeof(struct contacts),file);
	fclose(file);
	printf("Save Sucess!!!\n");
}


void InputData(struct contacts* pcontacts) //let user input data one by one and put into contact struct
{
	int iInputCount=200;
	printf("%s\n",InputTip[0]);
	scanf("%s",pcontacts->cNameBuf);
	if(!CheckInput(pcontacts->cNameBuf))
		strcpy(pcontacts->cNameBuf,"NoName");
	printf("%s\n",InputTip[1]);
	scanf("%s",pcontacts->cTelBuf);
	while(!CheckInput(pcontacts->cTelBuf))
	{
		printf("%s\n",CheckTip);
		scanf("%s",pcontacts->cTelBuf);
		iInputCount--;
		if(iInputCount<0)
			return;
	}
	printf("%s\n",InputTip[2]);
	scanf("%s",pcontacts->cOfficTelBuf);
	printf("%s\n",InputTip[3]);
	scanf("%s",pcontacts->cHomeTelBuf);
	printf("%s\n",InputTip[4]);
	scanf("%s",pcontacts->cQQNumber);
	printf("%s\n",InputTip[5]);
	scanf("%s",pcontacts->cAddress);
}


void Addcontacts(){
	struct contacts contacts;
	int bContinue=1;
	int iSel;
	memset(&contacts,0,sizeof(contacts));//clear buffer
	InputData(&contacts);
	SavecontactsToFile(&contacts);
	while(bContinue) { //allow user to enter more
		printf("Add new contacts press '1',press '2' return\n");
		scanf("%d",&iSel);
		if(iSel==1)
		{
			ClearScreen();
			memset(&contacts,0,sizeof(contacts));//clear buffer
			InputData(&contacts);
			SavecontactsToFile(&contacts);
		}
		else if(iSel==2 )
		{
			bContinue=0;
		}
	}
}

void SearchNumber()
{
	char cTelNumber[10];
	FILE *file;
	int iDataTotalCount;
	struct contacts contacts;
	int iPos;
	int i;
	int found=0;
	printf("%s\n",InputTelTip);
	scanf("%s",cTelNumber);
	iDataTotalCount=GetFileDataCount();
	file=fopen("contacts.dat","r");
	for(i=0;i<iDataTotalCount;i++)
	{
		printf("%d",iDataTotalCount);
		iPos=sizeof(struct contacts)*i;
		fseek(file,iPos,SEEK_SET);
		fread(&contacts,sizeof(struct contacts),1,file);
		if(strcmp(cTelNumber,contacts.cHomeTelBuf)==0)
		{
			found=1;
			printf("%s",SearchText[0]);
			printf("%s\n",contacts.cNameBuf);
			printf("%s",SearchText[1]);
			printf("%s\n",contacts.cTelBuf);
			printf("%s",SearchText[2]);
			printf("%s\n",contacts.cOfficTelBuf);
			printf("%s",SearchText[3]);
			printf("%s\n",contacts.cHomeTelBuf);
			printf("%s",SearchText[4]);
			printf("%s\n",contacts.cQQNumber);
			printf("%s",SearchText[5]);
			printf("%s\n",contacts.cAddress);
			getch();
			break;
		}
	}
	if(!found) printf("Not Found\n");
	getch();
	fclose(file);
}


void ViewList(int iCurpage)
{
	FILE *file;
	int i;
	struct contacts contacts;	
	int iDataTotalPage;
	int iDataTotalCount;
	int iDataCountPerPage;
	int iPos;
	int j;
	ClearScreen();
	iDataCountPerPage=20;
	iDataTotalCount=GetFileDataCount();
	if(iDataTotalCount==0)
		iDataTotalPage=0;
	else
		iDataTotalPage=iDataTotalCount/20+1; //compute page number
	
	if(iCurpage==iDataTotalPage)//last page exception
		iDataCountPerPage=iDataTotalCount%20;
	file=fopen("contacts.dat","r");
	for(j=0;j<6;j++)
	{
		printf("%s   ",ListTitle[j]);
	}
	printf("%s   \n",ListTitle[6]);

	if(iDataTotalPage>0)
	{
		if(iCurpage>0 && iCurpage<=iDataTotalPage)
		{
			for(i=0;i<iDataCountPerPage;i++)
			{
				memset(&contacts,0,sizeof(struct contacts)); //clear buffer
				iPos=sizeof(struct contacts)*((iCurpage-1)*20+i); //The contact showing right now
				fseek(file,iPos,SEEK_SET);
				fread(&contacts,sizeof(struct contacts),1,file);
				printf("%d   ",(iCurpage-1)*20+(i+1));
				printf("%s   ",contacts.cNameBuf);
				printf("%s   ",contacts.cTelBuf);
				printf("%s   ",contacts.cOfficTelBuf);
				printf("%s   ",contacts.cHomeTelBuf);
				printf("%s   ",contacts.cQQNumber);
				printf("%s   \n",contacts.cAddress);
			}
			ListWaitUser(iCurpage);
		}
	}
	else{
		printf("Press Enter return...");
		getch();
	}
		if(file!=NULL)
		fclose(file);
}

void ViewData(int iCount){
	struct contacts contacts;
	FILE *file;
	ClearScreen();
	file=fopen("contacts.dat","r");
	if(file!=NULL){
		fseek(file,sizeof(struct contacts)*(iCount-1),SEEK_SET);//redirect offset to the data we are looking for
		fread(&contacts,sizeof(struct contacts),1,file);//get the struct
		printf("%s",ViewText[0]); //printing its data
		printf("%s\n",contacts.cNameBuf);
		printf("%s",ViewText[1]);
		printf("%s\n",contacts.cTelBuf);
		printf("%s",ViewText[2]);
		printf("%s\n",contacts.cOfficTelBuf);
		printf("%s",ViewText[3]);
		printf("%s\n",contacts.cHomeTelBuf);
		printf("%s",ViewText[4]);
		printf("%s\n",contacts.cQQNumber);
		printf("%s",ViewText[5]);
		printf("%s\n",contacts.cAddress);
		fclose(file);
		DataWaitUser(iCount);
	}
	else{//file can't be opened
		printf("Press Enter return...");
		getch();//getpass
	}
}

void DeleteData(){
	FILE *file;
	int iIndex;
	int iDataTotalCount;
	int iPos;
	int i;
	struct contacts contacts;
	char buf[478];
	buf[0]='\0';
	printf("%s",DeleteTip);
	scanf("%d",&iIndex);//iIndex-1=delated data position
	iDataTotalCount=GetFileDataCount();
	if(iIndex<=0 || iIndex > iDataTotalCount){
		printf("Data Not Exist ,return main menu\n");
		getch();
		return;
	}
	file=fopen("contacts.dat","r+");
	for(i=0;i<(iDataTotalCount-1);i++){ //iterate through all data
		memset(&contacts,0,sizeof(struct contacts));
		iPos=sizeof(struct contacts)*(iIndex+i);
		fseek(file,iPos,SEEK_SET);
		fread(&contacts,sizeof(struct contacts),1,file);//retrive that contact
		iPos=sizeof(struct contacts)*(iIndex+i-1);
		fseek(file,iPos,SEEK_SET);
		fwrite(&contacts,1,sizeof(struct contacts),file);//move it foward,the first run will overwrite the deleted data
	}
	fclose(file);
}

void mainloop()
{
	ClearScreen();
	ShowWelcome();
	getch();
	while(1)
	{
		ClearScreen();
		ShowRootMenu();
		switch(GetSelect())
		{
		case 1:
			ClearScreen();
			Addcontacts();
			break;
		case 2:
			ClearScreen();
			SearchNumber();
			break;
		case 3:
			ViewList(1);
			break;
		case 4:
			ViewData(1);
			break;
		case 5:
			DeleteData();
			break;
		case 6:
			exit(0);
			break;
		}
	}
}

int main()
{
	mainloop();
	return 0;
}

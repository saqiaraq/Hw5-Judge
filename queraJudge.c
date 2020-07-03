#include<stdlib.h>
#include <stdio.h>
#include <string.h>

//This file gets another program and its type with the input and output folder and gives you a grade
//***NOTE***
//both the program and the input output folder should be in the same folder as this program
//also input output folders should be sth like this:
//a folder for exp  named testcases wich hase a foler named input and a seperate folder named output 


// has 3 functions
int judge(const char [],const char [],const char [],const char []);
int inputFile(char []);
void inputInput(char [], char [],const char []);
void empty(char[]);


//gets two strings compares them
//(gets the output and the output of the entered program)
//1 for = and 0 for !=
int judge(const char answer[], const char keys[], const char adressFile[], const char adad[]) {
	char ans[200] = { "" }, key[200] = { "" }, temp[200] = { "" };
	strcpy(ans, adressFile);
	strcat(ans, "\\");
	strcat(ans, answer);
	for (int i = 0; answer[i] != '\\'; i++)
		temp[i] = answer[i];
	strcpy(key, adressFile);
	strcat(key, "\\");
	strcat(key, temp);
	strcat(key, "\\out\\output");
	strcat(key, adad);
	FILE *fAns, *fKey;
	int chAns, chKey;


	//fAns = fopen("D:\\alireza\\emt3003\\q1\\ProjectQ1\\test\\output1.txt", "r");
	//fKey = fopen("D:\\alireza\\emt3003\\q1\\ProjectQ1\\test\\output20.txt", "r");

	fAns = fopen(ans, "r");
	fKey = fopen(key, "r");

	chAns = getc(fAns);
	chKey = getc(fKey);
	while ((chAns != EOF) && (chKey != EOF) && (chAns == chKey)) {
		chAns = getc(fAns);
		chKey = getc(fKey);
	}
	int ret = 0;
	if (chAns == chKey)
		ret = 1;
	else if (chAns != chKey)
		ret = 0;
	fclose(fAns);
	fclose(fKey);
	return ret;
}



//this function gets an input for the adress of the program
//and compiles the program
//1 for succesfull compile and 0 for unsuccesfull
int inputFile(char srcfile[]) {


	/*
	in order to compile a file these are the strings you need

	1. a gcc compile string with the adress of the file and in the below exp form
	//"gcc programname.formatoftheprogram -o programname.exe"

	char test[1000]={"gcc Project1.c -o ProjectQ1.exe"};

	2.an if for the results and you have to pass it to the system function

	if(system(test)!=0)printf("not succesfull");
	else printf("succesfull");
	*/


	char komaki[100] = { "" };
	printf("***NOTE***\nPLEASE put the source file in the same folder as the program(queraJudge)\n");
	printf("Please enter the name of the source file: \n");
	scanf("%s", srcfile);
	printf("Please enter the format of the source file(.cpp/.c): \n");
	scanf("%s", komaki);

	strcat(srcfile, komaki);
	char srcAdress[500] = { "gcc " }, temp[100] = { "" };
	strcat(srcAdress, srcfile);
	strcat(srcAdress, " -o ");
	strncpy(temp, srcfile, strlen(srcfile) - strlen(komaki));
	strcat(srcAdress, temp);
	strcat(srcAdress, ".exe");
	if (system(srcAdress) != 0) {
		printf("\n**ERROR**\nCOMPILING FAILED\nThere was a COMPILING ERROR\n\n");
		return 0;
	}
	else {
		printf("COMPILE SUCCESFULL\n\n");
		return 1;
	}
}


//this function gets the folder for input and outputs
//makes the outputs
//then sends each output of the program and
//the judge output related to the other output to
//the ***judge*** function
void inputInput(char srcFile[], char asli[], const char adres[]) {
	printf("***NOTE***\nPLEASE put the input folder in the same folder as the program(queraJudge)\n");
	char temp[200], temp2[200], khali[200] = { "<" }, infile[200] = { "in\\input" }, outfile[200] = { "output" };
	printf("Please enter the name of the folder for input files: \n");
	scanf("%s", temp);

	//the name of the testcase folder

	strcat(temp, "\\");
	strcpy(temp2, temp);
	char fold[200];
	printf("Please enter the name of the folder you want me to put the outputs: \n");
	scanf("%s", fold);

	// the name of the folder you want to put the output of your program

	strcat(temp2, fold);
	strcat(temp, infile);

	//here we make the folder for the outputs

	char mkdir[200] = { "mkdir " };
	strcat(mkdir, asli);
	strcat(mkdir, "\\");
	strcat(mkdir, temp2);
	system(mkdir);
	strcat(temp2, "\\");
	strcat(temp2, outfile);
	strcpy(outfile, temp2);
	strcpy(infile, temp);
	strcat(asli, "\\");
	strcat(asli, srcFile);

	int i, count;
	printf("Please enter the start and the finish of inputs:\nFor Example 1 5\nstarts from 1 and finishes at 5 \n");
	scanf("%d %d", &i, &count);
	char mem1[200] = { "" }, mem2[200] = { "" };
	strcpy(mem1, infile);
	strcpy(mem2, outfile);
	strcat(asli, " ");
	strcpy(temp2, asli);
	int ans, sumans = 0, ff = 0, fff = 0;
	ff=i;
	for (; i <= count; i++) {
		strcpy(asli, temp2);
		strcpy(infile, mem1);
		strcpy(outfile, mem2);
		strcpy(khali, "<");
		sprintf(temp, "%d.txt", i);
		strcat(infile, temp);
		strcat(outfile, temp);
		strcat(khali, infile);
		strcat(khali, "> ");
		strcat(khali, outfile);
		strcat(asli, khali);

		//here is what you sould pass to system function for exp
		//system(programadress <inputadress> where,you,want,to,put,the,output");
		//system("D:\\alireza\\emt3003\\q1\\ProjectQ1\\test\\ProjectQ1.exe <p\\in\\input1.txt > p\\ol\\output1.txt");

		if (system(asli) != 0) {
			printf("***ERROR***\nYOU DONT HAVE TESTCASE NUMBER %d\n", i - 1);
			fff++;
			continue;
		}

		//passes each output of the program and the judge output to ***judge*** function
		//with the adress of them
		if (ans = judge(outfile, infile, adres, temp)) {
			printf("test case %d\t TRUE\t T\n", i);
		}
		else {
			printf("test case %d\t FALSE\t F\n", i);
		}
		sumans = ans + sumans;
		/*
		if(ff==0){
		if(system(asli)!=0){
		if(ff==0)
		printf("***ERROR***\nYOU ONLY HAVE %d TESTCASES\n",i-1);
		ff++;
		fff++;
		continue;
		}
		if (ans = judge(outfile, infile,adres,temp)) {
		printf("test case %d\t TRUE\n", i);
		}
		else {
		printf("testcase %d\t FALSE\n",i);
		}
		sumans = ans + sumans;
		}*/
	}
	if (fff)
		printf("Please make sure to enter the right amount of testcases next time :)))\n");
	printf("\n\nTRUE testcases:\t%d\nFALSE testcases:\t%d\nTOTAL testcases:\t%d\n", sumans, count - sumans - fff-ff+1, count - fff-ff+1);
}

//gets a string and makes the string null
void empty(char str[]) {
	for (int i = 0; str[i] != '\0'; i++)
		str[i] = '\0';
}

int main() {
	int y;
	char srcfile[200] = { "" }, asli[200] = { "" };
	char adres[200] = { "" };
	char temp[200] = { "" };
	int flag = 0;
	int brk = 1;
	printf("\n*****************WELCOME*****************\n\n\n\n***NOTE***\nThis program is designed to get a program and some testcases(inputs and outputs)\nThen make the outputs of the program based on the inputs given \nand put them in a given place\nThen compare each output and give a grade\n#Quera_Judge\n\n\n");
	for (y = strlen(__FILE__); __FILE__[y] != '\\'; y--);
	char tempfile[200];
	strcpy(tempfile, __FILE__);
	while (1) {

		//this part we make the adress for compiling

		strncpy(asli, tempfile , y);
		strcpy(adres, asli);
		while (inputFile(srcfile) != 1);

		//here the compiling is finished
		//then we make a string for making of the testcases

		for (flag = strlen(srcfile); srcfile[flag] != '.'; flag--);
		strncpy(temp, srcfile, flag);
		strcat(temp, ".exe");
		inputInput(temp, asli, adres);
		printf("Do you want to test another program?(1/0)\n");
		scanf("%d", &brk);
		if (brk == 1) {

			//if you want to continue we make each string empty again

			//strcpy(adres, "");
			empty(adres);
			empty(srcfile);
			empty(asli);
			empty(temp);
			//strcpy(srcfile, "");
			//strcpy(asli, "");
			//strcpy(temp, "");
			brk = 1;
			flag = 0;
		}
		else {
			break;
		}
	}
	printf("\n\n\n\n*****************GOODBYE*****************\n\n\n\n");
	return 0;
}

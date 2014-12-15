/*1426107	syouta hirama		*
*ロボットプログラミング 課題	*
*アドレス帳						*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>	//srand()のシード値生成のため
#include <string.h>
#include <Windows.h>	//Sleep()のため
#include <ctype.h>	//名前の頭文字を大文字に変換するため
#include <conio.h>

#define ARRAY_SIZE 256	//配列のサイズを指定
#define ENTER 0x0D
#define BACKSPACE 0x08

//デフォルト関数
void new_addres( );
void read_addres( );
void serch_addres(char strserch[ARRAY_SIZE]);
void edit_addres( );
void delete_addres( );
void game();
void help(char modestr[ARRAY_SIZE]);
void fortune( );
char* strget(char *str, int len);
char* passinput(char* pass);
void configfile();
void option();

FILE *file;
FILE *config;

const char filename[] = "addres.addres";	//ファイル名の指定
char passinit[ARRAY_SIZE];
char pass[ARRAY_SIZE];

struct person
{
	char name[ARRAY_SIZE];
	long number;
	long phone1;
	long phone2;
};

int main(void)
{
	int passlimit = 0;
	char password[ARRAY_SIZE];
	char *user = getenv("USERNAME");	//コンピュータ名の表示のために環境変数を取得
	char mode[ARRAY_SIZE];
	configfile();

	printf("Hello, %s\n", user);	//コンピュータ名の表示

	help(mode);	//モード一覧の表示
	printf("\n");

	if (strcmp(passinit, "TRUE") == 0){
		while (passlimit < 3){
			passinput(password);
			if (strcmp(pass, password) == 0){
				passlimit = 3;
				printf("\n");
			}
			else{
				printf("Password error\n");
				++passlimit;
				if (passlimit == 3){
					printf("3 times miss!!\nProgram fin...\n");
				}
			}
		}
	}
	else{
		strcpy(password, pass);
	}

	if (strcmp(password, pass) == 0){
		while (strcmp(mode, "end") != 0)	//"end"が入力されるまで続ける
		{

			memset(mode, '\0', sizeof mode);	//mode配列を初期化
			file = fopen(filename, "a+");	//追加書き込みモードでファイルを開く
			printf("mode select >");
			strget(mode, sizeof mode);

			if (strncmp(mode, "new", 3) == 0)
			{
				if (strcmp(mode, "new") == 0) new_addres();
				else if (strcmp(mode, "new -h") == 0) help("help new");
			}
			else if (strncmp(mode, "read", 4) == 0)
			{
				if (strcmp(mode, "read") == 0) read_addres();
				else if (strcmp(mode, "read -h") == 0) help("help read");
			}
			else if (strncmp(mode, "serch", 5) == 0)
			{
				if (strcmp(mode, "serch -h") == 0) help("help serch");
				else if (strncmp(mode, "serch", 5) == 0) serch_addres(mode);
			}
			else if (strncmp(mode, "edit", 4) == 0)
			{
				if (strcmp(mode, "edit") == 0) edit_addres(mode);
				else if (strcmp(mode, "edit -h") == 0) help("help edit");
			}
			else if (strncmp(mode, "delete", 6) == 0)
			{
				if (strcmp(mode, "delete") == 0) delete_addres();
				else if (strcmp(mode, "delete -h") == 0) help("help delete");
			}
			else if (strncmp(mode, "game", 4) == 0)
			{
				if (strcmp(mode, "game") == 0) game();
				else if (strcmp(mode, "game -h") == 0) help("help game");
			}
			else if (strcmp(mode, "end") == 0);
			else if (strncmp(mode, "help", 4) == 0) help(mode);
			else if (strcmp(mode, "cls") == 0) system("cls");	//画面のクリア
			else if (strcmp(mode, "date") == 0) system("date /T");	//日付表示
			else if (strcmp(mode, "time") == 0) system("time /T");	//時間表示
			else if (strcmp(mode, "now") == 0)	//日付と時間の表示
			{
				system("date /T");
				system("time /T");
			}
			else if (strcmp(mode, "fortune") == 0) fortune();	//占い機能
			else if (strncmp(mode, "option", 6) == 0){
				if (strcmp(mode, "option") == 0) option();
				else if (strcmp(mode, "option -h") == 0) help("help option");
			}
			else printf("mode error\n");

			if (file != NULL) fclose(file);	//ファイルのクローズ

			fflush(stdin);	//バッファ捨て

		}
	}

	return 0;
}

void new_addres( )	//アドレス登録関数
{

	char answer[ARRAY_SIZE];	//返答用

	struct person student;	//構造体をstudent名で呼び出し

	//学番入力
	printf("student number >");
	scanf("%07ld", &student.number);
	//名前入力
	printf("name >");
	strget(student.name, sizeof student.name);
	//電話番号入力
	printf("phonenumber >");
	scanf("%03ld%ld", &student.phone1, &student.phone2);
	//登録するかどうかの質問
	printf("Would you like to register?(yes/no) >");
	strget(answer, sizeof answer);

	if (strcmp(answer, "yes") == 0||strcmp(answer,"y")==0)	//yesだった場合
	{
		//学番と名前の書き出し
		fprintf(file, "%07ld %s ", student.number, student.name);
		if (student.phone1 == 70 || student.phone1 == 80 || student.phone1 == 90)	//携帯番号だった場合
		{
			fprintf(file, "%03ld%08ld\n", student.phone1, student.phone2);
		}
		else
		{
			fprintf(file, "%03ld%07ld\n", student.phone1, student.phone2);
		}
		//登録したアドレス表示
		printf("\n%07ld %s ", student.number, student.name);
		if (student.phone1 == 70 || student.phone1 == 80 || student.phone1 == 90)
		{
			printf("%03ld%08ld\n", student.phone1, student.phone2);
		}
		else
		{
			printf("%03ld%07ld\n", student.phone1, student.phone2);
		}
		printf("Register this addres\n");

	}
	//noだった場合
	else
	{
		printf("\n");
		printf("Not register\n");
	}

	printf("\n");

}

void read_addres( )	//アドレス帳の呼び出し
{

	int i = 1;	//行表示
	int spacelen;	//名前と電話番号の間の空白数

	struct person input;	//構造体をinput名で呼び出し

	printf("\n");
	//最後まで読み込む
	while (fscanf(file, "%ld %s %03ld%ld", &input.number, input.name, &input.phone1, &input.phone2) != EOF)
	{
		printf("%d：\t学番：%07ld 名前：%s", i++, input.number, input.name);
		//空白を揃える
		for (spacelen = 0; spacelen < (20 - strlen(input.name)); ++spacelen)
		{
			printf(" ");
		}
		if (input.phone1 == 70 || input.phone1 == 80 || input.phone1 == 90)	//携帯番号だった場合
		{
			printf("電話番号：%03ld%08ld\n", input.phone1, input.phone2);
		}
		else
		{
			printf("電話番号：%03ld%07ld\n", input.phone1, input.phone2);
		}
	}
	printf("\n");
}

void serch_addres(char strserch[ARRAY_SIZE])	//アドレスの検索
{
	struct person input;	//構造体をinput名で呼び出し

	int i = 1;	//行数
	int str1;	//文字分解のため
	int str2 = 0;	//文字分解のため
	int spacelen;	//空白用
	char serch[ARRAY_SIZE];	//検索文字列
	char number[ARRAY_SIZE];	//読み込んだ学番を文字列に
	char phone1[ARRAY_SIZE];	//読み込んだ電話番号を文字列に
	char phone2[ARRAY_SIZE];	//読み込んだ電話番号を文字列に
	char serch_select[ARRAY_SIZE];	//検索モード用

	memset(serch_select, '\0', sizeof serch_select);	//serch_select配列の初期化
	memset(serch, '\0', sizeof serch);	//serch配列の初期化

	//search+文字列だった場合
	if (strncmp(strserch, "serch ", 6) == 0)
	{
		if (strncmp(strserch, "serch studentnumber ", 20) == 0)	//学番検索
		{
			for (str1 = 20; str1 <= strlen(strserch); ++str1)
			{
				serch[str2++] = strserch[str1];	//検索したい学番だけ入れる
			}
			serch[str2] = '\0';	//最後にnullを代入
			strncpy(serch_select, "studentnumber", 13);
		}
		else if (strncmp(strserch, "serch name ", 11) == 0)	//名前検索
		{
			for (str1 = 11; str1 <= strlen(strserch); ++str1)
			{
				serch[str2++] = strserch[str1];	//検索したい学番だけ入れる
			}
			serch[str2] = '\0';	//最後にnullを代入
			strncpy(serch_select, "name", 4);
		}
		else if (strncmp(strserch, "serch phonenumber ", 18) == 0)	//電話番号検索
		{
			for (str1 = 18; str1 <= strlen(strserch); ++str1)
			{
				serch[str2++] = strserch[str1];	//検索したい電話番号だけ入れる
			}
			serch[str2] = '\0';	//最後にnullを代入
			strncpy(serch_select, "phonenumber", 12);
		}
		else
		{
			for (str1 = 6; str1 <= strlen(strserch); ++str1)
			{
				serch[str2++] = strserch[str1];	//検索したい文字列だけ代入
			}
			serch[str2] = '\0';	//最後にnullを代入
			strncpy(serch_select, "all", 3);
		}
	}
	else
	{
		printf("\n");
		printf("What do you want to serch? >");	//検索したいモード(?)を入力

		strget(serch_select, sizeof serch_select);

		if (strcmp(serch_select, "studentnumber") == 0) strcpy(strserch, "serch studentnumber ");
		else if (strcmp(serch_select, "name") == 0) strcpy(strserch, "serch name ");
		else if (strcmp(serch_select, "phonenumber") == 0) strcpy(strserch, "serch phonenumber ");
		else
		{
			strcpy(serch_select, "all");
			strcpy(strserch, "all");
		}
		printf("Input serch strings >");	//検索したい文字列を入力

		strget(serch_select, sizeof serch_select);

		printf("\n");
	}

	printf("serch mode >\"%s\"\n", serch_select);
	printf("serch >\"%s\"\n", serch);
	printf("\n");
	while (fscanf(file, "%ld %s %03ld%ld", &input.number, input.name, &input.phone1, &input.phone2) != EOF)
	{
		sprintf(number, "%07ld", input.number);
		sprintf(phone1, "%03ld", input.phone1);
		if (input.phone1 == 70 || input.phone1 == 80 || input.phone1 == 90)
		{
			sprintf(phone2, "%08ld", input.phone2);
		}
		else
		{
			sprintf(phone2, "%07ld", input.phone2);
		}
		strcat(phone1, phone2);

		if (strncmp(strserch, "serch studentnumber ", 20) == 0)
		{
			if (strstr(number, serch) != NULL)
			{
				printf("%d：\t学番：%07ld 名前：%s", i, input.number, input.name);
				for (spacelen = 0; spacelen < (20 - strlen(input.name)); ++spacelen)
				{
					printf(" ");
				}
				printf(" 電話番号：");
				if (input.phone1 == 70 || input.phone1 == 80 || input.phone1 == 90)
				{
					printf("%03ld%08ld\n", input.phone1, input.phone2);
				}
				else
				{
					printf("%03ld%07ld\n", input.phone1, input.phone2);
				}
			}
		}
		else if (strncmp(strserch, "serch name ", 11) == 0)
		{
			if (strstr(input.name, serch) != NULL)
			{
				printf("%d：\t学番：%07ld 名前：%s", i, input.number, input.name);
				for (spacelen = 0; spacelen < (20 - strlen(input.name)); ++spacelen)
				{
					printf(" ");
				}
				printf(" 電話番号：");
				if (input.phone1 == 70 || input.phone1 == 80 || input.phone1 == 90)
				{
					printf("%03ld%08ld\n", input.phone1, input.phone2);
				}
				else
				{
					printf("%03ld%07ld\n", input.phone1, input.phone2);
				}
			}
		}
		else if (strncmp(strserch, "serch phonenumber ", 18) == 0)
		{
			if (strstr(phone1, serch) != NULL)
			{
				printf("%d：\t学番：%07ld 名前：%s", i, input.number, input.name);
				for (spacelen = 0; spacelen < (20 - strlen(input.name)); ++spacelen)
				{
					printf(" ");
				}
				printf(" 電話番号：");
				if (input.phone1 == 70 || input.phone1 == 80 || input.phone1 == 90)
				{
					printf("%03ld%08ld\n", input.phone1, input.phone2);
				}
				else
				{
					printf("%03ld%07ld\n", input.phone1, input.phone2);
				}
			}
		}
		else
		{
			if (strstr(input.name, serch) != NULL || strstr(number, serch) != NULL || strstr(phone1, serch) != NULL)
			{
				printf("%d：\t学番：%07ld 名前：%s", i, input.number, input.name);
				for (spacelen = 0; spacelen < (20 - strlen(input.name)); ++spacelen)
				{
					printf(" ");
				}
				printf(" 電話番号：");
				if (input.phone1 == 70 || input.phone1 == 80 || input.phone1 == 90)
				{
					printf("%03ld%08ld\n", input.phone1, input.phone2);
				}
				else
				{
					printf("%03ld%07ld\n", input.phone1, input.phone2);
				}
			}
		}
		i++;
	}
	printf("\n");
}

void edit_addres( )
{
	int i = 1;
	int number;
	int spacelen;
	char answer[ARRAY_SIZE];
	struct person input;
	struct person student;
	FILE *fp_hoge;

	printf("\n");
	printf("Edit No. >");
	scanf("%d", &number);
	printf("\n");
	printf("student number >");
	scanf("%07ld", &student.number);
	printf("name >");
	strget(student.name, sizeof student.name);
	printf("phonenumber >");
	scanf("%03ld%ld", &student.phone1, &student.phone2);
	printf("Would you like to change addres?(yes/no) >");
	strget(answer, sizeof answer);

	if (strcmp(answer, "yes") == 0||strcmp(answer,"y")==0)
	{

		fp_hoge = fopen("hoge.addres", "w");

		while (fscanf(file, "%ld %s %03ld%ld", &input.number, input.name, &input.phone1, &input.phone2) != EOF)
		{

			if (i == number)
			{
				fprintf(fp_hoge, "%07ld %s ", student.number, student.name);
				if (input.phone1 == 70 || input.phone1 == 80 || input.phone1 == 90)
				{
					fprintf(fp_hoge, "%03ld%08ld\n", student.phone1, student.phone2);
				}
				else
				{
					fprintf(fp_hoge, "%03ld%07ld\n", student.phone1, student.phone2);
				}
			}
			else
			{
				fprintf(fp_hoge, "%07ld %s ", input.number, input.name);
				if (input.phone1 == 70 || input.phone1 == 80 || input.phone1 == 90)
				{
					fprintf(fp_hoge, "%03ld%08ld\n", input.phone1, input.phone2);
				}
				else
				{
					fprintf(fp_hoge, "%03ld%07ld\n", input.phone1, input.phone2);
				}
			}
			i++;
		}

		fcloseall( );

		file = fopen(filename, "w+");
		fp_hoge = fopen("hoge.addres", "r");

		i = 1;

		printf("\n");

		while (fscanf(fp_hoge, "%ld %s %03ld%ld", &input.number, input.name, &input.phone1, &input.phone2) != EOF)
		{
			fprintf(file, "%07ld %s ", input.number, input.name);
			if (i == number) printf("%d：\t学番：%07ld 名前：%s", i, input.number, input.name);
			for (spacelen = 0; spacelen < (20 - strlen(input.name)); ++spacelen)
			{
				printf(" ");
			}
			if (input.phone1 == 70 || input.phone1 == 80 || input.phone1 == 90)
			{
				fprintf(file, "%03ld%08ld\n", input.phone1, input.phone2);
				if (i == number) printf("電話番号：%03ld%08ld\n", input.phone1, input.phone2);
			}
			else
			{
				fprintf(file, "%03ld%07ld\n", input.phone1, input.phone2);
				if (i == number) printf("電話番号：%03ld%07ld\n", input.phone1, input.phone2);
			}
			i++;
		}

		fcloseall( );

		remove("hoge.addres");

	}

	printf("\n");

}

void delete_addres( )
{
	int i = 1;
	int number;
	char answer[ARRAY_SIZE];
	struct person input;
	FILE *fp_hoge;

	printf("\n");

	printf("Delete No.? >");
	scanf("%d", &number);
	printf("Are you sure you want to delete?(yes/no) >");
	strget(answer, sizeof answer);
	printf("\n");

	if (strcmp(answer, "yes") == 0||strcmp(answer,"y")==0)
	{

		fp_hoge = fopen("hoge.addres", "w");

		for (i = 1; fscanf(file, "%ld %s %03ld%ld", &input.number, input.name, &input.phone1, &input.phone2) != EOF; ++i)
		{
			if (i != number)
			{
				fprintf(fp_hoge, "%07ld %s ", input.number, input.name);
				if (input.phone1 == 70 || input.phone1 == 80 || input.phone1 == 90)
				{
					fprintf(fp_hoge, "%03ld%08ld\n", input.phone1, input.phone2);
				}
				else
				{
					fprintf(fp_hoge, "%03ld%07ld\n", input.phone1, input.phone2);
				}
			}
		}


		fcloseall( );

		file = fopen(filename, "w+");
		fp_hoge = fopen("hoge.addres", "r");

		while (fscanf(fp_hoge, "%ld %s %03ld%ld", &input.number, input.name, &input.phone1, &input.phone2) != EOF)
		{
			fprintf(file, "%07ld %s ", input.number, input.name);
			if (input.phone1 == 70 || input.phone1 == 80 || input.phone1 == 90)
			{
				fprintf(file, "%03ld%08ld\n", input.phone1, input.phone2);
			}
			else
			{
				fprintf(file, "%03ld%07ld\n", input.phone1, input.phone2);
			}
		}

		fcloseall( );

		remove("hoge.addres");

	}

	printf("\n");
}

void help(char modestr[ARRAY_SIZE])
{

	printf("\n");
	if (strcmp(modestr, "help new") == 0) printf("\"new mode\" is new addres input\n");
	else if (strcmp(modestr, "help read") == 0) printf("\"read mode\" is read addres book\n");
	else if (strcmp(modestr, "help serch") == 0) printf("\"serch mode\" is name serch\n");
	else if (strcmp(modestr, "help edit") == 0) printf("\"edit mode\" is edit addres book\n");
	else if (strcmp(modestr, "help delete") == 0) printf("\"delete mode\" is delete addres\n");
	else if (strcmp(modestr, "help game") == 0) printf("\"game mode\" is Number guessing game\n");
	else if (strcmp(modestr, "help option") == 0) printf("\"option mode\" is password lock and password change\n");
	else if (strcmp(modestr, "help end") == 0) printf("close addres book\n");
	else
	{
		printf("exist mode > ");
		printf("new, read, serch, edit, delete, fortune, game, option, end\n");
		printf("\n");
		printf("help [mode] - description of each mode\n");
	}
	printf("\n");
}

void fortune( )
{

	int fortune;
	char name[ARRAY_SIZE];
	srand((unsigned) time(NULL));
	fortune = rand( ) % 6;

	printf("\n");
	printf("I will divination your fortune\n");
	printf("Please enter the name you divine >");
	strget(name,sizeof name);
	name[0] = toupper(name[0]);
	printf("\n");
	printf("%s fortune of today is ... >",name);
	Sleep(2000);
	if (fortune == 0) printf("Excellent luck!!!");
	else if (fortune == 1) printf("Great luck!!");
	else if (fortune == 2) printf("Minimum luck");
	else if (fortune == 3) printf("Luck");
	else if (fortune == 4) printf("Bad");
	else if (fortune == 5) printf("Excellent bad...");

	printf("\n\n");
}

char* strget(char* str, int len)
{
	char *nlstr;
	fflush(stdin);
	fgets(str, len, stdin);
	nlstr = strchr(str, '\n');
	if (nlstr != NULL) *nlstr = '\0';

	return str;
}

void game(){
	int limit = 0;
	int computer_number = 0;
	int answer = 0;
	int my_number = 0;
	int computer_answer = 0;
	int max_com_number = 100;
	int min_com_number = 0;

	srand((unsigned)time(NULL));
	computer_number = rand() % 99 + 1;
	computer_answer = rand() % 99 + 1;

	printf("2桁以内の数字を当て合います\n");

	printf("2桁以内の自分の数字を入力してください >");
	scanf("%d", &my_number);

	printf("2桁以内のコンピュータの数字を当ててください\n");


	for (limit = rand() % 6 + 5; limit > 0 && answer != computer_number&&computer_answer != my_number; limit--){
		printf("残り%d回\n", limit);
		printf("数字を入力してください >");
		scanf("%d", &answer);

		if (answer == computer_number){
			printf("当たりです！！\n");
		}
		else{
			if (answer > computer_number){
				printf("数字がでかいです\n");
			}
			else
			{
				printf("数字が小さいです\n");
			}
		}

		do{
			computer_answer = rand() % 99 + 1;
		} while (computer_answer >= max_com_number || computer_answer <= min_com_number);

		if (computer_answer > my_number){
			max_com_number = computer_answer;
		}
		else{
			min_com_number = computer_answer;
		}

		if (answer != computer_number){
			printf("コンピュータの回答 >%d\n", computer_answer);
			if (computer_answer == my_number){
				printf("コンピュータの勝ちです\n");
			}
		}
	}

	if (answer != computer_number){
		printf("ドカス\n");
		printf("コンピュータの答えは %d です\n", computer_number);
	}

	printf("\n");

}

char* passinput(char* pass){
	char ch;
	char buf[256];
	int len;

	buf[0] = pass[0] = '\0';
	do{
		printf("\rPlease input password >%s ", buf);
		printf("\rPlease input password >%s", buf);
		ch = getch();
		len = strlen(buf);
		switch (ch){
			case ENTER:
				printf("\n");
				break;
			case BACKSPACE:
				if (len > 0){
					pass[len - 1] = '\0';
					buf[len - 1] = '\0';
				}
				break;
			default:
				pass[len] = ch;
				pass[len + 1] = '\0';
				buf[len] = '*';
				buf[len + 1] = '\0';
				break;
		}
	} while (ch != ENTER);

	return pass;
}

void configfile(){
	int n;
	int j;
	char hoge[ARRAY_SIZE];
	
	memset(passinit, '\0', sizeof passinit);
	memset(pass, '\0', sizeof pass);
	memset(hoge, '\0', sizeof hoge);	

	config = fopen("addres.ini", "r");
	if (config == NULL){
		config = fopen("addres.ini", "w");
		memset(passinit, '\0', sizeof passinit);
		memset(pass, '\0', sizeof pass);
		strcpy(passinit, "TRUE");
		strcpy(pass, "pass");
		fprintf(config, "PASSON=%s\n", passinit);
		fprintf(config, "PASSWORD=%s\n", pass);
		fclose(config);
	}
	fclose(config);
	config = fopen("addres.ini", "r");

	fscanf(config, "%s",passinit);
	fscanf(config,"%s",pass);
	j = 7;
	for (n = 0; passinit[j] != '\0'; ++n){
		hoge[n] = passinit[j++];
	}
	memset(passinit, '\0', sizeof passinit);
	strcpy(passinit, hoge);
	j = 9;
	for (n = 0; pass[j] != '\0'; ++n){
		hoge[n] = pass[j++];
	}
	memset(pass, '\0', sizeof pass);
	strcpy(pass, hoge);
	fclose(config);
}

void option(){
	char answer[ARRAY_SIZE];
	char optionmode[ARRAY_SIZE];
	char changepass[ARRAY_SIZE];
	printf("\n");
	printf("Are you sure you want to change any options\n");
	printf("Password lock or Password change?(lock/change) >");
	strget(optionmode, sizeof optionmode);
	if (strcmp(optionmode, "lock") == 0){
		do{
			printf("Do you put the password?(yes/no) >");
			strget(answer, sizeof answer);
			if (strcmp(answer, "yes") == 0){
				strcpy(passinit, "TRUE");
				config = fopen("addres.ini", "w");
				fprintf(config, "PASSON=%s\n", passinit);
				fprintf(config, "PASSWORD=%s\n", pass);
				fclose(config);
			}
			else if (strcmp(answer, "no") == 0){
				strcpy(passinit, "FALSE");
				config = fopen("addres.ini", "w");
				fprintf(config, "PASSON=%s\n", passinit);
				fprintf(config, "PASSWORD=%s\n", pass);
				fclose(config);
			}
			else printf("error");
		} while (strcmp(answer, "yes") == 0 && strcmp(answer, "no") == 0);
	}
	if (strcmp(optionmode, "change") == 0){
		printf("Please enter the string you want to password >");
		strget(changepass, sizeof changepass);
		printf("Change password \"%s\", OK?(yes/no) >",changepass);
		strget(answer, sizeof answer);
		if (strcmp(answer, "yes") == 0){
			strcpy(pass, changepass);
			config = fopen("addres.ini", "w");
			fprintf(config,"PASSON=%s\n", passinit);
			fprintf(config,"PASSWORD=%s\n", pass);
			fclose(config);
		}
		else printf("error");
	}
}
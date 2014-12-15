#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int comans(int myn);

int main(void){
	int computer_number = 0;
	int answer = 0;
	int my_number = 0;
	int computer_answer = 0;

	srand((unsigned)time(NULL));
	computer_number = rand() % 99 + 1;
	computer_answer = rand() % 99 + 1;

	printf("2桁以内の数字を当て合います\n");

	printf("2桁以内の自分の数字を入力してください >");
	cin >> my_number;

	printf("2桁以内のコンピュータの数字を当ててください\n");


	for (int limit = rand() % 6 + 5; limit > 0 && answer != computer_number&&computer_answer != my_number; limit--){
		printf("残り%d回\n", limit);
		printf("数字を入力してください >");
		cin >> answer;

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

		computer_answer = comans(my_number);

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

	return 0;

}

int comans(int myn){
	static int max_com_number = 99;
	static int min_com_number = 1;
	int computer_answer;

	do{
		computer_answer = rand() % 99 + 1;
	} while (computer_answer >= max_com_number || computer_answer <= min_com_number);

	if (computer_answer > myn){
		max_com_number = computer_answer;
	}
	else{
		min_com_number = computer_answer;
	}

	return computer_answer;
}
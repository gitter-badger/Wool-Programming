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

	printf("2���ȓ��̐����𓖂č����܂�\n");

	printf("2���ȓ��̎����̐�������͂��Ă������� >");
	cin >> my_number;

	printf("2���ȓ��̃R���s���[�^�̐����𓖂ĂĂ�������\n");


	for (int limit = rand() % 6 + 5; limit > 0 && answer != computer_number&&computer_answer != my_number; limit--){
		printf("�c��%d��\n", limit);
		printf("��������͂��Ă������� >");
		cin >> answer;

		if (answer == computer_number){
			printf("������ł��I�I\n");
		}
		else{
			if (answer > computer_number){
				printf("�������ł����ł�\n");
			}
			else
			{
				printf("�������������ł�\n");
			}
		}

		computer_answer = comans(my_number);

		if (answer != computer_number){
			printf("�R���s���[�^�̉� >%d\n", computer_answer);
			if (computer_answer == my_number){
				printf("�R���s���[�^�̏����ł�\n");
			}
		}
	}

	if (answer != computer_number){
		printf("�h�J�X\n");
		printf("�R���s���[�^�̓����� %d �ł�\n", computer_number);
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
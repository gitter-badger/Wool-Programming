#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int errorflag=0;
int calcflag=1;
int hoge=0;

double tonumber(char moji[256][256]);	//������𐔎��ɕϊ�
double answercalc(double number1,double number2,char moji);	//���Z����֐�
double kaijou(double number);

int main(void){
	double number[1024];	//�����p
	double answer;	//�����p
	char enzan[1024];	//���Z�q�p
	char moji[256][256];	//�����p

	printf("���Z�q��e����͂���ƏI�����܂�\n");
	printf("input(���� ���Z�q �����̏��ɃX�y�[�X���J���Ȃ�����͂��Ă�������) ��\n");
	scanf("%s %s %s",moji[0],enzan,moji[1]);	//������ ���Z�q ������ �̏��ɓ���
	number[0]=tonumber(moji[0]);	//1�Ԗڂ̕�����𐔎��ɕϊ�
	number[1]=tonumber(moji[1]);	//2�Ԗڂ̕�����𐔎��ɕϊ�
	answer=answercalc(number[0],number[1],enzan[0]);	//�v�Z

	if(!errorflag){
		printf(" = %g ",answer);	//�����\��
	}else{
		printf("error!\n");
		return 0;
	}

	while(calcflag){
		scanf("%s %s",enzan,moji[0]);	//���Z�q ������ �̏��ɓ���
		number[0]=tonumber(moji[0]);	//������𐔎��ɕϊ�
		answer=answercalc(answer,number[0],enzan[0]);	//�v�Z

		if(calcflag){
			if(!errorflag){
				printf(" = %g ",answer);	//�����\��
			}else{
				printf("error!\n");
				return 0;
			}
		}else{
			printf("end\n");
			return 0;
		}
	}
		
	return 0;
}

double tonumber(char moji[256][256]){
	int i,j=0,nullmoji;
	double ans;
	char number[1024];
	for(i=0;moji[0][i]!='\0';++i){
		nullmoji=i;
	}
	if(moji[0][0]=='s'&&moji[0][1]=='i'&&moji[0][2]=='n'){
		for(i=3;moji[0][i]!='\0';++i){
			number[j]=moji[0][i];
			++j;
		}
		ans=sin((atof(number))*M_PI/180.0);
	}else if(moji[0][0]=='c'&&moji[0][1]=='o'&&moji[0][2]=='s'){
		for(i=3;moji[0][i]!='\0';++i){
			number[j]=moji[0][i];
			++j;
		}
		if(((atoi(number)+90)%180)!=0){
			ans=cos((atof(number))*M_PI/180.0);
		}else{
			ans=0;
		}
	}else if(moji[0][0]=='t'&&moji[0][1]=='a'&&moji[0][2]=='n'){
		for(i=3;moji[0][i]!='\0';++i){
			number[j]=moji[0][i];
			++j;
		}
		if(((atoi(number)+90)%180)!=0){
			ans=tan((atof(number))*M_PI/180.0);
		}else{
			errorflag=1;
		}
	}else if(moji[0][0]=='l'&&moji[0][1]=='o'&&moji[0][2]=='g'){
		for(i=3;moji[0][i]!='\0';++i){
			number[j]=moji[0][i];
			++j;
		}
		if(atof(number)>0){
			ans=log(atof(number));
		}else{
			errorflag=1;
		}
	}else if(moji[0][nullmoji]=='!'){
		for(i=0;moji[0][i]!='!';++i){
			number[j]=moji[0][i];
			++j;
		}
		ans=kaijou(atof(number));
	}else{
		ans=atof(moji);
	}
	
	return ans;

}

double answercalc(double number1,double number2,char moji){
	double ans;
	switch(moji){
		case '+':
			ans=number1+number2;
			break;
		case '-':
			ans=number1-number2;
			break;
		case '*':
			ans=number1*number2;
			break;
		case '/':
			if(number2!=0){
				ans=number1/number2;
				break;
			}else{
				errorflag=1;
				break;
			}
		case '^':
			ans=pow(number1,number2);
			break;
		case 'e':
			calcflag=0;
			ans=0;
			break;
		default:
			printf("�l���c\n");
			ans=0;
			break;
	}

	return ans;
}

double kaijou(double number){
	int i;
	double ans;
	if(number==((int)number)&&number>0){
		for(i=(number-1);i>=1;--i){
			number*=i;
		}
		ans=number;
	}else if(number==0){
		ans=1;
	}else{
		errorflag=1;
		ans=0;
	}
	return ans;
}
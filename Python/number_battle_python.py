# -*- coding: utf-8 -*-
import random
print "2���ȓ��̐����𓖂č����܂�"
my_number=input("2���ȓ��̎����̐�������͂��Ă������� >")
print "2���ȓ��̃R���s���[�^�̐����𓖂ĂĂ�������"
print "����ł�...�X�^�[�g�ł�"
random.seed()
computer_number=random.randint(1,99)
max_computer_number=100
min_computer_number=0
for i in range(random.randint(7,15))[::-1]:
    print "�c��",i+1,"��ł�"
    my_answer=input("input answer >")
    if my_answer==computer_number:
        print "������ł�!!"
        break
    else:
        if my_answer>computer_number:
            print "�ł����ł�"
        else:
            print "�������ł�"
	computer_answer=random.randint(min_computer_number,max_computer_number)
    while computer_answer > max_computer_number and computer_answer < min_computer_number:
        computer_answer=random.randint(min_computer_number,max_computer_number)
    if computer_answer>my_number:
        max_computer_number=computer_answer
    else:
        min_computer_number=computer_answer
    if my_answer!=computer_number:
        print "�R���s���[�^�̉� >",computer_answer
        if my_number==computer_answer:
            print "�R���s���[�^�̏����ł�"
            break
if my_answer != computer_number:
    print "�h�J�X"
    print "�R���s���[�^�̐�����",computer_number,"�ł�"
raw_input("Please press any key")
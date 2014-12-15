# -*- coding: utf-8 -*-
import random
print "2桁以内の数字を当て合います"
my_number=input("2桁以内の自分の数字を入力してください >")
print "2桁以内のコンピュータの数字を当ててください"
print "それでは...スタートです"
random.seed()
computer_number=random.randint(1,99)
max_computer_number=100
min_computer_number=0
for i in range(random.randint(7,15))[::-1]:
    print "残り",i+1,"回です"
    my_answer=input("input answer >")
    if my_answer==computer_number:
        print "当たりです!!"
        break
    else:
        if my_answer>computer_number:
            print "でかいです"
        else:
            print "小さいです"
	computer_answer=random.randint(min_computer_number,max_computer_number)
    while computer_answer > max_computer_number and computer_answer < min_computer_number:
        computer_answer=random.randint(min_computer_number,max_computer_number)
    if computer_answer>my_number:
        max_computer_number=computer_answer
    else:
        min_computer_number=computer_answer
    if my_answer!=computer_number:
        print "コンピュータの回答 >",computer_answer
        if my_number==computer_answer:
            print "コンピュータの勝ちです"
            break
if my_answer != computer_number:
    print "ドカス"
    print "コンピュータの数字は",computer_number,"です"
raw_input("Please press any key")
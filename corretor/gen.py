#!/usr/bin/python3
import time as tm
import random as rd

rd.seed(tm.clock())

N = 1000
MAXTEST = 50
for i in range(1, N + 1):
    entr = []
    nome = './in/entrada' + str(i) + '.txt'
    nint = rd.randint(1, MAXTEST)
    arq = open(nome, 'w')
################################################################################
    ops = "IIIIIRBBAA"
    for j in range(nint):
        x = rd.randint(0, 9)
        op = ops[x]
        if op == 'I':
            a = rd.randint(1, 99)
            entr.append(a)
            b = rd.randint(1, 99)
            arq.write(op + ' ' + str(a) + ' ' + str(b) + '\n')
        elif op == 'R' or op == 'B':
            b = rd.randint(0, 3)
            if b != 1 and len(entr) > 0:
                a = entr[rd.randint(0, len(entr) - 1)]
            else :
                a = rd.randint(1, 99)
            arq.write(op + ' ' + str(a) + '\n')
        else:
            arq.write(op + '\n')
    arq.write('P' + '\n')
################################################################################
    arq.close()

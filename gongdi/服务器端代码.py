import socket

import os
from datetime import datetime


sk = socket.socket()
print(sk)

def task2():
    address = ('',8000)
    sk.bind(address)  # 将本地地址与一个socket绑定在一起

    sk.listen(5)  # 最多允许有3个客户称呼
    while True:
      cs,addr=sk.accept()
      print('success')
      data=cs.recv(1024)
      path='E:/aaa/2.txt'
      f=open(path,'a+')
      f.write(data.decode('utf-8'))
      f.close()

if __name__=='__main__':
    #try:
        # thread.start_new_thread(task1)
        task2()

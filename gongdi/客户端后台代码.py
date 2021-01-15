import socket
import _thread as thread
import os

sk = socket.socket()

print(sk)


def task1():
    address = ('192.168.31.65', 9000)
    sk.connect(address)
    flag = 1
    # BASE_DIR = os.path.dirname(os.path.abspath("H:/photo/"))
    while True:

        # inp = input('>>>>>>>>')  # post|11.png

        # cmd, path = inp.split('|')  # 拿到post，以及文件11.jpg
        name = "father"
        openway = "true"

        if (flag == 1):
            # inp = "post|" + name + "|" + openway
            # cmd, path = inp.split('|')  # 拿到post，以及文件11.jpg
            file_info = 'host|%s|%s' % (name, openway)  # split获取字符串的信息       以此方式打包，依次为   cmd/name/size
            sk.send(file_info.encode())  # 发送真实数据
            flag = 2
            print("shangchuanchenggong")
        else:
            path = "C:/Users/Lenovo/Desktop/1.jpg"
            filename = os.path.basename(path)
            file_size = os.stat(path).st_size
            file_info = 'invader|%s|%s' % (filename, file_size)  # split获取字符串的信息       以此方式打包，依次为   cmd/name/size
            sk.sendall(bytes(file_info, 'utf8'))  # 第一次发送请求，不是具体内容，而是先发送数据信息

            f = open(path, 'rb')

            has_sent = 0

            while has_sent != file_size:
                data = f.read(1024)

                sk.sendall(data)  # 发送真实数据

                has_sent += len(data)

            f.close()
            print('上传成功')
            # os.remove(path)
            flag = 1


if __name__ == '__main__':
    task1()


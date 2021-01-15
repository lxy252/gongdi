import serial
import time
import datetime
import send
import RPi.GPIO as GPIO


channel = 4                          #引脚号14
 
GPIO.setmode(GPIO.BCM)
GPIO.setup(channel, GPIO.IN)

from time import sleep
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.5)
def recv(serial): 
    TemData= ''
    Data = ''
   #
    ser.write(bytes.fromhex('BB002700032200105C7E'))
    
    
      #while True:
        #serial.read(8)
    TemData = serial.read(24)
        #serial.read(4)
    if TemData == b'':
            #break
            return Data
            
    else:
            print(TemData.hex()+'\n')
            Data = Data+TemData.hex()
            return Data
            #continue
        
    #return Data

def deal(Data):
    time=''
    news_Data = []
    temp=[]
    DealData=Data.split('bb')

    FL_DealData=[]
    for i in DealData:
        if i!='01ff000115167e' and i not in news_Data:
            news_Data.append(i)
        
    for i in  news_Data:
        if i!='01ff000115167e': #and i not in  FL_DealData:
              i=i[14:37]
              if i not in  FL_DealData:
                      FL_DealData.append(i)
    if FL_DealData!=['']:
       
        time=datetime.datetime.now().strftime('%Y%m%d%H%M%S')
        for i in FL_DealData:
            if i!='':
                print(i)
                send.task1(i+' '+'1 '+time+'\n')


Flag =GPIO.input(channel)
while True:
    if Flag==1 and GPIO.input(channel)==0:
        time_start = time.time()

        data =deal(recv(ser))
    
        time_end = time.time()
        Flag =0
    elif Flag==0 and GPIO.input(channel)==0:
        Flag=0
    else:
        Flag=1
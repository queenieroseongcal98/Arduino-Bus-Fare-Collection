import serial 
import MySQLdb
import time

#establish connection to MySQL. 
dbConn = MySQLdb.connect("localhost","root","","rfidfare") or die ("could not connect to database")
#open a cursor to the database
cursor = dbConn.cursor()

device = 'COM7' #this is the serial port
try:
  print ("Trying...",device)
  arduino = serial.Serial(device, 9600) 
except: 
  print ("Failed to connect on",device)
while True:
    time.sleep(1)
    try:
        data=arduino.readline()
        print (data)
        print ("NING SUD 1")
        pieces=data.split(" ") #split data by the space
        print (pieces)
        #Insert the data to the Database
        try:
            cursor=dbConn.cursor()
            sqli = 'INSERT INTO fare_table (ID, MEM, ALLOWED, BAL) VALUES (%s,%s,%s,%s)'
            print ("NING SUD 2")
            print (data)
            val = (data)
            cursor.execute(sqli,val)
            #cursor.execute("""INSERT INTO rfid_data (ID,ID_MEMBER,IS_ALLOWED,BAL) VALUES (%s,%s,%s,%s)""", (pieces[0],pieces[1], pieces[2]))
            dbConn.commit()
            cursor.close()
        except MySQLdb.IntegrityError:
            print ("failed to insert data")
        finally:
            cursor.close()
    except:
        print ("Processing")

# Модуль socket для сетевого программирования
from socket import *
from datetime import datetime
import sqlite3

# Подключаемся к БД

# Создаем курсор - это специальный объект который делает запросы и получает их результаты

# данные сервера
host = '0.0.0.0'
port = 777
addr = (host, port)

# socket - функция создания сокета
# первый параметр socket_family может быть AF_INET или AF_UNIX
# второй параметр socket_type может быть SOCK_STREAM(для TCP) или SOCK_DGRAM(для UDP)
udp_socket = socket(AF_INET, SOCK_DGRAM)
# bind - связывает адрес и порт с сокетом
udp_socket.bind(addr)
sql = "INSERT INTO noise.db ( date, time, device, value) VALUES (?, ?, ?, ?)"
# Бесконечный цикл работы программы
while True:
    print('wait data...')
    db = sqlite3.connect('noise.db')
    cursor = db.cursor()
    # recvfrom - получает UDP сообщения
    conn, addr = udp_socket.recvfrom(1024)
    s = conn.decode("utf-8")
    date = datetime.strftime(datetime.now(), "%Y.%m.%d")
    time = datetime.strftime(datetime.now(), "%H:%M:%S")
    print('client addr: ', addr)
    print(s,' ',s[0],' ',s[1:4], '\ndate: ', date, '\ntime: ', time)
    cursor.execute(sql, ( date, time, s[0], s[1:4]))
    db.commit()
    db.close()

udp_socket.close()



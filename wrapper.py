from ctypes import *

MAX_SIZE = 64
input_rozmiar = -1
input_praw = -1

while input_rozmiar < 0 or input_rozmiar > MAX_SIZE:
    input_rozmiar = int(input("Podaj rozmiar macierzy"))

while input_praw < 0 or input_praw > 100:
    input_praw = int(input("Podaj prawdopodobienstwo wystopienia zera w macierzy"))

example = CDLL('./perkolacja.so')
result = example.add(input_rozmiar, input_praw)
print(result) # 5
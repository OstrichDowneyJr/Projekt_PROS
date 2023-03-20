from ctypes import WinDLL

cPerkolacja = WinDLL(r"c:\Users\janbu\Documents\VS_Code\C\Projekt_PROS\mydll.dll")

print("Witam, podaj rozmiar tablicy:")

rozmiar = input()

print("Podaj prawdopodobieństwo wystąpienia 0:")
prog = input()

cPerkolacja.perkolacja(rozmiar, prog)
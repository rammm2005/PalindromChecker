def is_palindrome(word):
    word = word.lower()
    word = word.replace("", "")
    reversedWord = word[::-1]

    if word == reversedWord:
        return True
    else:
        return False

while True:
    inputWord = input("Masukkan sebuah kata (atau ketik 'exit' untuk keluar): ")

    if inputWord.lower() == 'exit':
        break

    if is_palindrome(inputWord):
        print(f"'{inputWord}' adalah palindrom (True) dan memiliki {len(inputWord)} karakter.")
    else:
        print(f"'{inputWord}' bukan palindrom (False) dan memiliki {len(inputWord)} karakter.")

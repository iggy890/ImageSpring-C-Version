import time

def convert(text):
    new = ""
    for i in text:
        if i == '\n':
            new = (new + "\\n")

        new = (new + i)

    return new

searchClicked = False
addImageClicked = False

def searchClicked():
    searchClicked = True

def addImageClicked():
    addImageClicked = True

from tkinter import *
window = Tk()
window.title("ImageSpring (C Version)")
window.geometry("800x400")

lbl = Label(window, text="Directory:")
lbl.grid(row=1, column=1)

lbl2 = Label(window, text="Topic:")
lbl2.grid(row=1, column=2)

dir = Entry(window, width=30)
dir.grid(row=2, column=2)

topic = Entry(window, width=30)
topic.grid(row=2, column=1)

search = Button(window, text="Search")
search.grid(row=2, column=3)

addImage = Button(window, text="Add Image")
addImage.grid(row=2, column=4)

version = Label(window, text="Version: 1.0")
version.grid(row=1, column=4)

result = Label(window, text="Welcome to ImageSpring!")
result.grid(column=1, row=10)

def openWithoutClearing(filename):
    r = open(filename, "r")
    c = r.read()
    r.close()
    w = open(filename, "w")
    w.write(c)
    return w

def loop():
    w = openWithoutClearing("window.txt")
    while True:
        c = w.readline(5)
        if not c == "":
            result.configure(window, text=c)
        
        writeText = str(dir.get())
        writeText = (writeText + "\n" + str(topic.get()))
        writeText = (writeText + "\n" + str())
        
window.mainloop()
loop()
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

def searchClick():
    searchClicked = True

def addImageClick():
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

search = Button(window, text="Search", command=searchClick)
search.grid(row=2, column=3)

addImage = Button(window, text="Add Image", command=addImageClick)
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

def wait(secs):
    time.sleep(secs)
r = open("window.txt", "r")
w = openWithoutClearing("window.txt")
def task():
    c = r.readline(5)
    if not c == "":
        result.configure(window, text=c)
        
    writeText = (f'"{str(dir.get())}"')
    writeText = (writeText + f'\n"{str(topic.get())}"')
    writeText = (writeText + f"\n{int(searchClicked)}")
    writeText = (writeText + f"\n{int(addImageClicked)}")
    writeText = (writeText + f"\n{c}")
    print(writeText)
    w.write(writeText)
    window.after(2000, task)

window.after(2000, task)
window.mainloop()
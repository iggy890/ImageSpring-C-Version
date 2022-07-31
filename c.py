from tkinter import Tk, Label, Button, Entry
from threading import Thread

window = Tk()
window.title("ImageSpring (C Version)")
window.geometry("800x400")

lbl, lbl2, dir, topic, version, result, sc, ac = Label(window, text="Directory:"), Label(window, text="Topic:"), Entry(window, width=30), Entry(window, width=30), Label(window, text="Version: 1.0"), Label(window, text="Loading..."), 0, 0

lbl.grid(row=1, column=1), lbl2.grid(row=1, column=2), dir.grid(row=2, column=2), topic.grid(row=2, column=1), version.grid(row=1, column=4), result.grid(column=1, row=10)

def searchClick():
    global sc
    sc = 1

def addImageClick():
    global ac
    ac = 1

search, addImage = Button(window, text="Search", command=searchClick), Button(window, text="Add Image", command=addImageClick)
search.grid(row=2, column=3), addImage.grid(row=2, column=4)

def read_open_close():
    r = open("Saves/windowEdits.txt", "r")
    result.configure(text=r.read())
    r.close()
    print("read")

def write_open_close():
    global sc, ac
    w = open("Saves/window.txt", "w")

    wText = dir.get()
    wText = f"{wText}\n{topic.get()}"
    wText = f"{wText}\n{sc}"
    wText = f"{wText}\n{ac}"

    w.write(wText)
    w.close()
    ac, sc = 0, 0

def task():
    t = Thread(target=read_open_close)
    t2 = Thread(target=write_open_close)
    t.start()
    t2.start()
    t.join(0)
    t2.join(0)
    window.after(1, task)


window.after(0, task)
window.mainloop()
from tkinter import Tk, Label, Button, Entry

window = Tk()
window.title("ImageSpring (C Version)")
window.geometry("800x400")

lbl, lbl2, dir, topic, version, result, sc, ac = Label(window, text="Directory:"), Label(window, text="Topic:"), Entry(window, width=30), Entry(window, width=30), Label(window, text="Version: 1.0"), Label(window, text="Welcome to ImageSpring!"), 0, 0

lbl.grid(row=1, column=1), lbl2.grid(row=1, column=2), dir.grid(row=2, column=2), topic.grid(row=2, column=1), version.grid(row=1, column=4), result.grid(column=1, row=10)

def searchClick():
    global sc
    sc = 1

def addImageClick():
    global ac
    ac = 1

search = Button(window, text="Search", command=searchClick)
search.grid(row=2, column=3)

addImage = Button(window, text="Add Image", command=addImageClick)
addImage.grid(row=2, column=4)

def task():
    global sc, ac
    r = open("Saves/window.txt", "r")
    w = open("Saves/window.txt", "w")

    c = r.readline(5)
    
    writeText = dir.get()
    writeText = (writeText + f"\n{topic.get()}")
    writeText = (writeText + f"\n{sc}")
    writeText = (writeText + f"\n{ac}")
    writeText = (writeText + f"\n{c}")

    w.write(writeText)
    r.close()
    w.close()

    ac, sc = 0, 0
    
    window.after(0, task)

window.after(0, task)
window.mainloop()
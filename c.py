from tkinter import Tk, Label, Button, Entry

window = Tk()
window.title("ImageSpring (C Version)")
window.geometry("800x400")

lbl, lbl2, dir, topic, version, result, sc, ac = Label(window, text="Directory:").grid(row=1, column=1), Label(window, text="Topic:").grid(row=1, column=2), Entry(window, width=30), Entry(window, width=30), Label(window, text="Version: 1.0").grid(row=1, column=4), Label(window, text="Loading..."), 0, 0

result.grid(column=1, row=10), dir.grid(row=2, column=1), topic.grid(row=2, column=2)

def searchClick():
    print("click")
    globals()['sc'] = 1

def addImageClick():
    print("ai clcik")
    globals()['ac'] = 1

search, addImage = Button(window, text="Search", command=searchClick).grid(row=2, column=3), Button(window, text="Add Image", command=addImageClick).grid(row=2, column=4)

def read_open_close():
    r = open("Saves/windowEdits.txt", "r")
    result.configure(text=r.read())
    r.close()

def write_open_close():
    w = open("Saves/window.txt", "w")
    val = globals()

    wText = dir.get()
    wText = f"{wText}\n{topic.get()}"
    wText = f"{wText}\n{val['sc']}"
    wText = f"{wText}\n{val['ac']}"

    w.write(wText)
    w.close()
    val['ac'], val['sc'] = 0, 0

def task():
    read_open_close()
    write_open_close()
    window.after(1, task)


window.after(0, task)
window.mainloop()
raise SystemExit()
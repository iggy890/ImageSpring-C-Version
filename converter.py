def convert(text):
    new = ""
    for i in text:
        if i == '\n':
            new = (new + "\\n")

        new = (new + i)

    return new

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

window.mainloop()
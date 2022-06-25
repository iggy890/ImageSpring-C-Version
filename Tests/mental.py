from tkinter import *
import random, time

an = 15

window = Tk()
window.geometry("500x75")
window.title("Mental maths")

text = Label(window, text="5 + 10")
ans = Entry(window)

def update():
    global an
    if int(ans.get()) == an:
        text.configure(text="Correct")
        print("Correct")
        time.sleep(1)
        num = random.randint(5, 150)
        num2 = random.randint(5, 150)
        an = num + num2
        text.configure(text=("{} + {}".format(num, num2)))
    else:
        text.configure(text="Incorrect")
        print("Incorrect")
        time.sleep(1)
        num = random.randint(5, 150)
        num2 = random.randint(5, 150)
        an = num + num2
        text.configure(text=("{} + {}".format(num, num2)))

button = Button(window, text="Submit", command=update)

button.grid(column=1, row=3)
ans.grid(column=2, row=2)
text.grid(column=1, row=2)

window.mainloop() 
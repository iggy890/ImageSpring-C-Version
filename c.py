# Imports
from tkinter import Tk, Label, Button, Entry

# Intialize Tkinter and create a window
window = Tk()
window.title("ImageSpring (C Version)")
window.geometry("800x400")

# Create Labels, Entrys and variables
lbl, lbl2, dir, topic, version, result, sc, ac = Label(window, text="Directory:").grid(row=1, column=1), Label(window, text="Topic:").grid(row=1, column=2), Entry(window, width=30), Entry(window, width=30), Label(window, text="Version: 1.0").grid(row=1, column=4), Label(window, text="Loading..."), 0, 0

# Grid the Buttons
result.grid(column=1, row=10), dir.grid(row=2, column=1), topic.grid(row=2, column=2)

# Change the 'sc' (searchClick variable) to True
def searchClick():
    globals()['sc'] = 1 # Change to True

# Change the 'ac' (addImageClick variable) to True
def addImageClick():
    globals()['ac'] = 1 # Change to True

# Create the Buttons
search, addImage = Button(window, text="Search", command=searchClick).grid(row=2, column=3), Button(window, text="Add Image", command=addImageClick).grid(row=2, column=4)

# Read the windowEdits file
def read_open_close():
    # Open the file
    r = open("Saves/windowEdits.txt", "r")

    # Change the result text to the windowEdits file
    result.configure(text=r.read())

    # Close the file
    r.close()

# Write to the window.txt file
def write_open_close():
    # Open the file
    w = open("Saves/window.txt", "w")

    # Set 'val' to globals()
    # globals() is a way to avoid global variables
    val = globals()

    # Create and assign the text to be written
    # To the window.txt file
    wText = dir.get()
    wText = f"{wText}\n{topic.get()}"
    wText = f"{wText}\n{val['sc']}"
    wText = f"{wText}\n{val['ac']}"

    # Write to the window.txt file
    w.write(wText)

    # Close the file
    w.close()

    # Set the 'ac' and 'sc' variables to False
    val['ac'], val['sc'] = 0, 0

# Execute both functions
def task():
    read_open_close() # Read the windowEdits file
    write_open_close() # Write to the window.txt file
    window.after(1, task) # Execute function in 1ms

# Execute the task function after 0ms
window.after(0, task)

# The mainloop of tkinter
window.mainloop()

# Raise the SystemExit exception to forcefully exit
raise SystemExit()
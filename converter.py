def convert(text):
    new = ""
    for i in text:
        if i == '\n':
            new = (new + "\\n")

        new = (new + i)

    return new
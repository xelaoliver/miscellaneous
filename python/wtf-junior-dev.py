file = []
longestLine = 0

with open("C:/Users/emmet/Desktop/Programming/Project/weird.cpp") as f:
    for i in f:
        if len(i) > longestLine:
            longestLine = len(i)
        file.append(i.rstrip())

newFile = []
for i, line in enumerate(file):
    endcharacters = ""
    i = len(line)-1
    while line and line[i] in [";", "}", ")", "{", "]", ","]:
        endcharacters = line[i]+endcharacters
        line = line[:i]
        i -= 1
    
    tabs = longestLine-len(line)
    line += " "*tabs

    line += endcharacters+"\n"
    newFile.append(line)

open("C:/Users/emmet/Desktop/Programming/Project/weird.cpp", "w").close()
change = open("C:/Users/emmet/Desktop/Programming/Project/weird.cpp", "w")
change.writelines(newFile)
change.close()

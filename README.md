# GlobalLoadLibraryInjector

# WHAT IS THIS:
a tool used to inject dynamically linked libraries into a processes virtual memory.

# WHAT IT DOES:
as said above. This just allows you to inject your own code into a process. Its useful for debugging and some sort of stuff.

# HOW TO USE:
Make a project, add a cpp file, copy the code into that file.
Next make sure go to properties->General and make sure its configuration type is "Application"(.exe) and make sure C++ Language Standard is C++20
Now go on to properties->Advanced and make sure the character set is multi-byte. WE ONLY USE MULTI-BYTE IN THIS HOUSE!
Now make sure your compiling release \ x86 or x64 depending on your games bit type and dll type.
Change any string that says csgo.exe to your game, if its csgo then leave it.
Now go to filePath and change that string to your dll path. MAKE SURE to add the "\\" per directory entry or else its gonna read it wrong.
next compile, run as admin and there your done!

Project is complete there is still some stuff to do like reworks with the UI which I'll never do 
because I don't want to ever touch this code base ever again because how horrible it looks to the human eye.

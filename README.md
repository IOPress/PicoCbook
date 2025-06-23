# PicoCbook
Before you clone or download this repo it is a good idea to first install
VS Code and the Pico extension and create and run a basic helloworld program.
This ensures that the setup is correct and it downloads the Pico SDK ond other 
essential components. 

Once you are sure that VS Code, the extension and the SDK are all installed correcty
and work, you can move on to install the repo. There are many ways of doing this but
one of the simplest is to open a terminal, which can be one in VS Code. Change directory
to the folder that you would like to install the repo and use the command:

    git clone https://github.com/IOPress/PicoCbook.git
This assumes that git is installed. As long as it is you should see something like. 

    Cloning into 'PicoCbook'...
    remote: Enumerating objects: 902, done.
    remote: Counting objects: 100% (902/902), done.
    remote: Compressing objects: 100% (470/470), done.
    remote: Total 902 (delta 364), reused 719 (delta 275), pack-reused 0 (from 0)
    Receiving objects: 100% (902/902), 1.63 MiB | 4.58 MiB/s, done.
    Resolving deltas: 100% (364/364), done.
    
The repo is stored in a folder called PicoCbook within the current directory. 
Within the PicoCbook folder is a folder for each chapter and within that a folder 
for each project. To work with a project in VS Code you need to open the folder that
contains the project. This is because the Pico Extension cannot work with multi-folder
projects. So if you want to run the HelloWorld program - don't open PicoCbook, don't open C2
but open PicoCBook/C2/HelloWorld. 
You can then use the Pico extension to run the program.
If it doesn't work try Clean CMake, and if that doesn't work try importing the project.

All of the projects are as listed in the book with the exception of chapter 18.
In the book you are recommended to download FreeRTOS as a repo within each probject.
To reduce the need to store FreeRTOS multiple times it is installed as a standard
folder within C18. The projects are modified to use FreeRTOS in this new location. 
In addition with this arrangment it is necessary to store FreeRTOSConfig.h in the 
project directory rather than FreeRTOS-Kernel/Indlude. It is arguable that this is 
a better place for it as it provides a per-project configuration. 
Also notice that if you follow the instruction in the book to clone the FreeRTOS repo 
then it is installed as a git sub-module. FreeRTOS-Kernel in the projects is a standard
folder and not a separate repo. It is also not a complete copy - just the files that are
required to run on a Pico.

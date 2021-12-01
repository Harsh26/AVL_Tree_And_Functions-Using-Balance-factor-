***How To Run .cpp FILE In WINDOWS using CYGWIN***

Pre-Requisites: 

1.You must install Cygwin in your windows machine.

2. Please ensure that all files inside .zip given by me, is placed in easily accessible location.
     For Example place it in- 
                     -------->   C:\cygwin\home\user\cpp\main.cpp
                     -------->   C:\cygwin\home\user\cpp\helper.cpp
                     -------->   C:\cygwin\home\user\cpp\AVL.cpp
                     -------->   C:\cygwin\home\user\cpp\helper.h
                     -------->   C:\cygwin\home\user\cpp\makefile

Running commands:

1. Open Cygwin. Ensure that you are inside cpp	 folder. using following commands in cygwin bash-
			
----->	Run in shell-	   $ pwd
	Output must be -      /home/user/cpp

2. Compilation & run using makefile. Note that makefile has all required commands and you just need to do following:

----->  	Run in shell- 	  $ make
          ----Output will be displayed after few seconds----

IMPORTANT NOTE: I have tested above commands in my friend's system & they are running fine.
                              If, for some reason, they dont run in your system, I've also attached full AVL.cpp file.
                              Run that file using 
                                             
                                 ------>         g++ AVL.cpp -o run   [*Use this step only if make command doesnot run*]     

3. You will be prompted to ***Menu Driven Mode*** Screen.

4. Choose any option between 1-6. And see output in terminal for all options Except option (4) AVL_Print.

5. For printing, Please take absolute precautions. Note that after AVL_Print function call, a DOT file will be generated in same location.
    According to above Example DOT file will be in:

                           --------->   C:\cygwin\home\user\cpp\myfile.gv. 

    This DOT file will be generated once you try printing.


Steps to visualize "myfile.gv":

     A) Ensure that graphviz is installed in your machine.

     B) Go to cmd. And then to "myfile.gv" file location. In above example(through cmd) go to 
                                                          ---------->     C:\cygwin\home\user\cpp        

                                                         

      C) Write command in following format-

            C:\cygwin\home\user\cpp\> "dot executable location in your computer" -Tpng <filename.gv> -o <newfilename.png>

   For above example in my pc :

         ----->  C:\cygwin\home\user\cpp\> "C:\Program Files\Graphviz2.38\bin\dot.exe" -Tpng myfile.gv -o myfile.png 
 

      D) Open png image to see output.


***How To Run .cpp FILE In Linux***

1.Please ensure that all files inside .zip given by me is placed in easily accessible location.

2. Once all file are there, open shell and go to that directory where you pasted all files.

3. Write '$ make' command and it should run the program.

4. IMPORTANT NOTE: I have tested above commands in my friend's system & they are running fine.
                              If, for some reason, they dont run in your system, I've also attached full AVL.cpp file.
                              Run that file using 
                                             
                                 ------>         g++ AVL.cpp -o run   [*Use this step only if make command doesnot run*]     

5. Rest steps same as windows.
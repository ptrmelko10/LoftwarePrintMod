# LoftwarePrintMod
Middleware program to split up pick tickets

Description
-----------

The program will take input from WMS a file that contains the Loftware instructions to print a pick order. The program will parse out multiple orders to create separate print jobs.
   
The output files are names after the input file with a letter appended after the filename. Currently the program supports up to 27 (A-Z) parsed files.
   
The parser finds the line "LP_PAGE_NO,x of y" and if x == y, then the parser advances 5 more lines and closes the output file in the directory: \\xxxx\loftware$\WDDrop where is it then handled by Loftware.
   
Once the input file reaches end of file, the file is closed and delted.

Back Story
----------
This program was created on the side when I was an intern. The program split up pick tickets since they were being printed in the batches causing picking errors. 

Usage
-----
The program was setup to run as a started task on a server machine. The user would select and print a batch of pick orders from WMS. The print file would be routed to a specific directory on the server machine where the C++ program would scan for new files of the "PAS" file extension. Once a *.PAS file is found, it splits up the pick tickets as separate files and passes each file to the loftware directory where the print template is generated and sent to the print in the warehouse.

License
-------
The code in LoftwarePrintMod.cpp is considered open source and is covered under the MIT License. See LICENSE.TXT for full disclosure of the license.

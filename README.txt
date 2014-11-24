------------------------------------------
    _            _              ___ ____  
   / \   ___ ___(_) __ _ _ __  / _ \___ \ 
  / _ \ / __/ __| |/ _` | '_ \| | | |__) |
 / ___ \\__ \__ \ | (_| | | | | |_| / __/ 
/_/   \_\___/___/_|\__, |_| |_|\___/_____|
                   |___/                  
------------------------------------------
Author: 	Matt W. Martin, 4374851
		kaethis@tasmantis.net

Project:	CS2010, Assignment 02
		Dictionary II (String Vector Implementation)

Date Issued:	24 Oct-2014
Date Archived:	[REDACTED]

Comments:	This lab consists of just one program: dict 

		- dict: This program will read either a text file or input and build
			a "Dictionary" of words (and sort them alphabetically, too!)
			based on that file or user input.  This Dictionary will
			contain not only each word, but also the frequency of each
			unique word.

			NOTE: By default, this Dictionary can store a maximum 100
			      words.

		To read from a file, execute like so:		$  ./dict < TEXT.txt
		(Where "TEXT" is the name of your file.)

		Otherwise, the program will request input from the user as soon as
		the program executes: it will interpret the each word from the input
		and add them to the Dictionary before printing its contents on the
		screen.

MAKE:		./dict		Creates the dict program described above.
		./clean		Removes dict program.
		./archive	Creates a .tar in parent-directory (../).
		
GIT Repository:			https://github.com/kaethis/CS2010_Assign02.git

Notes (Optional):	- To test reading from a file, I've again included the
			  excerpt from Jaron Lanier's "You Are Not A Gadget: A
			  Manifesto". 

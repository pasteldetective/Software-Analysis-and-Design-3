Jackie Yee
Project 2
CSCI 335

For this programming assignment, I created and tested linear_probing.h, double_hashing.h and spell_check.cc. 
For linear_probing.h, I was able to implement it through going through the functions of the provided quadratic_probing.h and augment the function that handled the current_position of the array and compared it to the array size. What needed to be added was a collision that incremented and the offset needed to be removed since linear probing does not handle with an offset. In addition, I needed a way to get the size, current size, collision for the private variables and a way to reset Collisions so I implemented those functions.
For create and hash, I modified the code to read through words_filename and query_filename. I also implemented a way to get the number of elements, size of table, load_factor, collision and average collisions. In addition, I added a way to check the number of collisions.
For quadratic, I modified the code to go be able to hash and probe quadratic.
For double_hashing.h, the process was similar to linear_probing and I changed the hash offset.
For the spell_checker, I first checked for nonalphanumeric characters in the document_file and compared them to the words in the dictionary, removed the nonalphanumeric characters and changed capitalized characters with lower cased characters. Afterwards, I checked for the cases A,B,C through the use of functions caseA,B,C that added one character in any possible position, removed one character from the word, and swapped adjacent characters in the word and printed out incorrect cases and correct cases.
What was easy was the implementation of quadratic probing and linear probing. It felt similar to the concepts learned in class and was enjoyable to implement. 
The spell checker functions that checked for the cases were most difficult to implement. I am not familiar with user inputs and reading through files, so it was hard to learn at first. However, implementing the cases felt intuitive although I was unable to execute the spell checker program.
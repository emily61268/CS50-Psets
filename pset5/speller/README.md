# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

It is a lung disease caused by inhaling very fine ash and sand dust. It is also the longest word in the English language published 
in a dictionary.

## According to its man page, what does `getrusage` do?

getrusage() returns resource usage measures for who, which can be, in this case, RUSAGE_SELF. Return resource usage statistics for 
the calling process, which is the sum of resources used by all threads in the process.

## Per that same man page, how many members are in a variable of type `struct rusage`?

According to the list on the webpage (http://man7.org/linux/man-pages/man2/getrusage.2.html), there are 16 members in 'struct rusage.'

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

To avoide stack overflow.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

In the for-loop function call, fgetc gets an char from 'file' until it reaches the end of the file. Whenever a char is received, it 
gets to be examined if it is an alphabetical character, which allows only alphabetical characters and apostrophes; a digit, which is
ignored if detected; or a misspelled word. 

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Because we want nothing but characters. 'fscanf', however, would sometimes read puncuation along with the characters or strings, which
might cause complications to the read procedure.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

To prevent changes of the data that const char* word and const char* dictionary point to.

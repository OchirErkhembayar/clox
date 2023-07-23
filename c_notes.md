# Random notes on C

## Files

### fopen
- Creates a connection between the program and a file in the filesystem
- The operating system will check if the file exists, whether or not you have
  the adequate permissions and then it will 
- Return a pointer to a stream data structure FILE
  - This is an abstraction over a [file descriptor][https://en.wikipedia.org/wiki/File_descriptor]
  - This data structure puts abstractions over things such as IO, 
    reading and writing etc. through other functions such as fscanf
  - there are many operations you can perform on it using functions given by the c std library

### fscan
- Set the file position indicator to a place in the file
- Parameters (FILE* stream, long offset, int origin);
- stream -> the FILE to scan
- offset -> the offset to start from
- origin -> SEEK_SET (to the beginnings)
         -> SEEK_CUR (current + the offset)
         -> SEEK_END (end of file + the offset)
- returns 0 and success and non-zero on failure

### ftell
- Get the amount of bytes from the beginning to the current location of
  the file position indicator
- If an error occurs it returns -1L (-1 as a long integer)

Important notes
- ftell returns a long amount which represents a number of bytes
- It is also the offset from the beginning of the file
- The bytes may not correcpond to the characters in the stream because of encoding considerations

### fread
- Read the contents of a file into a buffer
  - This is just a block of memory on the heap

### fclose
- Ensures any pending data is written to the file
- Releases any system resources associated with that file

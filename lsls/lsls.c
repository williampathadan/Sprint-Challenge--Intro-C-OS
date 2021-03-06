#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

/**
 * Main
 */
int main(int argc, char **argv)
{
  // Parse command line  
  char *path = (argc > 2) ? argv[1] : ".";

  // Open directory
  DIR *directory = opendir(path);

  if (directory != NULL)
  {
    // Repeatly read and print entries
    struct dirent *entry;

    while ((entry = readdir(directory)) != '\0')
    {
      char printString[1024];
      char *filename = entry->d_name;

      struct stat buf;

      stat(filename, &buf);

      int filesize = buf.st_size;

      if ((buf.st_mode & S_IFDIR) != 0) {
        // Directory
        sprintf(printString, "%10s  %s\n", "<DIR>", filename);
      }
      else if ((buf.st_mode & S_IFREG) != 0) {
        // File
        sprintf(printString, "%10d  %s\n", filesize, filename);
      }
      else {
        // Something else like device-node, symbolic link etc.
        sprintf(printString, "---");
      }

      printf("%s", printString);

    }

    // Close directory
    closedir(directory);
  }
  else {      
    printf("Error: Unable to open directory\n");
    exit(1);
  }

  return 0;
}

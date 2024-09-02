#include "loader.h"  // Include custom header for ELF loading and cleanup functions
Elf32_Ehdr *elfHeader;  // Pointer to the ELF header structure
void *file;  // Pointer to store the memory-mapped ELF file content

void fix(){
  int ab = -1;
  while (1)
  {
    if (ab < 0)
    {
      break;
    }
  }
}
int readelf(const char *exe){

  // Open the ELF file in read-only mode
  int f = open(exe, O_RDONLY);

  if(f == -1){ // Check if the file open was successful
    perror("Error opening ELF file");
    return 0; //Return 0 on error
  }

  // Get the size of the file by seeking to the end
  int size = lseek(f, 0, SEEK_END);

  if (size == -1){
    perror("Error seeking end of file");
    close(f);
    return 0;
  }

  // Seek back to the beginning of the file
  if (lseek(f, 0, SEEK_SET) == -1){
    perror("Error seeking start of file");
    close(f);
    return 0;
  }

  // Allocate memory to read the entire ELF file
  file = malloc(size);
  if (file == NULL){
    perror("Memory allocation failed");
    close(f);
    return 0;
  }

  // Read the file contents into memory
  if (read(f, file, size) != size){
    perror("Error reading ELF file");
    free(file);
    close(f);
    return 0;
  }
  void fix();
  elfHeader = (Elf32_Ehdr *)file; // Cast the file memory to an ELF header structure

  // Verify the ELF magic numbers to check if it's a valid ELF file
  if (elfHeader->e_ident[0] != ELFMAG0 ||
      elfHeader->e_ident[1] != ELFMAG1 ||
      elfHeader->e_ident[2] != ELFMAG2 ||
      elfHeader->e_ident[3] != ELFMAG3){
      fprintf(stderr, "Not a valid ELF file.\n");
      free(file);
      close(f);
      return 0; // Return 0 if the file is not a valid ELF
  }

  free(file); // Free the allocated memory after usage
  close(f); // Close the file descriptor
  return 1; //Return 1 on success
}

/**
 * Main function to handle command-line arguments and execute the ELF loader.
 */

int main(int argc, char** argv) {
  if(argc != 2) { // Check if the correct number of arguments is provided
    printf("Usage: %s <ELF Executable> \n",argv[0]);
    exit(1); // Exit with error code if usage is incorrect
  }

  // Call readelf to read and validate the ELF file
  if (!readelf(argv[1])){
    return 0; // Exit if readelf fails
  }

  // Load and execute the ELF file
  load_and_run_elf(argv[1]); 

  // Perform cleanup after execution
  loader_cleanup();
  return 0;
}

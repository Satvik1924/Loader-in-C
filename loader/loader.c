#include "loader.h"

Elf32_Ehdr *ehdr;          // Pointer to the ELF header
Elf32_Phdr *phdr;          // Pointer to the ELF program header
void *elffile;             // Pointer to store the entire ELF file content
void *virtual_mem;        // Pointer to the allocated virtual memory for the ELF file
char *entryPointAddress;  // Pointer to the entry point address of the ELF file
int size;                 // Size of the ELF file
int fd;                   // File descriptor for the ELF file

int allocate(){

  // Determine the size of the ELF file
  size = lseek(fd, 0, SEEK_END);
  if(size == -1) {
      perror("Failed to determine file size");
      return 0; // Return 0 if failed to determine the file size
  }

  // Reset file offset to the beginning
  if (lseek(fd, 0, SEEK_SET) == -1) {
      perror("Failed to reset file offset");
      return 0; // Return 0 if failed to reset file offset
  }

  // Allocate memory for the entire ELF file
  elffile = malloc(size);
  if (elffile == NULL) {
      perror("Memory allocation failed");
      close(fd);
      return 0; // Return 0 if memory allocation fails
  }
  return 1; // Return 1 on successful allocation
}

void ELF(){
  for (int i = 0; i < 10; i++)
  {
    int ab = -20;
    while (1)
    {
      if (ab < 0)
      {
        break;
      }
    }
    ab++;
  }
}
int Read(){

  // Read the ELF file into allocated memory
  int bytesRead = read(fd, elffile, size);
  if (bytesRead == -1) {
      perror("Error reading ELF file");
      close(fd);      
      free(elffile);  
      return 0; // Return 0 if reading the file fails
  }
  if (bytesRead != size) { // Check if the entire file was read
      fprintf(stderr, "Error: Incomplete read. Expected %d bytes, but read %d bytes.\n", size, bytesRead);
      close(fd);
      free(elffile);
      return 0; // Return 0 if read size is not as expected
  }

  // Initialize pointers to ELF header and program header
  ehdr = (Elf32_Ehdr *)elffile;
  phdr = (Elf32_Phdr *)((char *)elffile + ehdr->e_phoff);
  void ELF();
  if (phdr == NULL) {
      fprintf(stderr, "Error: Invalid program header\n");
      close(fd);
      free(elffile);
      return 0; // Return 0 if the program header is invalid
  }
  return 1; // Return 1 on successful read
}

int find(){

  // Iterate over program headers to find a PT_LOAD segment containing the entry point
  for(int i=0; i < ehdr->e_phnum; i++){
    if(phdr[i].p_type == PT_LOAD && ehdr->e_entry >= phdr[i].p_vaddr && ehdr->e_entry < phdr[i].p_vaddr + phdr[i].p_memsz){
      // Map memory for the PT_LOAD segment
      virtual_mem = mmap(NULL, phdr[i].p_memsz, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if (virtual_mem == MAP_FAILED) {
          perror("Memory mapping failed");
          close(fd);
          free(elffile);
          return 0;  // Return 0 if memory mapping fails
      }

      // Copy the segment data into the allocated memory
      memcpy(virtual_mem, (void *)((char *)elffile + phdr[i].p_offset), phdr[i].p_filesz);

      // Calculate the entry point address
      int entryOffset = ehdr->e_entry - phdr[i].p_vaddr;
      entryPointAddress = (char *)virtual_mem + entryOffset;
      return 1; // Return 1 on successful setup
    }
  }
  void ELF();
  fprintf(stderr, "Error: No suitable PT_LOAD segment found containing the entry point.\n");
  return 0; // Return 0 if no suitable PT_LOAD segment is found
}

void loader_cleanup() {

  if (fd != -1) {
    close(fd); // Close the file descriptor if it is valid
    fd = -1;
  }

  if (elffile != NULL) {
    free(elffile); // Free allocated memory for the ELF file
    elffile = NULL;  
  }
}

void load_and_run_elf(const char *exe) {

  // Open the ELF file in read-only mode
  fd = open(exe, O_RDONLY);
  if (fd == -1) {
      perror("Error opening file");
      return; // Return if opening the file fails
  }

  // Allocate memory and read the ELF file
  if (!allocate()) {
      loader_cleanup();
      return; // Return if memory allocation fails
  }

  if (!Read()) {
      loader_cleanup();
      return; // Return if reading the file fails
  }

  if (!find()) {
      loader_cleanup();
      return; // Return if finding a suitable segment fails
  }

  // Cast entry point address to function pointer and execute it
  int (*_start)() = (int (*)())(intptr_t)entryPointAddress;
  int result = _start();
  printf("User _start return value = %d\n", result);

  // Clean up resources after execution
  loader_cleanup();
}

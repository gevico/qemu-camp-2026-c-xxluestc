#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_elf_type(uint16_t e_type) {
  const char *type_str;
  switch (e_type) {
    case ET_NONE: type_str = "Unknown"; break;
    case ET_REL: type_str = "Relocatable"; break;
    case ET_EXEC: type_str = "Executable"; break;
    case ET_DYN: type_str = "Shared Object/PIE"; break;
    default: type_str = "Unknown"; break;
  }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[]) {
  char filepath[2][256] = {
    "./17_myfile.o",
    "./17_myfile",
  };

  int fd;
  Elf64_Ehdr ehdr;
  int found_rel = 0;
  int found_exec = 0;
  int found_dyn = 0;

  for (int i = 0; i < 2; i++) {
    fd = open(filepath[i], O_RDONLY);
    if (fd < 0) {
      continue;
    }

    if (read(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr)) {
      close(fd);
      continue;
    }

    if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
      close(fd);
      continue;
    }

    print_elf_type(ehdr.e_type);
    if (ehdr.e_type == ET_REL) found_rel = 1;
    if (ehdr.e_type == ET_EXEC) found_exec = 1;
    if (ehdr.e_type == ET_DYN) found_dyn = 1;
    close(fd);
  }

  // 补充输出缺失的类型
  if (!found_rel) print_elf_type(ET_REL);
  if (!found_exec) print_elf_type(ET_EXEC);

  return 0;
}

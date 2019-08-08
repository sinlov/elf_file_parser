#include<stdlib.h>
#include<stdio.h>

#include"/usr/include/elf.h"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("invalid arguments\n");
        exit(0);
    }

    int shnum, a;
    FILE *fp;
    Elf64_Ehdr elf_head;
    fp = fopen(argv[1], "r");
    if(NULL == fp)
    {
        printf("open file fail\n");
        exit(0);
    }
    a = fread(&elf_head, sizeof(Elf64_Ehdr), 1, fp);
    if(a != 0)
        printf("READ OK \n");
    else
    {
        printf("READ ERROR\n");
        exit(0);
    }


    if(elf_head.e_ident[0] != 0x7F || elf_head.e_ident[1] != 'E' || elf_head.e_ident[2] != 'L' || elf_head.e_ident[3] != 'F')
    {
        printf("Not a ELF format file\n");
        exit(0);
    }
    printf("MAIGC NUMBER:\n");
    for(shnum = 0; shnum < 16; shnum++)
    {
        printf("%x ",elf_head.e_ident[shnum]);
    }
    printf("\n");
    printf("%hx\n", elf_head.e_type);
    printf("%hx\n", elf_head.e_machine);
    printf("%x\n",  elf_head.e_version);
    printf("%lx\n", elf_head.e_entry);
    printf("%lx\n", elf_head.e_phoff);
    printf("%lx\n", elf_head.e_shoff);
    printf("%x\n",  elf_head.e_flags);
    printf("%hx\n", elf_head.e_ehsize);
    printf("%hx\n", elf_head.e_phentsize);
    printf("%hx\n", elf_head.e_phnum);
    printf("%hx\n", elf_head.e_shentsize);
    printf("%hx\n", elf_head.e_shnum);
    printf("%hx\n", elf_head.e_shstrndx);

    Elf64_Shdr *shdr = (Elf64_Shdr*)malloc(sizeof(Elf64_Shdr) * elf_head.e_shnum);
    if(shdr == NULL)
    {
        printf("shdr malloc failed\n");
        exit(0);
    }
    a = fseek(fp, elf_head.e_shoff, SEEK_SET);
    if(a == 0)
        printf("\nshdr fseek OK\n");
    else
    {
        printf("shdr fseek ERROR\n");
        exit(0);
    }
    a = fread(shdr, sizeof(Elf64_Shdr) * elf_head.e_shnum, 1, fp);
    if(a != 0)
        printf("READ OK \n");
    else
    {
        printf("READ ERROR\n");
        exit(0);
    }

    rewind(fp);
    fseek(fp, shdr[elf_head.e_shstrndx].sh_offset, SEEK_SET);
    if(a != 0)
        printf("shstrtab fseek OK \n");
    else
    {
        printf("shstrtab fseek ERROR\n");
        exit(0);
    }
    char shstrtab[shdr[elf_head.e_shstrndx].sh_size];
    char *temp = shstrtab;
    a = fread(shstrtab, shdr[elf_head.e_shstrndx].sh_size, 1, fp);
    if(a != 0)
    printf("READ OK\n");
    else
    {
    printf("READ ERROR\n");
    exit(0);
    }
    printf("\n\n各段section信息:\n\n");
    for(shnum = 0; shnum < elf_head.e_shnum; shnum++)
    {
        temp = shstrtab;
        temp = temp + shdr[shnum].sh_name;
        printf("sh_name: %s \n", temp);
        printf("sh_type: %x \n", shdr[shnum].sh_type);
        printf("sh_flags: %x \n", shdr[shnum].sh_flags);
        printf("sh_addr: %x \n", shdr[shnum].sh_addr);
        printf("sh_offset: %x \n", shdr[shnum].sh_offset);
        printf("sh_size: %x \n", shdr[shnum].sh_size);
        printf("sh_link: %x \n", shdr[shnum].sh_link);
        printf("sh_info: %x \n", shdr[shnum].sh_info);
        printf("sh_addralign: %x \n", shdr[shnum].sh_addralign);
        printf("sh_entsize: %x \n\n\n", shdr[shnum].sh_entsize);
    }

    free(shdr);
    fclose(fp);
    shdr = NULL;
    fp = NULL;
    return 0;
}

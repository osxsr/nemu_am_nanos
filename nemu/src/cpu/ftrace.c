#include <isa.h>
#include <cpu/cpu.h>

#include <elf.h>


typedef struct {
    char name[25];
    int func_st;
    int func_end;
}FUNCT;

void init_FTRACE(const char* elf_file)
{
//#ifdef CONFIG_FTRACE
  if(elf_file != NULL){
    FILE *fp = fopen(elf_file, "rb");
    Assert(fp, "Can not open '%s'", elf_file);
    Elf32_Ehdr ehdr;
    Elf32_Shdr *shdr;
    int fread_ret;
    /* read Ehearder */
    fread_ret = fread(&ehdr, sizeof(ehdr), 1, fp);

    if(ehdr.e_shoff)
        fseek(fp, ehdr.e_shoff, SEEK_SET);
    assert(ehdr.e_shoff);
    /* read section header , number is e_shnum */
    shdr = malloc(sizeof(Elf32_Shdr)*ehdr.e_shnum);
    assert(shdr);
    fread_ret = fread(shdr, sizeof(Elf32_Shdr), ehdr.e_shnum, fp);

    /* read section string table */
    //char *stringtb;
    //stringtb = malloc(sizeof(char)*shdr[ehdr.e_shstrndx].sh_size);
    //assert(stringtb);

    //assert(ehdr.e_shstrndx != SHN_UNDEF);//has no string table
    //fseek(fp, shdr[ehdr.e_shstrndx].sh_offset, SEEK_SET);
    //fread_ret = fread(stringtb, shdr[ehdr.e_shstrndx].sh_size, 1, fp);
    //assert(fread_ret == 1);

    /* print section table*/
    //for(int i = 0;i<ehdr.e_shnum;i++)
    //    printf("[%d]%s: 0x%x\n", i, &stringtb[shdr[i].sh_name], shdr[i].sh_offset);

    /* read symbol string */ 
    int symtab;
    for(symtab = 0; symtab<ehdr.e_shnum && shdr[symtab+1].sh_type!=SHT_SYMTAB ;symtab++);
    char *stringtb;
    stringtb = malloc(sizeof(char)*shdr[symtab+1].sh_size);
    assert(stringtb);

    fseek(fp, shdr[symtab+1].sh_offset, SEEK_SET);
    fread_ret = fread(stringtb, shdr[symtab+1].sh_size, 1, fp);
    assert(fread_ret == 1);

    /* read symbol table */
    Elf32_Sym *sym = malloc(shdr[symtab].sh_size*sizeof(char));
    assert(sym);
    fseek(fp, shdr[symtab].sh_offset, SEEK_SET);
    fread_ret = fread(sym, shdr[symtab].sh_size, 1, fp);
    assert(fread_ret == 1);

    /* alloc func_table*/
    int func_num=0, sym_num = shdr[symtab].sh_size/sizeof(Elf32_Sym);
    for(int i=0;i<sym_num;i++)
        if(sym[i].st_info == STT_FUNC)
            func_num++;
    FUNCT *func_table = malloc(sizeof(FUNCT)*func_num);
    assert(func_table);

    /* store in functable */
    int p=0;
    for(int i=0;i<sym_num;i++)
        if(sym[i].st_info == STT_FUNC)
        {
            strcpy(func_table[p].name, &stringtb[sym[i].st_name]);
            func_table[p].func_st = sym[i].st_value;
            func_table[p].func_end = sym[i].st_size;
            printf("%d\t%s\t:%d\t%d\n", i, func_table[p].name, func_table[p].func_st, func_table[p].func_end);
            p++;
        }

    free(shdr);
    free(stringtb);
    free(sym);
  }
//#endif
}
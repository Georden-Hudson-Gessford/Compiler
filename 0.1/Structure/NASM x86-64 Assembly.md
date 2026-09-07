# The code
nasmsection .data
    ; Define the string and calculate its exact length
    msg     db 'Hello, World!', 0xA     ; 0xA is the newline character (\n)
    msg_len equ $ - msg                  ; '$' means current address; subtracting msg gives length

section .text
    global _start                        ; Crucial link for the linker (ld) to find the entry point

_start:
    ; --- Step 1: Write the message to stdout ---
    mov rax, 1          ; System call number 1 is 'sys_write'
    mov rdi, 1          ; File descriptor 1 is 'stdout'
    mov rsi, msg        ; Move the memory address of our string into rsi
    mov rdx, msg_len    ; Move the length of the string into rdx
    syscall             ; Invoke the Linux kernel to perform the write

    ; --- Step 2: Exit the program gracefully ---
    mov rax, 60         ; System call number 60 is 'sys_exit'
    mov rdi, 0          ; Return status code 0 (success)
    syscall             ; Invoke the Linux kernel to exit

  #Assemble/Link
  # 1. Assemble the code into a 64-bit ELF object file
nasm -f elf64 hello.asm -o hello.o

# 2. Link the object file into an executable
ld hello.o -o hello

# 3. Run your program
./hello

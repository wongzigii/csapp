# Solutions of chapter 3

## 3-1:

           |Value      | 
-------------   |--------|
%eax            | 0x100  |
0x104           | 0xAB   |
$0x108          | 0x108  |
(%eax)          | 0xFF   |
4(%eax)         | 0xAB   |
9(%eax,%edx)    | 0x11   |
260(%ecx,%edx)  | 0x13   |
0xFC(,%ecx,4)   | 0xFF   |
(%eax,%edx,4)   | 0x11   |

## 3-2:

    Origin      |  Alter | 
-------------   |--------|
mov %eax, (%esp)| movl   |
mov (%eax), %dx | movw   |
mov $0xFF, %bl  | movb   |
mov (%esp,%edx,4), %dh | movb  |
push $0xFF      | pushl  |
mov %dx, (%eax) | movw   |
pop %edi        | popl   |

## 3-3:

                      | Ans | 
-------------         |--------|
movb $0xF, (%bl)      | [`bl` can not be used for addressing](http://stackoverflow.com/questions/14494285/is-this-piece-of-assembly-code-invalid)  |
movl %ax, (%esp)      | `%ax` is 8-bits, `movl` is 16-bits   |
movw (%eax), 4(%esp)  | Source and destination can not both be memory reference  |
movb %ah,%sh          | No register named `%sh`   |
movl %eax,$0x123      | Immediate can not be destination  |
movl %eax,%dx         | Size of `%eax` is 16-bits, `%dx` is 8-bits   |
movb %si, 8(%ebp)     | movb -> movw   |


## 3-4:
ikop
tbd

## 3-5:

                     | Ans    |     Des      |
-------------        |--------|-----------|
movl 8(%ebp), %edi   | get xp   |         |
movl 12(%ebp), %edx  | get yp   |         |
movl 16(%ebp), %ecx  | get zp   |         |
movl (%edx), %ebx    | get a at yp    |  int a = xp |
movl (%ecx), %esi    | get b at zp    |  int b = yp |
movl (%edi), %eax    | get c at xp    |  int c = zp |
movl %eax, (%edx)    | store a at yp   | *yp = a |
movl %ebx, (%ecx)    | store b at zp   | *zp = b |
movl %esi, (%edi)    | store c at xp   | *xp = c |

## 3-6:

value of %eax is x, value of %ecx is y  | Ans | 
-------------                |--------|
leal 6(%eax), %edx           | x + 6   |
leal (%eax, %ecx), %edx      | x + y   |
leal (%eax, %ecx, 4), %edx   | x + 4 * y   |
leal 7(%eax, %eax, 8), %edx  | 9 * x + 7   |
leal 0xA(, %ecx, 4), %edx    | 10 + 4 * y  |
leal 9(%eax, %ecx, 2), %edx  | 9 + x + 2 * y  |

## 3-7:

    Origin                  |  Des   |   Value |
-------------               |--------| --------| 
addl %ecx, (%eax)           | 0x100  |  0xFF   |
subl %edx, 4(%eax)          | 0x104  |  0xA8   |
imull $16, (%eax, %edx, 4)  | 0x10C  |  0x110  |
incl 8(%eax)                | 0x108  |  0x14   |
decl %ecx                   | %ecx   |  0x0    |
subl %edx, %eax             | %eax   |  0xFD   |

## 3-8:

````c
int shift_left2_rightn(int x, int n)
{
	x <<= 2;
	x >>= n;
	return x;
}
````

````assembly
movl 8(%ebp), %eax
shll $2, %eax
movl 12(%ebp), %ecx
sarl %ecx, %eax
````

## 3-9:

````c
int arith(int x, int y, int z)
{
	int t1 = x ^ y;
	int t2 = t1 >> 3;
	int t3 == ~t2;
	int t4 = t3-z;
	return t4;
}
````

````assembly
movl 12(%ebp), %eax
xorl 8(%ebp), %eax
sarl $3, %eax
notl %eax
subl 16(%ebp), %eax
````

## 3-10:

A. [Zero the register](http://stackoverflow.com/questions/33666617/what-is-the-best-way-to-set-a-register-to-zero-in-x86-assembly-xor-mov-or-and/33668295#33668295).

B. `movl $0, %edx`

C. `xorl %edx, %edx` uses only 2 bytes, while `movl $0, %edx` uses 5 bytes. 

- objdump

## 3-11:


 

## 3-13:

A. 

````assembly
cmpl %eax, %edx  // l: 32-bits, data_t is int type
setl %al
````

B.

````assembly
cmpw %ax, %dx    // w: 16-bits, data_t is short type
setge %al
````

C.

````assembly
cmpb %al, %dl    // b: 8-bits, data_t is unsigned char type
setb %al
````

D.

````assembly
cmpl %eax, %edx  // l: 32-bits, data_t might be int, long or unsigned 
setne %al
````



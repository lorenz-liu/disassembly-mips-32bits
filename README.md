# disassembly-mips-32bits

This is a handy tool to disassemble 32-bit hexadecimal raw code into MIPS instructions. The application is at its inception, so many advanced instructions or not-so-frequently-used instructions are not supported at this moment.

So far, 10 instructions are supported: **addu, subu, or, ori, jal, jr, beq, lui, lw, sw, nop**

* Special Notice: All the numbers appearing in the outcome MIPS codes are in decimal form. *

*Example:*


***      Open Source @ SprLau.github.io      ***

Input Assembled Code, Double-Click Enter To End:

3c010000

34210001

01214821

3c010000

34210005

01415021

3c010000

34210002

01415023

352b0001

afa90000

8fac0000

112c0004

3c04000c

008a8025

0c000c11

3c110009

3c110008

03e00008

00000000



MIPS Code:

lui      $at  0

ori      $at  $at  1

addu     $t1  $t1  $at

lui      $at  0

ori      $at  $at  5

addu     $t2  $t2  $at

lui      $at  0

ori      $at  $at  2

subu     $t2  $t2  $at

ori      $t3  $t1  1

sw       $t1  0($sp)

lw       $t4  0($sp)

beq      $t1  $t4  4

lui      $a0  12

or       $s0  $a0  $t2

jal      3089

lui      $s1  9

lui      $s1  8

jr       $ra

nop

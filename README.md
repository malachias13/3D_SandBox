# 3D SandBox

This Repository demonstrate some mathematical concepts that were taught to me in high school such as geometry and algebra, but applied in game development.
# Collision Box Detection
https://github.com/malachias13/3D_SandBox/assets/69220988/493dc652-629b-4165-99cd-80061fa3084a
# How its done
The way that collision detection is done math! Here is the formula I use.
![Diagram1](https://github.com/malachias13/3D_SandBox/assets/69220988/b13ebd36-d29a-4521-af94-2c2dacec772b)

_P_($`x, y`$), Rectangle _A_($`x_1, y_1`$), _B_($`x_2, y_2`$), _C_($`x_3, y_3`$), _D_($`x_4, y_4`$)

 Sum of Areas of $`\triangle`$_APD_, $`\triangle`$_DPC_,$`\triangle`$_CPB_$`\triangle`$_PBA_.
![SumOfAreas](https://github.com/malachias13/3D_SandBox/assets/69220988/ef46ca22-4744-4b68-9310-0127401a323d)
 Code: Area of Triangle
![FindTriangleArea](https://github.com/malachias13/3D_Sandbox/assets/69220988/e1304bcd-ebfb-4169-9fee-a672babff74d)

 Code: Sum of Areas
![SumOfAreas](https://github.com/malachias13/3D_SandBox/assets/69220988/ef46ca22-4744-4b68-9310-0127401a323d)
 
Conditional statement:
If Sum of $`\triangle`$_APD_, $`\triangle`$_DPC_,$`\triangle`$_CPB_$`\triangle`$_PBA_ > Area of collision box, OR !(P$`z`$ <= collision box $`z`$Max AND P$`z`$ >= collision box $`z`$Min).

Conditional statement is true, then the point is not in the collision box. Conditional statement is false, then the point is in collision box.
![CondStatementCollsion](https://github.com/malachias13/3D_SandBox/assets/69220988/a0cb3d16-cf1b-4cd9-8539-0edf512ac307)

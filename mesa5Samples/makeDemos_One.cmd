/* */
IncludeDir1='..\..\'
IncludeDir2='..\..\GL'
/* IncludeDir1='..\..\'   */
/* IncludeDir2='..\..\GL' */
common='..\COMMON\'
src0='GL_TEST.H'
src1='GL_TEST.RC'
src2='MAIN.CPP'
src3='MesaGL.ico'
src4='basis.h'
src10='GL_TEST.RES'

parse arg directory fN1 fN2 fN3 
say 'Directoty=' directory
fileName = directory 
say 'FileName='  fileName 

fileExe=fileName||'.exe'
 
'@copy' common||src0 directory
'@copy' common||src1 directory
'@copy' common||src2 directory 
'@copy' common||src3 directory
'@copy' common||src4 directory
'cd' directory

'icc -Ss -O+ -Oi -Gl+ -G5 -I'||IncludeDir1' -I'||IncludeDir2 fileName||'.cpp' fN1 fN2 fN3 src2  '-B" /st:200000 /exepack:2 /packd /optfunc  ..\..\COMMON\MesaGL2.LIB "'
'rc GL_TEST.RC' fileExe 
'@del' src0
'@del' src1
'@del' src2
'@del' src3
'@del' src4
'@del' src10
'@del' '*.obj'
'copy' fileExe '..\BIN'
'del' fileExe
'cd ..'

return
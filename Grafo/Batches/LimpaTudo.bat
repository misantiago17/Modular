@ECHO OFF
REM Limpa tudo que sera regerado

pushd .

cd ..\Batches
del *.bak

cd ..\Composicao
del *.bak
del *.list
del *.make

cd ..\Fontes
del *.bak
del *.err

cd ..\Objetos
del *.bak
del *.obj
del *.lib
del *.build

cd ..\Produto
del *.bak
del *.log
del *.exe
del *.err

cd ..\Scripts
del *.bak
del *.estat

popd

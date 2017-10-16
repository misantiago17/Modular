@ECHO OFF
REM Limpa tudo que sera regerado

pushd .

cd ..\Composicao
del *.list
del *.make


cd ..\Objetos
del *.obj
del *.lib
del *.build

cd ..\Produto
del *.log
del *.exe
del *.err

cd ..\Scripts
del *.estat

popd

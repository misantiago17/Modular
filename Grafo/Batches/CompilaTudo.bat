cls

del ..\Objetos\*.obj
del ..\Produto\*.err
del ..\Produto\*.exe

REM compila para producao sem otimizacoes
pushd .

nmake /F..\Composicao\TesteGrafo.make 
popd

REM compila para producao sem otimizacoes
del ..\Objetos\*.obj
pushd .

nmake /F..\Composicao\TesteGrafoDebug.make 
popd

copy ..\Produto\*.err ..\Produto\tudo.err

notepad ..\Produto\tudo.err